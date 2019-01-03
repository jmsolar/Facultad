/* SccsId is  @(#)floatIEEE.h	58.10 04/06/05 */
/************************************************************************
 * File:	floatIEEE.h
 *
 * This file contains the floating-point definitions for a standard IEEE
 * system.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define floatFormatType floatFormatIEEECode

/* IEEE Floating point definitions
 *
 * A single-precision float is of the form seeeeeeeefffffffffffffffffffffff;
 * where "s" is a one-bit sign bit of the fractional part, "eeeeeeee" is the
 * exponent, an eight-bit unsigned binary integer (with an implied bias of 127),
 * and "fffffffffffffffffffffff" is a twenty three-bit fraction, which, when
 * incremented by 1, becomes the mantissa for this floating-point value.
 * The mantissa is in the range [1.0...2.0).
 * The value of the float is mantissa * (2 raisedTo: (exponent - 127)).
 *
 * A double-precision float (or "double") is of the form
 * seeeeeeeeeeedddddddddddddddddddddddddddddddddddddddddddddddddddd; where "s"
 * is a one-bit sign bit of the fractional part, "eeeeeeeeeee" is the exponent,
 * an eleven-bit unsigned binary integer (with an implied bias of 1023), and
 * "dddddddddddddddddddddddddddddddddddddddddddddddddddd" is a fifty two-bit
 * fraction, which, when incremented by 1, becomes the mantissa for this
 * floating-point value.  The mantissa is in the range [1.0...2.0).
 * The value of the double is mantissa * (2 raisedTo: (exponent - 1023)).
 */
#define exponentBias 127				/*  bias of exponent for floats */
#define floatSignMask 0x80000000L
#define fExponentMask 0x7f800000L		/* float exponent mask */
#define fExponentMaskShifted 0xFFL		/* exponent mask shifted by offset */
#define bitsFloatData 23				/* bit size of float mantissa */
#define fExponentOffset 23				/* lsb of float exponent */
#define doubleBias 1023L				/* bias of exponent for doubles */
#define bitsDoubleData 53				/* bit size of double mantissa */
#define dExponentMask 0x7FF00000L		/* double half-word exponent mask */
#define dExponentOffset 20				/* lsb of double half-word exponent */
#define dExpOffset64 52L				/* lsb of double 64-bit-word exponent */
#define dExponentMaskShifted 0x7FFL		/* mask shifted by dExponentOffset */
#define dNanAsInt {0x7fffffff, 0xffffffff}
#define numDblExpBits 11				/* number of bits in double exponent */

/*
 * floatIsInfOrNaN(num) returns TRUE if num equals NaN or positive or
 * negative infinity, FALSE otherwise. Note that "num" must be an
 * lvalue that contains a single-precision "float."
 */
#define floatIsInfOrNaN(f)  (fExponentMask == (*(q32 *)&(f) & fExponentMask))

/*
 * doubleIsInfOrNaN(num) returns TRUE if num equals NaN or positive or
 * negative infinity, FALSE otherwise. Note that "num" must be an
 * lvalue that contains a double-precision "double" float.
 */

#if bigEndian
# define doubleIsInfOrNaN(d) (dExponentMask == (*(q32 *)&(d) & dExponentMask))
#else
# define doubleIsInfOrNaN(d) (dExponentMask == (*((q32 *)&(d)+1) & dExponentMask))
#endif

#define floatGetExponent(f) ((int)((*(q32 *)&(f) >> fExponentOffset) \
									& fExponentMaskShifted) - exponentBias)
#define rawFloatGetExponent(aq32) ((int)(((aq32) >> fExponentOffset) \
									& fExponentMaskShifted) - exponentBias)
#define rawFloatIsZero(aq32) (((q32)(aq32) << 1) == 0)
#if 1
# if bigEndian
#	define doubleGetExponent(d) \
        (((unsigned)(*(unsigned char*)&d & 127) << 4 ) + \
         ((unsigned)(*((unsigned char*)&d+1) & 240) >> 4 ) - \
         doubleBias)
# else
#	define doubleGetExponent(d) \
        (((unsigned)(*((unsigned char*)&d+7) & 127) << 4) + \
         ((unsigned)(*((unsigned char*)&d+6) & 240) >> 4) - \
         doubleBias)
# endif
#elif 0
	/* the following should work but at least gcc 3.0.3 generates invalid code
	 * for asSmallInt(doubleGetExponent(d)) on x86.  So we keep the klunkier
	 * but more reliably compiled version above.  Sigh.
	 */
# if bigEndian
#	define doubleGetExponent(d) (((*(sq32 *)&(d) >> dExponentOffset) & dExponentMaskShifted) - doubleBias)
# else
#	define doubleGetExponent(d) ((((*(sq32 *)&(d)+1) >> dExponentOffset) & dExponentMaskShifted) - doubleBias)
# endif
#else
	/* the following should also work but at least gcc 3.0.3 generates invalid
	 * code for asSmallInt(doubleGetExponent(d)) on x86.  So we keep the
	 * klunkier but more reliably compiled version above.  Sigh.
	 */
