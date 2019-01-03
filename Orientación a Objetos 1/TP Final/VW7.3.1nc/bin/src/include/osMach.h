/* SccsId is  @(#)osMach.h	58.10 04/06/05 */
/************************************************************************
 * File:	osMach.h
 *
 * This file contains the operating system definitions for the MACH OS.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define	operatingSystem	operatingSystemBSD

#define SIGNALSemaphores 1

#define maxPathNameLength 1024

/* These are the defines to read and write image files */
#define fileHandle int

/* Flags for use with pdOpenImage and pdSeek */
#ifndef assembly
#include <bsd/libc.h>

extern fileHandle pdOpenImage(char *, int, int *);
extern int pdCloseImage(fileHandle);
extern int pdRead(fileHandle, void *, int, int *);
extern int pdWrite(fileHandle, void *, int, int *);

#endif
#define imageReadFlags O_RDONLY
#define imageWriteFlags (O_WRONLY | O_CREAT | O_TRUNC)
#define imageOpenError -1
#define fileHandleForImageResource -2

#define pdSeek(file, offset) lseek(file, offset, L_SET)
