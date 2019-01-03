/* SccsId is @(#)platWin32x86.h	58.10 04/06/05 */
/************************************************************************
 * File: platWin32x86.h
 *
 * This file contains the platform-dependent definitions for Win32
 * with no 16-bit support on x86 compatibles.
 *
 *	Copyright (C) 2003 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#include "platNT86.h"

#undef Has1616Pointers
#define Has1616Pointers 0
