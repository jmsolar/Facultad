/* SccsId is @(#)nt.ntvw.h	58.10 04/06/05 */
/************************************************************************
 *  File: ntvw.h
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 * Resource identifiers.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define IDM_ABOUT	100
#if 0	/* Some load cursors to indicate activity while loading the image. */
		/* Currently unused. */
#	define LOADCURSOR1 318
#	define LOADCURSOR2 319
#	define LOADCURSOR3 320
#	define LOADCURSOR4 321
#endif
#define OEICON		323	/* optional program icon, type ICON */
#define OESPLASH	324	/* optional herald bitmap, type BITMAP */
#define STRAPPNAME	325	/* optional application name, type STRING */
#if OBSOLETE
# define STRTITLE	327
# define STRMENU	328
# define STRMEMORY	329
# define STRCMDLINE	330
#endif
#define OEIMAGEDATA	332	/* optional virtual image, type OEIMAGEDATA */
#define NOCMDLINE	333	/* optional flag to ignore command line, type NOCMDLINE */
