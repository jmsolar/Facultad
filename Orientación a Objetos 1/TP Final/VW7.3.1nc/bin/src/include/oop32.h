/* SccsId is @(#)oop32.h	58.10 04/06/05 */
/************************************************************************
 * File: oop32.h
 *
 * This file contains the definitions associated with oops and otEntries
 * on 32-bit platforms.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/*
 * Oop and Ot entry defs
 *
 * **** NOTE: Some of this is duplicated in unsafe_oops.h
 */
#if !defined(assembly)
typedef struct otEntryS {
	union { /* object's indirection to body/forwarding pointer */
		struct otEntryS	**toOops;
		struct {
# if LEFT_BIT_FIELD_ORDER
			unsigned pointer			: 30;
			unsigned isForwarded		: 1;
			unsigned needsScanning		: 1;
# elif RIGHT_BIT_FIELD_ORDER
			unsigned needsScanning		: 1;
			unsigned isForwarded		: 1;
			unsigned pointer			: 30;
# else
#	error "plat header file must define compiler's bit ordering"
# endif
# define needsScanningBit				0
# define isForwardedBit					1
		} forwarding;
	  	/* Nobody actually USES this, but it helps in debugging. */
		quantum *toQuanta;
	} ptr;
	struct otEntryS *classOop;
	union { /* object's header flags size and hash */
		oopUInt flagWord;
		oopInt  flagOopInt;
		struct {
# if LEFT_BIT_FIELD_ORDER
			unsigned hasPtrs			: 1;
#	if EPHEMERONS
			unsigned isEphemeronNotWeak	: 1;
#	else
			unsigned isCheckMarked		: 1;
#	endif
			unsigned isMarked			: 1;
			unsigned inRt				: 1;
			unsigned isImmutable		: 1;
			unsigned size				:11;
			unsigned inOldRt			: 1;
			unsigned isGCSpecial		: 1;
			unsigned hash				:14;
# elif RIGHT_BIT_FIELD_ORDER
			unsigned hash				:14;
			unsigned isGCSpecial		: 1;
			unsigned inOldRt			: 1;
			unsigned size				:11;
			unsigned isImmutable		: 1;
			unsigned inRt				: 1;
			unsigned isMarked			: 1;
#	if EPHEMERONS
			unsigned isEphemeronNotWeak	: 1;
#	else
			unsigned isCheckMarked		: 1;
#	endif
			unsigned hasPtrs			: 1;
# endif
/**** NOTE: Some of these are duplicated in unsafe_oops.h */
# define firstHashBit				 0
# define   bitsInHash				14
# define gcSpecialFlagBit			14
# define oldRtFlagBit				15
# define firstSizeBit				16
# define   bitsInSize				11
# define isImmutableBit				27
# define rtFlagBit					28
# define markedFlagBit				29
# if EPHEMERONS
#	define ephemeronNotWeakFlagBit	30
# else
#	define checkMarkedFlagBit		30
# endif
# define hasPtrsFlagBit				31
		} bits;
	} misc;
} otEntry, *oop;
#endif /* assembly */

#define slotsInOtEntry (sizeof(otEntry) / sizeof(oopSized))

/***** NOTE: Some of these are duplicated in unsafe_oops.h */

#define nonOop ((oop)0)
#define numTagBits 2
#define numLitBits (bitsInOop - numTagBits)
#define tagBitsMask ((1<<numTagBits)-1)
#define signBitMask (-1L << (bitsInOop - 1))
#define allButSignMask ((q32)-1 >> 1)
#define maxSigBits (numLitBits - 1)
#define oopNum(ooop) ((oopInt)(ooop))
#define oopBits(ooop) ((oopUInt)(ooop))
#define tagBits(ooop) ((oopUInt)(ooop) & tagBitsMask)

/* Representation of immediate quantities */
#define immBit 0
#define immBit1Rel 1 /* for glue */
#define immBitBE 31  /* for HP glue */
#define immBitState 1
#if immBitState
/* NOTE: Duplicated in unsafe_oops.h */
#	define oopIsImm(ooop) ((oopBits(ooop) & (1<<immBit)) != 0)
#else
#	define oopIsImm(ooop) ((oopBits(ooop) & (1<<immBit)) == 0)
#endif

/* Representation of SmallIntegers */
#define intBit 1
#define intBit1Rel 2 /* for glue */
#define intBitBE 30  /* for HP glue */
#define intBitState 1
#if intBitState
/* NOTE: Duplicated in unsafe_oops.h */
#	define oopIsInt(ooop) ((oopBits(ooop) & (1<<intBit)) != 0)
#else
#	define oopIsInt(ooop) ((oopBits(ooop) & (1<<intBit)) == 0)
#endif

#define intTag ((intBitState<<intBit)|(immBitState<<immBit))
/* NOTE: Duplicated in unsafe_oops.h */
#define oopIntVal(ooop) arithRShift(oopNum(ooop), numTagBits)
#define oopUIntVal(ooop) (oopBits(ooop) >> numTagBits)
/* NOTE: Duplicated in unsafe_oops.h */
#define asSmallInt(value) ((oop) (((oopInt)(value) << numTagBits) + intTag))

/* Representation of immediate Characters */
#define charTag (((1-intBitState)<<intBit)|(immBitState<<immBit))
#define asChar(value) ((oop) (((oopUInt)(value) << numTagBits) + charTag))
#define oopCharVal(ooop) (oopBits(ooop) >> numTagBits)
#define oopIsChar(ooop) (tagBits(ooop) == charTag)

