/* SccsId is @(#)bits32.h	58.10 04/06/05 */
/************************************************************************
 * File:	bits32.h
 *
 * This file contains definitions for the 32-bit VM and 32 bit C compilers.
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#define HPS32 1
#ifndef assembly
# undef byte
# undef bool
typedef unsigned char byte;
typedef unsigned short wideChar;
# ifndef __STDBOOL_H__
typedef unsigned int bool;
# endif
typedef int memIndex;			/* integer large enough for sizeof(anything) */
typedef unsigned int memUIndex; /* ditto but unsigned */
typedef byte quantum;			/* Machine's natural addressing unit. */
typedef int oopSized;			/* Same size as an oop. */
typedef int oopInt;				/* Integer the same size as an oop. */
typedef unsigned int oopUInt;	/* Unsigned integer the same size as an oop. */
typedef unsigned char    q8;	/*  8 bits */
typedef signed   char   sq8;	/*  8 bits */
typedef unsigned short  q16;	/* 16 bits */
typedef signed   short sq16;	/* 16 bits */
typedef unsigned long   q32;	/* 32 bits */
typedef signed   long  sq32;	/* 32 bits */
# define  q64 ulonglong			/* 64 bits; typedef platform dependent */
# define sq64  longlong			/* 64 bits; typedef platform dependent */

# include "unicode.h"
    
/*
 * If the platform's C compiler defines signed and unsigned 64-bit integer
 * types then platFOO.h defines them to be longlong and ulonglong and
 * defines HAS_64_BIT_ARITHMETIC to be 1.  Otherwise we provide a substitute
 * type and associated definitions sufficient to support a microsecond clock.
 */
# if HAS_64_BIT_ARITHMETIC
#  if !defined(add64)
#	define add64(s,a,b)      ((s)  = (a) + (b))
#	define add32to64(s,tt)   ((s) += (tt))
#	define sub64(d,a,b)      ((d)  = (a) - (b))
#	define sub32from64(s,tt) ((s) -= (tt))
#	define inc64(n) ((n) += 1)
#	define dec64(n) ((n) -= 1)
#	define eq64(a,b) ((a) == (b))
#	define lt64(a,b) ((a) <  (b))
#	define gt64(a,b) ((a) >  (b))
#	define le64(a,b) ((a) <= (b))
#	define ge64(a,b) ((a) >= (b))
#	define gt0_64(v) ((v) > 0)
#	define gt32_64(sf,tt) ((sf) > (tt))
#	define as64(d,h,l) ((d) = (ulonglong)(h) * ((ulonglong)1 << 32) + (l)) /* +ve only! */
#	define init64(h,l) (((ulonglong)(h) * ((ulonglong)1<<32)) + (l))
#	define from64(n) (n)
#	define div64(a,b) ((a) / (b))
#	define mul64(a,b) ((a) * (b))
#  endif
#else /* HAS_64_BIT_ARITHMETIC */
# if bigEndian
typedef struct {          long hi; unsigned long lo; }  longlong;
typedef struct { unsigned long hi; unsigned long lo; } ulonglong;
#	define init64(h,l) { (h), (l) }
# else
typedef struct { unsigned long lo;          long hi; }  longlong;
typedef struct { unsigned long lo; unsigned long hi; } ulonglong;
#	define init64(h,l) { (l), (h) }
# endif

#	define add64(s,a,b) do {				\
	(s).hi = (a).hi + (b).hi;				\
	(s).lo = (a).lo + (b).lo;				\
	if ((a).lo > (s).lo) (s).hi += 1;		\
  } while (0)

#	define add32to64(s,tt) do {				\
	(s).lo += (tt);							\
	if ((tt) > (s).lo) (s).hi += 1;			\
  } while (0)

#	define sub64(d,a,b) do {				\
	(d).hi = (a).hi - (b).hi;				\
	if ((a).lo < (b).lo) (d).hi -= 1;		\
	(d).lo = (a).lo - (b).lo;				\
  } while (0)

#	define sub32from64(s,tt) do {			\
	(s).lo -= (tt);							\
	if ((tt) < (s).lo) (s).hi -= 1;			\
  } while (0)

#	define inc64(n) do {					\
	if ((n).lo > ((n).lo + 1)) (n).hi += 1;	\
	(n).lo += 1;							\
  } while (0)

#	define dec64(n) do {					\
	if (((n).lo + 1) < 1) (n).hi -= 1;		\
	(n).lo -= 1;							\
  } while (0)

#	define eq64(a,b) ((a).hi == (b).hi && (a).lo == (b).lo)
#	define lt64(a,b) ((a).hi < (b).hi || (a).hi == (b).hi && (a).lo <  (b).lo)
#	define gt64(a,b) ((a).hi > (b).hi || (a).hi == (b).hi && (a).lo >  (b).lo)
#	define le64(a,b) ((a).hi < (b).hi || (a).hi == (b).hi && (a).lo <= (b).lo)
#	define ge64(a,b) ((a).hi > (b).hi || (a).hi == (b).hi && (a).lo >= (b).lo)
#	define gt0_64(v) ((v).hi > 0 || (v).lo > 0)
#	define gt32_64(sf,tt) ((sf).hi > 0 || (sf).lo > (tt))
#	define as64(d,h,l) ((d).hi = (h), (d).lo = (l)) /* +ve only! */
#	define from64(n) (assert((n).hi == 0), (n).lo)
extern ulonglong div64(ulonglong a,ulonglong b);
extern ulonglong mul64(ulonglong a,ulonglong b);
# endif /* HAS_64_BIT_ARITHMETIC */
#endif /* assembly */
