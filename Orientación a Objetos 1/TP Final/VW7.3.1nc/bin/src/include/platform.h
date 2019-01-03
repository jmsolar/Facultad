/* SccsId is  @(#)platform.h	58.10 04/06/05 */
/************************************************************************
 * File: platform.h
 *
 * This file pulls in the correct platform-dependent definitions by
 * including the .h files that are appropriate for the current platform
 * (the current "platform" is defined by make and passed to cc).
 * The fact that this file includes other .h files rather than the
 * actual definitions associated with a particular platform allows
 * the .h files associated with each platform to be modified without
 * forcing all the code for the other platforms to be recompiled.
 *
 * For each platform header files are included which define that platform's
 * processor, operating system, display/windowing system and floating point
 * processor/software.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/* The following contain lists of all defined platforms,
 * processors, operating systems and display/windowing systems.
 */
#include "platNames.h"
#include "procNames.h"
#include "osNames.h"
#include "dispNames.h"

#if platform == 0
#	error "unknown platform"

#elif platform == platNil
# undef  NilPlat
# define NilPlat 1
#	include "platNil.h"
#	include "procNil.h"
#	include	"bits32.h"
#	include "osNil.h"
#	include "dispNil.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platAix
# undef  AIX
# define AIX 1
# undef PROC_HERALD_NAME
# define PROC_HERALD_NAME " PowerPC"
#	include "platRS6000.h"
#	include "procPPCSysVABI.h"
#	include	"bits32.h"
#	include "osBSD.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platAix64
# undef  AIX
# define AIX 1
#	include "platAix64.h"
#	include "procPPC64SysVABI.h"
#	include	"bits64.h"
#	include "osBSD.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platHPPA
# undef  HPUXPA
# define HPUXPA 1
#	include "platHPPA.h"
#	include "procHPPA.h"
#	include	"bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platHPPA64
# undef  HPUXPA
# define HPUXPA 1
#	include "platHPPA64.h"
#	include "procHPPA64.h"
#	include	"bits64.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platPowerMac
#	include "platPowerMac.h"
# undef  PMac
# define PMac 1
#	include "procRS60x.h"
#	include	"bits32.h"
#	include "osMac.h"
#	include "dispMac.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platMacX
# undef  MACOSXPPC
# define MACOSXPPC 1
#	include "platMacX.h"
#	include "procRS60x.h"
#	include "osBSD.h" /* would prefer osMACH.h */
#	include "dispMacX.h"
#	include	"bits32.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platMacXX11
	/*
	 * We hope that this platform can be discarded in favour of an X11 GUI
	 * library complementing the Aqua one.
	 */
# undef  MACOSXPPC
# define MACOSXPPC 1
#	include "platMacX.h"
#	include "procRS60x.h"
#	include "osBSD.h" /* would prefer osMACH.h */
#	include "dispX11.h"
#	include	"bits32.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platMacX64
# undef  MACOSXPPC
# define MACOSXPPC 1
#	include "platMacX.h"
#	include "procRS60x64.h"
#	include "osBSD.h" /* would prefer osMACH.h */
#	include "dispMacX.h"
#	include	"bits64.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platNTPentium
# undef  NTPentium
# define NTPentium 1
#	include "platNT86.h"
#	include "procPentium.h"
#	include	"bits32.h"
#	include "osNT.h"
#	include "dispNT.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platWin32Pentium
# undef  NTPentium
# define NTPentium 1
#	include "platWin32x86.h"
#	include "procPentium.h"
#	include	"bits32.h"
#	include "osNT.h"
#	include "dispNT.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platWinCEPentium
# undef  CE386
# define CE386 1
#	include "platWinCE86.h"
#	include "procI386.h"
#	include	"bits32.h"
#	include "osNT.h"
#	include "dispnt.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platWinCEARM
# undef  CEARM
# define CEARM 1
#	include "platWinCEARM.h"
#	include "procARM.h"
#	include	"bits32.h"
#	include "osNT.h"
#	include "dispnt.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platWin64x86_64
# undef  Win64
# define Win64 1
#	include "platWin32x86.h"
#	include "procPentium.h"
#	include	"bits32.h"
#	include "osNT.h"
#	include "dispNT.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platSolaris4
# undef  Solaris4
# define Solaris4 1
#	include "platSolaris.h"
#	include "procSPARCnw.h"
#	include	"bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platSolaris4MM
# undef  Solaris4
# define Solaris4 1
#	include "platSolaris.h"
#	include "procSPARCnw.h"
#	include	"bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldBelowPerm.h"

#elif platform == platSolaris64
# undef  Solaris4
# define Solaris4 1
#	include "platSolaris64.h"
#	include "procSPARC64nw.h"
#	include	"bits64.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmTaggedPerm.h"

#elif platform == platAOSF
# undef  AOSF
# define AOSF 1
#	include "platAOSF.h"
#	include "procAXP.h"
#	include "bits32.h"
#	include "osAOSF.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platLinux86
# undef Linux86
# define Linux86 1
#	include "platLinux86.h"
#	include "procPentium.h"
#	include	"bits32.h"
#	include "osLinux.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platLinuxx86_64
# undef Linuxx86_64
# define Linuxx86_64 1
#	include "platLinuxx86_64.h"
#	include "procx86_64.h"
#	include	"bits64.h"
#	include "osLinux.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmTaggedPerm.h"

