/* SccsId is  @(#)sysOop.h	58.10 04/06/05 */
/************************************************************************
 * File: sysOop.h
 *
 * This file contains the public interface to the sysOopRegistry, (i.e. the
 * Smalltalk object that contains the oops of objects that are known to the VM).
 *
 *	Copyright (C) 1999 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

/* Guaranteed oop indices
 * NOTE: Some of these are duplicated in userprim.h
 */
#if HPS64
# include "sysOop64.h"
#else
# include "sysOop32.h"
#endif

/* Accessing defs
 */
#if !defined(assembly)
extern  oopInt	allocSysOopSlot(void);
extern  oop		freeSysOopSlot(oopInt);
#define			allocSysOopFailure (-1)
extern  void	registerSysOop(oop, oopInt);
extern  oopInt	registerNewSysOop(oop);
extern  oopInt	maxValidSysOopX(void);

/* sysOop
 *
 * Returns the sysOop at a given index. No range checking on the index
 * is performed, since this would slow down the access to sysOops.
 */
/* NOTE: Duplicated in unsafe_oops.h */
# define sysOop(oopIndex) sysOopRegistry[oopIndex]
extern  DLUP_IMPORT(oop *) sysOopRegistry;
# if IMMEDIATE_TABLE && ObjectsHaveDirectClassPointer
extern	DLUP_IMPORT(oop) immediateTable[];
# endif
#endif /* assembly */
