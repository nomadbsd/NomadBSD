#!/bin/sh
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/games:/usr/local/sbin:/usr/local/bin:/home/nomad/bin

export QT_QPA_PLATFORMTHEME=gtk2

#
# Kill dbus services from a previous session in order to prevent hangs.
#
uid=$(id| sed -E 's/.*uid=([0-9]+).*/\1/')
for s in 15 9; do
	for p in dbus-launch gvfsd-fuse; do
		pgrep -U ${uid} -q $p && pkill -$s $p
	done
done

cat ${HOME}/.config/plank.ini | dconf load /net/launchpad/plank/docks/
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

