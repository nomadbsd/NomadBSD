PREFIX		= /usr
PROGRAM		= nomadbsd-dmconfig-gui
BACKEND         = nomadbsd-dmconfig
BACKEND_DIR     = $${PREFIX}/libexec
PATH_THEME_DIR	= /usr/local/share/slim/themes
PATH_BACKEND	= $${BACKEND_DIR}/$${BACKEND}
APPSDIR		= $${PREFIX}/share/applications
TARGET		= $${PROGRAM}
TEMPLATE	= app
INSTALLS	= target desktopfile backend
RESOURCES	= resources.qrc
TRANSLATIONS	= locale/$${PROGRAM}_de.ts \
                locale/$${PROGRAM}_fr.ts \
                locale/$${PROGRAM}_ru.ts \
		locale/$${PROGRAM}_cs.ts \
                locale/$${PROGRAM}_id.ts

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

backend.files	  = $${BACKEND}
backend.path	  = $${BACKEND_DIR}
backend.CONFIG    = nostrip

desktopfile.path  = $${APPSDIR}
desktopfile.files = $${PROGRAM}.desktop

