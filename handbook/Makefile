# Requires textproc/markdown.
SOURCE=	handbook.md
HEADER=	header

all: handbook.html
handbook.html: ${SOURCE} ${HEADER}
	@if ! which -s markdown; then				\
		echo;						\
		echo "Error: Please install textproc/markdown"; \
		exit 1;						\
	fi
	cat ${HEADER} > ${.TARGET}
	markdown < ${SOURCE} >> ${.TARGET}
	echo '</body></html>' >> ${.TARGET}
clean:
	-rm -f handbook.html

