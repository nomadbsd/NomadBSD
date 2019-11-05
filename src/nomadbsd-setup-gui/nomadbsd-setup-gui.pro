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
               locale/$${PROGRAM}_ru.ts \
               locale/$${PROGRAM}_cs.ts
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

files.files          = files/*
files.path           = $${DATA_DIR}
file.CONFIG          = nostrip

QMAKE_EXTRA_TARGETS += cleanqm distclean backend files
INSTALLS            += target backend files

