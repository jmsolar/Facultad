/* SccsId is  @(#)mmAllocate.h	58.10 04/06/05 */
/************************************************************************
 * File: mmAllocate.h
 *
 * This file contains the definitions associated with the memory manager's
 * allocation routines.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/*
 * Object Size definitions.
 */
#define dataSizeIsLarge(sizeInBytes) ((sizeInBytes) > maxSmallObjDataSize)
#define slotSizeIsLarge(sizeInSlots) ((sizeInSlots) > bytesToOops(maxSmallObjDataSize))
#if HPS64
# define maxSmallObjDataSize 2048L
#else
# define maxSmallObjDataSize 1024L
#endif
#define maxSmallObjSlotSize bytesToOops(maxSmallObjDataSize)
/*
 * Public Allocation Functions
 *
 * The simplest way to allocate an object is to call one of the
 * two functions listed below, passing them the classOop of the
 * type of object that you want allocated. For fixed-size objects
 * use allocFSObj and for variable-size objects use allocVSObj.
 * Both functions will return the nonOop if the object cannot be
 * allocated. Both functions fully initialize the object.
 *
 * Note that both functions assume that you are passing in
 * the correct kind of class. That is, allocFSObj assumes that
 * you are passing in a fixedSizeClass and allocVSObj assumes
 * that you are passing in a variableSizeClass. If you don't
 * know what kind of class you have, you can call the classType
 * function, passing it the oop of your class and it will return
 * one of three values listed below.
 */
extern oop allocFSObj(oop);
extern oop allocVSObj(oop, memIndex);

#define notAClass 0
#define fixedSizeClass 1
#define variableSizeClass 2
extern int classType(oop);

/*
 * Public Allocation Macros
 *
 * There are several varieties of object allocation macros; however, all
 * of the macros are similar in that the first argument in the calling
 * sequence must be a variable that the macro can use to pass back the
 * oop of the newly allocated object. In addition, the caller must specify
 * the class and the size (in bytes) of the new object. If the allocation
 * fails, this fact is signalled by passing back the nonOop via the first
 * argument rather than the actual oop of the new object. The caller
 * should check for this possibility. In general, one should invoke these
 * macros to perform an allocation rather than invoking the underlying
 * allocation functions directly. Not only do the macros have a simpler
 * interface than the underlying functions, but some of the allocations
 * can be performed entirely by the macro, thus obviating the need for a
 * procedure call.
 *
 * The macros can differ from each other in the following respects:
 *
 * Data Initialization--Some macros initialize the data fields of the
 * new object; others simply leave the data uninitialized. The macros
 * that contain the prefix "calloc" DO initialize the object's data to a
 * default value (zero or nil, depending upon whether the object is a pointer
 * object or not), whereas those macros beginning with "alloc" leave the
 * object uninitialized, and the "ialloc" routines initialize the object
 * to a user-specified value. The VM typically uses the "alloc" macros because
 * it will have to initialize the objects itself, whereas the new and
 * new: primitives use the "calloc" macros.
 *
 * Ptrs vs NonPtrs--Those macros with the word "Ptr" in them create
 * objects whose data is strictly composed of pointers, and those with the
 * word "NonPtr" in them create objects whose data contains no pointers.
 * With the Ptr macros one should use the IdxPtr forms for indexable classes
 * and the plain Ptr forms for non-indexable classes.  The IdxPtr forms take
 * an additional argument: the number of fixedFields in slots.  This allows
 * the 64-bit implementation to keep the number of fixed fields in the header
 * rather than in the class's format word, providing much faster indexing in
 * the at:[put:] primitives.
 *
 * Classes vs class tags--Those macros with the word "Tag" in them create
 * instances of classes whose sysOopRegistry index or classTable index is
 * supplied as the argument.  Those macros without the word "Tag" in them
 * create instances of the class object which is supplied as an argument.
 *
 * Data Size--The ptr macros don't round up the data size (which is
 * specified in terms of bytes). That is, they assume that the data size
 * is already a multiple of the number of bytes contained in a single oop
 * (typically four). On the other hand, all of the non-ptr macros do round
 * up the data size, except those that have the word "OopSized" in them.
 * The "OopSized" macros assume that data size is already rounded and
 * therefore run slightly faster.
 *
 * Large Objects--To allocate large objects, one should use the macros with
 * "Large" in them. These macros will house the object in the optimal way.
 * If you use the other macros for allocating large objects, then the allocation
 * may fail for lack of space, or you may subsequently get non-optimal
 * performance. You should use the dataSizeIsLarge(sizeInBytes) macro to
 * determine if the size of your proposed object is considered to be large from
 * the memory manager's point of view.
 */

