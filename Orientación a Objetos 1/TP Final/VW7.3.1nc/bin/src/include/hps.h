/* SccsId is @(#)hps.h	58.10 04/06/05 */
/************************************************************************
 * File: hps.h
 *
 * Project-wide header file. In order to reduce compile-time dependencies,
 * this file should contain only those definitions that are truly generic.
 *
 * Note that this file includes the platform.h file, which provides
 * platform dependent information, consisting of defines and C language
 * typedefs.  No C language constructs (e.g. typedefs) are included
 * if the symbol "assembly" is defined.
 *
 * Another file that a routine might want to include in addition to this file
 * is oop.h. This file contains all the oop and otEntry definitions. These
 * definitions were not included in this file in order to reduce unnecessary
 * compile-time dependencies. That is, not all routines need access to the
 * oop or the otEntry definitions. For example, if a routine only needs to move
 * oop-sized entities around, it doesn't need to include oop.h since
 * platform.h includes a file that has a typedef called "oopSized" which
 * can be utilized for such purposes.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#ifndef assembly
#	include <stdio.h>
#	include <stdlib.h> /* for malloc/free most platforms */
#	include <malloc.h> /* for malloc/free other platforms */
#endif

#if !defined(TRUE)
#	define TRUE 1
#	define FALSE 0
#endif
#if !defined(NULL)
#	define NULL 0
#endif
/*
 * Support for dynamic-load user-primitives on Win32.  Data imported by a DLL
 * must be marked as declspec(dllimport) (since their loader cannot fixup data
 * references, and hence relies on the compiler to generate an extra level of
 * indirection to get the current value of a datum).  This mechanism must not
 * be used when building the OE.  So we provide a dummy DLUP_IMPORT definition
 * and use it in the declarations of data that must be available to plugins,
 * such as the sysOopRegistry.  The source of dynamic-load user-primitives then
 * provide the required definition.
 */
#if !defined(DLUP_IMPORT)
#	define DLUP_IMPORT(returnType) returnType
#endif
#define private static
#define forwardPrivate static
 
#include "versionDefines.h"

#include "platform.h"

#include "exError.h"

#ifndef assembly
/*
 * Some miscellaneous utility macros
 */
#ifndef max
#	define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
#	define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#define iabs(a) ((oopInt)(a) < 0 ? -(oopInt)(a): (oopInt)(a))
#define swap(a, b, t) ((t) = (a), (a) = (b), (b) = (t))
#define alignPtrTo(v,n) ((void *)(((unsigned long)(v) + (n)-1) & ~((n)-1)))
#define alignPtrDownTo(v,n) ((void *)((unsigned long)(v) & ~((n)-1)))
#define roundUpToUnit(v,n) (((v) + (n)-1) & ~((n)-1))
#define roundUpToType(v,t) roundUpToUnit(v,sizeof(t))
#define numElementsInArray(array) (sizeof(array)/sizeof((array)[0]))
/* __ntostr converts an integer manifest constant to a string */
#define __ntostrAux(n) # n
#define __ntostr(n) __ntostrAux(n)

/*
 * Some C compilers don't implement the ">>" operator as an arithmetic
 * shift when applied to a signed operand (the shift is guaranteed to
 * be logical if the operand is unsigned); therefore, in order to maintain
 * maximum portability, we include an arithRShift macro, which can be used
 * when an arithmetic right shift is desired.
 */
#ifndef arithRShift
#	if (((-1)>>1)==(-1))
#		define arithRShift(value, shiftWidth) ((oopInt)(value) >> shiftWidth)
#	else
#		define arithRShift(value, shiftWidth) \
			((((oopInt)(value)) & signBitMask) ? \
 			(((oopInt)(value)) >> shiftWidth) | \
					((oopInt)(-1) << (bitsInOop - shiftWidth)): \
				(((oopInt)(value)) >> shiftWidth))
#	endif
#endif

/*
 * Some C compilers implement the "/" operator by rounding towards zero when
 * the result is negative (and the operands are integral), while others round
 * towards negative infinity. To maintain portability, we use the following
 * macros whenever the result of an integral division could be negative.
 *
 * In addition, C compilers implement the "%" operator so that the following
 * equality holds: (a/b)*b + a%b == a. Hence, the semantics of "%" is tied to
 * the semantics of "/," and since "/" can vary from compiler to compiler
 * (see above), we implement two versions of "%." Rem returns the remainder
 * left by divTrunc and mod returns the remainder left by divFloor.
 */
