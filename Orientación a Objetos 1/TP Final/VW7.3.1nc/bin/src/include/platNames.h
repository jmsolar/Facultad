/* SccsId is @(#)platNames.h	58.10 04/06/05 */
/************************************************************************
 * File: platNames.h
 *
 * This file defines all of the platform symbolic names.
 *
 *	Copyright (C) 1999-2003 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/* The following is a list of all defined platforms.
 *
 * The defined symbols may be used on #if lines for platform code variations.
 * Do not use these symbols in non-platform code.
 *
 * Full 64-bit implementation platforms have a code of 64 or above.
 */

/* Current production platforms */

#define platHPPA			25	/* PA-RISC, HPUX 10 & 11 */
#define platLinux86			40	/* Intel x86 Linux */
#define platLinuxPPC	   	42	/* PowerPC Linux */
#define platLinuxSPARC		43	/* SPARC Linux */
#define platMacX			39	/* PowerPC MacOS X */
#define platNTPentium		41	/* IA-32 Pentium or compatible, NT/'95 et al */
#define platPowerMac		32	/* PowerPC MacOS 8 & 9 */
#define platRS6000			21	/* PowerPC AIX */
#define platAix				21	/* a.k.a. PowerPC AIX */
#define platSgi				62	/* MIPS R4000 or better, SGI Irix 6.x */
#define platSolaris4		29	/* Solaris 5.x SPARC32 */
#define platWinCEARM		48	/* StrongARM/XScale, WinCE 4.x */
#define platWinCEPentium	49	/* IA-32 Pentium or compatible, WinCE 4.x */
#define platWinCEEmulator	49	/* Synonym for WinCE Emulator */


/* Prospective or experimental platforms in development */

#define platLinux68k		44	/* m68k Linux */
#define platLinuxARM		45	/* StrongARM/XScale Linux */
#define platMacXX11			46	/* PowerPC MacOS X using X11 (will hopefully not be needed; just a different GUI library from platMacX) */
#define platLinuxPS2		50	/* MIPS "Emotion Engine" PlayStation/2 Linux Kit */
#define platLinuxx86_64		64	/* AMD x86-64, Linux 64-bit OE & OS */
#define platSolaris64		65	/* SPARC64, Solaris 5.x 64-bit OE & OS */


/* Lapsed platforms */

#define platAOSF			35	/* Alpha AXP OSF 32-bit OE, 64-bit OS	*/
#define platSun4			12	/* SPARC Sun4X							*/
#define platSun4MM			36	/* SPARC Sun4X using mmap() permspace	*/
#define platSolaris4MM		31	/* SPARC Solaris4 using mmap() permspace*/
#define platRS6000power2	38	/* Power2 AIX							*/
#define platANT				34	/* Alpha AXP, Windows NT 3.5			*/
#define platSni				63	/* MIPS, Siemens Nixdorf SIENIX 5.x		*/


/* Possible future platforms. */

#define platAix64			67	/* PowerPC 64, AIX 5.x 64-bit OE & OS */
#define platHPPA64			68	/* PA-RISC64, HPUX 11 64-bit OE & OS */
#define platSgi64			70	/* MIPS R12000, SGI Irix 6.x 64-bit OE & OS */
#define platMacX64			66	/* PowerPC 64, MacOS X 64-bit OE & OS */
#define platWin32Pentium	47	/* IA-32 Pentium et al, Win32 no 16-bit */
#define platWin64x86_64		69	/* x86-64, Win64 64-bit OE & OS */
/* #define platLinuxESA390	51	IBM ESA/390, Linux */
/* #define platNTMIPS		30	NTMips */
/* #define platOpenVMS		33	DEC VAX */
/* #define platAOSF64		71	Alpha AXP COMPAQ True64 64-bit OE & OS */


/* Obsoleted platforms. */
/* It is almost guaranteed that obsolete platforms will not build or run. */

/* #define platSun2			1		-- obsolete -- */
/* #define platSun3			2		-- obsolete -- */
/* #define platSun4			3		-- obsolete -- */
/* #define platIntel386		4		-- obsolete -- */
/* #define platSun386i		5		-- obsolete -- */
/* #define platSun3X10		6		-- obsolete -- */
/* #define platIsiX10		7		-- obsolete -- */
/* #define platMIPS			8		-- obsolete -- */
/* #define platMSDOS386		9		-- obsolete -- */
/* #define platSun3X		10		-- obsolete -- */
/* #define platSun4X11		11		-- obsolete -- */
/* #define platTitanNil		13		-- obsolete -- */
/* #define platMIPSNil		14		-- obsolete -- */
/* #define platVaxX11		15		-- obsolete -- */
/* #define platDecMips		16		-- obsolete -- */
/* #define platMac			17		-- obsolete -- */
/* #define platHP300		18		-- obsolete -- */
/* #define platSun386iX11	19		-- obsolete -- */
/* #define platApollo		20		-- obsolete -- */
/* #define platSCO386		22		-- obsolete -- */
/* #define platSeq386		23		-- obsolete -- */
/* #define platNeXT			24		-- obsolete -- */
/* #define platOS2			27		-- obsolete -- */
/* #define platWin386		28		-- obsolete -- */
/* #define platNT386		26		-- obsolete -- */


#define	platNil				99	/* NilPlat */

#ifdef NCUO
#	define platformThumbprint(platCode) ((platCode)|128)
#else
#	define platformThumbprint(platCode) ((platCode)&~128)
#endif
