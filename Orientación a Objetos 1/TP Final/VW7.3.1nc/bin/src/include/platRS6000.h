/* SccsId is  @(#)platRS6000.h	58.10 04/06/05 */
/************************************************************************
 * File: platRS6000.h
 *
 * This file contains the platform-dependent definitions for the IBM
 * RS6000 workstation.
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

#define defaultMappedPermSpaceBase ((quantum *)0x30000000)

#define pdFPUType() 1
#define DOUBLES_ALIGNED

#define GlueProc "glueRS6000.h"
#define indirectFunctionPointers 1

#define sc_pc sc_jmpbuf.jmp_context.iar
#define sc_gr sc_jmpbuf.jmp_context.gpr

/* I/O defines */
#define BSD 1
#if platform == platRS6000
#	define PLAT_OSNAME "unix bsd ibm rs6000powerPC aix"
#else
#	define PLAT_OSNAME "unix bsd ibm rs6000power2 aix"
#endif
#define HaveWriteSigiosOnDisplayConnection TRUE
#define SOCKLEN_SIZE_T size_t

#if !defined(HAS_64_BIT_ARITHMETIC)
#	define HAS_64_BIT_ARITHMETIC 1
#endif
#if !defined(assembly) && HAS_64_BIT_ARITHMETIC
typedef long long longlong;
typedef unsigned long long ulonglong;
#endif

#if 0 /* we assume this is no longer a problem with the v6 compiler */
# ifndef assembly
/*
 * override the arithemetic macros because the C preprocessor does not
 * follow the same rule as the compiled code.
 */
#	define divTrunc(dividend, divisor) \
	  (((oopInt)(dividend)) / ((oopInt)(divisor)))

#	define rem(dividend, divisor, scratch ) \
		((oopInt)(dividend) % (oopInt)(divisor))

#	define divFloor(dividend, divisor) \
	  (((dividend ^ divisor) & signBitMask) ? \
	    ((dividend & signBitMask) ? \
	      (((oopInt)(dividend)-((oopInt)(divisor)-1))/(oopInt)(divisor)): \
	      (((oopInt)(dividend)-((oopInt)(divisor)+1))/(oopInt)(divisor))):\
	    (oopInt)(dividend) / (oopInt)(divisor))

#	define mod(dividend, divisor, scratch) \
		(((dividend ^ divisor) & signBitMask) ? \
			((scratch = (oopInt)(dividend)%(oopInt)(divisor)) != 0 ? \
				scratch + (oopInt)(divisor) : \
				0) : \
			(oopInt)(dividend) % (oopInt)(divisor))

# endif
# define ASSERT_COMPILER_BUG 1
#endif /* 0 */
