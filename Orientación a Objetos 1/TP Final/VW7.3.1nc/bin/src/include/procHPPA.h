/* SccsId is  @(#)procHPPA.h	58.10 04/06/05 */
/************************************************************************
 * File: procHPPA.h
 *
 *  Definitions for the PA RISC
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define processor	procHPPA
#define ISAName          "PA-RISC"
#define procregs_h  "regsHPPA.h"
#define proccgen_h  "cgenHPPA.h"
#define procfloat_h "floatHPPA.h"

#define USE_JMPBUF 1

#define codeExpansionFactor 180			/* 680x0 = 100 */
#define PIC 1

/* Include definitions for processor with 32 bit oops and byte addressing */
#include "oop32bitsBA.h"

#define PCalignmask 3		/* machinePC's are longword aligned */

#define bigEndian 1			/* 1 = big-endian representation */

#define numRegArgs 2

/* IMMEDIATE_TABLE not defined; class access via table is slower (!) */