#ifndef divTrunc
# if (-1/2==0)
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

# else
#	define divTrunc(dividend, divisor) \
	  (((dividend ^ divisor) & signBitMask) ? \
	    ((dividend & signBitMask) ? \
	      (((oopInt)(dividend)+((oopInt)(divisor)-1))/(oopInt)(divisor)): \
	      (((oopInt)(dividend)+((oopInt)(divisor)+1))/(oopInt)(divisor))):\
	    (oopInt)(dividend) / (oopInt)(divisor))

#	define rem(dividend, divisor, scratch) \
		(((dividend ^ divisor) & signBitMask) ? \
			((scratch = (oopInt)(dividend)%(oopInt)(divisor)) ? \
				scratch - (oopInt)(divisor) : \
				0) : \
			(oopInt)(dividend) % (oopInt)(divisor))

#	define divFloor(dividend, divisor) \
	  (((oopInt)(dividend)) / ((oopInt)(divisor)))

#	define mod(dividend, divisor, scratch ) \
		((oopInt)(dividend) % (oopInt)(divisor))
# endif
#endif /* divTrunc */

/* Macros to support run-time assertion checking. Compile with the -DASSERT
 * switch to get the fast assertion checking and compile with both the
 * -DASSERT and the -DDEBUG switches to get full assertion checking with
 * the -o2k/-o11s/-o19s options (full assertion checking can be very slow).
 *
 * Note that the assert macro is also boolean, so you can say, e.g.
 *
 *	if (!assert(expression)) return FALSE;
 *
 * More usefully asserta et al always evaluate the expression so
 *		if (!asserta(expressionWithSideeffects)) statement
 * is idempotent w.r.t. assertion checking (-DASSERT makes no difference).
 *
 * There are four groups: assert for common assertions, dasserts for slow
 * assertions only run if OPTDasserts, OPTEasserts or OPTFasserts options are
 * supplied, easserts for extremely slow assert checks only run if OPTEasserts
 * or OPTFasserts options are supplied, and fasserts for fabulously slow assert
 * checks only run if the OPTFasserts option is supplied.  Note that there are
 * no dasserta, easserta or fasserta because it is pointless to avoid a quick
 * check after evaluating a slow expression.
 *
 * Here's the full list:
 *
 *	assert(e) => false	eval e iff asserts	assertFail iff asserts and !e
 *	asserta(e) => e		eval e always		assertFail iff asserts and !e
 *	assertf(comment) => false				always assertFail & report comment
 *	dassert(e) => false	eval e iff dasserts	assertFail iff dasserts and !e
 *	eassert(e) => false	eval e iff easserts	assertFail iff easserts and !e
 *	fassert(e) => false	eval e iff easserts	assertFail iff fasserts and !e
 */
#if defined(ASSERT)
# if !defined(assertsOn)
extern DLUP_IMPORT(bool) assertsOn;
# endif
# if !defined(dassertsOn)
extern DLUP_IMPORT(bool) dassertsOn;
# else
#	define dassertsOn 0
# endif
# define ifAssert(foo) foo

	/* DON'T condense these different macros.  If you do, the stringification
	 * is applied to the expanded argument, _not_ to the text of the argument
	 * giving a totally cryptic error report.
	 *
	 * E.g. If you define
	 *
	 *	#define assertIndexed(ex, index) \
	 *			(!(ex) && assertFail(#ex, __FILE__, __LINE__))
	 *
	 *	#define assert(ex) assertIndexed(ex, 0)
	 *
	 * and say e.g. assert(objDataInNewSpace(oop)) this expands to
	 * ... assertFail("(oop)->ptr.toOops <= oldNewSpaceBoundary", ...
	 * instead of the desired
	 * ... assertFail("objDataInNewSpace(oop)", ...
	 */
# if !ASSERT_COMPILER_BUG

extern void assertFail(const char *, const char *, int);