#elif platform == platLinuxSPARC
# undef LinuxSPARC
# define LinuxSPARC 1
#	include "platLinuxSPARC.h"
#	include "procSPARCnw.h"
#	include	"bits32.h"
#	include "osLinux.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platLinuxPPC
# undef  LinuxPPC
# define LinuxPPC 1
#	include "platLinuxPPC.h"
#	include "procPPCSysVABI.h"
#	include	"bits32.h"
#	include "osLinux.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platLinux68k
# undef  Linux68k
# define Linux68k 1
#	include "platLinux68k.h"
#	include "procMC68020.h"
#	include	"bits32.h"
#	include "osLinux.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platLinuxARM
# undef  LinuxARM
# define LinuxARM 1
#	include "platLinuxARM.h"
#	include "procARM.h"
#	include	"bits32.h"
#	include "osLinux.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platLinuxPS2
# undef  LinuxPS2
# define LinuxPS2 1
#	include "platLinuxPS2.h"
#	include "procMIPS.h"
#	include "bits32.h"
#	include "osLinux.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platSgi		/* SGI Irix 5.3, 6.x, MIPS ABI */
# undef  IRIX
# define IRIX 1
#	include "platSgi.h"
#	include "procMIPS.h"
#	include "bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

#elif platform == platSgi64		/* SGI Irix 6.x, MIPS ABI */
# undef  IRIX
# define IRIX 1
#	include "platSgi.h"
#	include "procMIPS64.h"
#	include "bits64.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmTaggedPerm.h"


/*
	Obsolete or lapsed platforms:

#elif platform == platNT386
# undef  NT386
# define NT386 1
#	include "platNT86.h"
#	include "procI386.h"
#	include	"bits32.h"
#	include "osNT.h"
#	include "dispNT.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platANT
# undef NTAXP
# define NTAXP 1
#	include "platANT.h"
#	include "procAXP.h"
#	include "bits32.h"
#	include "osNT.h"
#	include "dispNT.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platRS6000power2
# undef  AIX
# define AIX 1
# undef PROC_HERALD_NAME
# define PROC_HERALD_NAME " Power2"
#	include "platRS6000.h"
#	include "procRS6000.h"
#	include	"bits32.h"
#	include "osBSD.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platMac
# undef  Mac
# define Mac 1
#	include "platMac.h"
#	include "procMC68020.h"
#	include	"bits32.h"
#	include "osMac.h"
#	include "dispMac.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platSni     (* HEEG -- SIEMENS Nixdorf *)
# undef  Sni
# define Sni 1
# undef ENGINE_BUILDER
# define ENGINE_BUILDER " (Heeg)"
#	include "platSni.h"
#	include "procMIPS.h"
#	include "bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platSun3X
# undef  Sun3X
# define Sun3X 1
#	include "platSun3X.h"
#	include "procMC68020.h"
#	include	"bits32.h"
#	include "osSun.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platSun4
# undef  Sun4X
# define Sun4X 1
#	include "platSun4X.h"
#	include "procSPARCnw.h"
#	include	"bits32.h"
#	include "osSun.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platSun4MM
# undef  Sun4X
# define Sun4X 1
#	include "platSun4X.h"
#	include "procSPARCnw.h"
#	include	"bits32.h"
#	include "osSun.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldBelowPerm.h"
#elif platform == platNeXT
# undef  NeXT
# define NeXT 1
#	include "platNeXT.h"
#	include "procMC68020.h"
#	include	"bits32.h"
#	include "osMach.h"
#	include "dispNeXT.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platSCO386
#	include "platSCO386.h"
#	include "procI386.h"
#	include "bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platMSDOS386
#	include "platCompaq.h"
#	include "procI386.h"
#	include	"bits32.h"
#	include "osMSDOS.h"
#	include "dispEGA.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platApollo
#	include "platApollo.h"
#	include "procMC68020.h"
#	include "bits32.h"
#	include "osBSD.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platWin386
# undef  Win386
# define Win386 1
#	include "platWin.h"
#	include "procI386.h"
#	include	"bits32.h"
#	include "osMSDOS.h"
#	include "dispEGA.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platHP300
# undef  HP300
# define HP300 1
#	include "platHP300.h"
#	include "procMC68020.h"
#	include	"bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platSeq386
# undef  Seq386
# define Seq386 1
#	include "platSeq386.h"
#	include "procI386.h"
#	include	"bits32.h"
#	include "osV.h"
#	include "dispX11.h"
#	include "floatIEEE.h"
#	include "mmOldBelowPerm.h"
#elif platform == platDecMips
# undef  DecMips
# define DecMips 1
#	include "platDecMips.h"
#	include "procMIPS.h"
#	include "bits32.h"
#	include "osBSD.h"
#	include "dispDec.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"
#elif platform == platOS2
# undef  OS2
# define OS2 1
#	include "platos2.h"
#	include "procI386.h"
#	include	"bits32.h"
#	include "osOS2.h"
#	include "dispOS2.h"
#	include "floatIEEE.h"
#	include "mmOldAbovePerm.h"

*/

#else
#	error "unknown platform"
#endif

/* ensure no missing defines get defaulted to 0 */
#if processor == 0
#	error "null processor"
#endif
#if operatingSystem == 0
#	error "null operatingSystem"
#endif
#if displaySystem == 0
#	error "null displaySystem"
#endif

/*
 * Defaults for values optionally specified in each platXXX.h file.
 */
#ifndef signalInStackLimit
#   define signalInStackLimit HaveCleanSignals
#endif
#ifndef FstackLimitInRegister
#   define FstackLimitInRegister (HaveLimitRegister && \
                                 (CanSmashRegisters || !HaveCleanSignals))
#endif
#ifndef defaultMappedPermSpaceBase
#   define defaultMappedPermSpaceBase ((quantum *)0xf6d10000)
#endif

#ifndef maxBytesInNMethodZone
#   define maxBytesInNMethodZone (16 * 1024 * 1024)
#endif

#ifndef NCodeUsesCStackPointer
#	define NCodeUsesCStackPointer 0
#endif

# if !defined(SHLIB_EXTENSION)
#   define SHLIB_EXTENSION ".so"
#endif