/*
 * Standard allocation macros--no initialization.
 */
#define allocPtrObj(ooop, class, size) \
	allocObj(ooop, class, bytesToOops(size), size, flagWordWithPtrOn, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
#define tagAllocPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), bytesToOops(size), size, flagWordWithPtrOn, \
				dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
#define allocIdxPtrObj(ooop, class, numFixedSlots, byteSize) \
	allocObj(ooop, class, numFixedSlots, byteSize, flagWordWithPtrOn, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
#define tagAllocIdxPtrObj(ooop, clssTag, numFixedSlots, byteSize) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), numFixedSlots, byteSize, flagWordWithPtrOn, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
#define allocNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			 roundUpSize, dontInitData, nullInitVal, allocSmallObj)
#define tagAllocNonPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), 0, size, flagWordWithPtrOff, \
				roundUpSize, dontInitData, nullInitVal, allocSmallObj)
#define tagAllocOopSizedNonPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), 0, size, flagWordWithPtrOff, \
				dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
#define allocOopSizedNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
#if IMMUTABILITY
# define allocImmutableNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOffAndImmutabilityOn, \
			 roundUpSize, dontInitData, nullInitVal, allocSmallObj)
# define tagAllocImmutableNonPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), 0, size, \
				flagWordWithPtrOffAndImmutabilityOn, \
				roundUpSize, dontInitData, nullInitVal, allocSmallObj)
# define tagAllocOopSizedImmutableNonPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), 0, size, \
				flagWordWithPtrOffAndImmutabilityOn, \
				dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
# define allocOopSizedImmutableNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOffAndImmutabilityOn, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocSmallObj)
#endif

/*
 * Standard allocation macros--with default initialization.
 */
#define callocPtrObj(ooop, class, size) \
	allocObj(ooop, class, bytesToOops(size), size, flagWordWithPtrOn, \
			 dontRoundUpSize, initOopSizedData, sysOop(nilOopX), allocSmallObj)
#define callocIdxPtrObj(ooop, class, numFixedSlots, size) \
	allocObj(ooop, class, numFixedSlots, size, flagWordWithPtrOn, \
			 dontRoundUpSize, initOopSizedData, sysOop(nilOopX), allocSmallObj)
#define callocNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			 roundUpSize, initData, (oop)0, allocSmallObj)
#define tagCallocNonPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), 0, size, flagWordWithPtrOff, \
			 roundUpSize, initData, (oop)0, allocSmallObj)
#define callocOopSizedNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			 dontRoundUpSize, initOopSizedData, (oop)0, allocSmallObj)
#if IMMUTABILITY
# define callocImmutableNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOffAndImmutabilityOn, \
			 roundUpSize, initData, (oop)0, allocSmallObj)
# define tagCallocImmutableNonPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), 0, size, flagWordWithPtrOffAndImmutabilityOn, \
			 roundUpSize, initData, (oop)0, allocSmallObj)
#endif
/*
 * Standard allocation macros--with user-specified initialization.
 */
#define iallocPtrObj(ooop, class, size, initOop) \
	allocObj(ooop, class, bytesToOops(size), size, flagWordWithPtrOn, \
			dontRoundUpSize, initOopSizedData, initOop, allocSmallObj)
#define itagAllocPtrObj(ooop, clssTag, size, initOop) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), bytesToOops(size), size, flagWordWithPtrOn, \
			dontRoundUpSize, initOopSizedData, initOop, allocSmallObj)
#define iallocIdxPtrObj(ooop, class, numFixedSlots, size, initOop) \
	allocObj(ooop, class, numFixedSlots, size, flagWordWithPtrOn, \
			dontRoundUpSize, initOopSizedData, initOop, allocSmallObj)
#define iallocNonPtrObj(ooop, class, size, initVal) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			roundUpSize, initData, initVal, allocSmallObj)
#define itagAllocNonPtrObj(ooop, clssTag, size, initVal) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), 0, size, flagWordWithPtrOff, \
			roundUpSize, initData, initVal, allocSmallObj)
