/* SccsId is @(#)procx86_64.h	58.10 04/06/05 */
/***************************************************************************
 * File: procx86_64.h
 *
 * This file contains all the processor-dependent definitions for AMD x86-64
 * compatible 64-bit processors, an extension to the x86 architecture.
 *
 *	Copyright (C) 2003 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ***************************************************************************/

#define processor	procx86_64
#define ISAName     "x86-64"
#define procregs_h  "regsx86_64.h"
#define proccgen_h  "cgenx86_64.h"
#define procfloat_h "floatx86_64.h"

#define NCodeUsesCStackPointer 1
#define codeExpansionFactor 100		/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 64 bit oops and byte adressing */
#include "oop64bitsBA.h"

#define PCalignmask 0				/* machinePC's are byte aligned */

#define bigEndian 0					/* 0 = little-endian representation */

#define numRegArgs 2

#define IMMEDIATE_TABLE 1			/* class access via table is fastest */
