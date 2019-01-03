/* SccsId is @(#)platLinuxPS2.h	58.10 04/06/05 */
/************************************************************************
 * File: platLinuxPS2.h
 *
 * This file contains the platform-dependent definitions for the I386 and
 * later running Linux 2.x or later.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define RIGHT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */
#define bigEndian 0		/* LinuxMIPSPS/2 is little-endian */	

#define HaveCleanSignals TRUE
#ifdef PLATFORM_SIGNAL_HANDLER
#   define CanSmashRegisters TRUE
#else
#   define CanSmashRegisters FALSE
#endif
#define HaveLimitRegister FALSE

#ifndef F_ULOCK
#	define F_ULOCK 0
#	define F_LOCK  1
#	define F_TLOCK 2
#	define F_TEST  3
#endif

/* This should be in the processor include file, but differences in
 * platform assembler syntax makes this a better place
 */
#define GlueProc "glueLinuxPS2.h"
#define bigEndian 0

#define FPUSIGNAL
#define pdFPUType() 1

#define SC_PC uc_mcontext.sc_pc
#define SC_CAUSE uc_mcontext.sc_cause

/* I/O defines */
#define PLAT_OSNAME "unix sysV MIPS linux"

/* Use sbrk for initial alloc to ensure permSpace is below any new old segs. */
#define MORE_MEMORY_USES_SBRK 1
#define USV 1
#define USVR4 1
/* To interoperate with Linux Threads the stack zone needs to be allocated
 * on the stack.
 */
#define ALLOCATE_STACKZONE_ON_C_STACK TRUE

#define HaveWriteSigiosOnDisplayConnection TRUE

/*
 ** Revisit this.  In later versions of the linux kernel (i.e., >=2.2.x)
 ** we will be able to use poll(2) but for now we must use select(2)
 ** since the emulation of poll via select appears to be flawed.  Here's
 ** an excerpt from man poll(2):
 **
 ** AVAILABILITY
 **     The poll() systemcall was introduced in Linux 2.1.23.  The
 **     poll()  library  call  was  introduced in libc 5.4.28 (and
 **     provides emulation using select if your  kernel  does  not
 **     have a poll syscall).
 */
#define USE_POLL_SYSCALL 0

/* This is to ensure $edi & $esi are saved/restored on callback. */
#define USE_JMPBUF 1

#if !defined(PLATFORM_SUPPORTS_64_BITS)
#	define PLATFORM_SUPPORTS_64_BITS 1
#endif
#define HAS_64_BIT_ARITHMETIC 1
#ifndef assembly
typedef long long longlong;
typedef unsigned long long ulonglong;
#endif
