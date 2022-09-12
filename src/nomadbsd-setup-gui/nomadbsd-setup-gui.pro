PREFIX       = /usr
PROGRAM	     = nomadbsd-setup-gui
BACKEND      = nomadbsd-setup
DATA_DIR     = $${PREFIX}/share/nomadbsd-setup
BACKEND_DIR  = $${PREFIX}/libexec
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

cmd  = sed -E \"s|@POOLNAME@|$${POOLNAME}|; s|@ROOTLABEL@|$${ROOTLABEL}|;
cmd += s|@DATALABEL@|$${DATALABEL}|;
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

