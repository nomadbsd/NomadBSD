#!/bin/sh
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/games:/usr/local/sbin:/usr/local/bin:/home/nomad/bin

export QT_QPA_PLATFORMTHEME=gtk2
#
# If not set to "unix", gvfs will use bsdisks which fails to unmount volumes
# mounted on directories it does not expect.
#
export GIO_USE_VOLUME_MONITOR=unix

xrdb ~/.Xresources

uid=$(id -u)

#
# Check if ~/.cache is a symbolic link to a directory owned by the user.
# If the link's target is not a directory or does not exist, create a
# directory owned by the user under /tmp, and make ~/.cache a symbolic
# link to it.
#
if [ -L ~/.cache ]; then
	if [ -d ~/.cache ]; then
		ownerid=$(stat -L -f %u ~/.cache)
		if [ "${ownerid}" != "${uid}" ]; then
			recreate_cache=1
		fi
	else
		recreate_cache=1
	fi
	if [ "${recreate_cache}" = "1" ]; then
		user=$(whoami)
		unlink ~/.cache
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
eval $(dbus-launch --sh-syntax)

# Apply screen settings from DSBDisplaySettings
~/.config/DSB/dsbds.sh

# Apply screen settings from ArandR
~/.screenlayout/default.sh

tpquirk
enable_tapping
~/.config/xkbdmap.sh

[ -z "$1" -o "$1" = "default" ] && exec ck-launch-session openbox-session
exec ck-launch-session "$1"

