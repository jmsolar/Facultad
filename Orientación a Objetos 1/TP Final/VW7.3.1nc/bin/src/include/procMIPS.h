/* SccsId is  @(#)procMIPS.h	58.10 04/06/05 */
/************************************************************************
 * File: procMIPS.h
 *
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define processor	procMIPS
#define ISAName        "MIPS"
#define procregs_h  "regsmips.h"
#define proccgen_h  "cgenMips.h"
#define procfloat_h "floatMips.h"
#define MIPS

#define codeExpansionFactor 180			/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 32 bit oops and byte addressing */
#include "oop32bitsBA.h"

#define PCalignmask 3		/* machinePC's are longword aligned */

/*  bigEndian is defined in platXXX.h since the MIPS can run as big or little
 * endian. */

#define tBigEndian bigEndian  /* 0 = little-endian representation */

#define numRegArgs 2