#define iallocOopSizedNonPtrObj(ooop, class, size, initVal) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			dontRoundUpSize, initOopSizedData, initVal, allocSmallObj)

/*
 * Large object allocation macros--with default initialization.
 */
#define callocLargePtrObj(ooop, class, size) \
	allocObj(ooop, class, numFixedFieldsForClass(class), size, flagWordWithPtrOn, \
	  dontRoundUpSize, initOopSizedData, sysOop(nilOopX), allocLargePointerObj)
#define callocLargeIdxPtrObj(ooop, class, numFixedSlots, size) \
	allocObj(ooop, class, numFixedSlots, size, flagWordWithPtrOn, \
	  dontRoundUpSize, initOopSizedData, sysOop(nilOopX), allocLargePointerObj)
#define callocLargeNonPtrObj(ooop, class, size) \
	ooop = allocLargeByteObj(classTagFromClass(class), size, flagWordWithPtrOff, (oop)0)

/*
 * Large object allocation macros--with user-specified initialization.
 */
#define iallocLargePtrObj(ooop, class, size, initOop) \
	allocObj(ooop, class, numFixedFieldsForClass(class), size, flagWordWithPtrOn, \
	  dontRoundUpSize, initOopSizedData, initOop, allocLargePointerObj)
#define iallocLargeNonPtrObj(ooop, class, size, initVal) \
	ooop = allocLargeByteObj(classTagFromClass(class), size, flagWordWithPtrOff, initVal)

/*
 * Flag Word Defs.
 */
#define flagWordWithPtrOn			((oopUInt) hasPtrsMask)
#define flagWordWithPtrOff			((oopUInt) 0)
#define flagWordWithPtrAndGCOn  	((oopUInt) (hasPtrsMask | gcSpecialMask))
#define flagWordWithPtrGCAndEphOn	((oopUInt) (hasPtrsMask \
											  | gcSpecialMask \
											  | isEphemeronNotWeakMask))
#if IMMUTABILITY
# define flagWordWithPtrOffAndImmutabilityOn ((oopUInt) isImmutableMask)
#endif

/*
 * Public Shrinking Macros
 */
extern memIndex shrinkOldObject(oop, memIndex, memIndex);
extern oop      shrinkOrCopyNewObj(oop, memUIndex);
extern oop      shrinkOrCopyPtrObj(oop, memUIndex);

/*
 * Private allocation macros
 *
 * The following allocation macros are private to the memory manager.
 * They are only included here because they depend on other macros
 * that must appear here to support the public macros. In general,
 * these macros vary according to the memory zone in which they attempt
 * to allocate the object.
 *
 * That is, macros with an "Ns" or an "Os" in them only
 * try to allocate the object in newSpace or oldSpace respectively and fail
 * if there isn't room. They don't try to place the object in another
 * space; presumably the caller is prepared to take the appropriate
 * corrective action (like allocating them in another space). Those macros
 * without an "Ns" or an "Os" will try to place the object in another space
 * if newSpace if filled up.
 */

#if defined(firstIndexabilityBit)
# define setIndexabilityIfNeeded(o,ifv) setObjIndexabilityField(o, ifv)
#else
# define setIndexabilityIfNeeded(o,ifv) 0
#endif

/*
 * NewSpace allocation macros--no initialization.
 */
#define allocNsPtrObj(ooop, class, size) \
	allocObj(ooop, class, bytesToOops(size), size, flagWordWithPtrOn, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocInNewSpace)
#define tagAllocNsPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), bytesToOops(size), size, flagWordWithPtrOn, \
				dontRoundUpSize, dontInitData, nullInitVal, allocInNewSpace)
#define allocNsIdxPtrObj(ooop, class, numFixedSlots, size) \
	allocObj(ooop, class, numFixedSlots, , size, flagWordWithPtrOn, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocInNewSpace)
#define tagAllocNsIdxPtrObj(ooop, clssTag, numFixedSlots, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), numFixedSlots, size, flagWordWithPtrOn, \
				dontRoundUpSize, dontInitData, nullInitVal, allocInNewSpace)
