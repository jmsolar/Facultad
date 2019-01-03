/* SccsId is  @(#)osMac.h	58.10 04/06/05 */
/************************************************************************
 * File:	osMac.h
 *
 * This file contains the operating system definitions for Macintosh OS
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define	operatingSystem	operatingSystemMac

#define maxPathNameLength 255

/* These are the defines to read and write image files */
#define fileHandle short

/* Flags for use with pdOpenImage */
#define imageReadFlags 1
#define imageWriteFlags 0
#define imageOpenError 0
#define fileHandleForImageResource -1

#ifndef assembly
extern fileHandle	pdOpenImage(char *path, long flags, int *err);
extern int			pdOpenImageResource(byte **, long *);
extern long			pdRead(fileHandle file, void *buf, long nbytes, int *err);
extern long			pdWrite(fileHandle file, void *buf, long nbytes, int *err);
extern long			pdSeek(fileHandle file, long offset);
extern int			pdCloseImage(fileHandle file);
#endif
