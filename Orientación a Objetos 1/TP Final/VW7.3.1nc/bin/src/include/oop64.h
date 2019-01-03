/* SccsId is @(#)oop64.h	58.10 04/06/05 */
/************************************************************************
 * File: oop64.h
 *
 * This file contains the definitions associated with oops and otEntries
 * on 64-bit platforms.
 *
 *	Copyright (C) 2004 Cincom Systems, Inc.
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
			unsigned long pointer		: 61;
			unsigned unusedPtrBit2		: 1;
			unsigned isForwarded		: 1;
			unsigned needsScanning		: 1;
# elif RIGHT_BIT_FIELD_ORDER
			unsigned needsScanning		: 1;
			unsigned isForwarded		: 1;
			unsigned unusedPtrBit2		: 1;
			unsigned long pointer		: 61;
# else
#	error "plat header file must define compiler's bit ordering"
# endif
# define needsScanningBit				0
# define isForwardedBit					1
		} forwarding;
	  	/* Nobody actually USES this, but it helps in debugging. */
		quantum *toQuanta;
		/* for encoding up to 8-byte values in the indirection. */
		double	 doubleValue;
		byte	 bytes[8];
	} ptr;
	union { /* object's header flags, classTag, size and hash */
		oopUInt flagWord;
		oopInt  flagOopInt;
# if LEFT_BIT_FIELD_ORDER
#	define oopHeaderBitFields(indexabilityOddnessField,gcSpecialFields)	\
			unsigned hasPtrs			: 1; \
			unsigned unusedFlagWordBit62: 1; \
			unsigned hash				:20; \
				indexabilityOddnessField	 \
			unsigned isMarked			: 1; \
			unsigned isImmutable		: 1; \
			unsigned size				: 8; \
				gcSpecialFields				 \
			unsigned inRt				: 1; \
			unsigned inOldRt			: 1; \
			unsigned classTagField		:20;

#	define gcSpecialAsPair \
			unsigned isEphemeronNotWeak	: 1;	/* 23    */ \
			unsigned isGCSpecial		: 1;	/* 22    */

#	define nonPtrIndexabilityField \
			unsigned pad				: 4;				\
			unsigned dataInPointerField	: 1;	/* 37	 */ \
			unsigned oddBytes			: 3;	/* 34-36 */

#	define everythingButTheGirl \
			unsigned long dummyObjSlotCount	:44; \
			unsigned long classTagField		:20;

# elif RIGHT_BIT_FIELD_ORDER
#	define oopHeaderBitFields(indexabilityOddnessField,gcSpecialFields)	\
			unsigned classTagField		:20;	/*  0-19 */	\
			unsigned inOldRt			: 1;	/* 20    */	\
			unsigned inRt				: 1;	/* 21    */	\
				gcSpecialFields					/* 22-23 */	\
			unsigned size				: 8;	/* 24-31 */	\
			unsigned isImmutable		: 1;	/* 32    */	\
			unsigned isMarked			: 1;	/* 33    */	\
				indexabilityOddnessField		/* 34-41 */	\
			unsigned hash				:20;	/* 42-61 */	\
			unsigned unusedFlagWordBit62: 1;	/* 62    */	\
			unsigned hasPtrs			: 1;	/* 63    */

#	define gcSpecialAsPair \
			unsigned isGCSpecial		: 1;	/* 22    */ \
			unsigned isEphemeronNotWeak	: 1;	/* 23    */

#	define nonPtrIndexabilityField \
			unsigned oddBytes			: 3;	/* 34-36 */ \
			unsigned dataInPointerField	: 1;	/* 37	 */ \
			unsigned pad				: 4;

#	define everythingButTheGirl \
			unsigned long classTagField		:20; \
			unsigned long dummyObjSlotCount	:44;
# endif
/**** NOTE: Some of these are duplicated in unsafe_oops.h */
# define firstClassTagBit			 0
# define	bitsInClassTag			20
# define oldRtFlagBit				20
# define firstDummyObjSlotCountBit	20
# define bitsInDummyObjSlotCount	44
# define rtFlagBit					21
# define gcSpecialFlagBit			22
# define ephemeronNotWeakFlagBit	23
# define firstGCSpecialFieldBit		gcSpecialFlagBit
# define	bitsInGCSpecialField	 2
# define firstSizeBit				24
# define	bitsInSize				 8
# define isImmutableBit				32
# define markedFlagBit				33
# define firstIndexabilityBit		34
# define	bitsInIndexabilityField	 8
# define firstOddBytesBit			firstIndexabilityBit
# define	bitsInOddBytesField		log2bytesInOop
# define dataInPointerFieldBit		(firstOddBytesBit + bitsInOddBytesField)
# define firstHashBit				42
# define	bitsInHash				20
# define hasPtrsFlagBit				63
		struct {
			oopHeaderBitFields(	unsigned indexabilityField	: 8;	/* 34-41 */,
								gcSpecialAsPair)
		} bits;
		struct {
			oopHeaderBitFields(	nonPtrIndexabilityField,
								unsigned gcSpecial			: 2;	/* 22-23 */)
		} bitsAlt;
		struct {
			everythingButTheGirl
		} bitsNS;
	} misc;
} otEntry, *oop;
#endif /* assembly */

