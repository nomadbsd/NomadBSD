#!/bin/sh
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/games:/usr/local/sbin:/usr/local/bin:/home/nomad/bin

export QT_QPA_PLATFORMTHEME=gtk2

uid=$(id -u)

#
# Check if ~/.cache is a symbolic link to a directory owned by the user.
# If the link's target is not a directory or does not exist, create a
# directory owned by the user under /tmp, and make ~/.cache a symbolic
# link to it.
#
if [ -L ~/.cache ]; then
	if [ -d ~/.cache ]; then
		ownerid=$(stat -f %u ~/.cache)
		if [ "${ownerid}" != "${uid}" ]; then
			recreate_cache=1
		fi
	else
		recreate_cache=1
	fi
	if [ "${recreate_cache}" = "1" ]; then
		user=$(whoami)
		unlink -f ~/.cache
		cachedir=$(mktemp -d /tmp/${user}.XXXXXX)
		ln -s ${cachedir} ~/.cache
	fi
fi

#FIRSTRUN_START
# Put everything to be run only on the first login here
cat ${HOME}/.config/plank.ini | dconf load /net/launchpad/plank/docks/
sed -i '' '/^#FIRSTRUN_START/,/^#FIRSTRUN_END/d' $0
#FIRSTRUN_END

#
# Kill dbus services from a previous session in order to prevent hangs.
#
for s in 15 9; do
	for p in dbus-launch gvfsd-fuse; do
		pgrep -U ${uid} -q $p && pkill -$s $p
	done
done

sh ~/.config/DSB/autostart.sh
############################################################################
# Uncomment one of the following lines depending on the DE/WM you intend to
# start:
#

# Xfce
# . /usr/local/etc/xdg/xfce4/xinitrc

# GNOME
# exec /usr/local/bin/gnome-session

# MATE
# exec ck-launch-session dbus-launch --exit-with-session mate-session

# KDE
# exec ck-launch-session startkde
#
###########################################################################

exec ck-launch-session dbus-launch --exit-with-session openbox-session