/* No immediate doubles in the 32-bit implementation. */
#define oopIsSmallDouble(ooop) FALSE
/*
 * Class-related definitions.
 */
#define ObjectsHaveDirectClassPointer 1
/*
 * Returns the class of the oop, even if it is immediate.
 */
/* NOTE: Duplicated in unsafe_oops.h */
#if IMMEDIATE_TABLE
#	define immClass(ooop) (immediateTable[oopBits(ooop)&(1<<intBit)])
#else
#	define immClass(ooop) (oopIsInt(ooop) \
							? sysOop(smallIntegerClassX) \
							: sysOop(characterClassX))
#endif
#define classFromClassTag(clss) (clss)
#define classTagFromClass(cls) (cls)
#define oopClass(ooop) (!oopIsImm(ooop) ? objClass(ooop) : immClass(ooop))
#define oopClassTag(ooop) oopClass(ooop)
#define nonClassTag nonOop

/* Representation of ordinary objects (pointers to ot entries). */
/* At the moment, only the translator uses this: */
/* all other code assumes that ptrTag == 0. */
#define ptrTag (((1-intBitState)<<intBit)+((1-immBitState)<<immBit))

#define asOopPtr(ptr) ((oop *)(oopInt)(ptr))

/*
 * Public macros for accessing the fields of an object's header.
 *
 * Even though these macros are considered public, you should think
 * twice about using them. In general, only special purpose code
 * utilizes these macros. This is especially true of the store macros.
 */

/* Public Store Macros */
#define setObjClass(ooop, class) ((ooop)->classOop = (class))
#define setObjClassTag(ooop, classTag) setObjClass(ooop, classTag)

/* Public Fetch Macros */
/* NOTE: Duplicated in unsafe_oops.h */
#define objDataPtr(ooop, type) ((type *)((ooop)->ptr.toOops))

#if platform == platAOSF
/* an additional variant on objDataPtr is needed at the "firewall" between
 * 32-bit pointers and 64-bit pointers under xtaso on OSF-AXP.  The fw prefix
 * indicates a firewall routine.  This is an xtaso special alternate, used at
 * sensitive points in the plat code for AOSF builds.
 */
# define fwObjDataPtr(ooop, type) ((type *) ((oop)((ooop)->ptr.toOops)))
#else
# define fwObjDataPtr(ooop, type) objDataPtr(ooop, type)
#endif

/* NOTE: Duplicated in unsafe_oops.h */
#define objClass(ooop) ((ooop)->classOop)
#define objClassTag(ooop) objClass(ooop)
#if !defined(assembly)
typedef oop classTag;
#endif

/*
 * Size accessing macros specific to word size.
 */
/* Reserve some special values for size */
#define numSizeValuesReserved (32)

#define rawObjDataSize(ooop) (objSizeInHeader(ooop) \
							? objSizeField(ooop) \
							: objSizeOvflField(ooop))

#define rawObjBodySize(ooop) (objSizeInHeader(ooop) \
							? objSizeField(ooop) \
							: objSizeOvflField(ooop) + sizeOvflByteCount)

#define objDataSize(ooop) rawObjDataSize(ooop) /* byte size of any object */
#define objBodySize(ooop) rawObjBodySize(ooop)

#define objByteDataSize(ooop) (assert(!objHasPtrs(ooop)), rawObjDataSize(ooop))
#define objOopDataSlots(ooop)  sizeInOops(rawObjDataSize(ooop))
#define objOopBodySlots(ooop) sizeInOops(objBodySize(ooop))

/* These two are *only* for placeBodySizeInBody */
#define objSizeFieldSlots(ooop) sizeInOops(objSizeField(ooop))
#define objOvflSizeSlots(ooop) (sizeInOops(objSizeOvflField(ooop)) + sizeOvflSlotCount)

/*
 * The following size setting macros are PRIVATE to the memory manager.  There
 * are a number of pitfalls here.  In particular in the 64-bit system the size
 * field is a slot count, but in the 32-bit system it is a byte count.
 */
#define sizeMaxNormalBytes ((oopUInt)sizeMaxNormalVal)

/* The size field, if not the actual size, should be preserved. */
#define resetNonPtrObjDataSize(ooop, sizeOfData) do { \
	if (objSizeInHeader(ooop)) \
		setObjSizeField(ooop, sizeOfData); \
	else \
		setObjSizeOvflField(ooop, sizeOfData); \
} while (0)

#define resetPtrObjDataSlots(o, slots) resetNonPtrObjDataSize(o, oopsToBytes(slots))

#define setObjDataSizeInOvflField(ooop, sizeOfData, specialSizeEncoding) do { \
	setObjSizeField(ooop, specialSizeEncoding); \
	setObjSizeOvflField(ooop, sizeOfData); \
} while (0)

#define setNonPtrObjDataSizeInHeader(o,sizeOfData) setObjSizeField(o,sizeOfData)

#define setObjDataSize(ooop, sizeOfData) do { \
	if (!sizeOvfl(sizeOfData)) \
		setObjSizeField(ooop, sizeOfData); \
	else \
		setObjDataSizeInOvflField(ooop, sizeOfData, sizeOvflVal); \
} while (0)

/*
 * Macro to avoid shift implicit in
 * oop *dataPtr = objDataPtr(objOop);
 * oop *stop = dataPtr + objOopDataSlots(objOop);
 */
#define stopPtrForObj(objOop,dataPtr) ((oop *)((byte *)(dataPtr) + rawObjDataSize(objOop)))
