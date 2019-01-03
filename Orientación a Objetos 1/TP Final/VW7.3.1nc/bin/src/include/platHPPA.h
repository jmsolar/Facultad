/* SccsId is  @(#)platHPPA.h	58.10 04/06/05 */
/************************************************************************
 * File: platHPPA.h
 *
 * This file contains the platform-dependent definitions for the HP
 * 700 series workstation with the PA RISC processor.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define LEFT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define HaveCleanSignals TRUE
#ifdef PLATFORM_SIGNAL_HANDLER
#	define CanSmashRegisters TRUE
#else
#	define CanSmashRegisters FALSE
#endif
#define HaveLimitRegister TRUE

#define bytesInNMethodZone (1152 * 1024)

#define defaultMappedPermSpaceBase ((quantum *)0x7ab00000)

#define DOUBLES_ALIGNED

/* This platform is problematic.  SIGIO is difficult to get delivered and
 * sometimes wakeups are lost.  So use polling and only sleep for 500 msecs.
 */
#define PSEUDOPOLL
#define MAXWAITMILLISECONDS 500

#define sc_pc sc_ctxt.sl.sl_ss.ss_narrow.ss_pcoq_head /* for usvSig.c */
#define SC_PC uc_mcontext.ss_narrow.ss_pcoq_head /* for svr4Sig.c */

#define GlueProc "glueHPPA.h"

#define pdFPUType() 1

/* I/O defines */
#define USV 0
#define HP_UX 1
#define PLAT_OSNAME "unix sysv hp 700 hp-ux"
#define USE_TERMIO 1
#define HaveWriteSigiosOnDisplayConnection FALSE
#define SHLIB_EXTENSION ".sl"

#if !defined(PLATFORM_SUPPORTS_64_BITS)
#   define PLATFORM_SUPPORTS_64_BITS 0
#endif
#define HAS_64_BIT_ARITHMETIC 1
#ifndef assembly
typedef long long longlong;
typedef unsigned long long ulonglong;
#endif
