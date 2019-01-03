/* SccsId is  @(#)platSgi.h	58.10 04/06/05 */
/************************************************************************
 * File: platSGI.h	
 * 
 * HEEG:
 * This file contains the platform-dependent definitions for the SGI
 * IRIS MIPS workstation.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define LEFT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define HaveCleanSignals TRUE
#define CanSmashRegisters TRUE
#define HaveLimitRegister TRUE

#define bytesInNMethodZone (1152 * 1024)

/* It looks like PP does at present not really support oldBelowPerm,
 * so the defaultMappedPermSpaceBase is not used in vw2.5.2
 * Otherwise it should be coordinated with USE_MMAP_HINT.
 */
#define defaultMappedPermSpaceBase ((quantum *)0x36d10000)
#define USE_MMAP_HINT ((quantum *)0x30000000L)

/*
 * PLATFORM_SIGNAL_HANDLER defined for svr4Sig.c to enable use of a stack
 * limit register.  FPUSIGHNAL to get SIGFPE generated on floating point
 * errors.
 */
#define PLATFORM_SIGNAL_HANDLER
#define FPUSIGNAL
#define pdFPUType() 1

#define GlueProc "glueMIPS.h"
#define bigEndian 1
#define rtLinkage 1 /* ncode needs linkage between NCode and glue for sends */

/* I/O defines */
#define PLAT_OSNAME "unix sysV irix 6.x"

#define USE_JMPBUF 1	/* exMessage.c (callbacks) */
#define USE_TERMIO 1
#define USV 1
#define USVR4 1

#define HaveWriteSigiosOnDisplayConnection TRUE

#ifndef bzero
#	define bzero(s, n) memset((s), 0, (n))
#endif

#define SC_PC uc_mcontext.gregs[CTX_EPC]
#define SC_LIMIT uc_mcontext.gregs[CTX_V1]
#define SC_CAUSE uc_mcontext.gregs[CTX_CAUSE]


#define HAS_64_BIT_ARITHMETIC 1

#ifndef assembly /* avoid trouble in glue.h */

#include <sys/types.h>

typedef long long longlong;
typedef unsigned long long ulonglong;
/*
 * SOCKLEN_SIZE_T should be size_t but makefile compilation environment
 * defines (XOPEN, POSIX etc) are not right yet.
 */
#define SOCKLEN_SIZE_T int /* for unxSock.c */

/* Depending on the architecture we're compiling for, there
 * are some differences:
 * mips1: trad. 32 bit code.
 * mips2: trad. 32 bit code, but
 *        - load delays need not be filled by compiler
 *        - doubles are fetched and stored as 64 bit data and
 *          therefore must be properly aligned.
 * mips3: 64 bit instructions available, all registers are 64 bit.
 *        At the moment only experimental.
 */
#if _MIPS_ISA != _MIPS_ISA_MIPS1
#	define archMIPS2 1		/* avoid nops in load delay slots */
#	define DOUBLES_ALIGNED
#else
	extern int archMIPS2;		/* avoid nops in load delay slots */
#endif

/* prepare for experimental true color visual */
extern int useTrueColorVisual;

#endif /* !assembly */
