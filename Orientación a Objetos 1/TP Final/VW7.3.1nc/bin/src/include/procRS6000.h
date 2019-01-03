/* SccsId is  @(#)procRS6000.h	58.10 04/06/05 */
/************************************************************************
 * File: procRS6000.h
 *
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define processor	procRS6000
#define ISAName        "RS6000"
#define procregs_h  "regsRS6000.h"
#define proccgen_h  "cgenRS6000.h"
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
