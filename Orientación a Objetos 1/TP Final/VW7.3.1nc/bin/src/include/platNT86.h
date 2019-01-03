/* SccsId is @(#)platNT86.h	58.10 04/06/05 */
/************************************************************************
 * File: platNT86.h
 *
 * This file contains the platform-dependent definitions for the
 * NT 386.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define RIGHT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define HaveCleanSignals TRUE /* Use threads to avoid polling. */
#define CanSmashRegisters FALSE
#define HaveLimitRegister FALSE

#define GlueProc "glueNT86.h"

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
#	define setSaneFPUState() _asm { fnclex }
#else
#	define setSaneFPUState() _asm { fclex }
#endif
/* The old way instead of getting the external interface to set a sane FPU
 * state was to do so on every FPU operation.  Newer IA-32 processors such as
 * the Xeon have such poor f(n)clex performance that this isn't tennable any
 * more, even though its a much safer approach.
 */
#if !defined(setSaneFPUState)
# if NoWaitFInit
#	define pdClearFP _asm { fnclex }
# else
#	define pdClearFP _asm { fclex }
# endif
#endif

/* Microsoft state in the Developer Network documentation not to use
 * CreateThread and ExitThread if a thread uses libc.  But the standard
 * documentation with VisualC++ is mute on the topic.  According to the
 * Developer Network CD doing so results in a memory leak (see _ptiddata
 * in the VC++ crt source).
 */
#define USE_CRT_THREAD_FUNCS 1

# if USE_CRT_THREAD_FUNCS
#	define OurCreateThread(ss,sa,p,cf,pt) ((HANDLE)_beginthreadex(0,ss,sa,p,cf,pt))
#	define OurExitThread(rv) _endthreadex(rv)
#	define OurCreateThreadName "_beginthreadex"
#else
#	define OurCreateThread(ss,sa,p,cf,pt) CreateThread(0,ss,sa,p,cf,pt)
#	define OurExitThread(rv) ExitThread(rv)
#	define OurCreateThreadName "CreateThread"
#endif

#define OLE_COM 1

#define pdStartLongComp(n) 0 /* These are no-ops on NT */
#define pdFinishLongComp() 0

#if !defined(PLATFORM_SUPPORTS_64_BITS)
#	define PLATFORM_SUPPORTS_64_BITS 1
#	define HAS_64_BIT_ARITHMETIC 1
#endif
#ifndef assembly
#	if HAS_64_BIT_ARITHMETIC
typedef __int64 longlong;
typedef unsigned __int64 ulonglong;
#	endif
#endif

#if !defined(Has1616Pointers)
# define Has1616Pointers 1
#endif

#if defined(MSVC_VER)
/*
 * MSVC++ compiler work-arounds and enhancements.
 *
 * MSVC++ v5 (and possibly earlier versions) have a compiler bug that results
 * in floating-point unit stack over and underflows.  The following fp loop
	OEProfiler profile:
		[| ve fve se be |
		 ve := 178@182.
		 se := 536870911@390.
		 be := 16@162.
		 [fve := ve x asFloat@ve y asFloat. (fve / se * be) rounded] repeat]
 * will demonstrate the error fairly quickly, causing invalid primitive
 * failures.  Paradoxically the work-around is to disable the translated
 * floating-point primitives, hence the following define.
 * The problem is fixed in MSVC++ v6.
 *
 *  To ensure tight packing of structures one has to qualify <= 8 bit fields
 * with char.
 */
#	define NoTranslatedFloatPrims (MSVC_VER <= 5)
#	define CHECKMAP_CALLING_CONVENTION __fastcall
#	define charBitFieldQualifier char
#	define OENSFMT "%hs" /* %s differs from ANSI standard interpretation */
#endif

#define SHLIB_EXTENSION ".dll"
