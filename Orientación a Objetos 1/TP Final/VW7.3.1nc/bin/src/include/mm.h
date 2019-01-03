/* SccsId is @(#)mm.h	58.10 04/06/05 */
/************************************************************************
 * File: mm.h
 *
 * This file contains the generic public defs for the HPS memory manager.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/*
 * Object Defs
 */
#define objIsHybridCtx(ooop) contextIsHybrid(ooop)
#define ageObj(ooop)
#define ageObjMaximally(ooop)
extern oopInt getObjHash(oop);

/*
 * objHasData
 *
 * Answer if an object has data.  If the size field is non-zero there's data.
 */
#define objHasData(ooop) (objSizeField(ooop) != 0)

#if MM_PROC_REGISTRY
/*
 * mmRegisterNotify
 *
 * Registers a procedure that will subsequently be invoked by the memory
 * manager whenever it moves or recycles any object headers.
 *
 * The procedure being registered should accept a bool as its only
 * argument. This bool will be true if any old object headers were moved
 * or recycled (in which case young object headers should be assumed to have
 * been moved or recycled also) and false in the case that only young object
 * headers were affected.
 */
extern void mmRegisterNotify(void (*)(bool));
#endif

/*
 * Convenience Defs
 */
#define zeroOop asSmallInt(0)
#define twoFiftyFiveOop asSmallInt(255)

/*
 * Validity checking Defs
 */
extern DLUP_IMPORT(machinePC) minNZonePC, maxNZonePC;
extern DLUP_IMPORT(machinePC) minGluePC, maxGluePC;
extern DLUP_IMPORT(char *) startOfStackZone;
extern DLUP_IMPORT(char *) endOfStackZone;

#define couldBeOop(o) (oopIsImm(o) || couldBeObj(o))

#define probablyOop(o) (oopIsImm(o) || probablyObj(o))

#define addressInGlueRange(p) \
    ((machinePC)(p) >= minGluePC && (machinePC)(p) <= maxGluePC)

#define addressInNZoneRange(p) \
   ((machinePC)(p) >= minNZonePC && (machinePC)(p) <= maxNZonePC)

#define addressInNPCRange(p) (addressInGlueRange(p) || addressInNZoneRange(p))

#define addressInStackZoneRange(p) \
	((char *)(p) >= startOfStackZone && (char *)(p) < endOfStackZone)

/*
 * The check for aboveNewSpaceLowerBound eliminates NZone addresses.
 * Because the stack zone may be on the C stack a separate check is needed to
 * exclude stack refs.
 */
#define couldBeObj(objOop) \
	(!tagBits(objOop) \
	&& aboveNewSpaceLowerBound(objOop) \
	&& !addressInStackZoneRange(objOop) \
	&& (couldBeInNewSpace(objOop)||objIsOldAssert(objOop)||nonNewObjIsPerm(objOop)))

/* Stricter, slower check */
#define probablyObj(objOop) (!tagBits(objOop) \
					&& (couldBeInNewSpace(objOop) || addressInAnyOt(objOop)))

/* Why do we allow == *space.firstFreeSlot? Because where would the data go if so? */
#define couldBeDataPtr(ptr) \
  (  !((oopUInt)(ptr) & (sizeof(oop)-1)) \
  && (  (pastSpace.firstSlot <= (ptr) && (ptr) <= pastSpace.firstFreeSlot) \
	 || (eden.firstSlot <= (ptr) && (ptr) <= enVogueEdenAllocPtr()) \
	 || couldBeOldDataPtr(ptr) \
	 || (  dataPtrOfLsBlock(largeSpace.firstBlock) <= (ptr) \
		&& (ptr) <= dataPtrOfLsBlock(largeSpace.lastBlock)) \
	 || existsFixedSpaceSegmentFor(ptr) \
	 || (permSpace.firstSlot <= (ptr) && (ptr) <= permSpace.firstFreeSlot)))

#define probablyDataPtr(ptr) \
  (  !((oopUInt)(ptr) & (sizeof(oop)-1)) \
  && (  (pastSpace.firstSlot <= (ptr) && (ptr) <= pastSpace.firstFreeSlot) \
	 || (eden.firstSlot <= (ptr) && (ptr) <= enVogueEdenAllocPtr()) \
	 || addressInAnySegmentData(ptr) \
	 || (  dataPtrOfLsBlock(largeSpace.firstBlock) <= (ptr) \
		&& (ptr) <= dataPtrOfLsBlock(largeSpace.lastBlock)) \
	 || existsFixedSpaceSegmentFor(ptr) ))

#define couldBeNewDataPtr(ptr) \
  (  !((oopUInt)(ptr) & (sizeof(oop)-1)) \
  && (  (pastSpace.firstSlot <= (ptr) && (ptr) <= pastSpace.firstFreeSlot) \
	 || (eden.firstSlot <= (ptr) && (ptr) <= enVogueEdenAllocPtr()) \
	 || (  dataPtrOfLsBlock(largeSpace.firstBlock) <= (ptr) \
		&& (ptr) <= dataPtrOfLsBlock(largeSpace.lastBlock)) \
	 || existsFixedSpaceSegmentFor(ptr) ))

/*
 * Incremental state defs. Must be here for incMarkRequired below.
 * use characters for easy reporting to VI.  currentIncGCState is *not* to
 * be used directly.  It is a read-only export from mmGarbage.c to be used
 * only via getIncGCState().
 */
