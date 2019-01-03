/* SccsId is  @(#)oop32bitsBA.h	58.10 04/06/05 */
/************************************************************************
 * File: oop32bitsBA.h
 *
 * This file contains all the processor-dependent definitions for
 * systems with 32 bit oops and byte addressing.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#ifndef assembly
typedef unsigned char *machinePC;	/* hardware representation of PC */
#endif

#define quantaInOop 4 /* number of addressable units in an oop */
#define log2bytesInOop 2
#define bytesInOop 4
#define bitsInOop 32
#define bitsInByte 8

#define bytesToOops(bytes) ((oopUInt)(bytes) >> 2)
#define oopsToBytes(oops) ((oopUInt)(oops) << 2)

#define quantaToOops(quanta) ((oopUInt)(quanta) >> 2)
#define oopsToQuanta(oops) ((oopUInt)(oops) << 2)

#define bytesToQuanta(bytes) (bytes)
#define quantaToBytes(quanta) (quanta)

/*
 * Definitions related to N-code
 */

#define machineHasByteAddressing TRUE /* used in copyBits & scanCharacters */

