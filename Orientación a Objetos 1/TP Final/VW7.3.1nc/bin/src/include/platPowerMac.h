/* SccsId is  @(#)platPowerMac.h	58.10  04/06/05 */
/************************************************************************
 * File: platPowerMac.h
 *
 * This file contains the platform-dependent definitions for the PowerMacintosh
 * on PowerPC processors.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define LEFT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

#define HaveCleanSignals TRUE	/* FALSE for polling */
#define CanSmashRegisters FALSE
#define HaveLimitRegister TRUE

#define bytesInFreeZone (0 * 1024)   /* Mac's pdMoreMemory does this and more */
#define bytesInNMethodZone (1152 * 1024)

#define GlueProc "gluePowerMac.h"
#define indirectFunctionPointers 1

#define pdFPUType() 1
#define DOUBLES_ALIGNED

#define pdStartLongComp(n) 0 /* These are no-ops on MacOS */
#define pdFinishLongComp() 0

#if _LONG_LONG
	/* MPW's MrC provides a long long type and defines _LONG_LONG as 1 if it is
	 * available.
	 */
#	define HAS_64_BIT_ARITHMETIC 1
#	ifndef assembly
typedef long long longlong;
typedef unsigned long long ulonglong;
#	endif
#endif

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
