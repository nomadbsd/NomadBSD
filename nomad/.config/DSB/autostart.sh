#!/bin/sh
pcmanfm --desktop&
lxpanel&
~/.fehbg&
(sleep 10; dsbmc -i)&
(sleep 3; dsbbatmon)&
(sleep 3; dsbmixer -i)&
redshift -l`getlalo`&
xbindkeys&
#[INACTIVE]#compton&
~/.config/DSB/dsbds.sh&
