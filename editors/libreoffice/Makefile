# $FreeBSD$

.include "${.CURDIR}/Makefile.common"

MASTER_SITES=	http://download.documentfoundation.org/libreoffice/src/${PORTVERSION}/ \
		http://dev-www.libreoffice.org/src/:src \
		http://dev-www.libreoffice.org/extern/:ext
DISTFILES=	${PORTNAME}-${LOVERSION}${EXTRACT_SUFX} \
		${PORTNAME}-help-${LOVERSION}${EXTRACT_SUFX}
DIST_SUBDIR=	libreoffice
EXTRACT_ONLY:=	${DISTFILES}

COMMENT=	Full integrated office productivity suite

BUILD_DEPENDS=	p5-Archive-Zip>=0:${PORTSDIR}/archivers/p5-Archive-Zip \
		zip:${PORTSDIR}/archivers/zip \
		${LOCALBASE}/include/sqlext.h:${PORTSDIR}/databases/unixODBC \
		cppunit-config:${PORTSDIR}/devel/cppunit \
		dmake:${PORTSDIR}/devel/dmake \
		${LOCALBASE}/bin/gperf:${PORTSDIR}/devel/gperf \
		mdds>=0.9.0:${PORTSDIR}/devel/mdds \
		gpatch:${PORTSDIR}/devel/patch \
		ucpp:${PORTSDIR}/devel/ucpp \
		${LOCALBASE}/include/sane/sane.h:${PORTSDIR}/graphics/sane-backends \
		vigra-config:${PORTSDIR}/graphics/vigra \
		${LOCALBASE}/include/glm/glm.hpp:${PORTSDIR}/math/glm \
		bash:${PORTSDIR}/shells/bash \
		gsed:${PORTSDIR}/textproc/gsed
LIB_DEPENDS=	libfbembed.so:${PORTSDIR}/databases/firebird25-client \
		libapr-1.so:${PORTSDIR}/devel/apr1 \
		libboost_date_time.so:${PORTSDIR}/devel/boost-libs \
		libicutu.so:${PORTSDIR}/devel/icu \
		liblangtag.so:${PORTSDIR}/devel/liblangtag \
		liborcus-0.10.so:${PORTSDIR}/devel/liborcus \
		libcurl.so:${PORTSDIR}/ftp/curl \
		libcairo.so:${PORTSDIR}/graphics/cairo \
		libgraphite2.so:${PORTSDIR}/graphics/graphite2 \
		liblcms2.so:${PORTSDIR}/graphics/lcms2 \
		libcdr-0.1.so:${PORTSDIR}/graphics/libcdr01 \
		libetonyek-0.1.so:${PORTSDIR}/graphics/libetonyek01 \
		libfreehand-0.1.so:${PORTSDIR}/graphics/libfreehand \
		libgltf-0.0.so:${PORTSDIR}/graphics/libgltf \
		libwpg-0.3.so:${PORTSDIR}/graphics/libwpg03 \
		libGeneratedSaxParser.so:${PORTSDIR}/graphics/opencollada \
		libpng.so:${PORTSDIR}/graphics/png \
		libpoppler.so:${PORTSDIR}/graphics/poppler \
		libCoinMP.so:${PORTSDIR}/math/coinmp \
		liblpsolve55.so:${PORTSDIR}/math/lp_solve \
		libcmis-0.5.so:${PORTSDIR}/net/libcmis \
		libharfbuzz.so:${PORTSDIR}/print/harfbuzz \
		libmspub-0.1.so:${PORTSDIR}/print/libmspub01 \
		libpagemaker-0.0.so:${PORTSDIR}/print/libpagemaker \
		libnss3.so:${PORTSDIR}/security/nss \
		libclucene-core.so:${PORTSDIR}/textproc/clucene \
		libexpat.so:${PORTSDIR}/textproc/expat2 \
		libhunspell-1.3.so:${PORTSDIR}/textproc/hunspell \
		libhyphen.so:${PORTSDIR}/textproc/hyphen \
		libabw-0.1.so:${PORTSDIR}/textproc/libabw \
		libe-book-0.1.so:${PORTSDIR}/textproc/libe-book \
		libexttextcat-2.0.so:${PORTSDIR}/textproc/libexttextcat \
		libmwaw-0.3.so:${PORTSDIR}/textproc/libmwaw03 \
		libodfgen-0.1.so:${PORTSDIR}/textproc/libodfgen01 \
		librevenge-0.0.so:${PORTSDIR}/textproc/librevenge \
		libvisio-0.1.so:${PORTSDIR}/textproc/libvisio01 \
		libwpd-0.10.so:${PORTSDIR}/textproc/libwpd010 \
		libwps-0.4.so:${PORTSDIR}/textproc/libwps \
		libxml2.so:${PORTSDIR}/textproc/libxml2 \
		libxslt.so:${PORTSDIR}/textproc/libxslt \
		libmythes-1.2.so:${PORTSDIR}/textproc/mythes \
		librdf.so:${PORTSDIR}/textproc/redland \
		libserf-1.so:${PORTSDIR}/www/serf