#	define assert(ex) \
		(assertsOn && !(ex) && (assertFail(#ex, __FILE__, __LINE__),0))

#	define asserta(ex) \
		((ex) || (assertsOn && (assertFail(#ex, __FILE__, __LINE__),0)))

#	define assertf(commentaryString) \
		(assertsOn && (assertFail(commentaryString, __FILE__, __LINE__),0))

#	define dassert(ex) \
		(dassertsOn && !(ex) && (assertFail(#ex,__FILE__,__LINE__),0))

#	define eassert(ex) \
		(dassertsOn > 1 && !(ex) && (assertFail(#ex,__FILE__,__LINE__),0))

#	define fassert(ex) \
		(dassertsOn > 2 && !(ex) && (assertFail(#ex,__FILE__,__LINE__),0))

# else /* !ASSERT_COMPILER_BUG */
	/* There always has to be one, doesn't there?  The AIX compiler cannot
	 * handle the above assert macros.  Instead it very often generates a
	 * suprious call to assertFail.  To get around the bug we use a value
	 * returned by assertFail (always FALSE).  This generates less efficient
	 * and bulkier code, so alas we do have to maintain two versions.
	 */
extern bool assertFail(const char *, const char *, int);

#	define assert(ex) \
		(assertsOn && !(ex) && assertFail(#ex, __FILE__, __LINE__))

#	define asserta(ex) \
		((ex) || (assertsOn && assertFail(#ex, __FILE__, __LINE__)))

#	define assertf(commentaryString) \
		(assertsOn && assertFail(commentaryString, __FILE__, __LINE__))

#	define dassert(ex) \
		(dassertsOn && !(ex) && assertFail(#ex,__FILE__,__LINE__))

#	define eassert(ex) \
		(dassertsOn > 1 && !(ex) && assertFail(#ex,__FILE__,__LINE__))

#	define fassert(ex) \
		(dassertsOn > 2 && !(ex) && assertFail(#ex,__FILE__,__LINE__))

# endif /* !ASSERT_COMPILER_BUG */
extern void assertReport(const char *, ...);
# else
#	define assertsOn 0
#	define ifAssert(foo)
#endif /* ASSERT */

#ifndef assert
#	define assert(ex) FALSE
#endif
#ifndef asserta
#	define asserta(ex) (ex)
#endif
#ifndef assertf
#	define assertf(commentary) FALSE
#endif
#ifndef dassert
#	define dassert(ex) FALSE
#endif
#ifndef eassert
#	define eassert(ex) FALSE
#endif
#ifndef fassert
#	define fassert(ex) FALSE
#endif

#if MEASURE
#	ifndef assembly
extern void lineCount(const char *extra, const char *file, int line);
extern void valueCount(void *oop,const char *extra);
#	endif
#	define countLine(e)    lineCount(e,__FILE__,__LINE__)
#   define countValue(o,e) valueCount(o,e)
#else
#   define countLine(e)    0
#   define countValue(o,e) 0
#endif

/*
 * Macro to support time stamped event loging.  This currently only works on
 * Unix based platforms but is here for convenience (note that dumpHiddenLog()
 * is implemented in plat/unxAlarm.c). To enable this option
 * compile with -DDEBUG=2 (or any value greater than one).
 *
 * General usage is:  logThis("format string", some_value);
 * When the the log is dumped the some_value will be printed using the "format
 * string" (note the string is not copied). Logged events are held in a ring
 * buffer of hiddenLogSize until dumpHiddenLog() is called.
 */
#if DEBUG > 1
#	include <sys/time.h>

struct undercoverS {
	struct timeval time;
	char *format;
	oopUInt value;
};

#	define hiddenLogSize 1024

/* reserve an undercover slot first so this is reentrent */
#	define logThis(fmt, val) { \
			   int indx; \
			   indx = (hiddenIndex++) & (hiddenLogSize-1); \
			   (void)gettimeofday(&hiddenLog[indx].time, NULL); \
			   hiddenLog[indx].format = fmt; \
			   hiddenLog[indx].value = (oopUInt)(val); \
		   }

extern struct undercoverS hiddenLog[hiddenLogSize];
extern int hiddenIndex;
extern void dumpHiddenLog(char*);
#else
#	define logThis(fmt, val)
#	define dumpHiddenLog(who)
#endif

extern void doPanic(char*, int);
#define panic() doPanic(__FILE__,__LINE__)

extern FILE *pdDebugLog(bool);

#endif /* non-assembly */
