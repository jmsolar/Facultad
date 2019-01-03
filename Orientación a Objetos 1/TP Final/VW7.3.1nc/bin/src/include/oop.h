/* SccsId is @(#)oop.h	58.10 04/06/05 */
/************************************************************************
 * File: oop.h
 *
 * This file contains the definitions associated with oops and otEntries.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#if HPS64
# include "oop64.h"
#elif HPS32
# include "oop32.h"
#else
# error "neither HPS32 nor HPS64 is defined"
#endif

#if NO_BIT_FIELDS
# include "nbfObjHeaderAccess.h"
#else
# define objHash(ooop) ((ooop)->misc.bits.hash)
/* NOTE: Duplicated in unsafe_oops.h */
# if hasPtrsFlagBit == (bitsInOop - 1) /* must be sign bit */
#	define objHasPtrs(ooop) ((ooop)->misc.flagOopInt < 0)
# else
#	define objHasPtrs(ooop) ((ooop)->misc.bits.hasPtrs)
# endif
# define objSizeField(ooop) ((ooop)->misc.bits.size)
# if IMMUTABILITY
#	define objIsImmutable(ooop) ((ooop)->misc.bits.isImmutable)
# endif

/* Public Store Macros */
# define setObjDataPtr(ooop, dataPtr) ((ooop)->ptr.toOops = asOopPtr(dataPtr))
# define setObjHash(ooop, hashValue) ((ooop)->misc.bits.hash = (hashValue))
# define setObjHasPtrs(ooop, boolVal) ((ooop)->misc.bits.hasPtrs = (boolVal))
# if IMMUTABILITY
#	define setObjIsImmutable(ooop, boolVal) ((ooop)->misc.bits.isImmutable = (boolVal))
# endif

/*
 * Private macros for accessing the fields of an object's header.
 *
 * Subsytems other than the memory manager should NOT use these
 * macros. They only appear in this file in order to facilitate
 * their automatic inclusion according to the specifications
 * in platform.h and because various other public macros
 * utilize these macros.
 */

/* Private Fetch Macros */
/* NOTE: Duplicated in unsafe_oops.h */
# define objInRt(ooop) ((ooop)->misc.bits.inRt)
# define objIsMarked(ooop) ((ooop)->misc.bits.isMarked)
# define objForwardingPtr(ooop) ((oop)((ooop)->ptr.forwarding.pointer << log2bytesInOop))
# define objIsForwarded(ooop) ((ooop)->ptr.forwarding.isForwarded)
# define objInOldRt(ooop) ((ooop)->misc.bits.inOldRt)
# define objIsGCSpecial(ooop) ((ooop)->misc.bits.isGCSpecial)
# if EPHEMERONS
#	define objIsEphemeronNotWeak(ooop) ((ooop)->misc.bits.isEphemeronNotWeak)
# endif

/* Private Store Macros */
# define setObjInRt(ooop, boolVal) (objInRt(ooop) = (boolVal))
# define setObjIsMarked(ooop, boolVal)  (objIsMarked(ooop) = (boolVal))
# define setObjForwardingPtr(ooop, newOop) ((ooop)->ptr.forwarding.pointer = oopBits(newOop) >> log2bytesInOop)
# define setObjIsForwarded(ooop, boolVal) ((ooop)->ptr.forwarding.isForwarded = (boolVal))
# define setObjInOldRt(ooop, boolVal) (objInOldRt(ooop) = (boolVal))
# define setObjIsGCSpecial(ooop, boolVal) (objIsGCSpecial(ooop) = (boolVal))
# if EPHEMERONS
#	define setObjIsEphemeronNotWeak(ooop, boolVal) \
			(objIsEphemeronNotWeak(ooop) = (boolVal))
# endif
/*
 * The following size setting macro is PRIVATE to the memory manager.  There
 * are a number of pitfalls here.  In particular in the 64-bit system the size
 * field is a slot count, but in the 32-bit system it is a byte count.  Hence
 * the special size values sizeMaxNormalVal et al are in sizeField units;
 * _bytes_ in the 32-bit system, but _slots_ in the 64-bit system.
 */
# define setObjSizeField(ooop, n) (objSizeField(ooop) = (n))
#endif /* NO_BIT_FIELDS */
#define objMiscFlagWord(ooop) ((ooop)->misc.flagWord)
#define setObjMiscFlagWord(ooop, flagWord) (objMiscFlagWord(ooop) = (flagWord))

/*
 * Masks for the object header's flagword.
 */
