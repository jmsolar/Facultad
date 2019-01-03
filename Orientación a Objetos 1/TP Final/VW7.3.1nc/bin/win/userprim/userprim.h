/* SccsId is @(#)userprim.h	58.10 04/06/05 */
/***************************************************************************
 * File: userprim.h
 * 
 * Definition of VisualWorks(R) User-defined Primitives API
 *
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 ***************************************************************************/

#ifdef c_plusplus
extern "C" {
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/*
 * Define any platform dependent compiler type specifiers here
 * in case they are used in up_defs.h.  These declarations must
 * obviously precede the inclusion of up_defs.h.
 */
#ifdef _WINDLL
#define UPENTRY _far _pascal
#else
#ifdef _OS2
#define UPENTRY _Optlink
#else
#define UPENTRY
#endif
#endif

#ifndef _far
#define _far
#endif
#ifndef _pascal
#define _pascal
#endif

#include "up_defs.h"

/* system oop registry indicies */
/* From: sysOop32.h & sysOop64.h */
#define nilOopX 0
#define trueOopX 1
#define falseOopX 2
#if VW32
# define smallIntegerClassX 7
# define characterClassX 8
# define floatClassX 9
# define pointClassX 10
# define arrayClassX 12
# define semaphoreClassX 13
# define byteStringClassX 19
# define largePositiveIntegerClassX 20
# define largeNegativeIntegerClassX 28
# define byteSymbolClassX 22
# define byteArrayClassX 24
# define twoByteStringClassX 29
# define twoByteSymbolClassX 30
# define doubleClassX 32
#else
# define smallIntegerClassX 4
# define characterClassX 6
# define arrayClassX 15
# define semaphoreClassX 16
# define byteStringClassX 17
# define largePositiveIntegerClassX 18
# define largeNegativeIntegerClassX 19
# define byteSymbolClassX 21
# define byteArrayClassX 22
# define twoByteStringClassX 23
# define twoByteSymbolClassX 24
# define doubleClassX 25
# define pointClassX 27
# define floatClassX 28
#endif

/* =================== exported functions ======================= */

/* UPbegin()
 * doesn't do anything, defined for 2.3 backwards compatibility only
 */
#ifndef UPbegin
#define UPbegin(rcvr, na)
#endif

/* ====================== main entrance ========================== */
extern int
oeMain(int, char**, char**);

#ifdef UNSAFE
/* =====================================================================
 * WARNING -- If you compile your primitives with -DUNSAFE you will get
 * an equivalent user-primitive support API which will run somewhat
 * faster but bugs in your primitives can crash the resulting VM (rather
 * than fail), and worse some bugs can silently corrupt the VI.  You
 * should test your primitive code VERY carefully before compiling with
 * -DUNSAFE and using the resulting VM's on VI's you care about.
 * Finally, VMs built with -DUNSAFE and their derived VI's will not be
 * handled by Cincom technical support.
 * =====================================================================
 */
#  include "up_unsafe.h"

#else /* ndef(UNSAFE) */

#ifdef OPACIFY
#	ifdef OSF32

typedef unsigned int upHandle;			/* handles are opaque */

#	else

typedef unsigned long upHandle;			/* handles are opaque */

#	endif
#else /* OPACIFY */
#	ifdef WIN16

typedef unsigned long _oop;

#	else /* WIN16 */
#		ifdef OSF32
#			pragma pointer_size (save)
#			pragma pointer_size (short)
#		endif

typedef struct _otEntryS *_oop;

#		ifdef OSF32
#			pragma pointer_size (restore)
#		endif
#	endif /* WIN16 */

typedef _oop upHandle;

#endif /* OPACIFY */

/* 
 * UPaddPrimitive( primNumber, primFunc, numArgs ) --
 * Add primFunc with numArgs number of arguments as a user primitive.
 */
#define UPaddPrimitive(pn, pf, na) _UPaddPrimitive(pn, pf, na)
extern upBool UPENTRY
_UPaddPrimitive(upInt, upFunct, upInt);


/* 
 * UPnil() --
 * Return Smalltalk nil.
 */
extern upHandle UPENTRY UPnil(void);

/* 
 * UPreturnHandle( aUpHandle ) --
 * Primitive return this object.
 */
extern void UPENTRY
UPreturnHandle(upHandle);

/* 
 * UPreturnNil() --
 * Primitive return nil.
 */
extern void UPENTRY
UPreturnNil(void);

/* 
 * UPreturnTrue() --
 * Primitive return True.
 */
extern void UPENTRY
UPreturnTrue(void);

/* 
 * UPreturnFalse() --
 * Primitive return False.
 */
extern void UPENTRY
UPreturnFalse(void);

/* 
 * UPSTtoCbool( aUpHandle ) --
 * Convert this Smalltalk Boolean to a upBool [e.g. either TRUE or FALSE].
 */
extern upBool UPENTRY
UPSTtoCbool(upHandle);

/* 
 * UPSTtoCint( aUpHandle ) --
 * Convert this Smalltalk SmallInteger to a C upInt.
 */
extern upInt UPENTRY
UPSTtoCint(upHandle);

/* 
 * UPSTtoCchar( aUpHandle ) --
 * Convert this Smalltalk Character to a C character.
 */
extern upChar UPENTRY
UPSTtoCchar(upHandle);

/* 
 * UPSTtoCfloat( aUpHandle ) --
 * Convert this Smalltalk Float to a C Float.
 */
extern upFloat UPENTRY
UPSTtoCfloat(upHandle);

/* 
 * UPCtoSTbool( aUpBool ) --
 * Convert aUpBool to a Smalltalk Boolean.
 */
extern upHandle UPENTRY
UPCtoSTbool(upBool);

/* 
 * UPCtoSTint( aUpInt ) --
 * Convert aUpInt to a Smalltalk Integer.
 * We can only represent -[2^29] ... [2^29 - 1] (signed 30 bits).
 */
extern upHandle UPENTRY
UPCtoSTint(upInt);

/* 
 * UPCtoSTchar( aUpChar ) --
 * Convert aUpChar to a Smalltalk Character.
 */
extern upHandle UPENTRY
UPCtoSTchar(upChar);

/* 
 * UPinstVarSize( aUpHandle ) --
 * Return the number of this object's instance variables.
 */
extern upInt UPENTRY
UPinstVarSize(upHandle);

/* 
 * UPindexVarSize( aUpHandle ) --
 * Return the size of this object in number of indexed variables.
 */
extern upInt UPENTRY
UPindexVarSize(upHandle);


/* 
 * UPbasicAt( arrayUpHandle, index ) --
 * Return the upHandle at the one based index of arrayUpHandle.
 */
extern upHandle UPENTRY
UPbasicAt(upHandle, upInt);

/* 
 * UPinstVarAt( aUpHandle, index ) --
 * Return the value of the one based index'th instance variable.
 */
extern upHandle UPENTRY
UPinstVarAt(upHandle, upInt);

/* 
 * UPbyteAt( aUpHandle, index ) --
 * Return the byte at the one based index from aUpHandle which
 * should be a ByteArray or String.
 */
extern upByte UPENTRY
UPbyteAt(upHandle, upInt);

/* 
 * UPintegerAt( aUpHandle, index ) --
 * Return the upInteger at the one based index from aUpHandle which
 * should be a Array.
 */
extern upInt UPENTRY
UPintegerAt(upHandle, upInt);

/* 
 * UPfloatAt( aUpHandle, index ) --
 * Return the upFloat at the one based index from aUpHandle which
 * should be a Array.
 */
extern upFloat UPENTRY
UPfloatAt(upHandle, upInt);

/* 
 * UPbasicAtPut( arrayUpHandle, index, upHandleToBePut ) --
 * Put upHandleToBePut into the arrayUpHandle at the one based index.
 */
extern void /* was upHandle */ UPENTRY
UPbasicAtPut(upHandle, upInt, upHandle);

/* 
 * UPinstVarAtPut( aUpHandle, index, upHandleToBePut ) --
 * Put upHandleToBePut into the one based index'th instance variable.
 */
extern void /* was upHandle */ UPENTRY
UPinstVarAtPut(upHandle, upInt, upHandle);

/* 
 * UPbyteAtPut( aUpHandle, index, aUpByte ) --
 * Put the byte at the one based index in the ByteArray or String indicated
 * by aUpHandle.
 */
extern void /* was upByte */ UPENTRY
UPbyteAtPut(upHandle, upInt, upByte);

/* 
 * UPintegerAtPut( aUpHandle, index, aUpInt ) --
 * Put the integer at the one based index in the Array indicated
 * by aUpHandle.
 */
extern void /* was upInt */ UPENTRY
UPintegerAtPut(upHandle, upInt, upInt);

/* 
 * UPisCharacter( aUpHandle ) --
 * is aUpHandle a Character?
 */
extern upBool UPENTRY
UPisCharacter(upHandle);

/* 
 * UPisInteger( aUpHandle ) --
 * is aUpHandle a SmallInteger?
 */
extern upBool UPENTRY
UPisInteger(upHandle);

/* 
 * UPisByteArray( aUpHandle ) --
 * is aUpHandle a ByteArray?
 */
extern upBool UPENTRY
UPisByteArray(upHandle);

/* 
 * UPisBoolean( aUpHandle ) --
 * Is aUpHandle a Boolean?
 */
extern upBool UPENTRY
UPisBoolean(upHandle);

/* 
 * UPisFloat( aUpHandle ) --
 * Is aUpHandle a Float?
 */
extern upBool UPENTRY
UPisFloat(upHandle);

/*
 * UPisDouble(aUpHandle) --
 * Is the handle a Smalltalk Double?
 */
extern upBool UPENTRY
UPisDouble(upHandle);

/* 
 * UPisByteLike( aUpHandle ) --
 * Does aUpHandle have ByteArray accessing semantics?
 */
extern upBool UPENTRY
UPisByteLike(upHandle);

#endif
/* end of #ifdef(UNSAFE) */

/*
 * Message based callback API:
 */
extern upHandle UPENTRY
UPSendMessageMany(upHandle, upHandle, upHandle, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPSendMessage0(upHandle, upHandle, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPSendMessage1(upHandle, upHandle, upHandle, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPSendMessage2(upHandle, upHandle, upHandle, upHandle, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPSendMessage3(upHandle, upHandle, upHandle, upHandle, upHandle, upHandle _far*, upHandle);

/*
 * For C-oriented callbacks (char * instead of selector,
 * arguments passed in C-Array instead of Smalltalk Array).
 */
extern upHandle UPENTRY
UPCSendMessageMany(upHandle, char _far*, upHandle _far*, long, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPCSendMessage0(upHandle, char _far*, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPCSendMessage1(upHandle, char _far*, upHandle, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPCSendMessage2(upHandle, char _far*, upHandle, upHandle, upHandle _far*, upHandle);

extern upHandle UPENTRY
UPCSendMessage3(upHandle, char _far*, upHandle, upHandle, upHandle, upHandle _far*, upHandle);

/*
 * Static link registration:
 */

extern void UPENTRY
UPRegisterSymbolAndHandle(char  _far*, void  _far*);


/* doubles and allocation entrypoints have no UNSAFE implementation */

/* 
 * UPstringSize( aUpHandle ) --
 * Return the size of this string object in number of characters.
 */
extern upInt UPENTRY
UPstringSize(upHandle);

/* 
 * UPisString( aUpHandle ) --
 * is aUpHandle a String that can be stored into?
 */
extern upBool UPENTRY
UPisString(upHandle);

/* 
 * UPisReadOnlyString( aUpHandle ) --
 * is aUpHandle a String that is readable but possibly not stored into?
 */
extern upBool UPENTRY
UPisReadOnlyString(upHandle);

/* 
 * UPdoubleAt( aUpHandle, index ) --
 * Return the upDouble at the one based index from aUpHandle which
 * should be a Array.
 */
extern upDouble UPENTRY
UPdoubleAt(upHandle, upInt);

/*
 * UPSTtoCdouble(aUpHandle) --
 * Convert a Smalltalk Double to a upDouble.
 */
extern upDouble UPENTRY
UPSTtoCdouble(upHandle);

/*
 * UPCtoSTfloat(aUpFloat) --
 * Convert aUpFloat to a Smalltalk Float.
 */
extern upHandle UPENTRY
UPCtoSTfloat(upFloat);

/*
 * UPCtoSTdouble(aUpDouble) --
 * Convert aUpDouble to a Smalltalk Double.
 */
extern upHandle UPENTRY
UPCtoSTdouble(upDouble);

/*
 * UPfloatAtPut(aUpHandle, index, aUpFloat) --
 * Put the Float at the one based index in the Array indicated
 * by aUpHandle.
 */
extern void /* was upFloat */ UPENTRY
UPfloatAtPut(upHandle, upInt, upFloat);

/*
 * UPallocString(anUpChar, numElements) --
 * Allocate a Smalltalk String of size numElements and initialize
 * all its elements to anUpChar.
 */
extern upHandle UPENTRY
UPallocString(upChar, upInt);

/*
 * UPallocByteArray(anUpByte, numElements) --
 * Allocate a Smalltalk ByteArray of size numElements and initialize
 * all the elements to anUpByte.
 */
extern upHandle UPENTRY
UPallocByteArray(upByte, upInt);

/*
 * UPallocArray(anUpHandle, numElements) --
 * Allocate an Array of size numElements, and initialize all the elements
 * to anUpHandle.
 */
extern upHandle UPENTRY
UPallocArray(upHandle, upInt);

/*
 * UPcopySTtoCstring(aUpHandle, aUpString, aCount, startingAt) --
 * Copy up to aCount elements from the Smalltalk String aUpHandle beginning
 * with the one based index startingAt into the C string aUpString. 
 * Return the number of elements actually copied.
 */
extern upInt UPENTRY
UPcopySTtoCstring(upHandle, upChar  _far*, upInt, upInt);

/*
 * UPcopySTtoCbytes(aUpHandle, aUpBytes, aCount, startingAt) --
 * Copy up to aCount elements from the Smalltalk ByteArray aUpHandle beginning
 * with the one based index startingAt into the C byte array aUpBytes. 
 * Return the number of elements actually copied.
 */
extern upInt UPENTRY
UPcopySTtoCbytes(upHandle, upByte  _far*, upInt, upInt);

/*
 * UPcopySTtoCintArray(aUpHandle, aUpIntArray, aCount, startingAt) --
 * Copy up to aCount elements from the Smalltalk Array aUpHandle beginning
 * with the one based index startingAt into the C array aUpIntArray. 
 * Return the number of elements actually copied.
 */
extern upInt UPENTRY
UPcopySTtoCintArray(upHandle, upInt  _far*, upInt, upInt);

/*
 * UPcopySTtoCfloatArray(aUpHandle, aUpFloatArray, aCount, startingAt) --
 * Copy up to aCount elements from the Smalltalk Array aUpHandle beginning
 * with the one based index startingAt into the C float array aUpFloatArray. 
 * Return the number of elements actually copied.
 */
extern upInt UPENTRY
UPcopySTtoCfloatArray(upHandle, upFloat  _far*, upInt, upInt);

/*
 * UPcopyCtoSTstring(aUpHandle, aUpString, aCount, startingAt) --
 * Copy up to aCount elements from the C string aUpString into the 
 * Smalltalk String aUpHandle beginning with the one based index
 * startingAt. Return the the number of elements copied.
 */
extern upInt UPENTRY
UPcopyCtoSTstring(upHandle, upChar  _far*, upInt, upInt);

/*
 * UPcopyCtoSTbytes(aUpHandle, aUpBytes, aCount, startingAt) --
 * Copy up to aCount elements from the C byte array aUpBytes into the 
 * Smalltalk ByteArray aUpHandle beginning with the one based index
 * startingAt. Return the the number of elements copied.
 */
extern upInt UPENTRY
UPcopyCtoSTbytes(upHandle, upByte  _far*, upInt, upInt);

/*
 * UPcopyCtoSTintArray(aUpHandle, aUpIntArray, aCount, startingAt) --
 * Copy up to aCount elements from the C array aUpIntArray into the 
 * Smalltalk Array aUpHandle beginning with the one based index
 * startingAt. Return the the number of elements copied.
 */
extern upInt UPENTRY
UPcopyCtoSTintArray(upHandle, upInt  _far*, upInt, upInt);

/*
 * UPcopyCtoSTfloatArray(aUpHandle, aUpFloatArray, aCount, startingAt) --
 * Copy up to aCount elements from the C float array aUpFloatArray into the 
 * Smalltalk Array aUpHandle beginning with the one based index
 * startingAt. Return the the number of elements copied.
 */
extern upInt UPENTRY
UPcopyCtoSTfloatArray(upHandle, upFloat  _far*, upInt, upInt);

/* UPisArrayOf<something> have no UNSAFE implementations */

/*
 * UPisArrayOfInteger(arryHandle) --
 * Is aUpHandle a Array of Integers?
 */
extern upBool UPENTRY
UPisArrayOfInteger(upHandle);

/*
 * UPisArrayOfFloat(aUpHandle) --
 * Is aUpHandle a Array of Floats?
 */
extern upBool UPENTRY
UPisArrayOfFloat(upHandle);

/* UPmustBe<something> have no UNSAFE implementations */
/* 
 * UPmustBe<something>(handle) --
 * Same as the UPis<something> routines except fail if it isn't.
 */
extern void UPENTRY
UPmustBeCharacter(upHandle);
extern void UPENTRY
UPmustBeInteger(upHandle);
extern void UPENTRY
UPmustBeString(upHandle);
extern void UPENTRY
UPmustBeByteArray(upHandle);
extern void UPENTRY
UPmustBeArrayOfInteger(upHandle);
extern void UPENTRY
UPmustBeArrayOfFloat(upHandle);
extern void UPENTRY
UPmustBeBoolean(upHandle);
extern void UPENTRY
UPmustBeFloat(upHandle);
extern void UPENTRY
UPmustBeByteLike(upHandle);

/*
 * UPfail(errorCode) --
 * fail primitive (can be called anywhere, courtesy of longjmp).
 */
extern void UPENTRY
UPfail(upInt);

/*
 * UPinstallErrorHandler() --
 * Install function as error handler to catch errors in support routines.
 * Passing ((upFunct)NULL) as arg removes handler.
 * Returns previously installed handler.
 */
extern upFunct UPENTRY
UPinstallErrorHandler(upFunct);


/*
 * ===========================
 * new (post v2.5) API entries
 * ===========================
 */

#ifndef UNSAFE

/*
 * UPisImmediate(aUpHandle) --
 * Is aUpHandle an immediate object?
 */
extern upBool UPENTRY
UPisImmediate(upHandle);

/* 
 * UPregisteredHandleAt( anUpInt ) --
 * Return a handle from the registry.
 */
extern upHandle UPENTRY
UPregisteredHandleAt(upInt);

/*
 * UPclass(handle)
 * Return the class of the given object.
 */
extern upHandle UPENTRY
UPclass(upHandle);

#endif
/* end of #ifndef UNSAFE */

/*
 * UPregisteredHandleAtPut(index, handle) --
 * Put a handle at the given slot in the registry.
 */
extern void UPENTRY
UPregisteredHandleAtPut(upInt, upHandle);

/*
 * UPallocRegistrySlot() --
 * Allocate a slot in the registry, return slot number.
 */
extern upInt UPENTRY
UPallocRegistrySlot(void);

/*
 * UPallocFsObject(classHandle) --
 * allocate a fixed-size object of the given class, return handle
 * to the instance.
 */
extern upHandle UPENTRY
UPallocFsObject(upHandle);

/*
 * UPallocVsObject(classHandle, size) --
 * Allocate a variable-size object of the given class and the given
 * number of elements, return handle to the instance.
 */
extern upHandle UPENTRY
UPallocVsObject(upHandle, upInt);

/*
 * UPclassType(classHandle) --
 * Given a handle to a class, return an integer indicating if the class
 * has fixed size instances, variable size instances, or not-a-class.
 */
#define UPnotAClass 0
#define UPfixedSizeClass 1
#define UPvariableSizeClass 2
extern upInt UPENTRY
UPclassType(upHandle);

/*
 * UPsignalSemaphore(semHandle) --
 * Given a handle to a semaphore, signal the semaphore.
 */
extern void UPENTRY
UPsignalSemaphore(upHandle);

/*
 * UPpostInterrupt() --
 * Post an interrupt request (causes VI code break-out and a call
 * to poll-handler.
 */
extern void UPENTRY
UPpostInterrupt(void);

/*
 * UPinstallPollHandler(pollFunc) --
 * Register a poll function (called when interrupt posted).
 */
extern void UPENTRY
UPinstallPollHandler(upFunct);

/*
 * UPstartLongPrimitive(int) -- UPfinishLongPrimitive() --
 * Notify the VM that this primitive may take an int milliseconds to run.
 * This pair of functions should be used for ALL primitives that might take
 * 500 milliseconds or more to run.
 * If the function UPstartLongPrimitive is called then UPfinishLongPrimitive
 * must be called before the primitive returns.  UPstartLongPrimitive may be
 * called more than once but each call must be balanced with a call to
 * UPfinishLongPrimitive.
 */
extern void UPENTRY
UPstartLongPrimitive(upInt);
extern void UPENTRY
UPfinishLongPrimitive(void);

/*
 * UPisKindOf(objUpHandle, classUpHandle) --
 * Given a handle on an object and a class, return a boolean indicating
 * whether the instance belongs to that class or its superclasses.
 */
extern upBool UPENTRY
UPisKindOf(upHandle, upHandle);

#ifdef c_plusplus
}       /* end of C declarations */
#else
#ifdef __cplusplus
}       /* end of C declarations */
#endif
#endif
