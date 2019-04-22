PREFIX	     = /usr/libexec
PROGRAM	     = nomadbsd-install-gui
PATH_BACKEND = $${PREFIX}/nomadbsd-install
APPSDIR	     = /usr/local/share/applications
TARGET	     = $${PROGRAM}
TEMPLATE     = app
INSTALLS     = target desktopfile
RESOURCES    = resources.qrc
TRANSLATIONS = locale/$${PROGRAM}_de.ts \
               locale/$${PROGRAM}_ru.ts
QT	    += widgets
INCLUDEPATH += . lib
DEFINES	    += PROGRAM=\\\"$${PROGRAM}\\\"
DEFINES	    += PATH_NOMADBSD_INSTALL=\\\"$${PATH_BACKEND}\\\"
QMAKE_EXTRA_TARGETS += cleanqm distclean

HEADERS += src/wizard.h src/backend.h  lib/qt-helper/qt-helper.h
SOURCES += src/main.cpp src/wizard.cpp lib/qt-helper/qt-helper.cpp

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

