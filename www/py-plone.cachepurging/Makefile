# $FreeBSD$

PORTNAME=	plone.cachepurging
PORTVERSION=	1.0.10
CATEGORIES=	www python zope
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DIST_SUBDIR=	zope

MAINTAINER=	zope@FreeBSD.org
COMMENT=	Cache purging support for Zope 2 applications

LICENSE=	GPLv2

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}five.globalrequest>=0:${PORTSDIR}/devel/py-five.globalrequest \
		${PYTHON_PKGNAMEPREFIX}plone.registry>=0:${PORTSDIR}/www/py-plone.registry \
		${PYTHON_PKGNAMEPREFIX}z3c.caching>0:${PORTSDIR}/devel/py-z3c.caching \
		${PYTHON_PKGNAMEPREFIX}zope.annotation>=0:${PORTSDIR}/devel/py-zope.annotation \
		${PYTHON_PKGNAMEPREFIX}zope.component>=0:${PORTSDIR}/devel/py-zope.component \
		${PYTHON_PKGNAMEPREFIX}zope.event>=0:${PORTSDIR}/devel/py-zope.event \
		${PYTHON_PKGNAMEPREFIX}zope.i18nmessageid>=0:${PORTSDIR}/textproc/py-zope.i18nmessageid \
		${PYTHON_PKGNAMEPREFIX}zope.interface>=0:${PORTSDIR}/devel/py-zope.interface \
		${PYTHON_PKGNAMEPREFIX}zope.lifecycleevent>=0:${PORTSDIR}/devel/py-zope.lifecycleevent \
		${PYTHON_PKGNAMEPREFIX}zope.schema>0:${PORTSDIR}/devel/py-zope.schema \
		${PYTHON_PKGNAMEPREFIX}zope.testing>0:${PORTSDIR}/devel/py-zope.testing

NO_ARCH=	yes
USES=		python
USE_PYTHON=	autoplist distutils
#USES=		zope

.include <bsd.port.mk>
