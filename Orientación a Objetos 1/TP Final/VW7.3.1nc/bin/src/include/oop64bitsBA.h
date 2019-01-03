/* SccsId is  @(#)oop64bitsBA.h	58.10 04/06/05 */
/************************************************************************
 * File: oop64bitsBA.h
 *
 * This file contains all the processor-dependent definitions for
 * systems with 64 bit oops and byte addressing.
 *
 *	Copyright (C) 2004 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#ifndef assembly
typedef unsigned char *machinePC;	/* hardware representation of PC */
#endif

#define quantaInOop 8 /* number of addressable units in an oop */
#define log2bytesInOop 3
#define bytesInOop 8
#define bitsInOop 64
#define bitsInByte 8

#define bytesToOops(bytes) ((oopUInt)(bytes) >> 3)
#define oopsToBytes(oops) ((oopUInt)(oops) << 3)

#define quantaToOops(quanta) ((oopUInt)(quanta) >> 3)
#define oopsToQuanta(oops) ((oopUInt)(oops) << 3)

#define bytesToQuanta(bytes) (bytes)
#define quantaToBytes(quanta) (quanta)

/*
 * Definitions related to N-code
 */

#define machineHasByteAddressing TRUE /* used in copyBits & scanCharacters */

