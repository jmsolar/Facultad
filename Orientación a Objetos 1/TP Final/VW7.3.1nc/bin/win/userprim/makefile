# SccsId is @(#)nt.makefile	58.10 %G
########################################################################
# File: makefile
# 
# Description: makefile for linking user primitives on NT/2k/XP/95/98/ME win32
#
#	Copyright (C) 1999 Cincom Systems, Inc.
#	Santa Clara, California.  All Rights Reserved.
#
########################################################################

!IFNDEF TARGETOS
TARGETOS=BOTH
!ENDIF

!include <win32.mak>

!IFNDEF SRC
SRC=.
!ENDIF

# The Processor Architecture
MACHINE=IX86
# MACHINE=MIPS
# MACHINE=ALPHA_AXP

# The name of resultant VM executable(s)
WHO= vwuser.exe
WHOCONSOLE= vwuserconsole.exe

# Name(s) of User Primitive files
USEROBJ= validate.obj
# ntstart.obj is needed for the OE profiler
# customize.obj may be replaced by your version
BASEOBJS= ntstart.obj customize.obj
#
# compiler options
#
# define SAFETY= /DUNSAFE here if you want to live dangerously
SAFETY=

CCDEFS= $(SAFETY) /I$(SRC) /D__STDC__ /DFATNAME
CCFLAGS= $(cflags) $(cvars) $(cdebug) $(CCDEFS) /MD
LIBS=msvcrt.lib oldnames.lib $(winlibs) advapi32.lib lz32.lib winmm.lib mpr.lib shell32.lib wsock32.lib


$(WHO): $(BASEOBJS) $(USEROBJ) ntvw.res
	$(link) $(guiflags) ntvw.res $(BASEOBJS) $(USEROBJ) visual.lib $(LIBS) \
		/OUT:$(WHO) /MACHINE:$(MACHINE) /DEBUG:FULL /DEBUGTYPE:BOTH

$(WHOCONSOLE): $(BASEOBJS) $(USEROBJ) ntvw.res
	$(link) $(guiflags) ntvw.res $(BASEOBJS) $(USEROBJ) visual.lib $(LIBS) \
		/OUT:$(WHOCONSOLE) /MACHINE:$(MACHINE) /DEBUG:FULL /DEBUGTYPE:BOTH \
		/subsystem:console,$(APPVER)

# Use the following to statically link the C lib and not use the C lib DLL
# LIBS= $(libcmt) $(winlibs) advapi32.lib lz32.lib winmm.lib mpr.lib shell32.lib
#	$(link) $(guiflags) ntvw.res $(guilibs) advapi32.lib wsock32.lib mpr.lib \
#		$(BASEOBJS) $(USEROBJ) visual.lib \
#		/OUT:$(WHO) /MACHINE:$(MACHINE) /DEBUG:FULL /DEBUGTYPE:BOTH


ntvw.res:
        rc -r $(SRC)\ntvw.rc


ntstart.obj:
        $(cc) $(CCFLAGS) -DOE_PROFILE=1 $(SRC)\ntstart.c

# add any user files here -  probably in place of validate, etc.

validate.obj:  $(SRC)\validate.c $(SRC)\userprim.h $(SRC)\up_unsafe.h
        $(cc) $(CCFLAGS) $(SRC)\validate.c

customize.obj:  $(SRC)\customize.c $(SRC)\userprim.h $(SRC)\up_unsafe.h
        $(cc) $(CCFLAGS) $(SRC)\customize.c 

