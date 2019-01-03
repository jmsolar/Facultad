/* SccsId is  @(#)mmTaggedPerm.h	58.10 04/06/05 */
/************************************************************************
 * File: mmTaggedPerm.h
 *
 * This file contains the memory manager defs that are dependent on permSpace
 * objects being distinguished from oldSpace objects on the basis of the
 * alignment of object table entries which occupy a pair of quad words, even
 * alignment for oldSpace, odd alignment for permSpace.  This allows us to have
 * multiple permSpace segments.  See mmOldAbovePerm.h and mmOldBelowPerm.h for
 * alternate implementations of these defs for 32-bit platforms with object
 * table entries that occupy three long words (and hence not alignable) where
 * oldSpace is located either above or below permSpace in memory. This file
 * should be include by platform.h.
 *
 *	Copyright (C) 2004 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/*
 * Old and Perm Spaces are above New Space.
 */
#define oldAboveNew TRUE

#define mappedPermSpace FALSE /* In fact this can now be a variable or TRUE.
							   * With no above/below oldSpace constraint
							   * permSpace can be mapped anywhere above
							   * space.  So wwhether it can be mapped or not
							   * depends simply on the addresses in permSpace.
							   * It should probably become the default.
							   */

/*
 * As far as I can tell, all these "must be a single bounds check" comments
 * are bogus. Nothing will break if they aren't, but some things will get
 * slower, like maybe scavenges and storechecks. And even those I'm not
 * too sure about.  bh.
 */

/* Need to reorg this part of the universe real soon.
   Anyway, the memory layout in the New World is:
   NewSpace below SegmentedSpace
   SegmentedSpace contains segments from:
	OldSpace
	LargeSpace
	FixedSpace
	PermSpace

   LargeSpace and FixedSpace objects are identifiable by their size-tag.

   */

/*
 * Private Defs
 *
 * The intent is to make largeSpace segmentable and add fixedSpace,
 * also segmentable, so I wanted to move all the segmentable spaces
 * into one place. Notice that with this scheme it would be hard to
 * segment permSpace. Of course, that would be pretty hard anyway.
 *
 * These definitions are private to the memory manager subsytem.
 * They are included in the file because many are required by the
 * public definitions. Some, however, are candidates for removal
 * to more private files.
 *
 * Alrighty, here's the scoop. After image load, these values are defined:
 * newSpaceLowerBound		-- Lowest address in newSpace
 * oldNewSpaceBoundary		-- Highest address newSpace + 1
 *
 * From the above three values, we get the following reasonably private macros:
 * {above,below}NewSpaceLowerBound
 * {above,below}OldNewBoundary
 * {above,below}OldPermBoundary
 *
 * The three values are also used in growing oldSpace, absorbing and releasing
 * permSpace, and creating the translated primitives for doing the storeCheck,
 * but probably shouldn't be.
 *
 * From the eight private macros we get these public macros:
 * {above,below}NewSpaceLowerBound
 *	objInNewSpace
 * {above,below}OldNewBoundary
 *	objInNewSpace
 *	dataInLargeSpace
 *	dataInLargeSpace
 *	dataInPermSpace		-- OldAbovePerm
 *	dataInOldSpace		-- OldBelowPerm
 * {above,below}OldPermBoundary
 *	objIsPerm		-- OldBelowPerm
 *	nonNewObjIsPerm
 *	objInOldSpace		-- OldAbovePerm
 *	nonNewObjInOldSpace
 *	dataInOldSpace		-- OldAbovePerm
 *	dataInPermSpace		-- OldBelowPerm
 *	nonNewNonLargeDataInPermSpace
 *	nonNewNonLargeDataInOldSpace
 *
 * [objIsPerm and nonNewObjIsPerm should perhaps have their names changed
 * to objInPermSpace and nonNewObjInPermSpace just to keep the names
 * parallel.]
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
 * (If this layout changes, please update the doc in hpsmem.text
 * accordingly):
 *
 * [low addresses]
 * [NewSpace Items]
 * 		survivorSpace -- empty or holds scavenge survivors
 * 		survivorSpace -- empty or holds scavenge survivors
 * 		eden -- object creation space
 * [permSpace Items]
 *		permSpace -- contains all permanent object (if malloc'd)
 * [largeSpace Items]
 * 		largeSpace -- contains the data of large objects
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

/* These are private to this file. If you want to know about an object's
 * data, use the set of definitions objDataIn*Space.
 * Oddly, though these are internal, we're calling the permSpace segment
 * outside of segmented space. Not good.
 */

#define dataPointerInNewSpace(ptr) (belowOldNewBoundary(ptr) && (ptr) != NULL)

#define dataPointerInSegmentedSpace(ptr) aboveOldNewBoundary(ptr)

/* Public way to find out where an object's data is.
   Data is either in an untagged space [new, old, or perm] or a tagged
   space [large or fixed]. In the future, the tagged spaces may expand
   to include other policies and external storage management.
   */

#define objDataInUntaggedSpace(ooop) objSizeNontaggedSpace(ooop)

#define objDataInNewSpace(ooop) dataPointerInNewSpace(objDataPtr(ooop, oop))

#define objDataInOldSpace(ooop) (objSizeNontaggedSpace(ooop) \
	&& dataPointerInSegmentedSpace(objDataPtr(ooop, oop)))

#define objDataInPermSpace(ooop) \
	  (!dataPointerInNewSpace(objDataPtr(ooop, oop)) \
	&& !dataPointerInSegmentedSpace(objDataPtr(ooop, oop)))

#define objDataInTaggedSpace(ooop) (!objSizeNontaggedSpace(ooop))

#define objDataInLargeSpace(ooop) objSizeLargeSpace(ooop)

#define objDataInFixedSpace(ooop) objSizeFixedSpace(ooop)

#define objDataInHandleSpace(ooop) objSizeHandleSpace(ooop)


/* Since headers, unlike data, are only in new, old, and perm, these checks are
 * somewhat easier.
 */

#define objIsOld(objOop) (!objIsNew(objOop) && nonNewObjIsOld(objOop))
#define objIsOldAssert(objOop) (!objIsNewAssert(objOop) && nonNewObjIsOld(objOop))

#define objIsPerm(objOop) (!objIsNew(objOop) && nonNewObjIsPerm(objOop))


/* Special definitions needed for the store-check macros */
/* must be a single check */
#define permTagBit numTagBits
#if UseEdenAllocRegister
# define nonNewObjIsPerm(oldObj) (assert((oldObj) >= (oop)eden.boundary), \
								  oopBits(oldObj) & (1<<permTagBit))
# define nonNewObjIsOld(oldObj)  (assert((oldObj) >= (oop)eden.boundary), \
								  !nonNewObjIsPerm(oldObj))
#else
# define nonNewObjIsPerm(oldObj) (oopBits(oldObj) & (1<<permTagBit))
# define nonNewObjIsOld(oldObj)  (!nonNewObjIsPerm(oldObj))
#endif
