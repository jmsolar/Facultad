/* SccsId is  @(#)platSolaris.h	58.10 04/06/05 */
/************************************************************************
 * File: platSolaris.h
 *
 * This file contains the platform-dependent definitions for the sun4
 * run Solaris.
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

#define defaultMappedPermSpaceBase ((quantum *)0xef000000)

/* This should be in the processor include file, but differences in
 * platform assembler syntax makes this a better place
 */
#define GlueProc "glueSPARC.h"

#define pdFPUType() 1
#define DOUBLES_ALIGNED

/* define the context path to the PC and stackLimit register */
#define SC_PC uc_mcontext.gregs[REG_PC]
#define SC_LIMIT uc_mcontext.gregs[REG_G1]

/* I/O defines */
#define PLAT_OSNAME "unix sysV sun solaris"
#define USE_TERMIO 1
#define USV 1
#define USVR4 1

#define HaveWriteSigiosOnDisplayConnection TRUE

#if !defined(PLATFORM_SUPPORTS_64_BITS)
#	define PLATFORM_SUPPORTS_64_BITS 1
#endif
#if !defined(HAS_64_BIT_ARITHMETIC)
#	define HAS_64_BIT_ARITHMETIC 1
#endif
#if !defined(assembly) && HAS_64_BIT_ARITHMETIC
typedef long long longlong;
typedef unsigned long long ulonglong;
#endif