RUN_DEPENDS=	${LOCALBASE}/share/fonts/Caladea/Caladea-Bold.ttf:${PORTSDIR}/x11-fonts/crosextrafonts-caladea-ttf \
		${LOCALBASE}/share/fonts/Carlito/Carlito-Bold.ttf:${PORTSDIR}/x11-fonts/crosextrafonts-carlito-ttf \
		${LOCALBASE}/share/fonts/dejavu/DejaVuSans.ttf:${PORTSDIR}/x11-fonts/dejavu \
		${LOCALBASE}/share/fonts/GentiumBasic/GenBasI.ttf:${PORTSDIR}/x11-fonts/gentium-basic \
		${LOCALBASE}/share/fonts/Liberation/LiberationMono-Bold.ttf:${PORTSDIR}/x11-fonts/liberation-fonts-ttf \
		${LOCALBASE}/share/fonts/LinLibertineG/LinLibertine_DR_G.ttf:${PORTSDIR}/x11-fonts/linuxlibertine-g

DISTFILES+=	1f24ab1d39f4a51faf22244c94a6203f-xmlsec1-1.2.14.tar.gz:src \
		4b87018f7fff1d054939d19920b751a0-collada2gltf-master-cb1d97788a.tar.bz2:src

.if defined(PRERELEASE)
MASTER_SITES+=	http://dev-builds.libreoffice.org/pre-releases/src/
.endif

CONFLICTS_INSTALL=	libreoffice4-4.*

INSTALL_TARGET=	distro-pack-install
WRKSRC=		${WRKDIR}/${PORTNAME}-${LOVERSION}

GNU_CONFIGURE=	yes
USE_AUTOTOOLS=	autoconf aclocal
USE_GL=		gl glew glu
USE_OPENLDAP=	yes
USE_PERL5=	build
USE_QT4=	# empty but required
USE_XORG=	xaw xrandr
USES=		bison compiler:c++11-lib cpe gmake jpeg perl5 pkgconfig \
		python shared-mime-info tar:xz
WANT_GNOME=	yes

OPTIONS_DEFINE=	CUPS GNOME GTK2 GTK3 JAVA KDE4 MMEDIA PGSQL SDK SYSTRAY \
		TEST VERBOSE WEBDAV
OPTIONS_DEFAULT=	CUPS GTK2

JAVA_DESC=	Add Java support (XML filters, macros)
MMEDIA_DESC=	Enable multimedia backend for impress
PGSQL_DESC=	Build with PostgreSQL-SDBC driver
SDK_DESC=	Build with SDK
SYSTRAY_DESC=	Enable systemtray quickstarter
TEST_DESC=	Run all regression tests
VERBOSE_DESC=	Increase build verbosity
WEBDAV_DESC=	Enable webdav protocol

