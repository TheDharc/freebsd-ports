# New ports collection makefile for:	trueos-base
# Date created:				01 Feb 2013
# Whom:					Kris Moore <kmoore@FreeBSD.org>
#
# $FreeBSD$

PORTNAME=	trueos-base
PORTVERSION=	2020151123
CATEGORIES=	misc
MASTER_SITES=	# Empty
DISTFILES=	# Empty

MAINTAINER=	kmoore@FreeBSD.org
COMMENT=	PC-BSD / TrueOS Command-Line Utilities

RUN_DEPENDS=	pc-updatemanager:${PORTSDIR}/sysutils/pcbsd-utils \
		${LOCALBASE}/share/pcbsd/scripts/functions.sh:${PORTSDIR}/sysutils/pcbsd-libsh \
		lpreserver:${PORTSDIR}/sysutils/life-preserver \
		warden:${PORTSDIR}/sysutils/warden \
		iocage:${PORTSDIR}/sysutils/iocage-devel \
		pbi:${PORTSDIR}/sysutils/pbi-manager \
		beadm:${PORTSDIR}/sysutils/beadm \
		sudo:${PORTSDIR}/security/sudo \
		bash:${PORTSDIR}/shells/bash \
		zsh:${PORTSDIR}/shells/zsh \
		rsync:${PORTSDIR}/net/rsync \
		smartd:${PORTSDIR}/sysutils/smartmontools \
		jailme:${PORTSDIR}/sysutils/jailme \
		screen:${PORTSDIR}/sysutils/screen \
		nano:${PORTSDIR}/editors/nano \
		mosh:${PORTSDIR}/net/mosh \
		zfs-stats:${PORTSDIR}/sysutils/zfs-stats \
		ataidle>=0:${PORTSDIR}/sysutils/ataidle \
		anacron:${PORTSDIR}/sysutils/anacron \
		grub-mkconfig:${PORTSDIR}/sysutils/grub2-pcbsd \
		grub2-efi>=0:${PORTSDIR}/sysutils/grub2-efi \
		openntpd>=0:${PORTSDIR}/net/openntpd

NO_BUILD=	yes

do-install:
	${DO_NADA}

.include <bsd.port.mk>
