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
               locale/$${PROGRAM}_fr.ts \
               locale/$${PROGRAM}_ru.ts \
               locale/$${PROGRAM}_cs.ts \
               locale/$${PROGRAM}_id.ts
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

clean_backend.commands = rm -f $${BACKEND}
cleanqm.commands       = rm -f locale/*.qm

distclean.depends      = cleanqm clean_backend

target.files           = $${PROGRAM}
target.path            = $${PREFIX}/bin

isEmpty(MAC) {
	cmd = sed -E \"s/@EFI_PART_SIZE@/40M/\" $${BACKEND}.in
} else {
	cmd = sed -E \"s/@EFI_PART_SIZE@/200M/\" $${BACKEND}.in
}
system($$cmd > $${BACKEND})
system(chmod a+x $${BACKEND})
backend.files          = $${BACKEND}
backend.path           = $${BACKEND_DIR}
backend.CONFIG         = nostrip

desktopfile.path       = $${APPSDIR}
desktopfile.files      = $${PROGRAM}.desktop

QMAKE_EXTRA_TARGETS   += cleanqm distclean desktopfile backend clean_backend
INSTALLS              += target backend desktopfile

