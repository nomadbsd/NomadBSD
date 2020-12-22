PROGRAM             = lbi-gui
PYLUPDATE           = pylupdate5-3.7
PREFIX             ?= /usr/local
BINDIR              = ${DESTDIR}${PREFIX}/bin
DATADIR             = ${DESTDIR}${PREFIX}/share/${PROGRAM}
APPSDIR             = ${DESTDIR}${PREFIX}/share/applications
INSTALL_TARGETS     = ${PROGRAM} ${PROGRAM}.desktop translate
REPO_URL	    = https://github.com/mrclksr/linux-browser-installer
LBI_DIR		    = /tmp/linux-browser-installer
BSD_INSTALL_DATA   ?= install -m 0644
BSD_INSTALL_SCRIPT ?= install -m 555

all: ${PROGRAM} ${MODULE} ${PROGRAM}.desktop

${PROGRAM}: ${PROGRAM}.in
	sed -e "s|@LOCALE_PATH@|${DATADIR}|g; \
		s|@PROGRAM@|${PROGRAM}|g; \
		s|@DATADIR@|${DATADIR}|g; \
		s|@PATH_LBI_DIR@|${LBI_DIR}|g; \
		s|@REPO_URL@|${REPO_URL}|g; \
		s|@PREFIX@|${PREFIX}|g" ${PROGRAM}.in > ${PROGRAM}
	chmod a+x ${PROGRAM}

${PROGRAM}.desktop: ${PROGRAM}.desktop.in
	sed -e "s|@PROGRAM@|${BINDIR}/${PROGRAM}|g" \
		${PROGRAM}.desktop.in > ${PROGRAM}.desktop

lupdate: ${PROGRAM}
	${PYLUPDATE} -noobsolete ${PROGRAM}.pro

translate:
	for i in locale/*.ts; do \
		lrelease $$i -qm $${i%ts}qm; done

install: ${INSTALL_TARGETS}
	${BSD_INSTALL_SCRIPT} ${PROGRAM} ${BINDIR}
	if [ ! -d ${DATADIR} ]; then mkdir -p ${DATADIR}; fi
	if [ ! -d ${APPSDIR} ]; then mkdir -p ${APPSDIR}; fi
	${BSD_INSTALL_DATA} ${PROGRAM}.desktop ${APPSDIR}
	for i in locale/*.qm; do \
		${BSD_INSTALL_DATA} $$i ${DATADIR}; done

clean:
	-rm -f ${PROGRAM}
	-rm -f ${PROGRAM}.desktop
	-rm -f locale/*.qm
	-rm -rf __pycache__