#define allocNsNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			 roundUpSize, dontInitData, nullInitVal, allocInNewSpace)
#define tagAllocNsNonPtrObj(ooop, clssTag, size) \
	tagAllocObj(ooop,classTagFromIndex(clssTag),0,size,flagWordWithPtrOff, \
				roundUpSize, dontInitData, nullInitVal, allocInNewSpace)
#define allocNsOopSizedNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
			 dontRoundUpSize, dontInitData, nullInitVal, allocInNewSpace)

/*
 * NewSpace allocation macros--with initialization.
 */
#define callocNsPtrObj(ooop, class, size) \
	allocObj(ooop, class, numFixedFieldsForClass(class), size, flagWordWithPtrOn, \
		dontRoundUpSize, initOopSizedData, sysOop(nilOopX), allocInNewSpace)
#define callocNsIdxPtrObj(ooop, class, fixedSlots, size) \
	allocObj(ooop, class, fixedSlots, size, flagWordWithPtrOn, \
			dontRoundUpSize, initOopSizedData, sysOop(nilOopX), allocInNewSpace)
#define tagCallocNsIdxPtrObj(ooop, clssTag, fixedSlots, size) \
	tagAllocObj(ooop, classTagFromIndex(clssTag), fixedSlots, size, flagWordWithPtrOn, \
			dontRoundUpSize, initOopSizedData, sysOop(nilOopX), allocInNewSpace)
#define callocNsNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
		roundUpSize, initData, (oop)0, allocInNewSpace)
#define callocNsOopSizedNonPtrObj(ooop, class, size) \
	allocObj(ooop, class, 0, size, flagWordWithPtrOff, \
		dontRoundUpSize, initOopSizedData, (oop)0, allocInNewSpace)

/*
 * OldSpace allocation macros--no initialization.
 */
#define allocOsPtrObj(ooop, class, size) \
	ooop = allocInOldSpace(classTagFromClass(class), size, flagWordWithPtrOn, \
							nullInitVal, FALSE)

#define allocOsNonPtrObj(ooop, class, size) \
	ooop = allocInOldSpace(classTagFromClass(class), size, flagWordWithPtrOff, \
							nullInitVal, FALSE)

#define tagAllocOsNonPtrObj(ooop, clssTag, size) \
	ooop = allocInOldSpace(classTagFromIndex(clssTag),size,flagWordWithPtrOff, \
							nullInitVal, FALSE)

/*
 * OldSpace allocation macros--with initialization.
 */
#define callocOsPtrObj(ooop, class, size) \
	ooop = allocInOldSpace(classTagFromClass(class), size, flagWordWithPtrOn, \
							sysOop(nilOopX), FALSE)
#define callocOsNonPtrObj(ooop, class, size) \
	ooop = allocInOldSpace(classTagFromClass(class), size, flagWordWithPtrOff, \
							(oop)0, FALSE)


/*
 * PermSpace allocation macros--no initialization.
 */
#define allocPsPtrObj(ooop, class, size) \
	ooop = allocInPermSpace(classTagFromClass(class), size, flagWordWithPtrOn, nullInitVal)

#define allocPsNonPtrObj(ooop, class, size) \
	ooop = allocInPermSpace(classTagFromClass(class), size, flagWordWithPtrOff, nullInitVal)

/*
 * PermSpace allocation macros--with initialization.
 */
#define callocPsPtrObj(ooop, class, size) \
	ooop = allocInPermSpace(classTagFromClass(class), size, flagWordWithPtrOn, sysOop(nilOopX))
#define callocPsNonPtrObj(ooop, class, size) \
	ooop = allocInPermSpace(classTagFromClass(class), size, flagWordWithPtrOff, (oop)0)


/*
 * Large object allocation macros--no initialization.
 */
#define allocLargePtrObj(ooop, class, size) \
	allocObj(ooop, class, numFixedFieldsForClass(class), size, flagWordWithPtrOn, \
		dontRoundUpSize, dontInitData, nullInitVal, allocLargePointerObj)
#define allocLargeIdxPtrObj(ooop, class, numFixedSlots, size) \
	allocObj(ooop, class, numFixedSlots, size, flagWordWithPtrOn, \
		dontRoundUpSize, dontInitData, nullInitVal, allocLargePointerObj)
