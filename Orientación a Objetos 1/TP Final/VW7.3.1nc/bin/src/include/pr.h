/* SccsId is  @(#)pr.h	58.10 04/06/05 */
/************************************************************************
 * File: pr.h
 *
 * Contains definitions used by many of the primitive routines.  Also
 * has the primitives initialization routine.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#include "servRequest.h"

/* These macros may need definitions from stacks.h which needs frame.h */
/* Both frame.h and stacks.h are protected from multiple #include lines */

#define primFailedValue nonOop

/* longPrimReturn()
 *    This macro should be used in place of simply returning,
 * in any primitive that is long running.  The definition of long
 * running is not very well defined, but something that copies
 * more than 1K of data from point A to point B would
 * probably qualify.
 *
 *    The macro should be included only in primitives, and
 * not in support functions called by primitives.  It should
 * also not be called from a primitive that has been committed,
 * and the frame stabilized. For that, use longCommittedPrimReturn().
 *
 *    Note that this is only called in the success case of
 * the primitive.  The failure case should still be calling
 * primFailReturnWith().
 */
#define longPrimReturn(v) \
{ extern oop commitPrimitiveAndHandleRequests(oop);				\
		 oop value = (v);										\
	if (!anyRequests()) return value;							\
	return commitPrimitiveAndHandleRequests(value); 			\
}

/* longCommittedPrimReturn()
 *    This macro should be used in place of backToNcode(),
 * in any committed primitive that is long running.  The
 * definition of long running isn't fixed, but if the primitive
 * needed to be committed, it probably does enough work
 * to be called long-running.
 *
 *    The macro should be included only in primitives, and
 * not in support functions called by primitives.
 *
 *    Note that this is only called in the success case of
 * the primitive.  The failure case should still be calling
 * failCommittedPrimitive().
 */
#define longCommittedPrimReturn() \
{	if (anyRequests()) handleRequests();						\
	/* In case there's no reschedule requests */				\
	backToNcode();												\
	/*NOTREACHED*/												\
	return nonOop; /* to placate compiler */					\
}

/* NOTE: This macros require "stacks.h" to be included for the
 *       declaration of currentStack
 */
#define isCommittedPrimitive() (currentStack->primRcvr == nonOop)
#define setNotInPrimitiveAnyMore() (currentStack->primRcvr = nonOop)

#ifdef DEBUG
extern oop failPrimitive(oop, int, char *, int);
#else
extern oop failPrimitive(oop, int);
#endif
extern void handleRequests(void);
extern void backToNcode(void);
extern void backToNcodePop0(void);
extern void backToNcodePop1(void);
extern void backToNcodePop2(void);
extern void backToNcodePopping(void);
extern void backToNcodePopResult(void);


/* primFailReturnWithErrorCode
 *
 * Convert the argument, a C long datatype, into an error code that can be
 * returned as the value of a primitive when an error has occurred.
 */
#define primFailReturnWithErrorCode(oReceiver, lNumArgs, errorNumber, errorClass) \
	{\
	oop oErrorCode; \
	if (STLong(errorNumber, oErrorCode) == nonOop) \
		oErrorCode = PrimErrorAllocationFailed; \
	else oErrorCode = errorClass(oErrorCode); \
	primFailReturnWith(oReceiver, lNumArgs, oErrorCode); \
	}

#if defined(DEBUG)
# define primFailReturnWith(r, na, ec) return failPrimitive(ec, na, __FILE__, __LINE__)
# define primFailWith(na, ec)                 failPrimitive(ec, na, __FILE__, __LINE__)
#else
# define primFailReturnWith(r, na, ec) return failPrimitive(ec, na)
# define primFailWith(na, ec)                 failPrimitive(ec, na)
#endif
#define primFailReturn(r, na) primFailReturnWith(r, na, PrimErrorGenericError)

#define standardErrorCode(codeNumber) \
	objDataField(sysOop(errorCodeTableX), oop, codeNumber-1)

/* Primitive and external call error codes.  Although not all external error
 * codes are used we define them to help maintain the intended correspondence
 * between them.  An ExternalError of -N corresponds to standardErrorCode(N).
 */
