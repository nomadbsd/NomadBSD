#!/bin/sh
~/.config/DSB/dsbds.sh&
~/.fehbg&
compton&
tint2&
plank&
dsbmc -i&
dsbbatmon&
dsbmixer -i&
redshift -l$(getlalo)&
dunst&
xbindkeys&
