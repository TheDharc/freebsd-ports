# Kris Moore <kmoore@FreeBSD.org>
# $FreeBSD$

PORTNAME=	pcbsd-base
PORTVERSION=	2020151023
CATEGORIES=	misc
MASTER_SITES=
DISTFILES=

MAINTAINER=	kmoore@FreeBSD.org
COMMENT=	PC-BSD Base system packages

RUN_DEPENDS=	pc-updategui:${PORTSDIR}/sysutils/pcbsd-utils-qt5 \
		pc-updatemanager:${PORTSDIR}/sysutils/pcbsd-utils \
                ${LOCALBASE}/share/pcbsd/scripts/functions.sh:${PORTSDIR}/sysutils/pcbsd-libsh \
		syscache:${PORTSDIR}/sysutils/pcbsd-syscache \
		lpreserver:${PORTSDIR}/sysutils/life-preserver \
		warden:${PORTSDIR}/sysutils/warden \
		iocage:${PORTSDIR}/sysutils/iocage-devel \
		pbi:${PORTSDIR}/sysutils/pbi-manager \
		${LOCALBASE}/share/appcafe/dispatcher:${PORTSDIR}/sysutils/pcbsd-appweb \
		git:${PORTSDIR}/devel/git \
		beadm:${PORTSDIR}/sysutils/beadm \
		samba41>=0:${PORTSDIR}/net/samba41 \
		xorg>=0:${PORTSDIR}/x11/xorg \
		xf86-input-synaptics>=0:${PORTSDIR}/x11-drivers/xf86-input-synaptics \
		xf86-video-intel>=0:${PORTSDIR}/x11-drivers/xf86-video-intel \
		xf86-video-scfb>=0:${PORTSDIR}/x11-drivers/xf86-video-scfb \
		noto>=0:${PORTSDIR}/x11-fonts/noto \
		droid-fonts-ttf>=0:${PORTSDIR}/x11-fonts/droid-fonts-ttf \
		xv:${PORTSDIR}/graphics/xv \
		libvdpau>=0:${PORTSDIR}/multimedia/libvdpau \
		rdesktop:${PORTSDIR}/net/rdesktop \
		gtk2-qtcurve-theme>=0:${PORTSDIR}/x11-themes/qtcurve-gtk2 \
		qt4-style-qtcurve>=0:${PORTSDIR}/x11-themes/qtcurve-qt4 \
		gtk-theme-switch>=0:${PORTSDIR}/x11/gtk-theme-switch2 \
		alsa-lib>=0:${PORTSDIR}/audio/alsa-lib \
		fluxbox:${PORTSDIR}/x11-wm/fluxbox \
		fluxbox-tenr-styles-pack>=0:${PORTSDIR}/x11-themes/fluxbox-tenr-styles-pack \
		${LOCALBASE}/etc/rc.d/fail2ban:${PORTSDIR}/security/py-fail2ban \
		vorbis-tools>=0:${PORTSDIR}/audio/vorbis-tools \
		zip:${PORTSDIR}/archivers/zip \
		unzip:${PORTSDIR}/archivers/unzip \
		sudo:${PORTSDIR}/security/sudo \
		cdrdao:${PORTSDIR}/sysutils/cdrdao \
		growisofs:${PORTSDIR}/sysutils/dvd+rw-tools \
		ssh-askpass:${PORTSDIR}/security/openssh-askpass \
		cups-pdf>=0:${PORTSDIR}/print/cups-pdf \
		cups-filters>=0:${PORTSDIR}/print/cups-filters \
		cups-bjnp>=0:${PORTSDIR}/print/cups-bjnp \
		fusefs-ntfs>=0:${PORTSDIR}/sysutils/fusefs-ntfs \
		xdg-open:${PORTSDIR}/devel/xdg-utils \
		rsync:${PORTSDIR}/net/rsync \
		pwcview:${PORTSDIR}/multimedia/pwcview \
		mtools>=0:${PORTSDIR}/emulators/mtools \
		nss_mdns>=0:${PORTSDIR}/dns/nss_mdns \
		rar:${PORTSDIR}/archivers/rar \
		cursor-jimmac-theme>=0:${PORTSDIR}/x11-themes/cursor-jimmac-theme \
		cuse4bsd-kmod>=0:${PORTSDIR}/multimedia/cuse4bsd-kmod \
		webcamd>=0:${PORTSDIR}/multimedia/webcamd \
		system-config-printer:${PORTSDIR}/print/system-config-printer \
		numlockx:${PORTSDIR}/x11/numlockx \
		pciutils>=0:${PORTSDIR}/sysutils/pciutils \
		gpg:${PORTSDIR}/security/gnupg \
		linux_dvbwrapper-kmod>=0:${PORTSDIR}/multimedia/linux_dvbwrapper-kmod \
		xvkbd:${PORTSDIR}/x11/xvkbd \
		volman>=0:${PORTSDIR}/sysutils/volman \
		fribidi>=0:${PORTSDIR}/converters/fribidi \
		libdvdcss>=0:${PORTSDIR}/multimedia/libdvdcss \
		pam_ldap>=0:${PORTSDIR}/security/pam_ldap \
		pam_mkhomedir>=0:${PORTSDIR}/security/pam_mkhomedir \
		nss_ldap>=0:${PORTSDIR}/net/nss_ldap \
		rpm2cpio>=0:${PORTSDIR}/archivers/rpm2cpio \
		gsmartcontrol:${PORTSDIR}/sysutils/gsmartcontrol \
		xsane:${PORTSDIR}/graphics/xsane \
		libaacs>=0:${PORTSDIR}/multimedia/libaacs \
		xbrightness>=0:${PORTSDIR}/x11/xbrightness \
		x11vnc>=0:${PORTSDIR}/net/x11vnc \
		ataidle>=0:${PORTSDIR}/sysutils/ataidle \
		tk84>=0:${PORTSDIR}/x11-toolkits/tk84 \
		tk85>=0:${PORTSDIR}/x11-toolkits/tk85 \
		tk86>=0:${PORTSDIR}/x11-toolkits/tk86 \
		pulseaudio>=0:${PORTSDIR}/audio/pulseaudio \
		paprefs>=0:${PORTSDIR}/audio/paprefs \
		pavucontrol>=0:${PORTSDIR}/audio/pavucontrol \
		disktype>=0:${PORTSDIR}/sysutils/disktype \
		grub-mkconfig:${PORTSDIR}/sysutils/grub2-pcbsd \
		grub2-efi>=0:${PORTSDIR}/sysutils/grub2-efi \
		unrar:${PORTSDIR}/archivers/unrar \
		7z:${PORTSDIR}/archivers/p7zip \
		avahi-browse:${PORTSDIR}/net/avahi-app \
		anacron:${PORTSDIR}/sysutils/anacron \
		openntpd>=0:${PORTSDIR}/net/openntpd \
		socat>=0:${PORTSDIR}/net/socat \
		tor>=0:${PORTSDIR}/security/tor

NO_BUILD=	yes

do-install:
	${DO_NADA}

.include <bsd.port.mk>
