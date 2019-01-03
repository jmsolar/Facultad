/* SccsId is  @(#)procRS60x.h	58.10 04/06/05 */
/************************************************************************
 * File: procRS60x.h
 *
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define processor	procRS60x
#define ISAName        "PowerPC"
#define procregs_h  "regsRS6000.h"
#define proccgen_h  "cgenRS60x.h"
#define procfloat_h "floatRS6000.h"

#define USE_JMPBUF 1

#define codeExpansionFactor 180			/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 32 bit oops and byte addressing */
#include "oop32bitsBA.h"

#define PCalignmask 3		/* machinePC's are longword aligned */

#define bigEndian 1			/* 1 = big-endian representation */

#define numRegArgs 2

#define IMMEDIATE_TABLE 1	/* class access via table is fastest */
