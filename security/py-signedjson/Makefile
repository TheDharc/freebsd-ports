# Created by: Brendan Molloy <brendan+freebsd@bbqsrc.net>
# $FreeBSD$

PORTNAME=	signedjson
PORTVERSION=	1.0.0
DISTVERSIONPREFIX=	v
CATEGORIES=	security devel python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	brendan+freebsd@bbqsrc.net
COMMENT=	Sign JSON with Ed25519 signatures

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pynacl>=0.3.0:${PORTSDIR}/security/py-pynacl \
		${PYTHON_PKGNAMEPREFIX}unpaddedbase64>=1.0.1:${PORTSDIR}/devel/py-unpaddedbase64 \
		${PYTHON_PKGNAMEPREFIX}canonicaljson>=1.0.0:${PORTSDIR}/devel/py-canonicaljson
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pytest>0:${PORTSDIR}/devel/py-pytest

USES=		python
USE_GITHUB=	yes
USE_PYTHON=	autoplist distutils

GH_ACCOUNT=	matrix-org
GH_PROJECT=	python-signedjson

NO_ARCH=	yes

do-test:
	@(cd ${WRKSRC} && ${PYTHON_CMD} -m pytest tests)

.include <bsd.port.mk>
