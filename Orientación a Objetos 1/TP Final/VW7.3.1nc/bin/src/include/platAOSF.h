/* SccsId is  @(#)platAOSF.h	58.10 04/06/05 */
/************************************************************************
 * File: platAOSF.h
 *
 * This file contains the platform-dependent definitions for the Nil.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define RIGHT_BIT_FIELD_ORDER 1 /* Compiler ordering of bit fields in structs */

/*OSF32 indicated xtaso  compilation on Alpha OSF/1 v2.x, v 3.* using pointer
 * size pragmas to resolve the conflict between the VM's need for 32 bit wide
 * pointers and the 64 bit pointers native to OSF/1 on AXP.
 *
 * long defined to int to obtain 32 bit width for long data types used in
 * manipulating and/or storing pointer values.
 *
 * This include was originally in hps.h, moved here because it is platform
 * specific AND no pointers or declarations affected occur before this module
 * is included.  Code subsequently added to either hps.h or platform.h prior
 * to including this file might need to be moved after this include.
 */

#ifdef OSF32
#	define PLATFORM_IS_64_BITS 1
#	define PLATFORM_SUPPORTS_64_BITS 1
#	define HAS_64_BIT_ARITHMETIC 1
#	ifndef assembly
/* access to 64-bit longs avoiding define of long to int */
typedef long longlong;
typedef unsigned long ulonglong;
#		pragma pointer_size (short)
#	endif
#	define long int
#endif

#define HaveCleanSignals TRUE
#ifdef PLATFORM_SIGNAL_HANDLER
#	define CanSmashRegisters TRUE
#else
#	define CanSmashRegisters FALSE
#endif
#define HaveLimitRegister TRUE

#define bytesInNMethodZone (1152 * 1024)

/* I/O defines */
#define PLAT_OSNAME	"unix osf dec alpha osf1"
#define PHONYPAIR_ACCEPT_LOOP_DELAY_USECS 1

#define GlueProc "glueAXP.h"

#define pdFPUType() 1
#define DOUBLES_ALIGNED

/* On UNIX X11 platforms only, the HaveWriteSigiosOnDisplayConnection
 *   should specify whether SIGIO/SIGPOLL for the display connection
 *   can be signaled even if there is nothing readable on the connection.
 */

#define HaveWriteSigiosOnDisplayConnection TRUE

/* define OSF to select some system 5 includes for some unx platform choices */
#define OSF 1

/* define _BSD flag to get the bsd support from system headers*/
#define _BSD

/* setup sc_gr to mean sc_regs like MIPS did */
#define sc_gr sc_regs