# if bigEndian
#	define doubleGetExponent(d) (((*(sq32 *)&(d) & dExponentMask) >> dExponentOffset) - doubleBias)
# else
#	define doubleGetExponent(d) (((*((sq32 *)&(d)+1) & dExponentMask) >> dExponentOffset) - doubleBias)
# endif
#endif
#if HAS_64_BIT_ARITHMETIC
# define rawDoubleGetExponent(aq64) ((long)(((aq64) >> dExpOffset64) \
									& dExponentMaskShifted) - doubleBias)
# define rawDoubleIsZero(aq64) (((q64)(aq64) << 1) == 0)
#else
# error "implementation assumes 64-bit arithmetic which is available on all production vw7 platforms"
#endif

/*
 * Macro to unpack single-precision floating point number in mantissa
 * m[31]=sign, m[30:23]=expt, m[22:0]=mantissa.
 * Return mantissa(32)=mantissa, exponent(8)=exponent.
 */
#define unpackFloat( mantissa, exponent ) \
do{ exponent = (((q32) mantissa >> 23) & 0xff) - exponentBias; \
	mantissa <<= 8; \
	mantissa |= 0x80000000L; \
} while(0)

/* reverse unpackFloat; leaving result in mantissa */
#define packFloat(mantissa, exponent) \
do{ mantissa &= 0x7fffffffL; \
	mantissa >>= 8; \
	mantissa += (q32)((exponent + exponentBias) & 0xff) << 23; \
} while(0)



/*
 * Definition of error semantics.  In the original Smalltalk-80 specification
 * floating point primitives fail if they compute an invalid result, where
 * invalid is either infinity or a NaN.  But the ANSI specification allows an
 * implementation to conform to the ISO/IEC specification for mathematical
 * operations, i.e. it allows the implementation to answer the infinities and
 * NaNs.  Doing so is advantageous both for performance and interoperability
 * with other languages as these may yield infinities or NaNs through the
 * external interface.
 *
 * If IEEE_INF_NAN is non-zero then the engine will compile such that
 * floating-point primitives will answer infinities and NaNs.  If IEEE_INF_NAN
 * if zero and ST80_INF_NAN is non-zero then the engine will compile such that
 * floating-point primitives will fail rather than answer infinities and NaNs.
 * If both IEEE_INF_NAN and ST80_INF_NAN are zero then the flag st80InfNaN
 * determines whether to fail as for ST80_INF_NAN or answer infinities and NaNs
 * as for IEEE_INF_NAN.
 */

#if IEEE_INF_NAN
# define floatIsIllegal(f) FALSE
# define doubleIsIllegal(d) FALSE
# define floatPrimitivesFailOnError FALSE
#elif ST80_INF_NAN
# define floatIsIllegal(f) floatIsInfOrNaN(f)
# define doubleIsIllegal(d) doubleIsInfOrNaN(d)
# define floatPrimitivesFailOnError TRUE
#else
# ifndef assembly
extern bool IEEEInfNaN;
# endif
# define floatIsIllegal(f) (!IEEEInfNaN && floatIsInfOrNaN(f))
# define doubleIsIllegal(d) (!IEEEInfNaN && doubleIsInfOrNaN(d))
# define floatPrimitivesFailOnError (!IEEEInfNaN)
#endif

/*
 * Sigh; we'd like to define these in terms of sizeof but sizeof is a compiler
 * notion, not a preprocessor notion and we need the sizes in the preprocessor.
 * Hence the assert to check the defines agree with the sizes.  We also ensure
 * that a double is always a multiple of oopSized and that a float is oopSized
 * except in the 64-bit system.
 */
#define bytesInFloatData 4
#define bytesInDoubleData 8
#define assertGoodFloatSizes assert(bytesInFloatData == sizeof(float)    \
								 && bytesInDoubleData == sizeof(double)   \
								 && (bytesInDoubleData % bytesInOop) == 0  \
								 && (	bytesInFloatData < bytesInOop       \
									 || (bytesInFloatData % bytesInOop) == 0))

#if IMMUTABILITY
# if bytesInFloatData < bytesInOop
#  define allocFloat(floatOop) tagAllocImmutableNonPtrObj(floatOop,floatClassX,bytesInFloatData)
# else
#  define allocFloat(floatOop) tagAllocOopSizedImmutableNonPtrObj(floatOop,floatClassX,bytesInFloatData)
#endif
# define allocDouble(doubleOop) tagAllocOopSizedImmutableNonPtrObj(doubleOop,doubleClassX,bytesInDoubleData)
#else
# if bytesInFloatData < bytesInOop
#  define allocFloat(floatOop) tagAllocNonPtrObj(floatOop,floatClassX,bytesInFloatData)
# else
#  define allocFloat(floatOop) tagAllocOopSizedNonPtrObj(floatOop,floatClassX,bytesInFloatData)
# endif
# define allocDouble(doubleOop) tagAllocOopSizedNonPtrObj(doubleOop,doubleClassX,bytesInDoubleData)
#endif

/*
 * To save time indexing the sysOopRegistry we provide macros that take the
 * class Double or class Float objects directly.  These are not useful if using
 * class tags.
 */