/**** NOTE: Some of these are duplicated in unsafe_oops.h */
#define hashMask (((1L << bitsInHash) - 1) << firstHashBit)
/* This has to be a power of two minus one for tmakeQ */
#define sizeMaxVal ((1L << bitsInSize) - 1)
#define sizeMaxNormalVal (sizeMaxVal - numSizeValuesReserved)

/* Special values of size:
   sizeOvflVal		The body is in new, old, or permSpace, and size is at [-1]
   sizeLargeVal		The body is in largeSpace, and size is at [-1]
   sizeFixedVal		The body is in fixedSpace, and size is at [-1]
   sizeHandleVal    The body is outside of any known space, malloced perhaps,
                    and size is at [-1]
   maybe more unallocated
 */


/* These values, the range, and the checking macros should remain private
   to this file. Any code that is interested in the existence of the overflow
   field should use the macros for that, not go looking at the value of the
   size field.

   sizeOvflVal should always be sizeMaxNormalVal+1 so that values from
   zero to sizeOvflVal all belong in perm/old/new space, and none of the
   tag values are in the middle of that range.
 */
#define sizeOvflVal        (sizeMaxNormalVal+1)
#define sizeLargeSpaceVal  (sizeMaxNormalVal+2)
#define sizeFixedSpaceVal  (sizeMaxNormalVal+3)
#define sizeHandleSpaceVal (sizeMaxNormalVal+4)

#define objSizeOvfl(ooop) (objSizeField(ooop) == sizeOvflVal)
#define objSizeLargeSpace(ooop)  (objSizeField(ooop) == sizeLargeSpaceVal)
#define objSizeFixedSpace(ooop)  (objSizeField(ooop) == sizeFixedSpaceVal)
#define objSizeHandleSpace(ooop) (objSizeField(ooop) == sizeHandleSpaceVal)
#define objSizeNontaggedSpace(ooop) (objSizeField(ooop)<=(unsigned)sizeOvflVal)

/* testing of the fixity of an object's data */
#define objDataImmobile(obj) (objSizeFixedSpace(obj) || objSizeHandleSpace(obj))

#define isForwardedMask (1L << isForwardedBit)
#define isImmutableMask (1L << isImmutableBit)
#define gcSpecialMask  (1L << gcSpecialFlagBit)
# if EPHEMERONS
# define isEphemeronNotWeakMask (1<< ephemeronNotWeakFlagBit)
#else
# define isCheckMarkedMask (1L << checkMarkedFlagBit)
#endif
#define inRtMask (1L << rtFlagBit)
#define isMarkedMask (1L << markedFlagBit)
#define inOldRtMask (1L << oldRtFlagBit)
#define hasPtrsMask (1UL << (oopUInt)hasPtrsFlagBit)
/*
 * The objDataField macro is provided as a short-hand for accessing an object's
 * data fields. Obviously you would not use it if you had cached the address to
 * the data and were using this address, for instance, to avoid the unnecessary
 * indirection while fetching a set of consecutive values.
 */
#define objDataField(ooop, type, index) *(objDataPtr(ooop, type) + (index))

/*
 * DON'T use this macro unless you've already done a store check.
 * Use the storeOop macros in mm.h instead.
 */
#define setObjDataField(ooop, type, index, val) \
	(*(objDataPtr(ooop, type) + (index)) = (val))

#if platform == platAOSF
/* xtaso variation
 * additional variants on objDataField and setObjDataField are needed at the
 * "firewall" between 32 bit and 64 bit pointers under xtaso on OSF-AXP.
 * the fw prefix indicates a firewall routine.
 *
 * these are the xtaso special alternates, used at sensitive points in the plat
 * code for AOSF builds.
 */
# define fwObjDataField(ooop, type, index) \
        ((type)(((ooop)->ptr.toOops)[index]))

# define fwSetObjDataField(ooop, type, index, val) \
        (((ooop)->ptr.toOops)[index] = (oop)(val))

#else
# define fwObjDataField(ooop, type, index) objDataField(ooop, type, index)

# define fwSetObjDataField(ooop, type, index, val) \
        setObjDataField(ooop, type, index, val)
#endif


/*
 * Size overflow macros
 */

/* The size of an object can be in the header, in the overflow field, or
   outside of hps.
   */
#define objSizeInHeader(ooop) (objSizeField(ooop) <= (oopUInt)sizeMaxNormalVal)

/* The following definition is "correct" but slow.  Since we don't currently
 * use any of the reserved overflow sizes we use the subsequent definition.
 */