#define allocLargeNonPtrObj(ooop, class, size) \
	ooop = allocLargeByteObj(classTagFromClass(class), size, flagWordWithPtrOff, nullInitVal)

/*
 * Large newSpace object allocation macros--no initialization.
 */
#if 0
/* Sorry, but no pointers in largeSpace objects */
# define allocLargeNsPtrObj(ooop, class, size) \
	ooop = allocInLargeSpace(classTagFromClass(class), size, flagWordWithPtrOn, nullInitVal)
#endif
#define allocLargeNsNonPtrObj(ooop, class, size) \
	ooop = allocInLargeSpace(classTagFromClass(class), size, flagWordWithPtrOff, nullInitVal)
#define tagAllocLargeNsNonPtrObj(ooop, clssTag, size) \
	ooop = allocInLargeSpace(classTagFromIndex(clssTag), size, flagWordWithPtrOff, nullInitVal)

/*
 * Large newSpace object allocation macros--with initialization.
 */
#if 0
/* Sorry, but no pointers in largeSpace objects */
# define callocLargeNsPtrObj(ooop, class, size) \
	ooop = allocInLargeSpace(classTagFromClass(class), size, flagWordWithPtrOn, sysOop(nilOopX))
#endif
#define callocLargeNsNonPtrObj(ooop, class, size) \
	ooop = allocInLargeSpace(classTagFromClass(class), size, flagWordWithPtrOff, (oop)0)

/*
 * Fixed newSpace object allocation macros
 */
#define allocFixedSpaceNsNonPtrObj(ooop, class, size) \
	ooop = allocInFixedSpace(classTagFromClass(class), size, flagWordWithPtrOff, nullInitVal)
#define callocFixedSpaceNsNonPtrObj(ooop, class, size) \
	ooop = allocInFixedSpace(classTagFromClass(class), size, flagWordWithPtrOff, (oop)0)

/*
 * Special system object allocation macros--no initialization.
 */
#define allocSysPtrObj(ooop, class, size) do { \
	ooop = allocInOldSpace(classTagFromClass(class),size,flagWordWithPtrOn,\
						   nullInitVal,TRUE); \
	if ((ooop) != nonOop) \
		setIndexabilityIfNeeded(ooop,bytesToOops(size)); \
} while (0)
#define tagAllocSysPtrObj(ooop, clssTag, size) do { \
	ooop = allocInOldSpace(classTagFromIndex(clssTag),size,flagWordWithPtrOn,nullInitVal,TRUE); \
	if ((ooop) != nonOop) \
		setIndexabilityIfNeeded(ooop,bytesToOops(size)); \
} while (0)
#define allocSysIdxPtrObj(ooop, class, fixed, size) do { \
	ooop = allocInOldSpace(classTagFromClass(class),size,flagWordWithPtrOn,\
						   nullInitVal,TRUE); \
	if ((ooop) != nonOop) \
		setIndexabilityIfNeeded(ooop,fixed); \
} while (0)
#define tagAllocSysIdxPtrObj(ooop, classTag, fixed, size) do { \
	ooop = allocInOldSpace(classTagFromIndex(classTag),size,flagWordWithPtrOn,\
						   nullInitVal,TRUE); \
	if ((ooop) != nonOop) \
		setIndexabilityIfNeeded(ooop,fixed); \
} while (0)
#define allocSysNonPtrObj(ooop, class, size) \
	ooop = allocInOldSpace(classTagFromClass(class),size,flagWordWithPtrOff,\
						   nullInitVal,TRUE)
#define tagAllocSysNonPtrObj(ooop, classTag, size) \
	ooop = allocInOldSpace(classTagFromIndex(classTag),size,flagWordWithPtrOff,nullInitVal,TRUE)

/*
 * Special system object allocation macros--with default initialization.
 */
#define callocSysPtrObj(ooop, class, size) \
	iallocSysPtrObj(ooop, class, size, sysOop(nilOopX))
#define tagCallocSysPtrObj(ooop, clssTag, size) \
	itagAllocSysPtrObj(ooop, clssTag, size, sysOop(nilOopX))
#define tagCallocSysIdxPtrObj(ooop, clssTag, fixed, size) \
	itagAllocSysIdxPtrObj(ooop, clssTag, size, fixed, sysOop(nilOopX))