typedef char incGCState;
enum {
	incMarkAborted     = 'a',
	incResting         = 'r',
	incMarking         = 'm',
	incNillingWeakPtrs = 'n',
	incSweeping        = 's'
};
extern DLUP_IMPORT(incGCState)  currentIncGCState;
#define getIncGCState() currentIncGCState
extern void incMarkObj(oop);

/*
 * Macros that support the incremental mark phase.
 */
#define objBehindMarkWave(target) (getIncGCState() == incMarking \
								&& objIsMarked(target))

#define incMarkRequired(target, ooop) (objBehindMarkWave(target) \
									&& !objIsMarked(ooop))

/*
 * store-checking defs
 *
 * The store macros should always be used when storing an oop, since
 * such a store may require that the receiver be registered in a VM table.
 * StoreOop, storeOopInOld, and storeOopInNew do the checking, registering,
 * and storing for you, whereas checkStoreOop, checkStoreOopInOld, and
 * checkStoreOopInNew do the checking and the registering, but not the storing.
 *
 * CHECK_STORE_USES_INDEX is set if the store-check macros use the target index.
 * Since it isn't set the translator is able to generate more concise code.
 */

#define CHECK_STORE_USES_INDEX 0

/*
 * General store-checking macro. Target must be a NON-IMMEDIATE object.
 *
 * NOTE: Logically duplicated in unsafe_oops.h
 */
#define checkStoreOop(target, index, ooop) \
do { \
	assert(!oopIsImm(target)); \
	\
	if (objIsNew(target)) \
		checkStoreOopInNew(target, index, ooop); \
	else \
		checkStoreOopInNonNew(target, index, ooop); \
} while (0)

/*
 * General store-checking macro. Both target and ooop must be NON-IMMEDIATE objects.
 *
 * NOTE: Logically duplicated in unsafe_oops.h
 */
#define checkStoreObj(target, index, ooop) \
do { \
	assert(!oopIsImm(target)); \
	\
	if (objIsNew(target)) \
		checkStoreObjInNew(target, index, ooop); \
	else \
		checkStoreObjInNonNew(target, index, ooop); \
} while (0)

/*
 * Store into a NEW target.
 *
 * NOTE: Logically duplicated in unsafe_oops.h
 */
#define checkStoreOopInNew(target, index, ooop) \
	/* Nothing to do, for now */ \
	assert(!oopIsImm(target) && objIsNewAssert(target))

/*
 * Check the store of a NON-IMMEDIATE object into an NEW target.
 */
#define checkStoreObjInNew(target, index, ooop) \
	/* Nothing to do, for now */ \
	assert(!oopIsImm(target) && objIsNewAssert(target) && !oopIsImm(ooop))

/*
 * Store into a NON-NEW target.
 *
 * NOTE: Logically duplicated in unsafe_oops.h
 */
#define checkStoreOopInNonNew(target, index, ooop) \
do { \
	assert(!oopIsImm(target) && !objIsNewAssert(target)); \
	\
	if (!oopIsImm(ooop)) /* filter out stores of immediates */ \
		checkStoreObjInNonNew(target, index, ooop); \
} while (0)

/*
 * Check the store of a NON-IMMEDIATE object into an NON-NEW target.
 *
 * NOTE: Logically duplicated in unsafe_oops.h
 */
#define checkStoreObjInNonNew(target, index, ooop) \
do { \
	assert(!oopIsImm(target) && !objIsNewAssert(target)); \
	assert(!oopIsImm(ooop)); \
	\
	if (objIsNew(ooop)) { /* storing a new object */ \
		if (!objInRt(target) /* avoid duplicate rt entries */ \
		 && !registerInRt(target)) \
			checkStoreFailureAction; \
	} \
	else /* storing a non-new object */ \
		checkStoreOldObjInNonNew(target, index, ooop); \
} while (0)

/*
 * Check the store of a NON-NEW object into an NON-NEW target.
 *
 * The functional version of this macro is called: chStOldObjInNonNew
 */
#define checkStoreOldObjInNonNew(target, index, ooop) \
do { \
	assert(!oopIsImm(target) && !objIsNewAssert(target)); \
	assert(!oopIsImm(ooop) && !objIsNewAssert(ooop)); \
	\
	if (incMarkRequired(target, ooop)) \
		incMarkObj(ooop); \
	if (!nonNewObjIsPerm(ooop)		/* filter out stores of perms */ \
	 &&  nonNewObjIsPerm(target)	/* storing an old into a perm */ \
	 && !objInOldRt(target)			/* avoid duplicate oldRt entries */ \
	 && !registerInOldRt(target)) \
		checkStoreFailureAction; \
} while (0)

#if ObjectsHaveDirectClassPointer
/*
 * Check the store of class field.
 */
#define checkStoreClass(target, classOop) \
do { \
	assert(!oopIsImm(target)); \
	\
	if (objIsNew(target)) \
		checkStoreObjInNew(target, 0, classOop); \
	else \
		checkStoreObjInNonNew(target, 0, classOop); \
} while (0)

/*
 * Check the store of class field.
 */
#define checkStoreClassInOld(target, classOop) \
do { \
	assert(!oopIsImm(target) && objIsOld(target)); \
	checkStoreObjInNonNew(target, 0, classOop);\
} while (0)

#else /* ObjectsHaveDirectClassPointer */
/*
 * Check the store of class field.
 */
