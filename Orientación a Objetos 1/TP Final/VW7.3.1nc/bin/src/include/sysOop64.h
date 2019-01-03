/* SccsId is  @(#)sysOop64.h	58.10 04/06/05 */
/************************************************************************
 * File: sysOop64.h
 *
 * This file defines both the known indices in the sysOopRegistry and the
 * known indices in the class table on 64-bit systems.
 *
 *	Copyright (C) 1999-2004 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/* Guaranteed oop indices
 * NOTE: Some of these are duplicated in userprim.h
 */
#define nilOopX 0
#define trueOopX 1
#define falseOopX 2
#define processSchedulerOopX 3
#define smallIntegerClassX 4
#define smallDoubleClassX 5
#define characterClassX 6
#define nonlocalReturnSelectorX 7
#define doesNotUnderstandSelectorX 8
#	define hybridMethodContextClassX 8
#define mustBeBooleanSelectorX 9
#	define hybridBlockContextClassX 9
#define cannotReturnSelectorX 10
#	define hybridBlockClosureClassX 10 /* unused; reserved for future use */
#	define maxHybridClassX 10
#define methodContextClassX 11
#define blockContextClassX 12
#define blockClosureClassX 13
#define messageClassX 14
#define arrayClassX 15
#define semaphoreClassX 16
#define byteStringClassX 17
#define largePositiveIntegerClassX 18
#define largeNegativeIntegerClassX 19
#define uninterpretedBytesClassX 20
#define byteSymbolClassX 21
#define byteArrayClassX 22
#define twoByteStringClassX 23
#define twoByteSymbolClassX 24
#define doubleClassX 25
#define weakArrayClassX 26
#define pointClassX 27
#define floatClassX 28
#define classTableX 29
#define weakArrayClassTablePagePunX 29
#define specialSelectorTableX 30
#define errorCodeTableX 31
#define rtOopX 32
#define oldRtOopX 33
#define finalQueueOopX 34
#define weakRefTombstoneOopX 35
#define badBytecodeSelectorX 36
#define attemptToAssignSelectorX 37
#define cannotResumeSelectorX 38
#define atSelectorX 39
#define atPutSelectorX 40
#define sizeSelectorX 41

#define numGuaranteedIndices 42
#define numGuaranteedClassIndices 30

#define classTagFromIndex(sysOopIndex) sysOopIndex

#if !defined(assembly)
extern oop  enterIntoClassTable(oop);
extern void mournClassTablePageEntry(oop);
extern void trimClassTable(void);
# ifdef ASSERT
extern bool validClassTable(bool);
# endif
#endif