#define callocSysWeakPtrObj(ooop, class, size) \
	iallocSysWeakPtrObj(ooop, class, size, sysOop(nilOopX))
#define callocSysNonPtrObj(ooop, class, size) \
	iallocSysNonPtrObj(ooop, class, size, 0)

/*
 * Special system object allocation macros--with user-specified initialization.
 */
extern bool oldSpaceObjOk(oop,bool);

#define iallocSysPtrObj(ooop, class, size, initOop) do { \
	ooop = allocInOldSpace(classTagFromClass(class), size, flagWordWithPtrOn, \
							initOop, TRUE); \
	if ((ooop) != nonOop) { \
		setIndexabilityIfNeeded(ooop, numFixedFieldsForClass(class)); \
		assert(oldSpaceObjOk(ooop,FALSE)); \
	} \
} while (0)
#define itagAllocSysPtrObj(ooop, clssTag, size, initOop) \
	ooop = allocInOldSpace(classTagFromIndex(clssTag), size, flagWordWithPtrOn, initOop, TRUE)
#define itagAllocSysIdxPtrObj(ooop, clssTag, fixedSlots, size, initOop) do { \
	ooop = allocInOldSpace(classTagFromIndex(clssTag), size, flagWordWithPtrOn, initOop, TRUE); \
	if ((ooop) != nonOop) { \
		setIndexabilityIfNeeded(ooop, fixedSlots); \
		dassert(oldSpaceObjOk(ooop,FALSE)); \
	} \
} while (0)
#if EPHEMERONS
# define iallocSysWeakPtrObj(ooop, class, sz, initOop) do { \
	ooop = allocInOldSpace(classTagFromClass(class),sz,flagWordWithPtrAndGCOn, \
							initOop, TRUE); \
	if ((ooop) != nonOop) { \
		setIndexabilityIfNeeded(ooop, numFixedFieldsForClass(class)); \
		dassert(oldSpaceObjOk(ooop,FALSE)); \
	} \
} while (0)
#else
# define iallocSysWeakPtrObj(ooop, class, size, initOop) \
	iallocSysPtrObj(ooop, class, size, initOop)
#endif
#define iallocSysNonPtrObj(ooop, class, size, initVal) do { \
	(ooop) = allocInOldSpace(classTagFromClass(class), size, flagWordWithPtrOff, \
							(oop)(initVal), TRUE); \
	if ((ooop) != nonOop) dassert(oldSpaceObjOk(ooop,FALSE)); \
} while (0)

/*
 * Fundamental allocation macros
 */
#define allocObj(newOop,class,fixedSlots,size,flags,sizeFunc,initDataFunc,initVal,otherAllocFunc) \
do { \
 ifAssert(extern bool scavengeInProgress;) \
  oop *dp = edenAllocPtr() + slotsInOtEntry + sizeOvflSlots(size); \
  assert(!scavengeInProgress); \
  assert(edenAllocPtrLive); \
  assert(!(sizeFunc(size) & tagBitsMask)); \
  (newOop) = (oop) edenAllocPtr(); \
  if ((edenAllocPtr() = asOopPtr((byte *)dp + sizeFunc(size))) \
   <= eden.warningThreshold) \
	initNewObj(newOop,dp,class,fixedSlots,size,flags,initDataFunc,initVal); \
  else { \
	edenAllocPtr() = asOopPtr(newOop); \
	(newOop) = otherAllocFunc(classTagFromClass(class), size, flags, initVal); \
	if ((newOop) != nonOop && (fixedSlots)) \
		setIndexabilityIfNeeded(newOop, fixedSlots); \
  } \
  assert((newOop) == nonOop || objDataSize(newOop) == (size)); \
} while (0)

#if HPS32
# define tagAllocObj(newOop,class,fixedSlots,size,flags,sizeFunc,initDataFunc,initVal,otherAllocFunc) \
    allocObj(newOop,class,fixedSlots,size,flags,sizeFunc,initDataFunc,initVal,otherAllocFunc)