#define PrimErrorNotImplemented			sysOop(nilOopX)
#define     PrimErrorGenericError		standardErrorCode(1)
#define ExternalErrorGenericError		((oopInt)asSmallInt(-1))
#define     PrimErrorAllocationFailed	standardErrorCode(2)
#define ExternalErrorAllocationFailed	((oopInt)asSmallInt(-2))
#define     PrimErrorMallocFailed		standardErrorCode(3)
#define ExternalErrorMallocFailed		((oopInt)asSmallInt(-3))
#define     PrimErrorBadArgument		standardErrorCode(4)
#define ExternalErrorBadArgument		((oopInt)asSmallInt(-4))
#define     PrimErrorBadReceiver		standardErrorCode(5)
#define ExternalErrorBadReceiver		((oopInt)asSmallInt(-5))
#define     PrimErrorInappropriate		standardErrorCode(6)
#define ExternalErrorInappropriate		((oopInt)asSmallInt(-6))
#define     PrimErrorInvalidIndex		standardErrorCode(7)
#define ExternalErrorInvalidIndex		((oopInt)asSmallInt(-7))
#define     PrimErrorWrongNumArgs		standardErrorCode(8)
#define ExternalErrorWrongNumArgs		((oopInt)asSmallInt(-8))
#define     PrimErrorTranslatorFailed	standardErrorCode(9)
#define ExternalErrorTranslatorFailed	((oopInt)asSmallInt(-9))
#define     PrimErrorIOError			standardErrorCode(10)
#define ExternalErrorIOError			((oopInt)asSmallInt(-10))
#define     PrimErrorNoMatch			standardErrorCode(11)
#define ExternalErrorNoMatch			((oopInt)asSmallInt(-11))
#define     PrimErrorNBAPIInternalError	standardErrorCode(12)
#define ExternalErrorNBAPIInternalError	((oopInt)asSmallInt(-12))
#define     PrimErrorUnsupported		standardErrorCode(13)
#define ExternalErrorUnsupported		((oopInt)asSmallInt(-13))
#define     PrimErrorBadHandle			standardErrorCode(14)
#define ExternalErrorBadHandle			((oopInt)asSmallInt(-14))
#define     PrimErrorNoThreadFound		standardErrorCode(15)
#define ExternalErrorNoThreadFound		((oopInt)asSmallInt(-15))
#define     PrimErrorUnattached			standardErrorCode(16)
#define ExternalErrorUnattached			((oopInt)asSmallInt(-16))
#define     PrimErrorOutOfThreads		standardErrorCode(17)
#define ExternalErrorOutOfThreads		((oopInt)asSmallInt(-17))
#define     PrimErrorExceptionRaised	standardErrorCode(18)
#define ExternalErrorExceptionRaised	((oopInt)asSmallInt(-18))
#define     PrimErrorHResultError		standardErrorCode(19)
#define ExternalErrorHResultError		((oopInt)asSmallInt(-19))
#define     PrimErrorInternalError		standardErrorCode(20)
#define ExternalErrorInternalError		((oopInt)asSmallInt(-20))
#define     PrimErrorExportFailed		standardErrorCode(21)
#define ExternalErrorExportFailed		((oopInt)asSmallInt(-21))
#define     PrimErrorImportFailed		standardErrorCode(22)
#define ExternalErrorImportFailed		((oopInt)asSmallInt(-22))
#define     PrimErrorPlatformError		standardErrorCode(23)
#define ExternalErrorPlatformError		((oopInt)asSmallInt(-23))
#define     PrimErrorNoModification		standardErrorCode(24)
#define ExternalErrorNoModification		((oopInt)asSmallInt(-24))
#define     PrimErrorUninitialized		standardErrorCode(25)
#define ExternalErrorUninitialized		((oopInt)asSmallInt(-25))
#define     PrimErrorBadVersion			standardErrorCode(26)
#define ExternalErrorBadVersion			((oopInt)asSmallInt(-26))
#define     PrimErrorClassTableFull			standardErrorCode(27)
#define ExternalErrorClassTableFull		((oopInt)asSmallInt(-27))

#define maximumPrimErrors 26


/* For the following macros, the argument MUST always be a
 *  valid oop.  For arguments that are indexes of some kind, they
 *  should be converted to SmallIntegers.
 */
#define primGenericError(err)	  cloneErrorWith(PrimErrorGenericError, err)
#define primAllocationFailed(s)	  cloneErrorWith(PrimErrorAllocationFailed, s)
#define primMallocFailed(err)	  cloneErrorWith(PrimErrorMallocFailed, err)
#define primBadArgument(argIndex) cloneErrorWith(PrimErrorBadArgument, argIndex)
#define primBadReceiver(arg)	  cloneErrorWith(PrimErrorBadReceiver, arg)
#define primInappropriate(arg)	  cloneErrorWith(PrimErrorInappropriate, arg)
#define primInvalidIndex(index)	  cloneErrorWith(PrimErrorInvalidIndex, index)
#define primWrongNumArgs(numArgs) cloneErrorWith(PrimErrorWrongNumArgs, numArgs)
#define primTranslatorFailed(err) cloneErrorWith(PrimErrorTranslatorFailed, err)
#define primIOError(err)		  cloneErrorWith(PrimErrorIOError, err)
#define primNoMatch(err)		  cloneErrorWith(PrimErrorNoMatch, err)
#define primNBAPIError(e)		  cloneErrorWith(PrimErrorNBAPIInternalError, e)
#define primPlatError(err)		  cloneErrorWith(PrimErrorPlatformError, err)

