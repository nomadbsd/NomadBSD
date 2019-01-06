#!/bin/sh
~/.config/DSB/dsbds.sh&
~/.fehbg&
compton&
tint2&
plank&
(sleep 10; dsbmc -i)&
dsbbatmon&
dsbmixer -i&
redshift -l$(getlalo)&
xbindkeys&
