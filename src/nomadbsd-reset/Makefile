PROGRAM             = nomadbsd-reset
PREFIX             ?= /usr
NOMADROOT          ?= nomadroot
NOMADDATA          ?= nomaddata
BINDIR              = ${PREFIX}/libexec
DATADIR             = ${PREFIX}/share/${PROGRAM}
INSTALL_TARGETS     = ${PROGRAM}
BSD_INSTALL_DATA   ?= install -m 0644
BSD_INSTALL_SCRIPT ?= install -m 555
.if defined(MAC)
SOURCE = ${PROGRAM}.mac
.else
SOURCE = ${PROGRAM}
.endif

install: ${SOURCE}
	${BSD_INSTALL_SCRIPT} ${SOURCE} ${DESTDIR}${BINDIR}/${PROGRAM}
	sed -i '' -e "s|@NOMADROOT@|${NOMADROOT}|;  \
		      s|@NOMADDATA@|${NOMADDATA}|g" \
		${DESTDIR}${BINDIR}/${PROGRAM}