extern void initPrimitives(void);
extern void initFloatPrims(void);
extern void initDoublePrims(void);
extern void initArithmeticPrims(void);
extern void initLargeIntPrims(void);
extern void initUserPrimitives(void);
extern void initOEprotocol(void);
extern void initLinkRegistryPrimitives(void);

extern void addCPrimitive(unsigned, oop (*)(), int);
extern void addVarArgCPrimitive(unsigned, oop (*)());
extern void addVarArgCPrimitiveForRange(unsigned, unsigned, oop (*)());
extern void addUPrimitive(unsigned, oop (*)(), int);
extern void addVarArgUPrimitive(unsigned, oop (*)());

/* Defines for documenting obsolete/unimplemented but assigned primitives. */
#define obsoletePrimitive(n,f,na) 0
#define unimplementedPrimitive(n,f,na) 0

#if platform == platAOSF
#	pragma pointer_size (long)
#endif

#ifndef pdStartLongComp
# if LOADABLE_GUI
extern void (*pdStartLongComp)(memIndex);
# else
extern void pdStartLongComp(memIndex);
# endif
#endif
#ifndef pdFinishLongComp
# if LOADABLE_GUI
extern void (*pdFinishLongComp)(void);
# else
extern void pdFinishLongComp(void);
# endif
#endif
extern void pdBeginCritical(void);
extern void pdEndCritical(void);
extern void pdResetCritical(void);

#if platform == platAOSF
#	pragma pointer_size (short)
#endif

extern void commitPrimitive(oop);
extern void commitPrimitiveWithRestart(oop);
extern void asynchReCommitOrFailPrimitive(oop, oop, bool);
extern oop  topOfStack(oop);

extern oop cloneErrorWith(oop, oop);
extern oop cloneCallCError(oopInt *);

#define bytesInPointData (2 * bytesInOop)	/* for both prArithmetic & prIO */

/* isKindOf() tests whether an object is an instance of a class or one of the
 *   class's subclasses.
 */
extern bool isKindOf(oop, oop);
/* checks if the first arg (a class) is the same as or inherits from any
 * of the other 1, 2, 3 or 4 classes.
 */
extern bool inheritsFrom1(oop, oop);
extern bool inheritsFrom2(oop, oop, oop);
extern bool inheritsFrom3(oop, oop, oop, oop);
extern bool inheritsFrom4(oop, oop, oop, oop, oop);

/* Macro that short circuits the check for class membership.
 */
#define fastIsKindOf(ooop, cls)\
  ((!oopIsImm(ooop) && objClass(ooop) == (cls)) || isKindOf(ooop, cls))
#define isMemberOf(ooop, cls) (assert( (cls) != sysOop(smallIntegerClassX) \
									&& (cls) != sysOop(characterClassX)), \
								!oopIsImm(ooop) && objClass(ooop) == (cls))

/*
 * In direct class pointer systems platformStringClassX is a sysOop index,
 * but in class-tag systems platformStringClassX is a classTag.  Hence to
 * map to a class from platformStringClassX in either context one must use
 * classFromClassTag(classTagFromIndex(platformStringClassX)), which is
 * sysOop(platformStringClassX) under the class pointer regime, and a
 * class table lookup of platformStringClassX under the class-tag regime.
 */
extern DLUP_IMPORT(memIndex) platformStringClassX;
#define platformStringClass() classFromClassTag(classTagFromIndex(platformStringClassX))
#define platformStringClassTag() classTagFromIndex(platformStringClassX)
#if OE_IS_UNICODE
extern DLUP_IMPORT(bool) platformStringIsTwoByte;
#else
# define platformStringIsTwoByte FALSE
#endif

/* copyToCString -- Copy a Smalltalk string into a C storage space.
 *	Assume the C string is large enough to accomodate the string.
 *	If the Smalltalk string is not in the host's encoding, perform
 *	character translation.  Return a pointer to the C string, or
 *	NULL if the source was not of a known string class or if it
 *	contains a character that the host has no representation for.
 *
 */
extern char *copyToCString(oop, char *, memIndex);
extern char *copySubStringToC(oop, char *, memIndex);
extern bool  isValidPlatformString(oop);
extern bool  promoteToFixedSpace(oop);
extern bool  tryBecome(oop,oop);

/* tempCString() answers a new null-terminated C string for a Smalltalk string,
 * or 0 if storage for the new string could not be allocated.
 * Storage for the C string is allocated in object space and will
 * therefore be reclaimed by the memory manager.  The C string will
 * therefore only be valid until return to nmethod code or until a call-back.
 */
extern char *tempCString(oop);

/*
 * wchar_t versions of some of the above.
 */
