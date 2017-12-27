# $FreeBSD: src/share/skel/dot.login,v 1.16 2001/06/25 20:40:02 nik Exp $
#
# .login - csh login script, read by login shell, after `.cshrc' at login.
#
# see also csh(1), environ(7).
#
if ( "`tty`" =~ "/dev/ttyv0" ) then
/usr/libexec/nomad/nomad_setup
echo "Starting Xorg. This might take a while ..."
service slim onestart; sleep 3; service slim onestart; sleep 3
service slim onestart
endif