#elif HPS64
# define tagAllocObj(newOop,clssTag,fixedSlots,size,flags,sizeFunc,initDataFunc,initVal,otherAllocFunc) \
do { \
 ifAssert(extern bool scavengeInProgress;) \
  oop *dp = edenAllocPtr() + slotsInOtEntry + sizeOvflSlots(size); \
  assert(!scavengeInProgress); \
  assert(edenAllocPtrLive); \
  assert(!(sizeFunc(size) & tagBitsMask)); \
  (newOop) = (oop) edenAllocPtr(); \
  if ((edenAllocPtr() = asOopPtr((byte *)dp + sizeFunc(size))) \
   <= eden.warningThreshold) \
	tagInitNewObj(newOop,dp,clssTag,fixedSlots,size,flags,initDataFunc,initVal); \
  else { \
	edenAllocPtr() = asOopPtr(newOop); \
	(newOop) = otherAllocFunc(clssTag, size, flags, initVal); \
	if ((newOop) != nonOop && (fixedSlots)) \
		setIndexabilityIfNeeded(newOop, fixedSlots); \
  } \
  assert((newOop) == nonOop || objDataSize(newOop) == (size)); \
} while (0)
#endif /* HPS32 elif HPS64 */

#if HPS32
# define initNewObj(ooop, dataPtr, class, fixedSlots, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	objClass(_newOop) = class; \
	objMiscFlagWord(_newOop) = flags; \
	setObjDataSize(_newOop, size); /* dp and flags must be done first */ \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)

# define tagInitObject(ooop, dataPtr, clssTag, size, flags, initVal) \
	initObject(ooop, dataPtr, clssTag, size, flags, initVal)
#elif HPS64
# define initNewObj(ooop, dataPtr, class, fixedSlots, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	objMiscFlagWord(_newOop) = (flags) | objHash(class); \
	/* dp and flags must be done first */ \
	setObjDataSizeGivenFixedFields(_newOop, fixedSlots, size); \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)
# define tagInitNewObj(ooop, dataPtr, clssTag, fixedSlots, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	objMiscFlagWord(_newOop) = (flags) | (clssTag); \
	/* dp and flags must be done first */ \
	setObjDataSizeGivenFixedFields(_newOop, fixedSlots, size); \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)
# define tagInitNewNonPtrObj(ooop, dataPtr, clssTag, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	objMiscFlagWord(_newOop) = (flags) | ((clssTag)<<firstClassTagBit); \
	/* dp and flags must be done first */ \
	setByteObjDataSize(_newOop, size); \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)
# define tagInitNewPtrObj(ooop, dataPtr, clssTag, fixedSlots, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	objMiscFlagWord(_newOop) = (flags) | ((clssTag)<<firstClassTagBit) | ((fixedSlots)<<firstIndexabilityBit); \
	/* dp and flags must be done first */ \
	setObjDataSize(_newOop, size); \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)
# define tagInitObject(ooop, dataPtr, clssTag, size, flagsAndIndex, initVal) \
do { \
	if ((initVal) == nullInitVal) \
		tagInitNewObj(ooop, dataPtr, clssTag, 0, size, flagsAndIndex, dontInitData, initVal); \
	else \
		tagInitNewObj(ooop, dataPtr, clssTag, 0, size, flagsAndIndex, initData, initVal); \
} while (0)
#endif /* HPS32 elif HPS64 */

#define initObject(ooop, dataPtr, class, size, flags, initVal) \
do { \
	if ((initVal) == nullInitVal) \
		initNewObj(ooop, dataPtr, class, numFixedFieldsForClass(class), size, flags, dontInitData, initVal); \
	else \
		initNewObj(ooop, dataPtr, class, numFixedFieldsForClass(class), size, flags, initData, initVal); \
} while (0)

#if HPS64
# define initNewNonPtrObjAnywhere(ooop, dataPtr, class, sizeTag, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
	register oopUInt _roundedBytes = roundUpToUnit(size,bytesInOop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	assert(classHasValidIdHash(class)); \
	objMiscFlagWord(_newOop) = (flags) | objHash(class) | ((_roundedBytes - (size)) << firstIndexabilityBit); \
	/* dp and flags must be done first */ \
	setObjDataSizeTaggedSpace(_newOop, _roundedBytes, sizeTag); \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)
# define tagInitNewNonPtrObjAnywhere(ooop, dataPtr, clssTag, sizeTag, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
	register oopUInt _roundedBytes = roundUpToUnit(size,bytesInOop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	assert(validClassIdHash(clssTag)); \
	objMiscFlagWord(_newOop) = (flags) | ((clssTag) << firstClassTagBit) | ((_roundedBytes - (size)) << firstIndexabilityBit); \
	/* dp and flags must be done first */ \
	setObjDataSizeTaggedSpace(_newOop, _roundedBytes, sizeTag); \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)