CUPS_CONFIGURE_ENABLE=	cups
CUPS_LIB_DEPENDS=	libcups.so:${PORTSDIR}/print/cups-client

GNOME_CONFIGURE_ENABLE=	dbus gconf lockdown
GNOME_IMPLIES=	GTK2
GNOME_LIB_DEPENDS=	libdbus-glib-1.so:${PORTSDIR}/devel/dbus-glib
GNOME_USE=	GNOME=gconf2

GTK_USE_GNOME=	gtk-update-icon-cache
GTK_USES=	desktop-file-utils
GTK_VARS=	POST_PLIST=add-plist-gnome

GTK2_CONFIGURE_ENABLE=	gtk
GTK2_USE=	GNOME=gtk20,${GTK_USE_GNOME}
GTK2_USES=	${GTK_USES}
GTK2_VARS=	${GTK_VARS}

GTK3_CONFIGURE_ENABLE=	gtk3
GTK3_USE=	GNOME=gtk30,${GTK_USE_GNOME}
GTK3_USES=	${GTK_USES}
GTK3_VARS=	${GTK_VARS}

JAVA_BUILD_DEPENDS=	ant:${PORTSDIR}/devel/apache-ant \
			${JAVAJARDIR}/commons-codec.jar:${PORTSDIR}/java/jakarta-commons-codec \
			${JAVAJARDIR}/commons-httpclient.jar:${PORTSDIR}/java/jakarta-commons-httpclient \
			${JAVAJARDIR}/commons-lang.jar:${PORTSDIR}/java/jakarta-commons-lang \
			${JAVAJARDIR}/commons-logging.jar:${PORTSDIR}/java/jakarta-commons-logging \
			${JAVAJARDIR}/junit.jar:${PORTSDIR}/java/junit \
			${JAVAJARDIR}/bsh.jar:${PORTSDIR}/lang/bsh
JAVA_CATEGORIES=	java
JAVA_CONFIGURE_ON=	--with-ant-home=${LOCALBASE}/share/java/apache-ant \
			--with-beanshell-jar=${JAVAJARDIR}/bsh.jar \
			--with-commons-codec-jar=${JAVAJARDIR}/commons-codec.jar \
			--with-commons-httpclient-jar=${JAVAJARDIR}/commons-httpclient.jar \
			--with-commons-lang-jar=${JAVAJARDIR}/commons-lang.jar \
			--with-commons-logging-jar=${JAVAJARDIR}/commons-logging.jar \
			--with-jdk-home="${JAVA_HOME}" \
			--with-junit=${JAVAJARDIR}/junit.jar \
			--with-hamcrest=${JAVAJARDIR}/hamcrest.jar \
			--without-system-jfreereport
JAVA_CONFIGURE_WITH=	java
# XXX jni.h from GNU classpath causes ABI conflicts.
JAVA_CONFLICTS_BUILD=	classpath-[0-9]*
JAVA_DISTFILES=	17410483b5b5f267aa18b7e00b65e6e0-hsqldb_1_8_0.zip:src \
		3404ab6b1792ae5f16bbd603bd1e1d03-libformula-1.1.7.zip:src \
		35c94d2df8893241173de1d16b6034c0-swingExSrc.zip:src \
		39bb3fcea1514f1369fcfc87542390fd-sacjava-1.3.zip:src \
		3bdf40c0d199af31923e900d082ca2dd-libfonts-1.1.6.zip:src \
		798b2ffdc8bcfe7bca2cf92b62caf685-rhino1_5R5.zip:src \
		8ce2fcd72becf06c41f7201d15373ed9-librepository-1.1.6.zip:src \
		97b2d4dba862397f446b217e2b623e71-libloader-1.1.6.zip:src \
		ace6ab49184e329db254e454a010f56d-libxml-1.1.7.zip:src \
		ba2930200c9f019c2d93a8c88c651a0f-flow-engine-0.9.4.zip:src \
		d8bd5eed178db6e2b18eeed243f85aa8-flute-1.1.6.zip:src \
		db60e4fde8dd6d6807523deb71ee34dc-liblayout-0.2.10.zip:src \
		eeb2c7ddf0d302fba4bfc6e97eac9624-libbase-1.1.6.zip:src \
		f94d9870737518e3b597f9265f4e9803-libserializer-1.1.6.zip:src
