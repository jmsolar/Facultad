/* SccsId is @(#)class.h	58.10 04/06/05 */
/************************************************************************
 * File:	class.h
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/* class.h */
/* Class object structure for HPS */
/**** NOTE: Some of these are duplicated in unsafe_oops.h */

typedef struct classS {
  oop superclass;		/* Behavior */
  oop mdict;			/* MethodDictionary */
  oop format;			/* SmallInteger, instance format */
} class;
#define classSuperclassOffset 0
#define classMDictOffset 1
#define classFormatOffset 2

/* The following are used for debugging.  Since classes have a different
 * format in VW and Jigsaw we need to compute this info at start-up.
 */
extern memIndex classNameX;
extern memIndex thisClassX;
extern oopUInt  metaclassInstSize;

/* Fields within the format word.  Note that all bit numbers refer to bit
 * positions AFTER doing an oopIntVal on the format word.  Once upon a time it
 * was possible for numClassFixedFieldsBits to be 12, but as the compiler can't
 * generate references to more than 256 instance variables, and the speed-up
 * to bounds checking with a per-object fixed-field count in the 64-bit engine
 * is likely to be high, and as no customers have complained of this limit, we
 * limit numClassFixedFieldsBits to 8.  But one still shouldn't write code that
 * assumes, for example, that fixed-size objects don't have an overflowed size,
 * since a become or changeClass might bring this about!
 */
#define numClassFixedFieldsBits 8
#define classFixedFieldsMask ((1 << numClassFixedFieldsBits) - 1)
#if HPS64
# define numFixedFields(objOop)\
	(!oopIsImm(objOop) && objHasPtrs(objOop) ? objIndexabilityField(objOop) : 0)
# define numFixedFieldsOfObj(objOop)\
	(objHasPtrs(objOop) ? objIndexabilityField(objOop) : 0)
# define numFixedFieldsOfPtrObj(objOop)\
	(assert(!oopIsImm(obj) && objHasPtrs(objOop)), objIndexabilityField(objOop))
#else
# define numFixedFields(objOop)\
 (oopUIntVal(objDataPtr(oopClass(objOop),class)->format) & classFixedFieldsMask)
# define numFixedFieldsOfObj(objOop)\
 (oopUIntVal(objDataPtr(objClass(objOop),class)->format) & classFixedFieldsMask)
#endif
#define numFixedFieldsForClass(classOop)\
 (oopUIntVal(objDataPtr(classOop,class)->format) & classFixedFieldsMask)
#define classIndexableFieldMask (1 << classIndexableBit)
#define classIndexableBit 12  /* zero indexed */
#define classPtrFieldMask (1 << classPointersBit)
#define classPointersBit 14  /* zero indexed */
#define classIsIndexable(clss) (oopBits(objDataPtr(clss,class)->format) &\
                                (1 << (classIndexableBit + numTagBits)))
#define classIsPointers(clss) (oopBits(objDataPtr(clss,class)->format) &\
                                (1 << (classPointersBit + numTagBits)))
#if defined(firstIndexabilityBit)
# define objIsIndexable(obj) (!objHasPtrs(obj) \
							|| objIndexabilityField(obj) < rawObjDataSize(obj) \
							|| classIsIndexable(objClass(obj)))
#else
# define objIsIndexable(obj) classIsIndexable(objClass(obj))
#endif

#if EPHEMERONS
# define classWeakBit 15  /* zero indexed */
# define classIsWeak(clss) (oopBits(objDataPtr(clss,class)->format) &\
                                (1 << (classWeakBit + numTagBits)))
# define classEphemeronBit 16  /* zero indexed */
# define classIsEphemeron(clss) (oopBits(objDataPtr(clss,class)->format) &\
                                (1 << (classEphemeronBit + numTagBits)))

# define formatValidityMask  ((1<<classIndexableBit)\
							| (1<<classPointersBit) \
							| (1<<classWeakBit) \
							| (1<<classEphemeronBit))

# define gcSpecialFormatMask  ((1<<classWeakBit) \
							 | (1<<classEphemeronBit))

# define ptrIndxFormatFlags	 ((1<<classIndexableBit)\
							| (1<<classPointersBit))

# define byteIndxFormatFlags  (1<<classIndexableBit)

# define weakFormatFlags	 ((1<<classIndexableBit)\
							| (1<<classPointersBit) \
							| (1<<classWeakBit))

# define ephemeronFormatFlags ((1<<classPointersBit) \
							 | (1<<classEphemeronBit))
#endif

/*
 * exPrimUtil.c provides a generic class hierarchy traversal interface
 * which is suitable to use when doing method lookups with multiple
 * inheritance.  For now we prefer to use inline code for performance.
 */
#define SIMPLE_SUPER_SEARCH
#ifndef SIMPLE_SUPER_SEARCH
# define superclassBranchLimit 20
typedef struct {
	oop supStack[superclassBranchLimit];
	memIndex cntr;
} superclassStack;

extern oop initSuperSearch(oop, superclassStack*);
extern oop nextClassToSearch(superclassStack*);
#endif

#define searchStackEmpty(stk)    ((stk)->cntr == -1)

extern char *className(oop);
