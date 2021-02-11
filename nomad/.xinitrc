#!/bin/sh

. ~/.xprofile

#FIRSTRUN_START
# Put everything to be run only on the first login here
cat ${HOME}/.config/plank.ini | dconf load /net/launchpad/plank/docks/
sed -i '' '/^#FIRSTRUN_START/,/^#FIRSTRUN_END/d' $0
#FIRSTRUN_END

[ -z "$1" -o "$1" = "default" ] && exec ck-launch-session openbox-session
exec ck-launch-session "$1"