#define checkStoreClass(target, classOop) \
do { \
	assert(!oopIsImm(target) && !oopIsImm(classOop)); \
	\
	if (!objIsNew(target)) \
		checkStoreClassInOld(target, classOop); \
} while (0)

/*
 * Check the store of class field.
 */
#define checkStoreClassInOld(target, classOop) \
do { \
	assert(!oopIsImm(target) && objIsOld(target)); \
	\
	if (!objIsNew(classOop) && incMarkRequired(target, classOop)) \
		incMarkObj(classOop); \
} while (0)

#endif /* ObjectsHaveDirectClassPointer */

/*
 * Broadside store check.
 */
#define checkStoreAllOops(target) \
do { \
	assert(!oopIsImm(target)); \
	\
	if (objIsNew(target)) \
		checkStoreAllOopsInNew(target); \
	else \
		checkStoreAllOopsInNonNew(target); \
} while (0)

/*
 * Broadside store check for NEW targets.
 */
#define checkStoreAllOopsInNew(target) \
	/* Nothing to do, for now */ \
	assert(!oopIsImm(target) && objIsNewAssert(target))

/*
 * Broadside store check for NON-NEW targets.
 */
#define checkStoreAllOopsInNonNew(target) \
do { \
	assert(!oopIsImm(target) && !objIsNewAssert(target)); \
	if (objBehindMarkWave(target)) \
		incMarkObj(target); \
	if ((!objInRt(target) && !registerInRt(target)) \
	 || (nonNewObjIsPerm(target) && !objInOldRt(target) && !registerInOldRt(target))) \
	    /* one of the above register functions failed */ \
	    checkStoreFailureAction; \
} while (0)

/*
 * Define the action to take when a check-store fails,
 * Clients may overrided by defining their own action first,
 * or redefining it first.
 */
#ifndef checkStoreFailureAction
#	define checkStoreFailureAction fatalError(noSubtext, errCodeRtOverflow|errInMman)
#endif

/*
 * Store macros.
 */

/*
 * General versions for storing arbitrary oops in various ages of assignee.
 * storeOopInNew is the most efficient as the store-check is empty.
 */
#define storeOop(target, index, ooop) \
do { \
	checkStoreOop(target, index, ooop); \
	setObjDataField(target, oop, index, ooop); \
} while(0)

#define storeOopInNew(target, index, ooop) \
do { \
	checkStoreOopInNew(target, index, ooop); \
	setObjDataField(target, oop, index, ooop); \
} while(0)

#define storeOopInOld(target, index, ooop) \
do { \
	checkStoreOopInNonNew(target, index, ooop); \
	setObjDataField(target, oop, index, ooop); \
} while(0)

/*
 * Versions for storing non-immediate oops in various ages of assignee.
 * These avoid an immediate check if there is a store check.
 */
#define storeObj(target, index, ooop) \
do { \
	checkStoreObj(target, index, ooop); \
	setObjDataField(target, oop, index, ooop); \
} while(0)

#define storeObjInNew(target, index, ooop) \
do { \
	checkStoreObjInNew(target, index, ooop); \
	setObjDataField(target, oop, index, ooop); \
} while(0)

#define storeObjInOld(target, index, ooop) \
do { \
	checkStoreObjInNonNew(target, index, ooop); \
	setObjDataField(target, oop, index, ooop); \
} while(0)

/*
 * Version avoiding a store-check, because immediate assignments do not need
 * to be checked.
 */
#define storeImm(target, index, ooop) \
do { \
	assert(oopIsImm(ooop)); \
	setObjDataField(target, oop, index, ooop); \
} while(0)

/*
 * N.B.  You might expect a storeNoCheck or storePerm for storing perm objects
 * into others, as these might be expected not to need checking.  However,
 * given permSpace can be absorbed into oldSpace we can never guarantee that
 * objects like nil, true and false will always be permObjects.  The translator
 * can perform this optimization because native code doesn't survive garbage
 * collection, and so for the duration of translated native code perm objects
 * will remain perm.
 */