#define slotsInOtEntry (sizeof(otEntry) / sizeof(oop))

#define objIndexabilityField(obj) ((obj)->misc.bits.indexabilityField)
#define oddBytesMask ((1<<log2bytesInOop)-1)
#define objOddBytes(obj) ((obj)->misc.bitsAlt.oddBytes)
#define objDataInPointerField(obj) ((obj)->misc.bitsAlt.dataInPointerField)
#define dummyObjSlotCount(obj) ((obj)->misc.bitsNS.dummyObjSlotCount)
/* Private Store Macros */
#define setObjOddBytes(obj,n) ((obj)->misc.bitsAlt.oddBytes = (n))
#define setObjDataInPointerField(obj,bv) ((obj)->misc.bitsAlt.dataInPointerField = (bv))
#define setObjIndexabilityField(obj,n) ((obj)->misc.bits.indexabilityField = (n))
#define setDummyObjSlotCount(obj,n) ((obj)->misc.bitsNS.dummyObjSlotCount = (n))

/***** NOTE: Some of these are duplicated in unsafe_oops.h */

#define nonOop ((oop)0)
#define numTagBits 3
#define numLitBits (bitsInOop - numTagBits)
#define tagBitsMask ((1<<numTagBits)-1)
#define signBitMask (-1L << (bitsInOop - 1))
#define allButSignMask ((q64)-1 >> 1)
#define maxSigBits (numLitBits - 1)
#define oopNum(ooop) ((oopInt)(ooop))
#define oopBits(ooop) ((oopUInt)(ooop))
#define tagBits(ooop) ((oopUInt)(ooop) & tagBitsMask)


/* Representation of immediate quantities */
#define immBit 0
#define immBit1Rel 1 /* for glue */
#define immBitBE 63  /* for HP glue */
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
#define intBitBE 62  /* for HP glue */
#define intBitState 1
#if intBitState
/* NOTE: Duplicated in unsafe_oops.h */
#	define oopIsInt(ooop) ((oopBits(ooop) & (1<<intBit)) != 0)
#else
#	define oopIsInt(ooop) ((oopBits(ooop) & (1<<intBit)) == 0)
#endif
#define intTag ((intBitState<<intBit)|(immBitState<<immBit))

/* Representation of immediate SmallDoubles */
#define dblBit 2
#define dblBit1Rel 3 /* for glue */
#define dblBitBE 61  /* for HP glue */
#define dblBitState 1
#if dblBitState
/* NOTE: Duplicated in unsafe_oops.h */
#	define oopIsSmallDouble(ooop) ((oopBits(ooop) & (1<<dblBit)) != 0)
#else
#	define oopIsSmallDouble(ooop) ((oopBits(ooop) & (1<<dblBit)) == 0)
#endif
#define dblTag ((dblBitState<<dblBit)|(immBitState<<immBit))

/* Representation of immediate Characters */
#define charTag (((1-intBitState)<<intBit)|((1-dblBitState)<<dblBit)|(immBitState<<immBit))
#define oopIsChar(ooop) (tagBits(ooop) == charTag)

/* NOTE: Duplicated in unsafe_oops.h */
#define oopIntVal(ooop) arithRShift(oopNum(ooop), numTagBits)
#define oopUIntVal(ooop) (oopBits(ooop) >> numTagBits)
/* NOTE: Duplicated in unsafe_oops.h */
#define asSmallInt(value) ((oop) (((oopInt)(value) << numTagBits) + intTag))

#define asChar(value) ((oop) (((oopUInt)(value) << numTagBits) + charTag))
#define oopCharVal(ooop) (oopBits(ooop) >> numTagBits)

/*
 * Class-related definitions.
 */
