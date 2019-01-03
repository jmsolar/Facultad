/* SccsId is @(#)bits64.h	58.10 04/06/05 */
/************************************************************************
 * File:	bits64.h
 *
 * This file contains definitions for the 64-bit VM and 64 bit C compilers.
 *
 *	Copyright (C) 2004 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define HPS64 1
#define PLATFORM_SUPPORTS_64_BITS 1
#define HAS_64_BIT_ARITHMETIC 1
#ifndef assembly
# undef byte
# undef bool
typedef unsigned char byte;
typedef unsigned short wideChar;
# ifndef __STDBOOL_H__
typedef unsigned int bool;
# endif
typedef long memIndex;			 /* integer large enough for sizeof(anything) */
typedef unsigned long memUIndex; /* ditto but unsigned */
typedef byte quantum;			 /* Machine's natural addressing unit. */
typedef long oopSized;			 /* Same size as an oop. */
typedef long oopInt;			 /* Integer the same size as an oop. */
typedef unsigned long oopUInt;	 /* Unsigned integer the same size as an oop. */
typedef unsigned char    q8;	 /*  8 bits */
typedef   signed char   sq8;	 /*  8 bits */
typedef unsigned short  q16;	 /* 16 bits */
typedef   signed short sq16;	 /* 16 bits */
typedef unsigned int    q32;	 /* 32 bits */
typedef   signed int   sq32;	 /* 32 bits */
typedef unsigned long   q64;	 /* 64 bits */
typedef   signed long  sq64;	 /* 64 bits */
# define ulonglong  q64			 /* pre-64-bit synonym for q64 */
# define  longlong sq64			 /* pre-64-bit synonym for sq64 */

# include "unicode.h"
    
# define add64(s,a,b)      ((s)  = (a) + (b))
# define add32to64(s,tt)   ((s) += (tt))
# define sub64(d,a,b)      ((d)  = (a) - (b))
# define sub32from64(s,tt) ((s) -= (tt))
# define inc64(n) ((n) += 1)
# define dec64(n) ((n) -= 1)
# define eq64(a,b) ((a) == (b))
# define lt64(a,b) ((a) <  (b))
# define gt64(a,b) ((a) >  (b))
# define le64(a,b) ((a) <= (b))
# define ge64(a,b) ((a) >= (b))
# define gt0_64(v) ((v) > 0)
# define gt32_64(sf,tt) ((sf) > (tt))
# define as64(d,h,l) ((d) = (q64)(h) * ((q64)1 << 32) + (l)) /* +ve only! */
# define init64(h,l) (((q64)(h) * ((q64)1<<32)) + (l))
# define from64(n) (n)
# define div64(a,b) ((a) / (b))
# define mul64(a,b) ((a) * (b))
#endif /* assembly */