/*
 * Private Defs
 *
 * These definitions are private to the memory manager subsytem.  They are
 * included in the file because many are required by the public definitions.
 * Some, however, are candidates for removal to more private files.
 *
 * Alrighty, here's the scoop. After image load, these values are defined:
 * newSpaceLowerBound
 * oldNewSpaceBoundary
 * oldPermSpaceBoundary
 *
 * Also note that when permSpace is absorbed and released, the value of
 * oldPermSpaceBoundary is changed.
 *
 * From the above four values, we get the following reasonably private macros:
 * newSpaceLowerBound		-- Lowest address in newSpace
 * oldNewSpaceBoundary		-- Highest address newSpace + 1
 * oldPermSpaceBoundary		-- oldAbovePerm
 *								   ?	Highest address in permSpace + 1
 *								   :	Lowest address in permSpace
 *
 * The three values are also used in growing oldSpace, absorbing and releasing
 * permSpace, and creating the translated primitives for doing the storeCheck,
 * but probably shouldn't be.
 *
 * From the six private macros we get these public macros:
 * {above,below}NewSpaceLowerBound
 *	objInNewSpace
 *	dataInNewSpace
 * {above,below}OldNewBoundary
 *	objInNewSpace
 *	dataInNewSpace
 *	dataInLargeSpace
 *	dataInLargeSpace
 *	dataInPermSpace		-- OldAbovePerm
 *	dataInOldSpace		-- OldBelowPerm
 * {above,below}OldPermBoundary
 *	objIsPerm		-- OldBelowPerm
 *	nonNewObjIsPerm
 *	objIsOld		-- OldAbovePerm
 *	nonNewObjInOldSpace
 *	dataInOldSpace		-- OldAbovePerm
 *	dataInPermSpace		-- OldBelowPerm
 *	nonNewNonLargeDataInPermSpace
 *	nonNewNonLargeDataInOldSpace
 *
 * A public macro that is listed under more than one private macro uses
 * all of the private macros it is listed under. Since memory may be
 * configured in one of two ways -- Old{Above,Below}Perm -- some of the
 * public macros use different private macros depending on the configuration.
 *
 * The configuration also effects how permSpace is absorbed and released,
 * and the details of growing oldSpace.
 *
 * The memory layout at system startup time is currently as follows
 * (If this layout changes, please update the doc in hpsmem.text accordingly):
 *
 * [low addresses]
 * [NewSpace Items]
 * 		survivorSpace -- empty or holds scavenge survivors
 * 		survivorSpace -- empty or holds scavenge survivors
 * 		eden -- object creation space
 * [largeSpace Items]
 * 		largeSpace -- contains the data of large objects
 * [permSpace Items]
 *		permSpace -- contains all permanent object (if malloc'd)
 * [oldSpace Items]
 * 		oldSpace -- contains all old objects (can be expanded)
 * [permSpace Items]
 *		permSpace -- contains all permanent object (if mmapped)
 * [high addresses]
 *
 * The layout of memory is somewhat arbitrary. The only architectural
 * assumptions that the memory manager currently makes about the layout of
 * memory is that all of newSpace (eden, pastSpace, and futureSpace) is below
 * all of oldSpace/permSpace in memory (this permits us to discern new objects
 * from old/perm objects with a single boundary check).  For similar reasons,
 * permSpace must be completely above or completely below oldSpace.
 *
 * Of course, if the above layout were to be changed slightly, some of the
 * "space" macros in mm.h may have to be modified accordingly since they
 * take advantage of the above order to implement quick boundary checks.
 *
 * Note that the location of permSpace depends upon whether it is allocated on
 * the heap via malloc (or a similar facility) or whether it is mapped into the
 * address space via mmap (or a similar facility).  If permSpace is mapped into
 * the address space, then it must be mapped fairly high since its location
 * constitutes a ceiling for the process's data heap on most platforms, hence
 * its location limits the extent to which oldSpace can be grown. On the other
 * hand, if permSpace is allocated on the data heap, then it must be below all
 * of oldSpace, since oldSpace will grow we want permSpace to be either
 * completely above or below oldSpace so that we can use a quick boundary check
 * to distinguish old objects from permanent objects.
 */

/*
 * newSpaceLowerBound = VM caches are below new/large/old/permSpace
 * are above.
 */
#	define aboveNewSpaceLowerBound(ptr) ((oop)(ptr) >= newSpaceLowerBound)
#	define belowNewSpaceLowerBound(ptr) ((oop)(ptr) <  newSpaceLowerBound)

/*
 * oldNewSpaceBoundary = newSpace is below and large/old/permSpace are above.
 * N.B.  If we have a register holding the eden allocation pointer then, because
 * eden is the highest space in newSpace and because allocations grow upwards in
 * eden, this register is also the highest legal address in newSpace, and so we
 * use it in place of the oldNewSpaceBoundary variable.  For assert checking we
 * provide a version that always checks against the boundary pointer.  For
 * callback code that doesn't want the complication of reestablishing the
 * register on a brief callback we allow allocations and boundary checking not
 * using the register if EdenAllocPtrInScope is false prior to including mm.h
 */
#if UseEdenAllocRegister && !defined(EdenAllocPtrInScope)
# define EdenAllocPtrInScope TRUE
#endif
#if UseEdenAllocRegister && EdenAllocPtrInScope
# define aboveOldNewBoundary(ptr) (assert(edenAllocPtrLive), \
								   (oop)(ptr) >= (oop)edenAllocAndLimitRegister)
# define belowOldNewBoundary(ptr) (assert(edenAllocPtrLive), \
								   (oop)(ptr) <  (oop)edenAllocAndLimitRegister)
#else
# define aboveOldNewBoundary(ptr) ((oop)(ptr) >= oldNewSpaceBoundary)
# define belowOldNewBoundary(ptr) ((oop)(ptr) <  oldNewSpaceBoundary)
#endif
#define aboveOldNewBoundaryAssert(ptr) ((oop)(ptr) >= oldNewSpaceBoundary)
#define belowOldNewBoundaryAssert(ptr) ((oop)(ptr) <  oldNewSpaceBoundary)

#define objIsNew(ooop) belowOldNewBoundary(ooop)
#define objIsNewAssert(ooop) belowOldNewBoundaryAssert(ooop)
#define oopIsNew(ooop) (!oopIsImm(ooop) && objIsNew(ooop))
#ifdef ASSERT
#define objIsNewForAssert(ooop) ((ooop) <  oldNewSpaceBoundary)
#endif

/*
 * NewSpace defs
 */