#define ObjectsHaveDirectClassPointer 0
/*
 * Returns the class of the oop, even if it is immediate.
 */
/* NOTE: Duplicated in unsafe_oops.h */
#define immClass(ooop) (firstClassTablePage[tagBits(ooop)])
#define oopClass(ooop) (oopIsImm(ooop) ? immClass(ooop) : objClass(ooop))
#define oopClassTag(ooop) (oopIsImm(ooop) ? tagBits(ooop) : objClassTag(ooop))
#define nonClassTag 0

#define objClassTag(ooop) ((ooop)->misc.bits.classTagField)
#define classTagMaxVal ((1<<bitsInClassTag)-1)
/* MaxPunnedClassHash should be sysOop index but few include sysOop.h */
#define MaxPunnedClassHash 10
#if !defined(assembly)
typedef q32 classTag; /* type big enough to hold an objClassTag */
#endif

/* NOTE: Duplicated in unsafe_oops.h */
#if !defined(assembly)
extern DLUP_IMPORT(oop *)	classTable[];
extern DLUP_IMPORT(oop *)	firstClassTablePage;
#endif
#define classTabIdxHi(n) ((oopUInt)(n) >> (bitsInClassTag/2))
#define classTabIdxLo(n) ((n) & ((1<<(bitsInClassTag/2))-1))
#define classFromClassTag(t) (classTable[classTabIdxHi(t)][classTabIdxLo(t)])
#define classTagFromClass(cls) objHash(cls)
#define objClass(ooop)	classFromClassTag(objClassTag(ooop))
#define validClassIdHash(h) ((h) > 0 && (h) <= classTagMaxVal \
							&& classTable[classTabIdxHi(h)] \
							&& !oopIsImm(classFromClassTag(h)) \
							&& (objHash(classFromClassTag(h)) == (h) \
							   || (h) <= MaxPunnedClassHash))
#define classHasValidIdHash(cl) (!oopIsImm(cl) \
							&& objHash(cl) \
							&& classTable[classTabIdxHi(objHash(cl))] \
							&& classTable[classTabIdxHi(objHash(cl))] \
										 [classTabIdxLo(objHash(cl))] == (cl))

/* Representation of ordinary objects (pointers to ot entries). */
/* At the moment, only the translator uses this: */
/* all other code assumes that ptrTag == 0. */
#define ptrTag (((1-intBitState)<<intBit)+((1-immBitState)<<immBit))

#define asOopPtr(ptr) ((oop *)(oopInt)(ptr))

/*
 * Public macros for accessing the fields of an object's header.
 *
 * Even though these macros are considered public, you should think twice about
 * using them. In general, only special purpose code utilizes these macros.
 * This is especially true of the store macros.
 */

/* Public Store Macros */
#define setObjClassTag(ooop,ct) ((ooop)->misc.bits.classTagField = (ct))

/* Public Fetch Macros */
/* NOTE: Duplicated in unsafe_oops.h */
#define objDataPtr(ooop, type) ((type *)((ooop)->ptr.toOops))
#define fwObjDataPtr(ooop, type) objDataPtr(ooop, type)

/*
 * Size accessing macros specific to word size.
 */
/* Reserve some special values for size */
#define numSizeValuesReserved (4)

#define rawObjDataSize(ooop) (objSizeInHeader(ooop) \
							? oopsToBytes(objSizeField(ooop)) \
							: objSizeOvflField(ooop))

#define rawObjBodySize(ooop) (objSizeInHeader(ooop) \
							? oopsToBytes(objSizeField(ooop)) \
							: objSizeOvflField(ooop) + sizeOvflByteCount)

#define objBodySize(ooop) rawObjBodySize(ooop)

#define objDataSize(ooop) (rawObjDataSize(ooop) /* byte size of any object */ \
							- (objHasPtrs(ooop) ? 0 : objOddBytes(ooop)))
#define objByteDataSize(ooop) (assert(!objHasPtrs(ooop)), \
								rawObjDataSize(ooop) - objOddBytes(ooop))

#define objOopDataSlots(ooop) (objSizeInHeader(ooop) \
								? objSizeField(ooop) \
								: bytesToOops(objSizeOvflField(ooop)))
#define objOopBodySlots(ooop) (objSizeInHeader(ooop) \
								? objSizeField(ooop) \
								: bytesToOops(objSizeOvflField(ooop)) + sizeOvflSlotCount)

