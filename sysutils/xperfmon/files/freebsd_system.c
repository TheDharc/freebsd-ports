/*
 * Perfmon Performance Monitor
 *
 * Copyright 1985, Massachusetts Institute of Technology
 * Copyright 1989, PCS Computer Systeme GmbH, West Germany
 * Copyright 1994, Sterling Software @ NASA-Ames Research Center
 * Copyright 1995, Regents of the University of California,
 *                 Lars K�ller <Lars_Koeller@odie.physik2.uni-rostock.de
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of PCS and Sterling Software not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  PCS and Sterling Software makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * PCS & STERLING SOFTWARE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL PCS & STERLING SOFTWARE
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Original Author:  Emanuel Jay Berkenbilt, MIT Project Athena
 * Author:           Thomas A. Baghli, PCS Computer Systeme GmbH, West Germany
 *                   tom@meepmeep.pcs.com
 * 1994 Revision
 * Author:           Roger Smith, Sterling Software @ NASA-Ames Research Center
 *                   Moffett Field, California, rsmith@proteus.arc.nasa.gov
 * 1995 FreeBSD 2.x Version
 * Author:           Lars Koeller, Univerity of Rostock, Germany
 *                   Lars_Koeller@odie.physik2.uni-rostock.de
 */

/* This file contains only system functions - that is the functions that
 * get the information the performance monitor is monitoring.  No calls
 * to any X routines should be made here.  The reason for doing this is
 * so that as the X toolkit becomes available and the X window system 
 * improves no changes will have to be made to this file, and as this
 * program is made available for a new type of machine, only this file
 * will need to be changed.
 */

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#if (defined(BSD) && (BSD >= 199306))
# include <osreldate.h>
#else
# error You have to use at least a FreeBSD 2.X system
#endif

#include <X11/IntrinsicP.h>

#include "system.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <paths.h>
#include <kvm.h>
#include <nlist.h>
#include <limits.h>
#include <errno.h>
#include <err.h>

#include <sys/file.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <sys/dkstat.h>
#include <sys/buf.h>
#include <sys/vmmeter.h>
#include <vm/vm.h>
#include <sys/time.h>
#include <net/if.h>
#if __FreeBSD_version >= 300000
# include <net/if_var.h>
#endif
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/conf.h>
#include <sys/rlist.h>
#include <sys/mount.h>
#include <nfs/nfsv2.h>
#include <nfs/rpcv2.h>
#include <nfs/nfs.h>

#ifndef CTL_FS
#define CTL_FS CTL_VFS		/* compatibility w/ Lite1 */
#endif

/*
 * It's a mess with all these version numbers:
 *
 *       2.0-RELEASE:                    199411
 *       2.1-current's:                  199501, 199503
 *       2.0.5-RELEASE:                  199504
 *       2.2-current before 2.1:         199508
 *       2.1.0-RELEASE:                  199511
 *       2.2-current before 2.1.5:       199512
 *       2.1.5-RELEASE:                  199607
 *       2.2-current before 2.1.6:       199608
 *       2.1.6-RELEASE:                  199612
 *       2.1.7-RELEASE:                  199612
 *       2.2-RELEASE:                    220000 (ahhhhh)
 *       3.0-current as of Feb 1997:     300000 (ohhhhh)
 */

/*
 * FreeBSD version 2.2 and greater have NFSv3
 */
#if __FreeBSD_version >= 220000
# define HAS_NFS_V3
#endif /* FreeBSD_version */

#include "is.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define WANT_STAT(x) (poss_stats[(x)] != NO_STAT)

/*
    Function Prototypes
*/
static int get_namelist(const char *kernel_name, const char *memory_name);
static void kread(int nlx, void *addr, size_t size);
static void collect_stats(void);
static int total_disk_transfers(void);
static int get_swapspace(void);

/*
    Variables & Structs
*/
static unsigned long *intrcnt;
static int nintr, hz;
static kvm_t *kd;
static char errbuf[_POSIX2_LINE_MAX];
static char dr_name[DK_NDRIVE][DK_NAMELEN];
static double etime;

int current_values[NUM_GRAPHS];
stat_type stats;

extern Widget perfmon[NUM_GRAPHS];

static struct packet {
    int input, output, collisions;
} packets, old_packets;

static struct nfsstats nfsstats;
static struct _nfsStats {
    int nfsServer, nfsClient;
} nfsStats, old_nfsStats;

