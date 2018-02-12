#!/bin/sh
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/games:/usr/local/sbin:/usr/local/bin:/home/nomad/bin

export QT_QPA_PLATFORMTHEME=qt5ct

if [ ! -f ~/.no_obmenu_init ]; then
	~/bin/update_obmenu -u
	touch ~/.no_obmenu_init
fi
exec openbox-session