/*
 * Eden is semi-private, used only by the translator and the memory manager.
 * IMPORTANT:  The translator assumes eden.warningThreshold is a constant
 * to speed-up allocation.  If eden.warningThreshold is changed then
 * tranNoteEdenWarningThresholdChanged must be called to cause any generated
 * code to be updated to reflect the new value.  If possible a register is used
 * to hold eden's firstFreeSlot, which is then used both as the eden allocation
 * pointer and as the boundary separating newSpace from oldSpace and permSpace.
 * A callee-saved register must be used to for the edenAllocAndLimitRegister.
 * Even so it must be written back before call-outs or returns from call-backs,
 * and and must be refreshed on entering the engine via a callback.
 */
typedef struct {
        oop *firstSlot;
#if UseEdenAllocRegister
        oop *cachedFirstFreeSlot;
# define edenAllocPtr() ((oop *)edenAllocAndLimitRegister)
# define enVogueEdenAllocPtr() (edenAllocPtrLive \
									? edenAllocPtr() \
									: eden.cachedFirstFreeSlot)
#else
        oop *firstFreeSlot;
# define edenAllocPtr() eden.firstFreeSlot
# define enVogueEdenAllocPtr() eden.firstFreeSlot
#endif
        oop *warningThreshold;
        oop *boundary;
} contiguousSpaceWithThreshold;

#if UseEdenAllocRegister
extern bool edenAllocPtrLive;
# define writeBackEdenAllocPtr() (eden.cachedFirstFreeSlot = edenAllocPtr(),\
								  edenAllocPtrLive = FALSE)
# define refreshEdenAllocPtr() (edenAllocPtr() = eden.cachedFirstFreeSlot,\
								edenAllocPtrLive = TRUE)
# define maybeRefreshEdenAllocPtr() do {				\
		if (!edenAllocPtrLive) {						\
			edenAllocPtr() = eden.cachedFirstFreeSlot;	\
			edenAllocPtrLive = TRUE;					\
		}												\
	} while (0)
# define edenAllocPtrShouldStillBeLiveAfterCallout() \
	(assert(edenAllocPtr() == eden.cachedFirstFreeSlot), \
	 edenAllocPtrLive = TRUE)
# define edenAllocPtrOk() (edenAllocPtrLive \
					    && edenAllocPtr() >= eden.firstSlot \
					    && edenAllocPtr() <= eden.boundary)
#else
# define edenAllocPtrLive TRUE
# define edenAllocPtrShouldStillBeLiveAfterCallout() 0
# define edenAllocPtrOk() (edenAllocPtr() >= eden.firstSlot \
					    && edenAllocPtr() <= eden.boundary)
# define writeBackEdenAllocPtr() 0
# define refreshEdenAllocPtr() 0
# define maybeRefreshEdenAllocPtr() 0
#endif

extern DLUP_IMPORT(contiguousSpaceWithThreshold) eden;

typedef struct {
	oop *firstSlot;
	oop *firstFreeSlot;
	oop *boundary;
} contiguousSpace;

extern DLUP_IMPORT(contiguousSpace) pastSpace, futureSpace;

extern DLUP_IMPORT(oop) newSpaceLowerBound, newSpaceUpperBound;

#define objInNewSpace(ooop) \
	(aboveNewSpaceLowerBound(ooop) && belowOldNewBoundary(ooop))
#if ObjectsHaveDirectClassPointer
# define classTagInNewSpace(ct) objInNewSpace(ct)
#else
# define classTagInNewSpace(ct) FALSE
#endif

#define slotsIn(spName) (spName.boundary - spName.firstSlot)
#define slotsLeft(spName) (spName.boundary - spName.firstFreeSlot)
#define slotsUsed(spName) (spName.firstFreeSlot - spName.firstSlot)

/* these three are real newSpace test macros */
#define objInFutureSpace(ooop) \
	(futureSpace.firstSlot <= asOopPtr(ooop) && \
	asOopPtr(ooop) < futureSpace.firstFreeSlot)
#define objInPastSpace(ooop) \
	(pastSpace.firstSlot <= asOopPtr(ooop) && \
	asOopPtr(ooop) < pastSpace.firstFreeSlot)
#define objInEden(ooop) \
	(eden.firstSlot <= asOopPtr(ooop) && asOopPtr(ooop) < edenAllocPtr())
#define objInEdenAssert(ooop) \
	(eden.firstSlot <= asOopPtr(ooop) && asOopPtr(ooop) < enVogueEdenAllocPtr())

/* these five are for assert checking */
#define couldBeInNewSpace(obj) \
	(objInEdenAssert(obj) || objInPastSpace(obj) || objInFutureSpace(obj))
#define objInEntiretyOfNewSpace(obj) (asOopPtr(obj) < eden.boundary \
		&& min(futureSpace.firstSlot,pastSpace.firstSlot) <= asOopPtr(obj))
#define objInEntiretyOfFutureSpace(obj) (asOopPtr(obj) < futureSpace.boundary \
									  && futureSpace.firstSlot <= asOopPtr(obj))
#define objInEntiretyOfPastSpace(obj) (asOopPtr(obj) < pastSpace.boundary \
									  && pastSpace.firstSlot <= asOopPtr(obj))
#define objInEntiretyOfEden(obj) (asOopPtr(obj) < eden.boundary \
							   && eden.firstSlot <= asOopPtr(obj))

/*
 * OldSpace defs */