struct nlist nl[] = {
#define X_CPTIME	0
	{ "_cp_time" },
#define X_SUM	   	1
	{ "_cnt" },
#define X_BOOTTIME      2
	{ "_boottime" },
#define X_DKXFER	3
	{ "_dk_xfer" },
#define X_HZ	    	4
	{ "_hz" },
#define N_IFNET       	5
	{ "_ifnet" },
#define X_INTRCNT 	6
        { "_intrcnt" },
#define X_EINTRCNT 	7
        { "_eintrcnt" },
#define VM_NSWAP        8
        { "_nswap" },   /* size of largest swap device */
#define VM_NSWDEV       9
        { "_nswdev" },  /* number of swap devices */
#define VM_DMMAX        10
        { "_dmmax" },   /* maximum size of a swap block */
#define VM_SWAPLIST     11
        { "_swaplist" },/* list of free swap areas */
#define VM_SWDEVT       12
        { "_swdevt" },  /* list of swap devices and sizes */
        { "" },
};

struct {
	long    time[CPUSTATES];
	long    xfer[DK_NDRIVE];
	struct  vmmeter Sum;
	struct  vmmeter Rate;
	int interrupts;
} s, s1;

int first_time_getswap;

#define rate s.Rate
#define sum  s.Sum

/*
    This routine does all necessary setting up of structures
    that will handle system calls.
*/
void sys_setup()
{
    get_namelist(getbootfile(), _PATH_KMEM);
    collect_stats();
    /* hack to enforce a resize of the 'Free Swap' graph
       without this the left border always displays the first drawn line
       cause this field isn't resized very often due to slow change of
       the free swapspace! */
    first_time_getswap = 1;
    etime = 1.0;
}


/*
    Update the data structures
*/
void update_stats()
{
    int state;
    double pct, tot;;

    collect_stats();

    tot = 0;
    for (state = 0; state < CPUSTATES; ++state)
        tot += s.time[state];
    if (tot)
        pct = 100 / tot;
    else
        pct = 0;
    current_values[USER_CPU_PERCENTAGE] = (s.time[CP_USER] + s.time[CP_NICE]) * pct;
    current_values[SYSTEM_CPU_PERCENTAGE] = (s.time[CP_SYS] + s.time[CP_INTR]) * pct;;
    current_values[IDLE_CPU_PERCENTAGE] = s.time[CP_IDLE] * pct;

    if (perfmon[FREE_MEM]) {
	if(!first_time_getswap)
	  current_values[FREE_MEM] = get_swapspace();
	else {
	  current_values[FREE_MEM] = 100;
	  first_time_getswap = 0;
	}
    }
    if (perfmon[DISK_TRANSFERS])
	current_values[DISK_TRANSFERS] = total_disk_transfers();
    if (perfmon[INTERRUPTS])
      current_values[INTERRUPTS] = (s.interrupts - s1.interrupts)/etime;
    if (perfmon[INPUT_PACKETS])
	current_values[INPUT_PACKETS] = (packets.input - old_packets.input)/etime;
    if (perfmon[OUTPUT_PACKETS])
	current_values[OUTPUT_PACKETS] = (packets.output - old_packets.output)/etime;
    if (perfmon[COLLISION_PACKETS])
	current_values[COLLISION_PACKETS] = (packets.collisions - old_packets.collisions)/etime;
    if (perfmon[NFS_CLIENT_CALLS])
	current_values[NFS_CLIENT_CALLS] = (nfsStats.nfsClient - old_nfsStats.nfsClient)/etime;
    if (perfmon[NFS_SERVER_CALLS])
	current_values[NFS_SERVER_CALLS] = (nfsStats.nfsServer - old_nfsStats.nfsServer)/etime;
}


/*
    Collect the overall disk transfer rates
*/
int
total_disk_transfers()
{
    register int i, total_xfers = 0;

    for(i=0; i < DK_NDRIVE; i++)
	total_xfers += s.xfer[i];
    return(total_xfers/etime);
}


