/* SccsId is  @(#)osLinux.h	58.10 04/06/05 */
/************************************************************************
 * File:	osLinux.h
 *
 * This file contains the operating system definitions for Linux UNIX
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define	operatingSystem	operatingSystemLinux

#define SIGNALSemaphores 1

#define maxPathNameLength 1024

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