JAVA_USE=	JAVA=yes
JAVA_VARS=	JAVA_BUILD=yes

KDE4_CONFIGURE_ENABLE=	kde4
KDE4_CONFIGURE_ENV=	KDE4DIR="${KDE4_PREFIX}" \
			QT4DIR="${QT_PREFIX}" \
			QT4INC="${QT_INCDIR}" \
			QT4LIB="${QT_LIBDIR}"
KDE4_USE=	KDE4=kdelibs QT4=moc_build,qmake_build

MMEDIA_CONFIGURE_ENABLE=	gstreamer-1-0
MMEDIA_USE=	GSTREAMER1=yes

PGSQL_CONFIGURE_ENABLE=	postgresql-sdbc
PGSQL_CONFIGURE_WITH=	gssapi krb5
PGSQL_USES=	pgsql

SDK_BUILD_DEPENDS=	doxygen:${PORTSDIR}/devel/doxygen
SDK_CONFIGURE_ENABLE=	odk
SDK_CONFIGURE_OFF=	--without-doxygen
SDK_CONFIGURE_ON=	--with-doxygen=${LOCALBASE}/bin/doxygen
SDK_DISTFILES=	185d60944ea767075d27247c3162b3bc-unowinreg.dll:ext

SYSTRAY_CONFIGURE_ENABLE=	systray

TEST_CONFIGURE_ENABLE=	cve-tests

VERBOSE_CONFIGURE_ON=	--enable-verbose

WEBDAV_CONFIGURE_ENABLE=	neon
WEBDAV_LIB_DEPENDS=	libneon.so:${PORTSDIR}/www/neon

