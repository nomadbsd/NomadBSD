#!/bin/sh
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/games:/usr/local/sbin:/usr/local/bin:/home/nomad/bin

export QT_QPA_PLATFORMTHEME=gtk2
cat ${HOME}/.config/plank.ini | dconf load /net/launchpad/plank/docks/
exec ck-launch-session dbus-launch --exit-with-session openbox-session