#if OE_IS_UNICODE
extern wchar_t *copySubStringToU(oop, wchar_t *, memIndex);
extern wchar_t *copyToUString(oop, wchar_t *, memIndex);
extern wchar_t *tempUString(oop);
#endif

/* STString() answers a new Smalltalk string for a C string.
 */
#if platform == platAOSF
#	pragma pointer_size(long)
#endif
extern oop STStringWithSize(const char *, memIndex);
# if OE_IS_UNICODE
extern oop STTwoByteStringWithSize(const wchar_t *, memIndex);
# endif
#if platform == platAOSF
#	pragma pointer_size(short)
#endif

/* Now (posix era) strlen(NULL) seg faults, so guard against passing null */
#define STString(s)		   ((s) ? STStringWithSize(s,strlen(s)) : nonOop)
#define	STTwoByteString(s) ((s) ? STTwoByteStringWithSize(s,wcslen(s)) : nonOop)


/*
 * Support for mapping integral values between the Smalltalk and C universes.
 *
 * N.B. In a mixed 64-bit 32-bit world there are pitfalls.  In particular,
 * casting a 64-bit signed integer to unsigned via e.g.
 *
 * longlong v; ...  (unsigned)v ...
 *
 * yields a 32-bit value.  i.e. unsigned is shorthand for unsigned int, so
 * the result has size sizeof(int), *not* sizeof(unsigned long long).  Even
 * *worse* is that casting from a 32-bit pointer to an unsigned long long
 * first casts to a long, so that sign extension occurs(!!!!!!!).
 *
 * Hence values are passed to the 64-bit version of cUnsignedToOop via
 * forUnsignedToOop, and the right cast is used so that sign extension
 * doesn't occur.
 */

typedef enum { Signed = 0, Unsigned = 1 } SignEnum;
#define isSignedEnum(aSign) (aSign == Signed)
#define isUnsignedEnum(aSign) (aSign == Unsigned)

extern bool  stOopToCValue(void *, oop, SignEnum, int);
#if PLATFORM_SUPPORTS_64_BITS && HAS_64_BIT_ARITHMETIC && !HPS64
# define forUnsignedToOop(v) (sizeof(v) > sizeof(unsigned) ? (ulonglong)(v) : (unsigned)(v))
extern oop  cSignedToOop(longlong);
extern oop  cUnsignedToOop(ulonglong);
#else
# define forUnsignedToOop(v) ((oopUInt)(v))
extern oop  cSignedToOop(long);
extern oop  cUnsignedToOop(unsigned long);
#endif

/* answers if oop is an integer and positive */
#define oopIsPosint(o) (oopIsImm(o) \
						? oopIsInt(o) && oopNum(o) >= 0 \
						: objClass(o) == sysOop(largePositiveIntegerClassX))
/* answers if oop is an integer and negative */
#define oopIsNegint(o) (oopIsImm(o) \
						? oopIsInt(o) && oopNum(o) < 0 \
						: objClass(o) == sysOop(largeNegativeIntegerClassX))


/* longAsOop() & STLong() answer a new Smalltalk integer (SmallInteger,
 * LargePositiveInteger, or LargeNegativeInteger) for a C long integer.
 *
 * On error, which can only be an allocation error, they answer nonOop.
 */
#define longAsOop(value) \
		(((value) <= (oopUInt)maxSmallInt && (value) >= minSmallInt) \
			? asSmallInt(value) \
			: cSignedToOop(value)) \

#define STLong(value, rOop) ((rOop) = longAsOop(value))

/* ulongAsOop() & STULong() answer a new Smalltalk integer (SmallInteger or
 * LargePositiveInteger) for a C unsigned long integer.
 *
 * On error, which can only be an allocation error, they answer nonOop.
 */
#define ulongAsOop(value) \
		(forUnsignedToOop(value) <= (oopUInt)maxSmallInt \
			? asSmallInt(value) \
			: cUnsignedToOop(forUnsignedToOop(value)))

#define STULong(value, rOop) ((rOop) = ulongAsOop(value))


/* CBool is a macro that answers a C bool (TRUE or FALSE) corresponding
 *   to the specified Smalltalk Boolean object.  It assumes that we've
 *   already determined the argument to be a Smalltalk Boolean.
 */
#define CBool(ooop) ((ooop) == sysOop(trueOopX) ? TRUE : FALSE)

/* STBool is a macro that answers a Smalltalk Boolean corresponding to
 *   the specified C boolean value.
 */
#define STBool(value) ((value) ? sysOop(trueOopX) : sysOop(falseOopX))

/* Arithmetic defs
 */
#define maxSmallInt ( ( 1L << maxSigBits ) - 1L )
#define maxInt (oopInt)( ( (oopUInt)1L << (maxSigBits + numTagBits) ) - 1L )
#define minSmallInt ( ~0L << maxSigBits )
#define minInt ( ~0L << ( maxSigBits + numTagBits ) )
