# $FreeBSD$

PORTNAME=	help
DISTVERSION=	${QT5_VERSION}
CATEGORIES=	devel
PKGNAMEPREFIX=	qt5-

MAINTAINER=	kde@FreeBSD.org
COMMENT=	Qt online help integration module

USE_QT5=	clucene core gui network sql widgets buildtools_build
QT_DIST=	tools
USES=		qmake
USE_LDCONFIG=	${PREFIX}/${QT_LIBDIR_REL}

BUILD_WRKSRC=	${WRKSRC}/src/assistant
INSTALL_WRKSRC=	${WRKSRC}/src/assistant

.include <bsd.port.mk>
