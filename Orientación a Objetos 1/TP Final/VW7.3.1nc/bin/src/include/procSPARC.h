/* SccsId is  @(#)procSPARC.h	58.10 04/06/05 */
/***************************************************************************
 * File: procSPARC.h
 *
 * This file contains all the processor-dependent definitions for the
 * SPARC "Sunrise" processor, using register windows in generated code.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ***************************************************************************/

#define processor	procSunrise
#define ISAName        "SPARC"
#define procregs_h  "regssun.h"
#define proccgen_h  "cgenSparc.h"
#define procfloat_h "floatSparc.h"

#define SPARC
#define USE_JMPBUF 1

#define codeExpansionFactor 160			/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 32 bit oops and byte adressing */
#include "oop32bitsBA.h"

#define PCalignmask 3		/* machinePC's are (long)word aligned */

#define bigEndian 1			/* 1 = big-endian representation */

#define numRegArgs 2

#define IMMEDIATE_TABLE 1	/* class access via table is fastest */

