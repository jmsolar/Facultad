/* SccsId is  @(#)exError.h	58.10 04/06/05 */
/************************************************************************
 * File: exError.h
 *
 * DESCRIPTION
 *	Define error codes, flags and routines.
 *
 * N.B. This file used to be called error.h but this conflicted with e.g.
 * Windows, which has its own error.h.  Include order can't resolve the problem
 * since at times both files need to be included.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/*
 * Error status codes.
 */
#define noError 0L
#define errCodeReadImage 1L
#define errCodeLoadImage 2L
#define errCodeImageType 3L
#define errCodeAllocHeap 4L
#define errCodeScavengerCrash 5L
#define errCodeAlloc	6L
#define errCodeCommandLine 7L
#define errCodeRtOverflow 8L
#define maxErrorCode 9L
#define errCodeMask	0xFFL

/* error severities */
#define errSevNotify	0x100L
#define errSevError		0x200L
#define errSevFatal		0x400L
#define errSevMask		0x700L
#define errSevShift		8

/* error code is platform defined flag */
#define errCodePlats	0x800L

/* error locations. Obsolete; doReportError gets filename and line number. */
#define errInTran		0x1000L
#define errInStack		0x2000L
#define errInPrim		0x3000L
#define errInMman		0x4000L
#define errInDisplay	0x6000L
#define errInTimer		0x9000L
#define errInInitialize	0xB000L
#define errInExtern		0xC000L
#define errInMask		0xF000L
#define errInPlat		0x10000L	/* this is a separate bit */
#define errInShift		12

/* error - whose fault */
#define errFaultUser	0x20000L
#define errFaultPlat	0x40000L
#define errFaultUs		0x60000L
#define errFaultLimit	0x80000L
#define errFaultMask	0xE0000L
#define errFaultShift	17

/* error addendum - contact distributor */
#define errContactUs	0x100000L

#ifndef assembly

typedef long errorStatus;
extern	errorStatus hpsErrorStatus;
extern	void	    initError(void);
extern	void	    doReportError(const char *, errorStatus, const char *, int);

/*
 *	This routine, in exLeave.c, exits the virtual machine.
 */
extern	void	vmExit(errorStatus);

#endif /* assembly */

/**********
 *  r e p o r t E r r o r
 *
 *  This macro sets the hpsErrorStatus and prints the error message
 *  if it a reportable error.
 */
#define reportError(subtext,ec) doReportError(subtext,ec,__FILE__,__LINE__)

/**********
 *  f a t a l E r r o r
 *
 *  This macro should only be invoked in the event of an error that cannot
 *  be dealt with locally or passed back up the caller chain. Currently,
 *  fatalError responds by printing an error message before quiting.
 ***/
#define fatalError(subtext,ec) doReportError(subtext,errSevFatal|(ec),__FILE__,__LINE__)
#define fatalErrorAt(subtext,ec,f,l) doReportError(subtext,errSevFatal|(ec),f,l)

#define noSubtext ((char *)0)
