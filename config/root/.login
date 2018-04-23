# $FreeBSD: src/share/skel/dot.login,v 1.16 2001/06/25 20:40:02 nik Exp $
#
# .login - csh login script, read by login shell, after `.cshrc' at login.
#
# see also csh(1), environ(7).
#
# vim: set tabstop=4:

if ( "`tty`" =~ "/dev/ttyv0" ) then
	/usr/libexec/nomad/nomad_setup
	set msg="Trying to find and load the correct driver for your"
	set msg="$msg graphics card ..."
	dialog --infobox "$msg" 5 40
	nvidia_setup
	intel_setup
	dialog --infobox "\nStarting Xorg...\n" 5 40
	(service slim onestart; sleep 3; service slim onestart; sleep 3; \
	service slim onestart) >& /dev/null
	lock -np
endif

