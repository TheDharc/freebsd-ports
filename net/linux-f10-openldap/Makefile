# Created by: peter
# $FreeBSD: head/net/linux-f10-openldap/Makefile 362313 2014-07-20 11:59:59Z rene $

PORTNAME=	openldap
PORTVERSION=	2.4.12
PORTREVISION=	2
CATEGORIES=	net linux
MASTER_SITES=	LOCAL/ehaupt/rpm/${LINUX_RPM_ARCH}/fedora/${LINUX_DIST_VER}

MAINTAINER=	emulation@FreeBSD.org
COMMENT=	Lightweight Directory Access Protocol libraries (Linux Fedora 10)

USE_LINUX=	f10
USE_LINUX_RPM=	yes

RPMVERSION=	1.fc10
USE_LDCONFIG=	yes
DESCR=	${.CURDIR}/../openldap24-server/pkg-descr

PLIST_FILES=	usr/lib/liblber-2.4.so.2 usr/lib/liblber-2.4.so.2.2.0 usr/lib/libldap-2.4.so.2 usr/lib/libldap-2.4.so.2.2.0 usr/lib/libldap_r-2.4.so.2 usr/lib/libldap_r-2.4.so.2.2.0 etc/openldap usr/share/man/man5/ldap.conf.5.gz usr/share/man/man5/ldif.5.gz
DOCSDIR=	usr/share/doc/${PORTNAME}-${PORTVERSION}
PORTDOCS=	ANNOUNCEMENT CHANGES COPYRIGHT LICENSE README

# do not install any openldap configuration directories/files
post-extract:
	${RM} -rf ${WRKSRC}/etc

# use a native openldap configuration directories/files
post-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/etc
	${LN} -sf ${LOCALBASE}/etc/openldap ${STAGEDIR}${PREFIX}/etc/openldap

.include <bsd.port.mk>