typedef struct oldSpaceSegmentS oldSpaceSegment;
struct oldSpaceSegmentS {
	oldSpaceSegment	*nextSeg;
	oldSpaceSegment	*prevSeg;
	oop				*firstSlot;
	oop				*firstFreeSlot;
	oop				firstFreeOtEntry;
	oop				firstOtEntry;
	/* The next two are only used in the middle of compaction */
	oop				newFirstFreeOtEntry;
	oop				*firstUnavailableSlot;
	bool			memoryWasMapped;
};

#define addressInOtOf(addr,seg) ((seg).firstFreeOtEntry < (oop)(addr) \
								&& (oop)(addr) <= (seg).firstOtEntry)
#define addressInNewOtOf(addr,seg) ((seg).newFirstFreeOtEntry < (oop)(addr) \
								 && (oop)(addr) <= (seg).firstOtEntry)

typedef struct {
	oldSpaceSegment *firstSeg;
	oldSpaceSegment *lastSeg;
	oldSpaceSegment *currentSeg;

	oop			firstThreadedOtEntry;
	memUIndex	numThreadedOtEntries;

	/*
	 * OldSpace free data lists.  There are a sequence of lists for small block
	 * sizes and a tree for all larger blocks.  The list has 65 entries to
	 * accomodate sizes from 1 to 64 slots (or 4 to 256 bytes), since there are
	 * typically peaks in the object size population at powers of two.  The
	 * zero'th entry is head of binary tree of larger blocks.
	 * Here's some object size distribution data from a development vw5i.3
	 * image including the STAMP news reader.

		| sizes |
		sizes := Dictionary new.
		ObjectMemory allObjects do:
			[:obj| | size |
			size := obj class instSize
					+ (obj class isPointers
							ifTrue: [obj basicSize * 4]
							ifFalse: [obj basicSize + 3 // 4])
					* 4.
			sizes at: size put: (sizes at: size ifAbsent: 0) + 1].
		sizes associations asSortedCollection: [:a1 :a2| a1 key < a2 key]

		self inject: 0 into:
			[:s :a| s + a value] 187043
		self inject: 0 into:
			[:s :a| a key > 512 ifTrue: [s + a value] ifFalse: [s]] 1998
		self inject: 0 into:
			[:s :a| a key > 256 ifTrue: [s + a value] ifFalse: [s]] 3960
		self inject: 0 into:
			[:s :a| a key > 128 ifTrue: [s + a value] ifFalse: [s]] 10487

		1998 / 1870.43 1.0682
		3960 / 1870.43 2.11716
		10487 / 1870.43 5.60673

	 * So nearly 98% of objects are handled as small chunks in a free list of
	 * 65 entries.
	 */
	memUIndex	numThreadedData;
	memUIndex	numThreadedDataSlots;
#	define NumFreeLists 65
	oop		   *freeDataLists[NumFreeLists];
	ulonglong	freeDataListsMask;
#if HAS_64_BIT_ARITHMETIC
# define freeDataListFlag(n) ((q64)1 << ((n)-1))
#else
# error "implementation assumes 64-bit arithmetic which is available on all production vw7 platforms"
#endif
} oldSpaceSegmentList;

/*
 * Currently the permSpace free list is a single list. We should probably have
 * made the effort to upgrade the permSpace free list to the same form as
 * oldSpace, but we didn't.  This is fine as long as permSpace doesn't support
 * allocation.
 */
typedef struct {
	oldSpaceSegment *firstSeg;
	oldSpaceSegment *lastSeg;
	oldSpaceSegment *currentSeg;

	oop firstThreadedOtEntry;
	memUIndex numThreadedOtEntries;

	oop      *firstThreadedData;
	oop      *prevThreadedData; /* &firstThreadedData or &of a data block */
	memUIndex numThreadedData;
	memUIndex numThreadedDataSlots;
} permSpaceSegmentList;

extern DLUP_IMPORT(oop) oldNewSpaceBoundary;

#define slotsInOldSpaceSegStruct (sizeof(oldSpaceSegment) / sizeof(oopSized))
#define slotsLeftInOldSpaceSeg(segName) \
	((oopUInt)(asOopPtr((segName).firstFreeOtEntry+1) - (segName).firstFreeSlot))

#define nullOldSpaceSeg ((oldSpaceSegment *)0L)
extern DLUP_IMPORT(oldSpaceSegment) oldSpace;
extern DLUP_IMPORT(oldSpaceSegmentList) oldSpaceSegs;

#define oopInOldSpace(ooop) (!oopIsImm(ooop) && objIsOld(ooop))

/*
 * Public PermSpace defs
 */
extern DLUP_IMPORT(oldSpaceSegment) permSpace;

extern DLUP_IMPORT(oop) oldPermSpaceBoundary;

/*
 * LargeSpace defs
 */
typedef struct ltEntryS ltEntry;
struct ltEntryS {
	ltEntry *prevBlock;
	ltEntry *nextBlock;
	oop objOop;
	oop *dataPtr;
	memIndex slotsInBlock;
};

typedef struct {
	ltEntry *topLtEntry;
	ltEntry *bottomLtEntry;
	ltEntry *firstBlock;
	ltEntry *firstFreeBlock;
	ltEntry *lastBlock;
	memIndex freeSlots;
	memIndex lowSpaceThreshold;
} largeSpaceS;