#if 0
#	define objSizeInOvflField(ooop) \
	((objSizeField(ooop) == sizeOvflVal) \
	 || (objSizeField(ooop) == sizeLargeSpaceVal) \
	 || (objSizeField(ooop) == sizeFixedSpaceVal) \
	 || (objSizeField(ooop) == sizeHandleSpaceVal))
#else
#	define objSizeInOvflField(ooop) (objSizeField(ooop) >= (unsigned)sizeOvflVal)
#endif

#define objSizeReallyInOvflField(ooop) \
	((objSizeField(ooop) == sizeOvflVal) \
	 || (objSizeField(ooop) == sizeLargeSpaceVal) \
	 || (objSizeField(ooop) == sizeFixedSpaceVal) \
	 || (objSizeField(ooop) == sizeHandleSpaceVal))

#define sizeOvfl(dataSize) ((oopUInt)(dataSize) > sizeMaxNormalBytes)
#define sizeOvflSlotCount	(1)
#define sizeOvflByteCount	oopsToBytes(sizeOvflSlotCount)

#define sizeOvflSlots(dataSize) (sizeOvfl(dataSize) ? sizeOvflSlotCount : 0)

#define sizeLargeOvflSlots(dataSize) sizeOvflSlotCount

#define sizeHandleOvflSlots(dataSize) sizeOvflSlotCount

#define objSizeOvflSlots(obj) (objSizeInOvflField(obj) ? sizeOvflSlotCount : 0)

/*
 * Size accessing macros common across 32-bit and 64-bit engines.
 */
#define objSizeOvflField(obj) objDataField(obj, oopUInt, -sizeOvflSlotCount)

#define setObjSizeOvflField(obj, size) \
			setObjDataField(obj, oopUInt, -sizeOvflSlotCount, size)

#define setObjDataSizeTaggedSpace(ooop, sizeOfData, specialSizeEncoding) do { \
	if ((specialSizeEncoding) == sizeLargeSpaceVal \
	 || (specialSizeEncoding) == sizeFixedSpaceVal) \
		setObjDataSizeInOvflField(ooop, sizeOfData, specialSizeEncoding); \
	else \
		assertf("bogus special size encoding"); \
} while (0)

#define sizeInOops(sizeInBytes) (bytesToOops((sizeInBytes)+(bytesInOop-1)))

/*
 * Class-related definitions.
 */
/* Check if an oop can be accessed like an (oop) Array, ByteArray, ByteString
 * or TwoByteString.  This check avoids the function call to basicAccessClass
 * in the simple case.
 */
#if !defined(assembly)
extern classTag basicAccessClass(classTag, bool);
#endif
#if ObjectsHaveDirectClassPointer
# define isLike(ooop, clsTag, writable) (!oopIsImm(ooop) \
    && (   sysOop(clsTag) == objClass(ooop) \
		|| sysOop(clsTag) == basicAccessClass(objClass(ooop), writable)))
# define basicAccessToClassTag(clsTag) sysOop(clsTag)
#else
# define isLike(ooop, clsTag, writable) (!oopIsImm(ooop) \
    && (   clsTag == objClassTag(ooop) \
		|| clsTag == basicAccessClass(objClassTag(ooop), writable)))
# define basicAccessToClassTag(clsTag) (clsTag)
#endif

/* Check whether an oop refers to an object with a variable byte array */
#define isByteLike(ooop) (!oopIsImm(ooop) && !objHasPtrs(ooop))

/* Check if an oop is a boolean */
#define oopIsBool(o) ((o) == sysOop(trueOopX) || (o) == sysOop(falseOopX))

/*
 * Object body defs.
 */
#define objBodyPtr(ooop, type) (objSizeInHeader(ooop) \
						? objDataPtr(ooop, type) \
						: (type *)(objDataPtr(ooop, oop) - sizeOvflSlotCount))

/*
 * The objVarDataPtr macro answers a pointer to the variable (arrayed)
 *   part of an object.  It requires class.h.
 */
/* NOTE: Duplicated in unsafe_oops.h */
#define objVarDataPtr(ooop) (objDataPtr(ooop, oop) + numFixedFields(ooop))

/*
 * The objVarOopSize macro answers the size of the variable (arrayed)
 *   part of an object.  It requires class.h.
 */
/* NOTE: Duplicated in unsafe_oops.h */
#define objVarOopSize(ooop) (objOopDataSlots(ooop) - numFixedFields(ooop))

/* comvenience macro for sizing C structs. */
#define oopsizeof(cType) bytesToOops(sizeof(cType))