#else /* HPS64 */
# define initNewNonPtrObjAnywhere(ooop, dataPtr, class, sizeTag, size, flags, initDataFunc, initVal) \
do { \
	register oop _newOop = (ooop); \
\
	setObjDataPtr(_newOop, dataPtr); \
	objClass(_newOop) = (class); \
	objMiscFlagWord(_newOop) = flags; \
	/* dp and flags must be done first */ \
	setObjDataSizeTaggedSpace(_newOop, size, sizeTag); \
	initDataFunc(_newOop, dataPtr, size, initVal); \
} while (0)

# define tagInitNewNonPtrObjAnywhere(ooop, dataPtr, clssTag, sizeTag, size, flags, initDataFunc, initVal) \
	initNewNonPtrObjAnywhere(ooop, dataPtr, clssTag, sizeTag, size, flags, initDataFunc, initVal)
#endif /* HPS64 */

#define initData(ooop, dataPtr, bytesInData, initVal) do { \
	register oopSized *dPtr = (oopSized *)(dataPtr); \
	register oopSized val = (oopSized)(initVal); \
	register oopSized *sPtr = dPtr + sizeInOops(bytesInData); \
	while (dPtr < sPtr) \
		*dPtr++ = val; \
	assert(objOk(ooop)); \
} while (0)

#define initOopSizedData(ooop, dataPtr, bytesInData, initVal) do { \
	register oopSized *dPtr = (oopSized *)(dataPtr); \
	register oopSized val = (oopSized)(initVal); \
	register oopSized *sPtr = dPtr + bytesToOops(bytesInData); \
	while (dPtr < sPtr) \
		*dPtr++ = val; \
	assert(objOk(ooop)); \
} while (0)

#define dontInitData(ooop, dataPtr, bytesInData, initVal)

#define roundUpSize(bytesInData) oopsToBytes(sizeInOops(bytesInData))

#define dontRoundUpSize(bytesInData) (bytesInData)

#define nullAllocFunc(class, size, flags, initVal) nonOop

#define nullTerminationByteCount (2)

#define nullTerminateByteObject(ooop, dataPtr, bytesInData) do { \
	register byte *dPtr = (byte *)(dataPtr); \
	dPtr += bytesInData; \
	*dPtr++ = (byte)0; \
	*dPtr++ = (byte)0; \
} while (0)

/*
 * Allocation Functions
 */
extern oop allocSmallObj(classTag, oopInt, oopUInt, oop);
extern oop allocLargePointerObj(classTag, oopInt, oopUInt, oop);
extern oop allocLargeByteObj(classTag, oopInt, oopUInt, oop);
extern oop allocInNewSpace(classTag, oopInt, oopUInt, oop);
extern oop allocInPastSpace(classTag, oopInt, oopUInt, oop);
extern oop allocInLargeSpace(classTag, oopInt, oopUInt, oop);
extern oop allocInFixedSpace(classTag, oopInt, oopUInt, oop);
extern oop allocInOldSpace(classTag, oopInt, oopUInt, oop, bool);
#if PERM_ALLOC
extern oop allocInPermSpace(oop, oopInt, oopUInt, oop);
#else
#	define allocInPermSpace(a, b, c, d) nonOop
#endif
extern oop createShallowCopyOf(oop);

#ifdef ASSERT
extern bool oldSpaceOk(bool fullSearch);
#endif

/*
 * Instrumentation functions.
 */
#if INSTR
extern void printAllocationStats(void);
extern void oldObjCount(oop);
#else
#	define printAllocationStats()
#	define oldObjCount(ooop)
#endif

#if TIMING || INSTR || SCAVENGE_TIMING
extern memIndex edenOverflowInOops;
extern memIndex edenOverflowInBytes;
extern void edenOverflow(memIndex);
extern void largeSpaceOverflow(memIndex);
#else
#	define     edenOverflow(bytesInObj)
#	define     largeSpaceOverflow(bytesInObj)
#	define     fixedSpaceOverflow(bytesInObj)
#endif