/*
    Collect all the data
*/
void
collect_stats()
{
    off_t ifnetaddr;
    register int i, tmp;
    int mib[3], size;

    kread(X_CPTIME, s.time, sizeof(s.time));
    kread(X_DKXFER, s.xfer, sizeof(s.xfer));
    kread(X_SUM, &sum, sizeof(sum) );

    nintr = nl[X_EINTRCNT].n_value - nl[X_INTRCNT].n_value;
    if ((intrcnt = (unsigned long *) malloc((size_t) nintr)) == NULL)
      err(1, "xperfmon++ malloc in collect_stats");
    nintr /= sizeof(long);    
    kread(X_INTRCNT, intrcnt, (size_t) nintr*sizeof(long));
    s1.interrupts = s.interrupts;
    s.interrupts = 0;
    for (i = 0; i < nintr; i++)
        s.interrupts += *(intrcnt + i);

    free(intrcnt);
    etime = 0;
    for (i=0; i < DK_NDRIVE; i++) {
	tmp = s.xfer[i];
	s.xfer[i] -= s1.xfer[i];
	s1.xfer[i] = tmp;
    }
    for (i=0; i < CPUSTATES; i++) {
	tmp = s.time[i];
	s.time[i] -= s1.time[i];
	s1.time[i] = tmp;
	etime += s.time[i];
    }
    if(etime == 0.)
	etime = 1.;
    etime /= hz;

/*
    Collect the Network-Traffic
*/

    if ((ifnetaddr = nl[N_IFNET].n_value) != 0) {
#if __FreeBSD_version < 300000
	struct ifnet ifnet;
	kread(N_IFNET, &ifnetaddr, sizeof(ifnetaddr));
	old_packets = packets;
	packets.input = packets.output = packets.collisions = 0;
	while (ifnetaddr) {
	    kvm_read(kd, ifnetaddr, &ifnet, sizeof ifnet );
	    packets.input += ifnet.if_ipackets;
	    packets.output += ifnet.if_opackets;
	    packets.collisions += ifnet.if_collisions;
	    ifnetaddr = (u_long) ifnet.if_next;
	}
#else /* 3.0-current, Jan 1997 */
      /* Stolen from netstat/if.c */
        struct ifnet ifnet;
        struct ifnethead ifnethead;
        u_long ifaddraddr, ifnetfound;
	struct ifaddr ifa;

        if(kvm_read(kd, ifnetaddr, (char *)&ifnethead, sizeof ifnethead) == -1)
	    return;
        ifnetaddr = (u_long)ifnethead.tqh_first;
        if(kvm_read(kd, ifnetaddr, (char *)&ifnet, sizeof ifnet) == -1)
	    return;

	old_packets = packets;
	packets.input = packets.output = packets.collisions = 0;
        ifaddraddr = 0;
        while (ifnetaddr || ifaddraddr) {
	    if (ifaddraddr == 0) {
		ifnetfound = ifnetaddr;
		if(kvm_read(kd, ifnetaddr, (char *)&ifnet, sizeof ifnet) == -1)
		    return;
		ifnetaddr = (u_long)ifnet.if_link.tqe_next;
		ifaddraddr = (u_long)ifnet.if_addrhead.tqh_first;
	    }
	    if (kvm_read(kd, ifaddraddr, (char *)&ifa, sizeof ifa) == -1) {
	      ifaddraddr = 0;
	      continue;
	    }
	    ifaddraddr = (u_long)ifa.ifa_link.tqe_next;

	    packets.input += ifnet.if_ipackets;
	    packets.output += ifnet.if_opackets;
	    packets.collisions += ifnet.if_collisions;
	}
#endif
    }

/*
    Collect the NFS and RPC Calls
*/

    size = sizeof(nfsstats);
    mib[0] = CTL_FS;
    mib[1] = MOUNT_NFS;
    mib[2] = NFS_NFSSTATS;

    if (sysctl( mib, 3, &nfsstats, &size, NULL, 0) < 0)
        return;
    else {
        old_nfsStats = nfsStats;

        nfsStats.nfsClient = nfsstats.rpccnt[NFSPROC_GETATTR] + 
                             nfsstats.rpccnt[NFSPROC_SETATTR] +
                             nfsstats.rpccnt[NFSPROC_LOOKUP] +
                             nfsstats.rpccnt[NFSPROC_READLINK] +
                             nfsstats.rpccnt[NFSPROC_READ] +
                             nfsstats.rpccnt[NFSPROC_WRITE] +
                             nfsstats.rpccnt[NFSPROC_CREATE] +
                             nfsstats.rpccnt[NFSPROC_REMOVE] +
                             nfsstats.rpccnt[NFSPROC_RENAME] +
                             nfsstats.rpccnt[NFSPROC_LINK] +
                             nfsstats.rpccnt[NFSPROC_SYMLINK] +
                             nfsstats.rpccnt[NFSPROC_MKDIR] +
                             nfsstats.rpccnt[NFSPROC_RMDIR] + 
                             nfsstats.rpccnt[NFSPROC_READDIR] +
#ifndef HAS_NFS_V3
                             nfsstats.rpccnt[NFSPROC_STATFS] +
                             nfsstats.rpccnt[NQNFSPROC_READDIRLOOK] +
#else /* HAS_NFS_V3 */
                             nfsstats.rpccnt[NFSPROC_READDIRPLUS] +
                             nfsstats.rpccnt[NFSPROC_FSSTAT] +
                             nfsstats.rpccnt[NFSPROC_FSINFO] +
                             nfsstats.rpccnt[NFSPROC_PATHCONF] +
                             nfsstats.rpccnt[NFSPROC_COMMIT] +
#endif /* HAS_NFS_V3 */
                             nfsstats.rpccnt[NQNFSPROC_GETLEASE] +
                             nfsstats.rpccnt[NQNFSPROC_VACATED] +
                             nfsstats.rpccnt[NQNFSPROC_EVICTED];

        nfsStats.nfsServer = nfsstats.srvrpccnt[NFSPROC_GETATTR] + 
                             nfsstats.srvrpccnt[NFSPROC_SETATTR] +
                             nfsstats.srvrpccnt[NFSPROC_LOOKUP] +
                             nfsstats.srvrpccnt[NFSPROC_READLINK] +
                             nfsstats.srvrpccnt[NFSPROC_READ] +
                             nfsstats.srvrpccnt[NFSPROC_WRITE] +
                             nfsstats.srvrpccnt[NFSPROC_CREATE] +
                             nfsstats.srvrpccnt[NFSPROC_REMOVE] +
                             nfsstats.srvrpccnt[NFSPROC_RENAME] +
                             nfsstats.srvrpccnt[NFSPROC_LINK] +
                             nfsstats.srvrpccnt[NFSPROC_SYMLINK] +
                             nfsstats.srvrpccnt[NFSPROC_MKDIR] +
                             nfsstats.srvrpccnt[NFSPROC_RMDIR] + 
                             nfsstats.srvrpccnt[NFSPROC_READDIR] +
#ifndef HAS_NFS_V3
                             nfsstats.srvrpccnt[NFSPROC_STATFS] +
                             nfsstats.srvrpccnt[NQNFSPROC_READDIRLOOK] +
#else /* HAS_NFS_V3 */
                             nfsstats.srvrpccnt[NFSPROC_READDIRPLUS] +
                             nfsstats.srvrpccnt[NFSPROC_FSSTAT] +
                             nfsstats.srvrpccnt[NFSPROC_FSINFO] +
                             nfsstats.srvrpccnt[NFSPROC_PATHCONF] +
                             nfsstats.srvrpccnt[NFSPROC_COMMIT] +
#endif /* HAS_NFS_V3 */
                             nfsstats.srvrpccnt[NQNFSPROC_GETLEASE] +
                             nfsstats.srvrpccnt[NQNFSPROC_VACATED] +
                             nfsstats.srvrpccnt[NQNFSPROC_EVICTED];
    }
}