#define slotsInLtEntry (sizeof(ltEntry) / sizeof(oopSized))
#define nullLtEntry ((ltEntry *)0L)
#define prevLsBlock(ent) ((ent)->prevBlock)
#define nextLsBlock(ent) ((ent)->nextBlock)
#define oopOfLsBlock(ent) ((ent)->objOop)
#define dataPtrOfLsBlock(ent) ((ent)->dataPtr)
#define slotsInLsBlock(ent) ((ent)->slotsInBlock)
#define lsBlockIsFree(ent) ((ent)->objOop == nonOop)

extern DLUP_IMPORT(largeSpaceS) largeSpace;

#ifdef ASSERT
extern DLUP_IMPORT(oop) largeSpaceBaseSlot;
extern DLUP_IMPORT(oop) largeSpaceUpperBound;
#endif

/*
 * FixedSpace defs
 */
typedef struct ftEntryS ftEntry;
struct ftEntryS {
	ftEntry *prevBlock;
	ftEntry *nextBlock;
	oop objOop;
	oop *dataPtr;
	memIndex slotsInBlock;
};

typedef struct fixedSpaceSegmentS fixedSpaceSegment;
struct fixedSpaceSegmentS {
  	fixedSpaceSegment *nextSeg;
	fixedSpaceSegment *prevSeg;
	ftEntry *topFtEntry;
	ftEntry *bottomFtEntry;
	ftEntry *firstBlock;
	ftEntry *firstFreeBlock;
	ftEntry *lastBlock;
	memIndex freeSlots;
};

typedef struct {
	fixedSpaceSegment *firstSeg;
	fixedSpaceSegment *lastSeg;
	fixedSpaceSegment *currentSeg;
} fixedSpaceSegmentList;

#define slotsInFixedSpaceSegStruct (sizeof(fixedSpaceSegment)/sizeof(oopSized))

#define slotsInFtEntry (sizeof(ftEntry) / sizeof(oopSized))
#define nullFtEntry ((ftEntry *)0L)
#define prevFsBlock(ent) ((ent)->prevBlock)
#define nextFsBlock(ent) ((ent)->nextBlock)
#define oopOfFsBlock(ent) ((ent)->objOop)
#define dataPtrOfFsBlock(ent) ((ent)->dataPtr)
#define slotsInFsBlock(ent) ((ent)->slotsInBlock)
#define fsBlockIsFree(ent) ((ent)->objOop == nonOop)

#define nullFixedSpaceSeg ((fixedSpaceSegment *)0L)

extern DLUP_IMPORT(fixedSpaceSegment) fixedSpace;
extern DLUP_IMPORT(fixedSpaceSegmentList) fixedSpaceSegs;

/*
 * Misc object macros
 */

extern bool registerInRt(oop);
extern bool registerInOldRt(oop);

#if defined(firstIndexabilityBit)
# define bogusSizeOvfl(ooop) (objSizeOvfl(ooop) \
		&& (	rawObjDataSize(ooop) <= sizeMaxNormalBytes \
			 || rawObjDataSize(ooop) & (sizeof(oop)-1)))
#else
# define bogusSizeOvfl(ooop) \
	(objSizeOvfl(ooop) && rawObjDataSize(ooop) <= sizeMaxNormalBytes)
#endif
#define objDataIsContig(ooop) (objBodyPtr(ooop, otEntry) == ((ooop) + 1))

#define couldBeOldDataPtr(ptr) (!((oopUInt)(ptr) & (sizeof(oop)-1)) \
								&& dataPointerInSegmentedSpace(ptr))
#define couldBeNonNewDataPtr(ptr) (!((oopUInt)(ptr) & (sizeof(oop)-1)) \
								&& (char *)(ptr) >= (char *)oldNewSpaceBoundary \
								&& (char *)(ptr) < maxSpacePtr)
#define objHeaderOk(ooop) (!objIsForwarded(ooop))

#define nullInitVal ((oop)1)

/*
 * Dummy objects are objects which have a dummy otEntry. These objects
 * are created by the garbage collector and the become: operation.
 * Invariant for old objects: dummies iff they are on threaded free list.
 * Invariant for new objects: dummies iff their size (in oopsized slots)
 * is encoded in the header's flag word.  If objects have a separate class
 * slot we use the entirety of the flag word to encode the size, but if the
 * class is encoded in the flag word then we use all the flag field except
 * the class field for the slot count.
 */
#define dummyObj(ooop) (objClassTag(ooop) == nonClassTag)

#if ObjectsHaveDirectClassPointer
# define slotsInNewSpaceDummy(obj) objMiscFlagWord(obj)
# define setSlotsInNewSpaceDummy(obj, slots) setObjMiscFlagWord(obj, slots)
#else
# define slotsInNewSpaceDummy(obj) dummyObjSlotCount(obj)
# define setSlotsInNewSpaceDummy(obj, slots) setDummyObjSlotCount(obj, slots)
#endif

