#PREFIX	     = .
PREFIX	     = /usr/libexec
PROGRAM	     = nomadbsd-adduser-gui
PATH_BACKEND = $${PREFIX}/nomadbsd-adduser
APPSDIR      = /usr/local/share/applications
TARGET	     = $${PROGRAM}
TEMPLATE     = app
INSTALLS     = target desktopfile
RESOURCES    = resources.qrc
TRANSLATIONS = locale/$${PROGRAM}_de.ts
QT	    += widgets
INCLUDEPATH += .
DEFINES	    += PROGRAM=\\\"$${PROGRAM}\\\"
DEFINES	    += PATH_NOMADBSD_ADDUSER=\\\"$${PATH_BACKEND}\\\"
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

desktopfile.path  = $${APPSDIR}
desktopfile.files = $${PROGRAM}.desktop