/* These two are *only* for placeBodySizeInBody */
#define objSizeFieldSlots(ooop) objSizeField(ooop)
#define objOvflSizeSlots(ooop) (bytesToOops(objSizeOvflField(ooop)) + sizeOvflSlotCount)

/*
 * The following size setting macros are PRIVATE to the memory manager.  There
 * are a number of pitfalls here.  In particular in the 64-bit system the size
 * field is a slot count, but in the 32-bit system it is a byte count.
 */
#define sizeMaxNormalBytes ((oopUInt)oopsToBytes(sizeMaxNormalVal))

/* The size field, if not the actual size, should be preserved. */
#define resetPtrObjDataSlots(ooop, slotsInData) do { \
	assert(objHasPtrs(ooop)); \
	if (objSizeInHeader(ooop)) \
		setObjSizeField(ooop, slotsInData); \
	else \
		setObjSizeOvflField(ooop, oopsToBytes(slotsInData)); \
} while (0)

#define resetNonPtrObjDataSize(ooop, sizeOfData) do { \
	oopUInt _roundedBytes = roundUpToUnit(sizeOfData,bytesInOop); \
	assert(!objHasPtrs(ooop)); \
	if (objSizeInHeader(ooop)) \
		setObjSizeField(ooop, bytesToOops(_roundedBytes)); \
	else \
		setObjSizeOvflField(ooop, _roundedBytes); \
	setObjIndexabilityField(ooop, _roundedBytes - (sizeOfData)); \
} while (0)

#define setNonPtrObjDataSizeInHeader(ooop, sizeOfData) do { \
	oopUInt _roundedBytes = roundUpToUnit(sizeOfData,bytesInOop); \
	setObjSizeField(ooop, bytesToOops(_roundedBytes)); \
	setObjIndexabilityField(ooop, _roundedBytes - (sizeOfData)); \
} while (0)

#define setObjDataSizeInOvflField(ooop, sizeOfData, specialSizeEncoding) do{\
	setObjSizeField(ooop, specialSizeEncoding);								\
	setObjSizeOvflField(ooop, sizeOfData);									\
} while (0)

#define setObjDataSize(ooop, sizeOfData) do {								\
	oopUInt _roundedBytes = roundUpToUnit(sizeOfData,bytesInOop);			\
	if (!sizeOvfl(_roundedBytes))											\
		setObjSizeField(ooop, bytesToOops(_roundedBytes));					\
	else																	\
		setObjDataSizeInOvflField(ooop, _roundedBytes, sizeOvflVal);		\
	if (!objHasPtrs(ooop))													\
		setObjIndexabilityField(ooop, _roundedBytes - (sizeOfData));		\
} while (0)

#define setPtrObjDataSize(ooop, fixedSlots, sizeOfData) do {				\
	oopUInt _roundedBytes = roundUpToUnit(sizeOfData,bytesInOop);			\
	if (!sizeOvfl(_roundedBytes))											\
		setObjSizeField(ooop, bytesToOops(_roundedBytes));					\
	else																	\
		setObjDataSizeInOvflField(ooop, _roundedBytes, sizeOvflVal);		\
	setObjIndexabilityField(ooop, fixedSlots);								\
} while (0)

#define setByteObjDataSize(ooop, sizeOfData) do {							\
	oopUInt _roundedBytes = roundUpToUnit(sizeOfData,bytesInOop);			\
	if (!sizeOvfl(_roundedBytes))											\
		setObjSizeField(ooop, bytesToOops(_roundedBytes));					\
	else																	\
		setObjDataSizeInOvflField(ooop, _roundedBytes, sizeOvflVal);		\
	setObjIndexabilityField(ooop, _roundedBytes - (sizeOfData));			\
} while (0)

/*
 * The following definition is temporary, at least for instance creation.
 * On instance creation we would like to set the indexability and size fields
 * with the single assignment of the flags field.
 */
#define setObjDataSizeGivenFixedFields(ooop, fixedSlots, sizeOfData) do {	\
	if (objHasPtrs(ooop))													\
		setPtrObjDataSize(ooop, fixedSlots, sizeOfData);					\
	else																	\
		setByteObjDataSize(ooop, sizeOfData);								\
} while (0)

/*
 * Macro to avoid rounding arithmetic implicit in
 * oop *dataPtr = objDataPtr(obj);
 * oop *stop = dataPtr + objOopDataSlots(obj);
 */
#define stopPtrForObj(obj,dataPtr) ((oop *)((byte *)(dataPtr) + rawObjDataSize(obj)))
