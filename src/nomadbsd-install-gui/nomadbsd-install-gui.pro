PREFIX	     = /usr
PROGRAM	     = nomadbsd-install-gui
BACKEND      = nomadbsd-install
BACKEND_DIR  = $${PREFIX}/libexec
PATH_BACKEND = $${BACKEND_DIR}/$${BACKEND}
APPSDIR	     = $${PREFIX}/share/applications
TARGET	     = $${PROGRAM}
TEMPLATE     = app
RESOURCES    = resources.qrc
TRANSLATIONS = locale/$${PROGRAM}_de.ts \
               locale/$${PROGRAM}_ru.ts \
               locale/$${PROGRAM}_cs.ts
QT	    += widgets
INCLUDEPATH += . lib
DEFINES	    += PROGRAM=\\\"$${PROGRAM}\\\"
DEFINES	    += PATH_NOMADBSD_INSTALL=\\\"$${PATH_BACKEND}\\\"
HEADERS     += src/wizard.h src/backend.h  lib/qt-helper/qt-helper.h
SOURCES     += src/main.cpp src/wizard.cpp lib/qt-helper/qt-helper.cpp

qtPrepareTool(LRELEASE, lrelease)
for(a, TRANSLATIONS) {
	cmd = $$LRELEASE $${a}
	system($$cmd)
}

cleanqm.commands     = rm -f locale/*.qm

distclean.depends    = cleanqm

target.files         = $${PROGRAM}
target.path          = $${PREFIX}/bin

isEmpty(MAC) {
backend.files        = backend/pc/$${BACKEND}
} else {
backend.files        = backend/mac/$${BACKEND}
}
backend.path         = $${BACKEND_DIR}
backend.CONFIG       = nostrip

desktopfile.path     = $${APPSDIR}
desktopfile.files    = $${PROGRAM}.desktop

QMAKE_EXTRA_TARGETS += cleanqm distclean desktopfile backend
INSTALLS            += target backend desktopfile

