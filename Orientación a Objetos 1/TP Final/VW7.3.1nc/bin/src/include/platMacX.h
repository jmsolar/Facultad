/* SccsId is  @(#)platMacX.h	58.10  04/06/05 */
/************************************************************************
 * File: platMacX.h
 *
 * This file contains the platform-dependent definitions for the Mac OS X
 * PowerMacintosh platform.
 *
 *	Copyright (C) 2000
 *	Georg Heeg Objektorientierte Systeme, Dortmund, Germany.
 *	Cincom Systems, Inc.  Santa Clara, California.
 *	All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define LEFT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define PLATFORM_SUPPORTS_64_BITS 1
#define HAS_64_BIT_ARITHMETIC 1
#ifndef assembly
typedef long long longlong;
typedef unsigned long long ulonglong;
#endif

#define HaveCleanSignals TRUE	/* FALSE for polling */
#define CanSmashRegisters FALSE
#define HaveLimitRegister TRUE

#define bytesInNMethodZone (1152 * 1024)
#define bytesInFreeZone (0 * 1024)   /* Mac's pdMoreMemory does this and more */

#define GlueProc "glueMacX.h"
#define indirectFunctionPointers 0

#define PLAT_OSNAME "unix bsd apple Power MacOSX"

#define pdFPUType() 1
#define sc_pc sc_ir
/* #define DOUBLES_ALIGNED NO - RALF 010927 */
#define MAXWAITMILLISECONDS 500

#ifndef assembly
/*
 * override the arithemetic macros because the C preprocessor does not
 * follow the same rule as the compiled code.
 */
#define arithRShift(value, shiftWidth) \
		(((oopInt) (value)) >> shiftWidth)
#define divTrunc(dividend, divisor) \
	  (((oopInt)(dividend)) / ((oopInt)(divisor)))

#define rem(dividend, divisor, scratch ) \
		((oopInt)(dividend) % (oopInt)(divisor))

#define divFloor(dividend, divisor) \
	  (((dividend ^ divisor) & signBitMask) ? \
	    ((dividend & signBitMask) ? \
	      (((oopInt)(dividend)-((oopInt)(divisor)-1))/(oopInt)(divisor)): \
	      (((oopInt)(dividend)-((oopInt)(divisor)+1))/(oopInt)(divisor))):\
	    (oopInt)(dividend) / (oopInt)(divisor))

#define mod(dividend, divisor, scratch) \
		(((dividend ^ divisor) & signBitMask) ? \
			((scratch = (oopInt)(dividend)%(oopInt)(divisor)) != 0 ? \
				scratch + (oopInt)(divisor) : \
				0) : \
			(oopInt)(dividend) % (oopInt)(divisor))

#endif