#if ObjectsHaveDirectClassPointer
# if IMMUTABILITY
#  define allocDoubleClass(doubleOop, doubleClass) \
	allocOopSizedImmutableNonPtrObj(doubleOop, doubleClass, bytesInDoubleData)
#  if bytesInFloatData < bytesInOop
#	define allocFloatClass(floatOop, floatClass) \
		allocImmutableNonPtrObj(floatOop, floatClass, bytesInFloatData)
#  else
#	define allocFloatClass(floatOop, floatClass) \
		allocOopSizedImmutableNonPtrObj(floatOop, floatClass, bytesInFloatData)
#  endif
# else /* IMMUTABILITY */
# define allocDoubleClass(doubleOop, doubleClass) \
	allocOopSizedNonPtrObj(doubleOop, doubleClass, bytesInDoubleData)
#  if bytesInFloatData < bytesInOop
#	define allocFloatClass(floatOop, floatClass) \
		allocNonPtrObj(floatOop, floatClass, bytesInFloatData)
#  else
#	define allocFloatClass(floatOop, floatClass) \
		allocOopSizedNonPtrObj(floatOop, floatClass, bytesInFloatData)
#  endif
# endif /* IMMUTABILITY */
#else /* ObjectsHaveDirectClassPointer */
# define allocDoubleClass(doubleOop, doubleClass) allocDouble(doubleOop)
# define allocFloatClass(floatOop, floatClass) allocFloat(floatOop)
#endif /* ObjectsHaveDirectClassPointer */

/*
 * Representation for immediate doubles.  These occupy just less than the middle
 * 1/8th of the double range, except for zero, whch takes 1/2048th of the range.
 * Only valid in the 64-bit implementation.
 * The encoded form has a low sign which allows for faster encode/decode:
 *
 *		[8 exponent subset bits][52 mantissa bits ][1 sign bit][3 tag bits]
 *
 * Encode/decode of non-zero values in machine code looks like:
 *
 *	Decode:					[8expsubset][52mantissa][1s][3tags]
 *	shift away tags:		[ 000 ][8expsubset][52mantissa][1s]
 *	add exponent offset:	[   11 exponent   ][52mantissa][1s]
 *	rot sign:		 		[1s][   11 exponent   ][52mantissa]
 *
 *	Encode:					[1s][   11 exponent   ][52mantissa]
 *	rot sign:				[   11 exponent   ][52mantissa][1s]
 *	sub exponent offset:	[ 000 ][8expsubset][52mantissa][1s]
 *	shift:					[8expsubset][52mantissa][1s][ 000 ]
 *	or tags:				[8expsubset][52mantissa][1s][3tags]
 *
 * but is slower in C because
 * a) there is no rotate, and
 * b) raw conversion between quadword and double must move bits through memory.
 */
#define immDblSignMask (1L<<numTagBits)
#define immDblSignShift (bitsInOop-numTagBits-1)
#define immDblNegZero (dblTag + immDblSignMask)
#define immDblMaxExp ((1<<(numDblExpBits-numTagBits)))
#define immDblExpLo (doubleBias-(immDblMaxExp/2)+1)
#define immDblExpHi (doubleBias+(immDblMaxExp/2))
#define immDblExpOffset (immDblExpLo << dExpOffset64)
#define immDblIsZero(anOop) (oopBits(anOop) <= immDblNegZero)

#define doubleGetExponentFromRaw(aq64) (((aq64)>>dExpOffset64)&dExponentMaskShifted)

#define immDblEncodeNonZero(aq64) ((((aq64)>>immDblSignShift)&immDblSignMask)  \
								| (((aq64)-immDblExpOffset)<<(numTagBits+1))\
								| dblTag)

/* WARNING!  This is a "cheap" encode that does not preserve -0.0d */
/* Use only in cases where its ok to map -0.0d to 0.0d */
#define immDblEncode(aq64) ((aq64) << 1 ? immDblEncodeNonZero(aq64) : dblTag)

#define immDblDecodeNonZero(o) (((oopBits(o)&immDblSignMask)<<immDblSignShift)\
							|((oopBits(o)>>(numTagBits+1))+immDblExpOffset))

#define immDblDecode(oop) (immDblIsZero(oop) \
							? (oopBits(oop)&immDblSignMask)<<immDblSignShift \
							: immDblDecodeNonZero(oop))

#if HPS64
#	define returnImmediateDoubleIfPossible(dbl) do { \
		q64 rawDouble = *(q64 *)&(dbl); \
		q64 offsetExponent = ((q64)(rawDouble << 1) >> (1+dExpOffset64)) - immDblExpLo; \
		if (offsetExponent <= (immDblMaxExp - 1L)) \
			return (oop)immDblEncodeNonZero(rawDouble); \
		else if (!(rawDouble << 1)) /* ensure -0.0 is returned as -0.0 */ \
			return (oop)((rawDouble>>immDblSignShift) | dblTag); \
	} while (0)
#else
#	define returnImmediateDoubleIfPossible(dbl) 0
#endif