ACLOCAL_ARGS=	-I "${WRKSRC}/m4"
CPPFLAGS+=	-isystem ${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

COLLADA_MODS=	COLLADABaseUtils COLLADAFramework \
		COLLADASaxFrameworkLoader GeneratedSaxParser
COLLADA_CFLAGS=	${COLLADA_MODS:S|^|-isystem ${LOCALBASE}/include/opencollada/|}
COLLADA_LIBS=	-L${LOCALBASE}/lib/opencollada \
		${COLLADA_MODS:S|^COLLADA|OpenCOLLADA|:S|^|-l|}

CONFIGURE_ARGS=	--disable-dependency-tracking \
		--disable-epm \
		--disable-fetch-external \
		--disable-gnome-vfs \
		--disable-kde \
		--disable-kdeab \
		--disable-mergelibs \
		--disable-online-update \
		--disable-packagekit \
		--enable-cairo-canvas \
		--enable-graphite \
		--enable-python=system \
		--enable-release-build \
		--exec-prefix=${PREFIX} \
		--with-alloc=system \
		--with-boost=${LOCALBASE} \
		--with-build-version="FreeBSD ports ${PKGVERSION}" \
		--with-external-dict-dir=${LOCALBASE}/share/hunspell \
		--with-external-hyph-dir=${LOCALBASE}/share/hyphen \
		--with-external-tar=${DISTDIR}/${DIST_SUBDIR} \
		--with-external-thes-dir=${LOCALBASE}/share/mythes \
		--with-gnu-patch=${LOCALBASE}/bin/gpatch \
		--with-os-version=${OSVERSION} \
		--with-parallelism=${MAKE_JOBS_NUMBER} \
		--with-system-curl \
		--with-system-dicts \
		--with-system-libs \
		--with-system-libxml \
		--with-system-opencollada \
		--with-system-ucpp \
		--with-system-zlib \
		--with-vendor="FreeBSD ports" \
		--without-fonts \
		--without-myspell-dicts \
		--without-system-npapi-headers

CONFIGURE_ENV=	DMAKE=${LOCALBASE}/bin/dmake \
		FIREBIRD_CFLAGS="-isystem ${LOCALBASE}/include" \
		FIREBIRD_LIBS="-L${LOCALBASE}/lib -lfbembed" \
		GNUTAR="${TAR}" \
		GPERF=${LOCALBASE}/bin/gperf \
		OPENCOLLADA_CFLAGS="${COLLADA_CFLAGS}" \
		OPENCOLLADA_LIBS="${COLLADA_LIBS}" \
		OPENSSL_CFLAGS="-I/usr/include" \
		OPENSSL_LIBS="-lcrypto -lssl" \
		PYTHON_CFLAGS="`${PYTHON_VERSION}-config --cflags`" \
		PYTHON_LIBS="`${PYTHON_VERSION}-config --libs`"

MAKE_ENV+=	CXXFLAGS_WARN="${CXXFLAGS_WARN}"
MAKE_ENV+=	GNUSED=${LOCALBASE}/bin/gsed
MAKE_ENV+=	DISPLAY= LANG=C LC_ALL=C

_MAKE_JOBS=	#

.include <bsd.port.pre.mk>

.if ${OPSYS} == FreeBSD
.if ${COMPILER_FEATURES:Mlibstdc++}
BROKEN=		Build with system libstdc++ is unsupported
.endif

.if ${OSVERSION} < 1000033
BUILD_DEPENDS+=	${LOCALBASE}/bin/flex:${PORTSDIR}/textproc/flex
CONFIGURE_ENV+=	FLEX=${LOCALBASE}/bin/flex
.endif
.endif # FreeBSD

.if ${COMPILER_TYPE} == "clang"
CXXFLAGS_WARN=	-Woverloaded-virtual -Wno-unused-parameter
.if${COMPILER_VERSION} >= 36
CXXFLAGS_WARN+=	-Wno-unused-local-typedefs
.endif
.else
CXXFLAGS_WARN=	-Wshadow -Woverloaded-virtual
.endif

pre-configure:
	@${TOUCH} ${WRKSRC}/autogen.lastrun

post-configure:
	@${TOUCH} ${WRKSRC}/src.downloaded

post-install:
	@cd ${STAGEDIR}${PREFIX} && \
	${FIND} -s lib/libreoffice -type d -empty \
	    -exec ${ECHO_CMD} "@dir {}" \; >> ${TMPPLIST}
	@cd ${STAGEDIR}${PREFIX} && \
	${FIND} -s bin etc lib man -not -type d >> ${TMPPLIST}
.for subdir in application-registry applications icons mime mime-info mimelnk
	@cd ${STAGEDIR}${PREFIX} && \
	${FIND} -s share/${subdir} -not -type d >> ${TMPPLIST}
.endfor

post-install-SDK-on:
.for subdir in include share share/doc share/idl
	@cd ${STAGEDIR}${PREFIX} && \
	${FIND} -s ${subdir}/libreoffice -not -type d >> ${TMPPLIST}
.endfor

add-plist-gnome:
.for subdir in gnome hicolor locolor
	@${ECHO_CMD} "@rmtry share/icons/${subdir}/icon-theme.cache" >> ${TMPPLIST}
	@${ECHO_CMD} "@exec ${LOCALBASE}/bin/gtk-update-icon-cache -q -f %D/share/icons/${subdir} 2>/dev/null || ${TRUE}" >> ${TMPPLIST}
	@${ECHO_CMD} "@unexec ${LOCALBASE}/bin/gtk-update-icon-cache -q -f %D/share/icons/${subdir} 2>/dev/null || ${TRUE}" >> ${TMPPLIST}
.endfor

.include <bsd.port.post.mk>
