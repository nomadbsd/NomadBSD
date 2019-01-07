#!/bin/sh
~/.config/DSB/dsbds.sh&
~/.fehbg&
compton&
tint2&
plank&
(sleep 10; dsbmc -i)&
(sleep 13; dsbbatmon)&
(sleep 16; dsbmixer -i)&
redshift -l$(getlalo)&
xbindkeys&
