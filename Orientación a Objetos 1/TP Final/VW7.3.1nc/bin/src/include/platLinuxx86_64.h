/* SccsId is @(#)platLinuxx86_64.h	58.10 04/06/05 */
/************************************************************************
 * File: platLinuxx86_64.h
 *
 * This file contains the platform-dependent definitions for the x86_64
 * in 64-bit mode running Linux 2.4.x or later.
 *
 *	Copyright (C) 2004 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define RIGHT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define HaveCleanSignals TRUE
#ifdef PLATFORM_SIGNAL_HANDLER
#   define CanSmashRegisters TRUE
#else
#   define CanSmashRegisters FALSE
#endif
#define HaveLimitRegister FALSE

#if !defined(UseEdenAllocRegister)
# define UseEdenAllocRegister FALSE
#endif
#if UseEdenAllocRegister && !defined(assembly)
register void *edenAllocAndLimitRegister asm("%r15");
#endif

/*
 * Use a 32-bit send cache even though this is a 64-bit platform.
 */
#define ThinSendCache 1

#ifndef F_ULOCK
#	define F_ULOCK 0
#	define F_LOCK  1
#	define F_TLOCK 2
#	define F_TEST  3
#endif

/* This should be in the processor include file, but differences in
 * platform assembler syntax makes this a better place
 */
#define GlueProc "glueLinuxx86_64.h"
/* This is potentially OS-specific and so does belong here.
 */
#define platcallc_h "linuxx86_64CallC.h"

#define pdFPUType() 1

/* The following instruction resets the floating-point unit to the desired
 * initial state which is necessary for correct detection of exceptions in
 * floating-point primitives.  The FPU won't generate a NaN for an illegal
 * operation such as a divide-by-zero if the exception bit corresponding to
 * that exception is already set in the FPU status word.  So to ensure NaNs
 * are produced it is necessary to clear the exception bits before any
 * floating-point operation.  This is because e.g. external code might leave
 * exception bits set in the status word.  We do this on re-entry to the system
 * after callouts or callbacks.
 * Implementing it as a single instruction is the fastest approach.
 */
#define setSaneFPUState() asm("fnclex")

/* define the context path to the PC register */
#if (__GLIBC__ == 2) && ( __GLIBC_MINOR__ < 2) && defined(EIP)
#	define SC_PC uc_mcontext.gregs[EIP]
#elif defined(REG_EIP)
#	define SC_PC uc_mcontext.gregs[REG_EIP]
#endif
#if !defined(OE_PROFILE)
# define OE_PROFILE 1
#endif

/* I/O defines */
#define PLAT_OSNAME "unix sysV x86_64 linux"

/* Use sbrk for initial alloc to ensure permSpace is below any new old segs. */
#define MORE_MEMORY_USES_SBRK 1
#define USV 1
#define USVR4 1
/* To interoperate with Linux Threads the stack zone needs to be allocated
 * on the stack.
 */
#define ALLOCATE_STACKZONE_ON_C_STACK TRUE

#define HaveWriteSigiosOnDisplayConnection TRUE

#define USE_POLL_SYSCALL 1

/* This is to ensure $edi & $esi are saved/restored on callback. */
#define USE_JMPBUF 1