/*
    Reads the nlist from the kernel
*/
int
get_namelist(kernel_name, memory_name)
    const char *kernel_name, *memory_name;
{
    time_t now;
    time_t boottime;
    register int i, c;
    int nintv;

    kd = kvm_openfiles(NULL, NULL, NULL, O_RDONLY, errbuf);
    if (kd == 0) {
        (void)fprintf(stderr, "xperfmon++: kvm_openfiles: %s\n", errbuf);
        exit(1);
    }

    if ((c = kvm_nlist(kd, nl)) != 0) {
        if (c > 0) {
            (void)fprintf(stderr,"xperfmon++: undefined symbols:");
            for (c = 0; c < sizeof(nl)/sizeof(nl[0]); c++)
                if (nl[c].n_type == 0)
                    fprintf(stderr, " %s", nl[c].n_name);
            (void)fputc('\n', stderr);
        } else
            (void)fprintf(stderr, "xperfmon++: kvm_nlist: %s\n", kvm_geterr(kd));            exit(1);
    }

    kread(X_BOOTTIME, &boottime, sizeof(boottime));
    kread(X_HZ, &hz, sizeof(hz));
    for (i = 0; i < DK_NDRIVE; i++) {
	strcpy(dr_name[i], "xx");
    }
    time(&now);
    nintv = now - boottime;
    if (nintv <= 0 || nintv > 60*60*24*365*10) {
	fprintf(stderr,
	    "Time makes no sense... namelist must be wrong.\n");
	exit(1);
    }
    return(nintv);
}


