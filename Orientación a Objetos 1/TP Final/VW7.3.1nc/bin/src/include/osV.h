/* SccsId is  @(#)osV.h	58.10 04/06/05 */
/************************************************************************
 * File:	osV.h
 *
 * This file contains the operating system definitions for UNIX system V
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define	operatingSystem	operatingSystemV

#define maxPathNameLength 1024

#define SIGNALSemaphores 1

/* These are the defines to read and write image files */
#define fileHandle int

#ifndef assembly

#include <fcntl.h>
#include <unistd.h>

extern fileHandle pdOpenImage(char *, int, int *);
extern int pdCloseImage(fileHandle);
extern long pdRead(fileHandle, void *, long, int *);
extern long pdWrite(fileHandle, void *, long, int *);

#endif

/* Flags for use with pdOpenImage */
#define imageReadFlags O_RDONLY
#define imageWriteFlags (O_WRONLY | O_CREAT | O_TRUNC)
#define imageOpenError -1
#define fileHandleForImageResource -2

#define pdSeek(file, offset) lseek(file, offset, SEEK_SET)
