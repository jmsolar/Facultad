/* SccsId is  @(#)sysOop32.h	58.10 04/06/05 */
/************************************************************************
 * File: sysOop32.h
 *
 * This file defines the known indices in the sysOopRegistry on 32-bit systems.
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
#define methodContextClassX 4
#define blockContextClassX 5
#define blockClosureClassX 6
#define smallIntegerClassX 7
#define characterClassX 8
#define floatClassX 9
#define pointClassX 10
#define messageClassX 11
#define arrayClassX 12
#define semaphoreClassX 13
#define doesNotUnderstandSelectorX 14
#define cannotReturnSelectorX 15
#define mustBeBooleanSelectorX 16
#define specialSelectorTableX 17
#define errorCodeTableX 18
#define byteStringClassX 19
#define largePositiveIntegerClassX 20
#define uninterpretedBytesClassX 21
#define byteSymbolClassX 22
#define cannotResumeSelectorX 23
#define byteArrayClassX 24
#define atSelectorX 25
#define atPutSelectorX 26
#define sizeSelectorX 27
#define largeNegativeIntegerClassX 28
#define twoByteStringClassX 29
#define twoByteSymbolClassX 30
#define rtOopX 31
#define doubleClassX 32
#define nonlocalReturnSelectorX 33
#define weakArrayClassX 34
#define oldRtOopX 35
#define finalQueueOopX 36
#define weakRefTombstoneOopX 37
#define badBytecodeSelectorX 38
#define attemptToAssignSelectorX 39

#define numGuaranteedIndices 40

#define classTagFromIndex(sysOopIndex) sysOop(sysOopIndex)
#define trimClassTable() 0