/*
    Kread reads something from the kernel, given its nlist index.
*/
static void
kread(nlx, addr, size)
        int nlx;
        void *addr;
        size_t size;
{
        char *sym;
        
        if (nl[nlx].n_type == 0 || nl[nlx].n_value == 0) {
                sym = nl[nlx].n_name;
                if (*sym == '_')
                        ++sym;
                (void)fprintf(stderr,
                    "xpermon++: symbol %s not defined\n", sym);
                exit(1);
        }
        if (kvm_read(kd, nl[nlx].n_value, addr, size) != size) {
                sym = nl[nlx].n_name;
                if (*sym == '_')
                       ++sym;
                (void)fprintf(stderr, "xperfmon++: %s: %s\n", sym, kvm_geterr(kd));
                exit(1);
        }
}

/*
 * get_swapspace is based on a program called swapinfo written
 * by Kevin Lahey <kml@rokkaku.atl.ga.us>.
 */
int
get_swapspace()
{
	char *header;
	int hlen, nswap, nswdev, dmmax;
	int i, div, avail, nfree, npfree, used;
	struct swdevt *sw;
	long blocksize, *perdev;
	struct rlist head;
#if __FreeBSD_version >= 220000
        struct rlisthdr swaplist;
        struct rlist *swapptr;
#else
	struct rlist *swaplist;
#endif
	u_long ptr;
	kread(VM_NSWAP, &nswap, sizeof(nswap));
	kread(VM_NSWDEV, &nswdev, sizeof(nswdev));
	kread(VM_DMMAX, &dmmax, sizeof(dmmax));
	kread(VM_SWAPLIST, &swaplist, sizeof(swaplist));
	if ((sw = malloc(nswdev * sizeof(*sw))) == NULL ||
	    (perdev = malloc(nswdev * sizeof(*perdev))) == NULL)
		err(1, "xperfmon++ malloc in get_swapspace");
	kread(VM_SWDEVT, &ptr, sizeof(ptr));
	kvm_read(kd, ptr, sw, nswdev * sizeof(*sw));
	/* Count up swap space. */
	nfree = 0;
	memset(perdev, 0, nswdev * sizeof(*perdev));
#if __FreeBSD_version >= 220000
	swapptr = swaplist.rlh_list;
	while (swapptr) {
#else
	while (swaplist) {
#endif
		int	top, bottom, next_block;
#if __FreeBSD_version >= 220000
		kvm_read(kd, (u_long)swapptr, &head, sizeof(struct rlist));
#else
		kvm_read(kd, (u_long)swaplist, &head, sizeof(struct rlist));
#endif
		top = head.rl_end;
		bottom = head.rl_start;

		nfree += top - bottom + 1;

		/*
		 * Swap space is split up among the configured disks.
		 *
		 * For interleaved swap devices, the first dmmax blocks
		 * of swap space some from the first disk, the next dmmax
		 * blocks from the next, and so on up to nswap blocks.
		 *
		 * The list of free space joins adjacent free blocks,
		 * ignoring device boundries.  If we want to keep track
		 * of this information per device, we'll just have to
		 * extract it ourselves.
		 */
		while (top / dmmax != bottom / dmmax) {
			next_block = ((bottom + dmmax) / dmmax);
			perdev[(bottom / dmmax) % nswdev] +=
				next_block * dmmax - bottom;
			bottom = next_block * dmmax;
		}
		perdev[(bottom / dmmax) % nswdev] +=
			top - bottom + 1;
#if __FreeBSD_version >= 220000
		swapptr = head.rl_next;
#else
		swaplist = head.rl_next;
#endif
        }

	header = getbsize(&hlen, &blocksize);
	div = blocksize / 512;
	avail = npfree = 0;
	for (i = 0; i < nswdev; i++) {
		int xsize, xfree;

		/*
		 * Don't report statistics for partitions which have not
		 * yet been activated via swapon(8).
		 */
		if (!(sw[i].sw_flags & SW_FREED))
			continue;

		/* The first dmmax is never allocated to avoid trashing of
		 * disklabels
		 */
		xsize = sw[i].sw_nblks - dmmax;
		xfree = perdev[i];
		used = xsize - xfree;
		npfree++;
		avail += xsize;
	}

	/*
	 * If only one partition has been set up via swapon(8), we don't
	 * need to bother with totals.
	 */
	used = avail - nfree;

	free(perdev);
	free(sw);
	return((100*nfree)/avail);   /* return free swap in percent */
}
