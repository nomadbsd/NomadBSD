ARCH=		amd64
RELEASE=	11.1-RELEASE
URL=		ftp://ftp.freebsd.org/pub/FreeBSD/releases
# Media size in GB
MEDIASIZE=	4
# Size of swap partition in MB
SWAPSIZE=	128
FRAGSIZE=	4096
SYSDIR=		${PWD}/sys
DISTDIR=	${PWD}/dists
DISTSITE=	${URL}/${ARCH}/${RELEASE}
DISTS=		base.txz
PKGLIST=	pkg.list
GIT_SITE=	https://github.com/mrclksr
GIT_REPOS=	${GIT_SITE}/DSBDriverd.git
GIT_REPOS+=	${GIT_SITE}/DSBMC.git
GIT_REPOS+=	${GIT_SITE}/DSBMC-Cli.git
GIT_REPOS+=	${GIT_SITE}/DSBMD.git
GIT_REPOS+=	${GIT_SITE}/dsbcfg.git
GIT_REPOS+=	${GIT_SITE}/libdsbmc.git
GIT_REPOS+=	${GIT_SITE}/DSBBatmon.git
GIT_REPO_DIRS=	DSBBatmon DSBDriverd DSBMC DSBMC-Cli DSBMD

KERNELTARGET=	${SYSDIR}/usr/obj/usr/src/sys/NOMADBSD/kernel
PKGDB=		${SYSDIR}/var/db/pkg/local.sqlite
XORG_CONF_D=	${SYSDIR}/usr/local/etc/X11/xorg.conf.d
FONTSDIR=	${SYSDIR}/usr/local/share/fonts
FONTPATHS_FILE=	${XORG_CONF_D}/files.conf
UZIP_IMAGE=	uzip_image
UZIP_MNT=	uzip_mnt

.ifdef BUILDKERNEL
DISTS+=	src.txz
.endif

init: initbase buildkernel instpkgs fontpaths
	(cd nomad  && tar cf - .) | (cd ${SYSDIR}/usr/home/nomad && tar xf -)
	chroot ${SYSDIR} sh -c 'chown -R nomad:nomad /usr/home/nomad'
.ifdef BUILDKERNEL
	(cd kernel && tar cf - .) | \
	    (cd ${SYSDIR}/usr/src/sys/${ARCH}/conf && tar xf -)
.endif

initbase: ${SYSDIR} updatebase
	if ! grep -q ^nomad ${SYSDIR}/etc/passwd; then \
		chroot ${SYSDIR} sh -c \
		    'pw useradd nomad -m -G wheel,operator,video \
		    -s /bin/csh'; \
	fi
	(cd config && tar cf - .) | \
	    (cd ${SYSDIR} && tar -xf - --uname root --gname wheel)
	chroot ${SYSDIR} sh -c 'cap_mkdb /etc/login.conf'

fontpaths: ${FONTPATHS_FILE}

