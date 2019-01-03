/* SccsId is  @(#)procAXP.h	58.10 04/06/05 */
/*********************************************************************
 * File: procAXP.h
 *
 * This file contains all the processor-dependent definitions for the
 * Alpha AXP processor.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 *
 *
 *********************************************************************/

#define processor	procAXP
#define ISAName        "AXP"
#define procregs_h  "regsAXP.h"
#define proccgen_h  "cgenAXP.h"
#define procfloat_h "floatAXP.h"

#define USE_JMPBUF 1

#define codeExpansionFactor 180			/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 32 bit oops and byte adressing  */
#include "oop32bitsBA.h"

#define PCalignmask 3		/* machinePC's are longword aligned */

#define bigEndian 0			/* 1 = big-endian representation */
#define tBigEndian bigEndian

#define numRegArgs 2

#define IMMEDIATE_TABLE 1		/* class access via table is fastest */
