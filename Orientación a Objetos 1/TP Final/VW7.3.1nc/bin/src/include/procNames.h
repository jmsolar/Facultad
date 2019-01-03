/* SccsId is @(#)procNames.h	58.10 04/06/05 */
/***************************************************************************
 * File: procNames.h
 *
 * This file defines symbolic names for all defined processor ISAs.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ***************************************************************************/

/* The following is a list of all defined processor ISAs. */

#define procMC68000				1	/* Obsolete */
#define procMC68010				2	/* Obsolete */
#define procMC68020				3
#define procSunrise				4	/* a.k.a. SPARC; Obsolete => #5 */
#define procSunriseNoWindows	5	/* a.k.a. SPARC */
#define procI386				6	/* Obsolete => #20 */
#define procI286				8	/* Obsolete */

#define procMC68030				10
#define procMC68040				11
#define procMIPS				12

#define procRS6000				14
#define procI486				15	/* Obsolete => #20 */
#define procHPPA				16
#define procARM					17
#define procVAX					18	/* Obsolete */
#define procAXP					19
#define procPentium				20
#define procRS60x				21
#define procPPCSysVABI			22

#define procAXP64				64
#define procx86_64				65
#define procSPARC64NoWindows	66
#define procPPC64				67
#define procHPPA64				68

#define	procNil					99
