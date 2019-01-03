/* SccsId is @(#)procARM.h	58.10 04/06/05 */
/***************************************************************************
 * File: procARM.h
 *
 * This file contains all the processor-dependent definitions for the
 * "Advanced Risc Machines" processor.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ***************************************************************************/

#define processor	procARM
#define ISAName        "ARM"
#define procregs_h  "regsARM.h"
#define proccgen_h  "cgenARM.h"
#define procfloat_h "floatARM.h"


#define codeExpansionFactor 120			/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 32 bit oops and byte adressing */
#include "oop32bitsBA.h"

#define PCalignmask 3		/* machinePC's are word aligned */

#define bigEndian 0			/* 1 = big-endian representation */

#define numRegArgs 2
#define numberOfRegisterArgs 4 /* C calling convention */

