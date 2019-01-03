/* SccsId is  @(#)procPentium.h	58.10 04/06/05 */
/***************************************************************************
 * File: procPentium.h
 *
 * This file contains all the processor-dependent definitions for the
 * Intel Pentium (iapx586) processor.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ***************************************************************************/

#define processor	procPentium
#define ISAName        "IA32"
#define procregs_h  "regs386.h"
#define proccgen_h  "cgen386.h"
#define procfloat_h "float386.h"

#define NCodeUsesCStackPointer 1
#define codeExpansionFactor 90		/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 32 bit oops and byte adressing */
#include "oop32bitsBA.h"

#define PCalignmask 0				/* machinePC's are byte aligned */

#define bigEndian 0					/* 0 = little-endian representation */

#define numRegArgs 2

#define IMMEDIATE_TABLE 1			/* class access via table is fastest */
