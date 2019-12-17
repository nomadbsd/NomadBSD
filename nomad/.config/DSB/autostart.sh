#!/bin/sh
chkmultihead&
~/.screenlayout/default.sh&
sh -c '~/.config/DSB/dsbds.sh; ~/.fehbg'&
compton&
tint2&
plank&
dsbmc -i&
dsbbatmon&
dsbmixer -i&
redshift -l$(getlalo)&
dunst&
xbindkeys&
daemon -f update_obmenu -a -p 5&
