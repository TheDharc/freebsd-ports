# Created by: msmith@FreeBSD.org
# $FreeBSD: head/devel/linux_kdump/Makefile 353859 2014-05-12 16:17:12Z nox $

PORTNAME=	linux_kdump
PORTVERSION=	1.5
PORTREVISION=	3
CATEGORIES=	devel linux
MASTER_SITES=	LOCAL/marcel

MAINTAINER=	emulation@FreeBSD.org
COMMENT=	Linux-compatibility ktrace.out processor

BUILD_DEPENDS=	${RUN_DEPENDS} # USE_LINUX_APPS only sets RUN_DEPENDS

USES=		uidfix
USE_LINUX=	yes
USE_LINUX_APPS=	devtools

ONLY_FOR_ARCHS=	i386 amd64
PLIST_FILES=	bin/linux_kdump man/man1/linux_kdump.1.gz

.include <bsd.port.pre.mk>

pre-everything::
	@${ECHO_MSG} '===> Using the FreeBSD source tree under ${SRC_BASE}'
	@${ECHO_MSG} '===> Set SRC_BASE to use an alternate source tree'

.if !exists(${SRC_BASE}/sys/i386/linux/syscalls.master)
IGNORE=	requires kernel source present in ${SRC_BASE}/sys
.endif
.if !exists(${SRC_BASE}/usr.bin/ktrace/subr.c)
IGNORE=	requires ktrace source present in ${SRC_BASE}/usr.bin/ktrace
.endif

.include <bsd.port.post.mk>
