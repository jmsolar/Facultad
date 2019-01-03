/* SccsId is  @(#)osSun.h	58.10 04/06/05 */
/************************************************************************
 * File:	osSun.h
 *
 * This file contains the operating system definitions for Sun's
 * UNIX 4.3
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define	operatingSystem	operatingSystemSun

#define SIGNALSemaphores 1

#define maxPathNameLength 1024

/* override the system default of 256.  Some versions have more */
#define FD_SETSIZE 2048

/* These are the defines to read and write image files */
#define fileHandle int

/* Flags for use with pdOpenImage */
#ifndef assembly
#	include <fcntl.h>
#	include <unistd.h>
#	include <sys/file.h>

extern fileHandle pdOpenImage(char *, int, int *);
extern int pdCloseImage(fileHandle);
extern long pdRead(fileHandle, void *, long, int *);
extern long pdWrite(fileHandle, void *, long, int *);

#endif
#define imageReadFlags O_RDONLY
#define imageWriteFlags (O_WRONLY | O_CREAT | O_TRUNC)
#define imageOpenError -1
#define fileHandleForImageResource -2

#define pdSeek(file, offset) lseek(file, offset, L_SET)
