/* SccsId is @(#)customize.c	58.10 04/06/05
 *
 * Copyright (C) 1999-2003 Cincom Systems, Inc. All rights reserved. 
 *
 * Modify this file if you want a different herald string or resource
 * class name (where applicable).  Any private command line options must
 * be removed before calling oeMain().
 */
#include "userprim.h"

static char sccsID[] = "@(#) VisualWorks(R) 7.3a, customize.c 58.10";
char *versionString = "VisualWorks(R) 7.3a, w/user primitives";


char *resourceClassName = "St80"; /* class name used to look up X resources */

int
#if OE_IS_UNICODE
wmain(int argc, wchar_t *argv[])
#else
main(int argc, char *argv[])
#endif
{
#if LOADABLE_GUI
	extern unsigned int guiSubsystemLinked;
	if (guiSubsystemLinked)
		showHerald = TRUE;
#endif
	/* Calling the C++  _main before main allows some platforms
	 * (currently confirmed for HPUX 11) to load C++ dynamic load libraries.
	 * If CPLUSPLUS is defined we call _main.
	 */
#ifdef CPLUSPLUS
	_main();
#endif
	return oeMain(argc, argv, 0);
}

/*
 * UPInitLinkRegistry
 *
 * All statically linked procedures accessible to
 * the Objectkit Smalltalk C Programming kit
 * must be defined in this function using
 * UPRegisterSymbolAndHandle(char *, void *).
 */
void
UPInitLinkRegistry()
{
}
