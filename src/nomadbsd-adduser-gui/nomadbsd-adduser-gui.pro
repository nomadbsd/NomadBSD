PREFIX	     = /usr
PROGRAM	     = nomadbsd-adduser-gui
BACKEND      = nomadbsd-adduser
BACKEND_DIR  = $${PREFIX}/libexec
PATH_BACKEND = $${BACKEND_DIR}/$${BACKEND}
APPSDIR      = $${PREFIX}/share/applications
TARGET	     = $${PROGRAM}
TEMPLATE     = app
RESOURCES    = resources.qrc
TRANSLATIONS = locale/$${PROGRAM}_de.ts \
               locale/$${PROGRAM}_fr.ts \
               locale/$${PROGRAM}_ru.ts \
               locale/$${PROGRAM}_id.ts \
               locale/$${PROGRAM}_es.ts
QT	    += widgets
INCLUDEPATH += .
DEFINES	    += PROGRAM=\\\"$${PROGRAM}\\\"
DEFINES	    += PATH_NOMADBSD_ADDUSER=\\\"$${PATH_BACKEND}\\\"
HEADERS     += src/wizard.h src/password.h src/backend.h
SOURCES     += src/main.cpp src/wizard.cpp src/password.cpp

qtPrepareTool(LRELEASE, lrelease)
for(a, TRANSLATIONS) {
	cmd = $$LRELEASE $${a}
	system($$cmd)
}

cleanqm.commands  = rm -f locale/*.qm
distclean.depends = cleanqm

target.files      = $${PROGRAM}
target.path       = $${PREFIX}/bin

backend.path      = $${BACKEND_DIR}
backend.files     = $${BACKEND}
backend.CONFIG    = nostrip

desktopfile.path  = $${APPSDIR}
desktopfile.files = $${PROGRAM}.desktop

INSTALLS = target backend desktopfile
QMAKE_EXTRA_TARGETS += cleanqm distclean
