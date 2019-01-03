/* SccsId is  @(#)platMac.h	58.10	04/06/05 */
/************************************************************************
 * File: platMac.h
 *
 * This file contains the platform-dependent definitions for the Macintosh II
 * on Motorola 68k processors.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define LEFT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define HaveCleanSignals TRUE
#define CanSmashRegisters FALSE
#define HaveLimitRegister TRUE

#define bytesInFreeZone (0 * 1024)  /* Mac's pdMoreMemory does this and more */
#define bytesInLargeObjectZone (500 * 1024)

#define GlueProc "glue68kMac.h"

#define PLATFORM_HAS_NO_DYNAMIC_LINK 1 /* well, so far... */

#define pdStartLongComp(n) 0 /* These are no-ops on MacOS */
#define pdFinishLongComp() 0

#ifndef assembly
int pdFPUType();  /* Prototype for function in macMain.c */
/*
 * override the arithemetic macros because the C preprocessor does not
 * follow the same rule as the compiled code.
 */
#define arithRShift(value, shiftWidth) (((oopInt) (value)) >> shiftWidth)
#define divTrunc(dividend, divisor) (((oopInt)(dividend)) / ((oopInt)(divisor)))
#define rem(dividend, divisor, scratch) ((oopInt)(dividend) % (oopInt)(divisor))

#define divFloor(dividend, divisor) \
	  (((dividend ^ divisor) & signBitMask) \
	    ? ((dividend & signBitMask) \
	      ? (((oopInt)(dividend)-((oopInt)(divisor)-1))/(oopInt)(divisor)) \
	      : (((oopInt)(dividend)-((oopInt)(divisor)+1))/(oopInt)(divisor))) \
	    : (oopInt)(dividend) / (oopInt)(divisor))

#define mod(dividend, divisor, scratch) \
		(((dividend ^ divisor) & signBitMask) \
			? ((scratch = (oopInt)(dividend)%(oopInt)(divisor)) != 0 \
				? scratch + (oopInt)(divisor) \
				: 0) \
			: (oopInt)(dividend) % (oopInt)(divisor))
#endif