/*
 * Bogus data macros
 *
 * Recall that a become operation can create newSpace objects whose actual
 * data is no longer contiguous with its otEntry. This causes a problem for
 * routines that need to scan newSpace in a linear fashion, since the object
 * involved in the become no longer points to the data that formerly followed
 * it's otEntry. Hence, the scanning routine doesn't know how far it should
 * jump to reach the otEntry of the next object, since the size field of the
 * above object refers not to the data immediately following it, but to data
 * elsewhere on the heap. In addition, the oldSpace compactor needs to
 * know the sizes of the free blocks in oldSpace that are uncovered by the
 * mark-sweep garbage collector (it cannot use backpointers to the block's
 * otEntries since the garbage collector destroys these otEntries when it
 * compacts the ot).
 *
 * We overcome these problems by overwriting the first field of the data
 * following such an object with the number of data fields that a scanning
 * routine would have to jump over. Note that we don't have to worry about
 * smashing the first data field since a become operation would have made a
 * copy of this data for the other object involved in the become to point to
 * and in the case of a free oldSpace block the data is obviously already
 * unreachable. However, since an object with no data may be involved in a
 * become, we need to be able to distinguish the first field of an otEntry
 * from a data field that has been smashed in the above manner, and in the
 * case of a free oldSpace block we need to be able to distinguish it from a
 * a backpointer to the ot. We do this by smashing the data field in such
 * a way that it could not be mistaken for the first field of an otEntry or
 * an oop (i.e., a backpointer to the ot).
 *
 * The following macros can be used to read the first field data field of
 * an object and discern how much, if any, bogus data needs to be skipped.
 * Also, they can be used to encode a data size in such a way that this
 * size won't be mistaken for the first field of an otEntry or an object oop.
 * Note that the encoding scheme assumes that the first field of an otEntry or
 * an object oop will contain a value that has zero in its low-order numTagBits
 * bits (currently both object oops and an object's data pointer field satisfy
 * this requirement). If this is true, then we can distinguish an encoded data
 * field from the first field of an otEntry by placing ones in the encoded
 * data field's first numTagBits bits.
 *
 * Is this a lie? An oop can be an immediate, so it has non-zero in the
 * low order bits. This is using the so-called unused tag-field to mark
 * blocks. 31 May 96 -bh
 * No, its not a lie.  We're talking about the ptr.toOops field in an OT entry
 * which has been reversed.  The ptr.toOops field is always 4-byte aligned
 * except under pointer reversal during compaction. eem 16 Jul 96
 */
#define numEncodingBits numTagBits
#define encodingMask (~(-1L << numEncodingBits))
#define encodeBogusDataSize(numSlots) \
	(((numSlots) << numEncodingBits) + encodingMask)

#define placeBodySizeInBody(ooop) do { \
	if (objSizeInOvflField(ooop)) \
		setObjSizeOvflField(ooop,encodeBogusDataSize(objOvflSizeSlots(ooop))); \
	else \
		setObjDataField(ooop, oopUInt, 0, \
						encodeBogusDataSize(objSizeFieldSlots(ooop))); \
} while(0)

#define decodeBogusDataSize(firstBogusDataField) \
	((oopUInt)(firstBogusDataField) >> numEncodingBits)
#define fieldIsEncoded(dataField)  (oopBits(dataField) & encodingMask)
#define bogusSentinel ((oop)(~encodingMask)) /* I am NOT encoded */
/* for assertion checking be more exact */
#define fieldIsReallyEncoded(f) ((oopBits(f) & encodingMask) == encodingMask)

/*
 * Misc exports
 */
extern	DLUP_IMPORT(char)	   *maxPtr;
extern	DLUP_IMPORT(oopInt)		temp1RegisteredOopX, temp2RegisteredOopX;
extern	oldSpaceSegment	*addressInOldSegment(void *);
extern	oldSpaceSegment	*addressInAnySegment(void *);
extern	oldSpaceSegment	*addressInPermSegment(void *);
extern	oldSpaceSegment	*addressInOldOt(void *);
extern	oldSpaceSegment	*addressInPermOt(void *);
extern	oldSpaceSegment	*addressInAnyOt(void *);
extern	oldSpaceSegment	*addressInOldNewOt(void *);
extern	oldSpaceSegment	*addressInAnyNewOt(void *);
extern	oldSpaceSegment	*addressInOldSegmentData(void *);
extern	oldSpaceSegment	*addressInAnySegmentData(void *);
extern	bool			 existsFixedSpaceSegmentFor(oop *);
extern	oopInt			 scanObjectMemory(oop,bool(*)(oop,oop),oop *,oop *);
extern	oopInt			 scanReferentsOf(oop,bool(*)(oop,oop),oop *,oop *);
#if MM_PROC_REGISTRY
extern	void	notifyRegisteredProcs(bool);
#else
#	define notifyRegisteredProcs(bool) 0
#endif

/*
 * Assertion defs
 */
#ifdef ASSERT
extern	char	*maxSpacePtr;

extern bool objDataOk(oop);
extern bool objOk(oop);
extern bool objIsAlive(oop);
extern bool objectMemoryOk(bool);
extern bool patchBadImages;
extern bool checkBadImages;
#endif

/*
 * General debugging defs; i.e. not specific to DEBUG build. See mman/mmDebug.c.
 */
extern void printSelector(FILE *,oop);
extern void printClassName(oop);
extern void printNameOfClass(FILE *,oop);
extern void printMethodName(FILE *, oop, oop);
extern bool dbObjMayBeClass(oop);
extern void dbObjClassName(oop);
extern void dbfObjClassName(oop,const char *,FILE *);
extern bool dbClassNameIs(char *,oop);
extern bool dbObjClassNameIs(char *,oop);

/*
 * Instrumentation defs
 */
#if INSTR
extern FILE *memoryLogFP;
#endif

/*
 * Timing defs
 */
#if TIMING || SCAVENGE_TIMING || IGC_TIMING
extern FILE *scavengeLogFP;
#endif