${FONTPATHS_FILE}: instpkgs
	if [ ! -d ${XORG_CONF_D} ]; then mkdir -p ${XORG_CONF_D}; fi
	(for i in ${FONTSDIR}/*; do \
		[ ! -d "$$i" ] && continue; \
		mkfontscale "$$i/"; \
		mkfontdir "$$i/"; \
	done; \
	echo "Section \"Files\""; \
	IFS=; \
	for i in ${FONTSDIR}/*; do \
		[ ! -d "$$i" ] && continue; \
		n=`head -1 "$$i/fonts.scale"`; \
		i=`echo $$i | sed -E 's#${SYSDIR}(/.*)$$#\1#'`; \
		if [ $$n -gt 0 ]; then \
			echo "  FontPath \"$$i\""; \
		else \
			if [ ! -z $${ns} ]; then \
				ns=`printf "$${ns}\n$$i"`; \
			else \
				ns="$$i"; \
			fi \
		fi \
	done; \
	echo $${ns} | while read i; do \
		echo "  FontPath \"$$i\""; \
	done; \
	echo "EndSection") > ${FONTPATHS_FILE}

${SYSDIR}:
	BSDINSTALL_DISTDIR=${DISTDIR} BSDINSTALL_DISTSITE=${DISTSITE} \
	    DISTRIBUTIONS="${DISTS}" bsdinstall jail ${SYSDIR}
	BSDINSTALL_DISTDIR=${DISTDIR} DISTRIBUTIONS=kernel.txz \
	BSDINSTALL_DISTSITE=${DISTSITE} bsdinstall distfetch
	BSDINSTALL_DISTDIR=${DISTDIR} BSDINSTALL_CHROOT=${SYSDIR} \
	    DISTRIBUTIONS=kernel.txz bsdinstall distextract

updatebase: ${SYSDIR}
	-(freebsd-update --currently-running ${RELEASE} \
		-f config/etc/freebsd-update.conf -b ${SYSDIR} fetch && \
	freebsd-update --currently-running ${RELEASE} \
		-f config/etc/freebsd-update.conf -b ${SYSDIR} install)

instpkgs: ${PKGDB}
	if grep -q ^cups: ${SYSDIR}/etc/group; then \
		chroot ${SYSDIR} sh -c 'pw groupmod cups -m root,nomad'; \
	fi

${PKGDB}: initbase ${PKGLIST}
	export ASSUME_ALWAYS_YES=yes; \
	    cat ${PKGLIST} | xargs -J% pkg -c ${SYSDIR} install -y %
	if [ ! -d ${SYSDIR}/git ]; then mkdir ${SYSDIR}/git; fi
.for r in ${GIT_REPOS}
	if [ ! -d ${SYSDIR}/git/${r:S,${GIT_SITE}/,,:S,.git,,} ]; then \
		chroot ${SYSDIR} sh -c 'cd /git && git clone ${r}'; \
	fi
.endfor
.for r in ${GIT_REPO_DIRS}
	chroot ${SYSDIR} sh -c 'cd /git/${r}; \
		ls *.pro > /dev/null 2>&1 && qmake; make && make install'
.endfor
	cp ${SYSDIR}/usr/local/etc/dsbmd.conf.sample \
	    ${SYSDIR}/usr/local/etc/dsbmd.conf
buildkernel: ${KERNELTARGET}

${KERNELTARGET}: initbase
.ifdef BUILDKERNEL
	if [ ! -f ${SYSDIR}/usr/src/Makefile ]; then \
		BSDINSTALL_DISTDIR=${DISTDIR} DISTRIBUTIONS=src.txz \
		    BSDINSTALL_DISTSITE=${DISTSITE} bsdinstall distfetch; \
		BSDINSTALL_DISTDIR=${DISTDIR} BSDINSTALL_CHROOT=${SYSDIR} \
		    DISTRIBUTIONS=src.txz bsdinstall distextract; \
	fi
	if [ ! -f ${SYSDIR}/usr/obj/usr/src/sys/NOMADBSD/kernel ]; then \
		(cd kernel && tar cf - .) | \
		    (cd ${SYSDIR}/usr/src/sys/${ARCH}/conf && tar xf -); \
		chroot ${SYSDIR} sh -c \
		    'mount -t devfs devfs /dev; \
		    cd /usr/src && make KERNCONF=NOMADBSD kernel'; \
		umount ${SYSDIR}/dev; \
	fi
.endif

image: nomadbsd.img

nomadbsd.img: uzip
	blksize=`echo "${FRAGSIZE} * 8" | bc`; \
	uzipsz=`du -B $${blksize} -m ${UZIP_IMAGE}.uzip | cut -f1`; \
	tot=`du -B $${blksize} -mc sys | tail -1 | cut -f1`; \
	r=`du -B $${blksize} -mc sys/boot/kernel.old sys/git sys/usr/obj \
		sys/usr/src sys/usr/share/doc sys/usr/local sys/var/cache/pkg \
		sys/var/db/ports sys/var/db/portsnap sys/var/log | \
		tail -1 | cut -f1`; \
	basesz=`expr $$tot - $$r + $$uzipsz`; \
	touch nomadbsd.img; \
	maxsize=`echo "scale=0; ${MEDIASIZE} * 1000^3 / 1024" | bc`; \
	mddev=`mdconfig -a -t vnode -f $@ -s $${maxsize}k || exit 1`; \
	if [ ! -d mnt ]; then mkdir mnt || exit 1; fi; \
	sh -c "gpart destroy -F $${mddev}; exit 0"; \
	gpart create -s gpt $${mddev} || exit 1; \
	gpart add -t freebsd-boot -l gpboot -b 40 -s 512K $${mddev} || exit 1;\
	gpart bootcode -b /boot/pmbr -p /boot/gptboot -i 1 $${mddev} || exit 1;\
	gpart add -t efi -l gpefiboot -a4k -s492k $${mddev} || exit 1; \
	newfs_msdos /dev/$${mddev}p2 || exit 1; \
	mount -t msdosfs /dev/$${mddev}p2 ./mnt || exit 1; \
	mkdir -p ./mnt/EFI/BOOT; \
	cp ${SYSDIR}/boot/boot1.efi ./mnt/EFI/BOOT; \
	umount ./mnt; \
	gpart add -t freebsd-swap -l gpswap -s ${SWAPSIZE}M $${mddev}; \
	gpart add -t freebsd-ufs -l gprootfs -s $${basesz}M $${mddev}; \
	gpart add -t freebsd-ufs -l gprivatefs $${mddev}; \
	newfs -E -U -O 1 -o time -b $${blksize} -f ${FRAGSIZE} \
	    -m 8 /dev/$${mddev}p4 || exit 1; \
	if [ ! -d mnt ]; then mkdir mnt || exit 1; sleep 1; fi; \
	mount /dev/$${mddev}p4 mnt || exit 1; \
	(cd ${SYSDIR} && rm -rf var/tmp/*; rm -rf tmp/*); \
	(cd ${SYSDIR} && tar -cf - \
	    --exclude '^boot/kernel.old' \
	    --exclude '^git*'		 \
	    --exclude '^pkgs/*'		 \
	    --exclude '^usr/obj*'	 \
	    --exclude '^usr/src*'	 \
	    --exclude '^usr/ports*'	 \
	    --exclude '^usr/*/doc/*'	 \
	    --exclude '^usr/local'	 \
	    --exclude '^home*'		 \
	    --exclude '^usr/home*'	 \
	    --exclude '^var/cache/pkg*'	 \
	    --exclude '^var/db/portsnap/*' \
	    --exclude '^var/db/ports/*'	 \
	    --exclude '^var/log/*' .) | (cd mnt && tar pxf -); \
	mkdir mnt/var/log; \
	(cd ${SYSDIR}/usr/home/nomad && tar cfz - .) > mnt/home.nomad.tgz; \
	mkdir mnt/usr.local.etc; \
	(cd ${SYSDIR}/usr/local/etc && tar cf - .) | \
 	    (cd mnt/usr.local.etc && tar vpxf -); \
	mkdir mnt/uzip; mkdir mnt/usr/local; \
	cp ${UZIP_IMAGE}.uzip mnt/uzip/usr.local.uzip; \
	umount mnt || umount -f mnt; mdconfig -d -u $${mddev}; \
	rmdir mnt

uzip: ${UZIP_IMAGE}.uzip

${UZIP_IMAGE}.img: init
	blksize=`echo "${FRAGSIZE} * 8" | bc`; \
	touch ${UZIP_IMAGE}.img; \
	mddev=`mdconfig -a -t vnode -f ${UZIP_IMAGE}.img -s 6000m || exit 1`; \
	newfs -O 1 -o time -b $${blksize} -f ${FRAGSIZE} -m 8 \
	    /dev/$${mddev} || exit 1; \
	if [ ! -d ${UZIP_MNT} ]; then mkdir ${UZIP_MNT} || exit 1; fi; \
	mount /dev/$${mddev} ${UZIP_MNT} || exit 1; \
	(cd ${SYSDIR}/usr/local && tar -cf -	\
	    --exclude '^etc' .) | (cd ${UZIP_MNT} && tar pxf -); \
	(cd ${UZIP_MNT} && ln -s /usr.local.etc etc); \
	umount ${UZIP_MNT} || umount -f ${UZIP_MNT}; \
	mdconfig -d -u $${mddev}; \
	rmdir ${UZIP_MNT}

${UZIP_IMAGE}.uzip: ${UZIP_IMAGE}.img
	mkuzip -Z -j 2 -d -s 19456 -o ${UZIP_IMAGE}.uzip ${UZIP_IMAGE}.img

baseclean:
	chflags -R noschg,nosunlnk ${SYSDIR}
	rm -rf ${SYSDIR}

uzipclean:
	rm -f ${UZIP_IMAGE}.img ${UZIP_IMAGE}.uzip

kernelclean:
	chroot ${SYSDIR} sh -c \
	    'mount -t devfs devfs /dev;	\
	    cd /usr/src && make KERNCONF=NOMADBSD cleankernel'
	umount ${SYSDIR}/dev

distclean:
	rm -rf ${DISTDIR}/*

clean: distclean baseclean uzipclean

allclean: clean
	rm -f nomadbsd.img

