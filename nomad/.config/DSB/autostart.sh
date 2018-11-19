#!/bin/sh
pcmanfm --desktop&
lxpanel&
~/.fehbg&
(sleep 10; dsbmc -i)&
dsbbatmon&
dsbmixer -i&
redshift -l`getlalo`&
xbindkeys&
#[INACTIVE]#compton&
~/.config/DSB/dsbds.sh&
