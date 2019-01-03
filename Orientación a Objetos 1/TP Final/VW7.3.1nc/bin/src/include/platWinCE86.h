/* SccsId is @(#)platWinCE86.h	58.10 04/06/05 */
/************************************************************************
 * File: platWinCE86.h
 *
 * This file contains the platform-dependent definitions for 
 * running Windows CE .NET on an Intel x86.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define OE_IS_UNICODE 1

#define RIGHT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define HaveCleanSignals  TRUE /* Use threads to avoid polling. */
#define CanSmashRegisters FALSE
#define HaveLimitRegister FALSE

#define GlueProc "glueNT86.h"

/*
 * On WinCE address space must be reserved in the initial alloc because later
 * attempts to grow memory fail.  So set the default headroom to four megabytes.
 */
#define defaulOldSpaceHeadroomSlots (1 * 1024 * 1024)

/* Microsoft state in the Developer Network documentation not to use
 * CreateThread and ExitThread if a thread uses libc.  But the standard
 * documentation with VisualC++ is mute on the topic.  According to the
 * Developer Network CD doing so results in a memory leak (see _ptiddata
 * in the VC++ crt source).  But WinCE doesn't have the C lib variants.
 */
#define USE_CRT_THREAD_FUNCS 0
#define OurCreateThread(ss,sa,p,cf,pt) CreateThread(0,ss,sa,p,cf,pt)
#define OurExitThread(rv) ExitThread(rv)
#define OurCreateThreadName "CreateThread"

#define OLE_COM 1

#define pdStartLongComp(n) 0 /* These are no-ops on NT */
#define pdFinishLongComp() 0

/* Float errors cause a signal (but only on Windows 3.1) */
#ifndef FIRENZE
#   define FPUSIGNAL
#endif

/* The following instruction resets the floating-point unit to the desired
 * initial state which is necessary for correct detection of exceptions in
 * floating-point primitives.  The 80x87 or Pentium FPU will not generate
 * a NaN for an illegal operation such as a divide-by-zero if the exception
 * bit corresponding to that exception is already set in the FPU status word.
 * So to ensure NaNs are produced it is necessary to clear the exception bits
 * before any floating-point operation.  This is because e.g. external code
 * might leave exception bits set in the status word.
 * Implementing it as a single instruction is the fastest approach.
 */
#define NoWaitFInit 1
#if NoWaitFInit
#	define pdClearFP _asm { fnclex }
#else
#	define pdClearFP _asm { fclex }
#endif

#if !defined(PLATFORM_SUPPORTS_64_BITS)
# define PLATFORM_SUPPORTS_64_BITS	1
# define HAS_64_BIT_ARITHMETIC		1
#endif
#ifndef assembly
# if HAS_64_BIT_ARITHMETIC
typedef __int64 longlong;
typedef unsigned __int64 ulonglong;
# endif

/* c library substitutes and renamings; why rename them in the first place? */
#define swab(a,b,c) _swab(a,b,c)
#define strdup(a) _strdup(a)
extern FILE *tmpfile(void);
#endif

#define Has1616Pointers 0 /* We won't support 16-bit code on WinCE */
#define CHECKMAP_CALLING_CONVENTION	__fastcall
#define charBitFieldQualifier char
#define SETTABLE_PRIORITY_CLASS 0
#define OENSFMT "%hs" /* %s differs from ANSI standard interpretation */
