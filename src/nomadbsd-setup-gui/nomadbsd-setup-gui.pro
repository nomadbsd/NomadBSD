PREFIX       = /usr
PROGRAM	     = nomadbsd-setup-gui
BACKEND      = nomadbsd-setup
DATA_DIR     = $${PREFIX}/share/nomadbsd-setup
BACKEND_DIR  = $${PREFIX}/libexec
MAC_MOD      = nomadbsd_setup_mac.pm
PC_MOD       = nomadbsd_setup_pc.pm
ZFS_MOD      = nomadbsd_setup_zfs.pm
PATH_BACKEND = $${BACKEND_DIR}/$${BACKEND}
TARGET	     = $${PROGRAM}
TEMPLATE     = app
RESOURCES    = resources.qrc
TRANSLATIONS = locale/$${PROGRAM}_de.ts \
               locale/$${PROGRAM}_fr.ts \
               locale/$${PROGRAM}_ru.ts \
               locale/$${PROGRAM}_cs.ts \
               locale/$${PROGRAM}_id.ts
QT	    += widgets
INCLUDEPATH += .
DEFINES	    += PROGRAM=\\\"$${PROGRAM}\\\"
DEFINES	    += PATH_NOMADBSD_SETUP=\\\"$${PATH_BACKEND}\\\"
!isEmpty(USE_ZFS) {
DEFINES	    += USE_ZFS=1
}
HEADERS     += src/wizard.h src/password.h src/backend.h
SOURCES     += src/main.cpp src/wizard.cpp src/password.cpp

qtPrepareTool(LRELEASE, lrelease)
for(a, TRANSLATIONS) {
	cmd = $$LRELEASE $${a}
	system($$cmd)
}
isEmpty(POOLNAME) {
	POOLNAME = nomadbsd_zroot
}
isEmpty(ROOTLABEL) {
	ROOTLABEL = nomadroot
}
isEmpty(DATALABEL) {
	DATALABEL = nomaddata
}
isEmpty(ASHIFT) {
	ASHIFT = 12
}
isEmpty(USE_ZFS) {
	FILESYSTEM = UFS
} else {
	FILESYSTEM = ZFS
}

cmd  = sed -E \"s|@POOLNAME@|$${POOLNAME}|; s|@ROOTLABEL@|$${ROOTLABEL}|;
cmd += s|@DATALABEL@|$${DATALABEL}|;
cmd += s|@ROOTLABEL@|$${ROOTLABEL}|;

isEmpty(MAC) {
	!isEmpty(USE_ZFS) {
		backend.files = backend/$${ZFS_MOD}
		cmd += s|@MODULE_ARCH@|zfs|;
	} else {
		backend.files = backend/$${PC_MOD}
		cmd += s|@MODULE_ARCH@|pc|;
	}
} else {
	!isEmpty(USE_ZFS) {
		backend.files = backend/$${ZFS_MOD}
		cmd += s|@MODULE_ARCH@|zfs|;
	} else {
		backend.files = backend/$${MAC_MOD}
		cmd += s|@MODULE_ARCH@|mac|;
	}
}
cmd += s|@FILESYSTEM@|$${FILESYSTEM}|;
cmd += s|@MODULE_PATH@|$${BACKEND_DIR}|;
cmd += s|@ASHIFT@|$${ASHIFT}|\" backend/$${BACKEND}.in

system($$cmd > backend/$${BACKEND})
system(chmod a+x backend/$${BACKEND})

clean_backend.commands = rm -f backend/$${BACKEND}
cleanqm.commands       = rm -f locale/*.qm
distclean.depends      = cleanqm clean_backend

target.files           = $${PROGRAM}
target.path            = $${PREFIX}/bin

backend.files         += backend/$${BACKEND}
backend.path           = $${BACKEND_DIR}
backend.CONFIG         = nostrip

files.files            = files/*
files.path             = $${DATA_DIR}
file.CONFIG            = nostrip

QMAKE_EXTRA_TARGETS   += cleanqm clean_backend distclean backend files
INSTALLS              += target backend files

