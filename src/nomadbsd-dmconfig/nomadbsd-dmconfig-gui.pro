PREFIX		= /usr
PROGRAM		= nomadbsd-dmconfig-gui
PATH_THEME_DIR	= /usr/local/share/slim/themes
PATH_BACKEND	= $${PREFIX}/libexec/nomadbsd-dmconfig
APPSDIR		= /usr/local/share/applications
TARGET		= $${PROGRAM}
QMAKE_STRIP	= echo
TEMPLATE	= app
INSTALLS	= target desktopfile backend
RESOURCES	= resources.qrc
TRANSLATIONS	= locale/$${PROGRAM}_de.ts
QT		+= widgets
INCLUDEPATH	+= . lib
DEFINES		+= PROGRAM=\\\"$${PROGRAM}\\\"
DEFINES		+= PATH_BACKEND=\\\"$${PATH_BACKEND}\\\"
DEFINES		+= PATH_THEME_DIR=\\\"$${PATH_THEME_DIR}\\\"
QMAKE_EXTRA_TARGETS += cleanqm distclean

HEADERS += src/mainwin.h lib/qt-helper/qt-helper.h
SOURCES += src/main.cpp src/mainwin.cpp lib/qt-helper/qt-helper.cpp

qtPrepareTool(LRELEASE, lrelease)
for(a, TRANSLATIONS) {
	cmd = $$LRELEASE $${a}
	system($$cmd)
}

cleanqm.commands  = rm -f locale/*.qm
distclean.depends = cleanqm

target.files      = $${PROGRAM}
target.path       = $${PREFIX}/bin
target.extra	  = strip $${PROGRAM}

backend.files	  = nomadbsd-dmconfig
backend.path	  = $${PREFIX}/libexec

desktopfile.path  = $${APPSDIR}
desktopfile.files = $${PROGRAM}.desktop

