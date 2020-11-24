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
sudo -E networkmgr&
redshift -l$(getlalo)&
dunst&
brightness_listener&
daemon -f update_obmenu -a -p 5&
~/.config/DSB/dsbxinput.sh&
