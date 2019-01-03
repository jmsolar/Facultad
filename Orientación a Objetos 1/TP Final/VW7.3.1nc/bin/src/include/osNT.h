/* SccsId is @(#)osNT.h	58.10 04/06/05  */
/************************************************************************
 * File:	osNT.h
 *
 * This file contains the operating system definitions for NT
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define	operatingSystem	operatingSystemNT

#define maxPathNameLength 255

#define fileHandle int

/* Flags for use with pdOpenImage */
#define imageReadFlags 0
#define imageWriteFlags 1
#define imageOpenError -1
#define fileHandleForImageResource -2

#ifndef assembly /* ignore this file when doing assembly */
/*
 * Prototypes
 */
extern int pdOpenImage(oeChar *path, bool forWrite, int *piError);
extern int pdOpenImageResource(void **, long *);
extern int pdCloseImage(fileHandle file);
extern int pdCloseImageResource(fileHandle file);
extern int pdRead(fileHandle file, void *buf, int nbytes, int *piError);
extern int pdWrite(fileHandle file, void *buf, int nbytes, int *piError);
extern int pdSeek(fileHandle file, int offset);
#endif
