/* SccsId is  @(#)osAOSF.h	58.10 04/06/05 */
/************************************************************************
 * File:	osAOSF.h
 *
 * Operating system definitions for UNIX BSD 4.3
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/
#ifdef OSF32
#undef long
#  ifndef assembly
#	pragma pointer_size (save)
#	pragma pointer_size (long)
#  endif
#endif

#define	operatingSystem	operatingSystemAOSF

#define SIGNALSemaphores 1

#define maxPathNameLength 1024

/* These are the defines to read and write image files */
#define fileHandle int

/* Flags for use with pdOpenImage and pdSeek */
#ifndef assembly
#include <fcntl.h>						/* for open() */
#include <unistd.h>						/* for read, write, close */
#include <sys/file.h>					/* for L_SET */

extern fileHandle pdOpenImage(char *, long, int *);
extern int pdCloseImage(fileHandle);
extern long pdRead(fileHandle, void *, long, int *);
extern long pdWrite(fileHandle, void *, long, int *);

#endif
#define imageReadFlags O_RDONLY
#define imageWriteFlags (O_WRONLY | O_CREAT | O_TRUNC)
#define imageOpenError -1
#define fileHandleForImageResource -2

#define pdSeek(file, offset) lseek(file, offset, L_SET)

#ifdef OSF32
#  ifndef assembly
#       pragma pointer_size (restore)
#  endif
#define long int
#endif
