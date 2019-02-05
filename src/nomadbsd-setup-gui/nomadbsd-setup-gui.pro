PREFIX	     = /usr/libexec
PROGRAM	     = nomadbsd-setup-gui
PATH_BACKEND = $${PREFIX}/nomadbsd-setup
TARGET	     = $${PROGRAM}
TEMPLATE     = app
INSTALLS     = target
RESOURCES    = resources.qrc
TRANSLATIONS = locale/$${PROGRAM}_de.ts
QT	    += widgets
INCLUDEPATH += .
DEFINES	    += PROGRAM=\\\"$${PROGRAM}\\\"
DEFINES	    += PATH_NOMADBSD_SETUP=\\\"$${PATH_BACKEND}\\\"
QMAKE_EXTRA_TARGETS += cleanqm distclean

HEADERS += src/wizard.h src/password.h src/backend.h
SOURCES += src/main.cpp src/wizard.cpp src/password.cpp

qtPrepareTool(LRELEASE, lrelease)
for(a, TRANSLATIONS) {
	cmd = $$LRELEASE $${a}
	system($$cmd)
}

cleanqm.commands  = rm -f locale/*.qm
distclean.depends = cleanqm

target.files      = $${PROGRAM}
target.path       = $${PREFIX}

