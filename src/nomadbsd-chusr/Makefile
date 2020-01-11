PROGRAM             = nomadbsd-chusr
PYLUPDATE           = pylupdate5-3.6
PREFIX             ?= /usr
BINDIR              = ${PREFIX}/bin
DATADIR             = ${PREFIX}/share/${PROGRAM}
APPSDIR             = ${PREFIX}/share/applications
INSTALL_TARGETS     = ${PROGRAM} ${PROGRAM}.desktop translate
BSD_INSTALL_DATA   ?= install -m 0644
BSD_INSTALL_SCRIPT ?= install -m 555

all: ${PROGRAM}

${PROGRAM}: ${PROGRAM}.in
	sed -e "s|@LOCALE_PATH@|${DATADIR}|; s|@PROGRAM@|${PROGRAM}|g" \
		${PROGRAM}.in > ${PROGRAM}
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
	${BSD_INSTALL_SCRIPT} ${PROGRAM} ${DESTDIR}${BINDIR}
	if [ ! -d ${DATADIR} ]; then mkdir -p ${DATADIR}; fi
	if [ ! -d ${APPSDIR} ]; then mkdir -p ${APPSDIR}; fi
	${BSD_INSTALL_DATA} ${PROGRAM}.desktop ${APPSDIR}
	for i in locale/*.qm; do \
		${BSD_INSTALL_DATA} $$i ${DATADIR}; done

clean:
	-rm -f ${PROGRAM}
	-rm -f ${PROGRAM}.desktop
	-rm -f locale/*.qm

