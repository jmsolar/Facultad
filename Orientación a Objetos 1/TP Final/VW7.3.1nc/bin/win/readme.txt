VisualWorks(R) 7.3 Windows Object Engine ReadMe
Copyright Cincom Systems, Inc. 1999-2004. All rights reserved.


PURPOSE OF THIS README FILE

This README identifies the distribution contents and directory
structure of this release of VisualWorks object engine for
Windows platforms.  Instructions for using the debug engines
are included at the end.

For installation instructions for this release, refer to the
VisualWorks Installation Guide (Install.pdf) in the root
VisualWorks directory.  For a description of the object
engines, refer to the VisualWorks Application Developer's
Guide (doc/AppDevGuide.pdf).


DISTRIBUTION CONTENTS

win/ (for Windows 98/2000/ME/XP/NT)
    readme.txt      - this file
    herald.bmp      - startup bitmap file
    herald.wav      - startup sound file
    heraldcs.bmp
    linkmaster.dll  - installer help dll for shortcuts to the oe
    ntVisualWorks.c - engine version selector source
    visual.exe      - the single OE executable (stripped) useful for packaging
    visual.map      - symbol address file for the OEProfiler
    VisualWorks.exe - executable for finding appropriate oe
    VisualWorks.ini - mapping file for VisualWorks.exe
    vwnt.exe        - stub exe for running VisualWorks as a Windows application
    vwnt.map        - symbol address file for the OEProfiler
    vwntconsole.exe - stub exe for running VisualWorks from the console
    vwntconsole.map - symbol address file for the OEProfiler
    vwntoe.dll      - engine DLL containing the actual virtual machine.
    vwntoe.map      - symbol address file for the OEProfiler

    assert/
        herald.bmp      - startup bitmap file
        herald.wav      - startup sound file
        vwnt.exe        - stub exe for running as a Windows application
        vwnt.map        - symbol address file for the OEProfiler
        vwntconsole.exe - stub exe for running from the console
        vwntconsole.map - symbol address file for the OEProfiler
        vwntoe.dll      - assert-enabled engine DLL containing the actual VM.
        vwntoe.map      - symbol address file for the OEProfiler

    debug/
        herald.bmp      - startup bitmap file
        herald.wav      - startup sound file
        vwnt.exe        - stub exe for running as a Windows application
        vwnt.map        - symbol address file for the OEProfiler
        vwntconsole.exe - stub exe for running from the console
        vwntconsole.map - symbol address file for the OEProfiler
        vwntoe.dll      - assert-enabled engine DLL containing the actual VM.
        vwntoe.map      - symbol address file for the OEProfiler

    userprim/     - linkable oe files
        customize.c
        logo.bmp
        makefile
        makefile.plugin
        ntvw.h
        ntvw.rc
        unsafe_oops.h
        up_defs.h
        up_unsafe.h
        UPrims.st
        UPrimTst.st
        userprim.h
        validate.c
        vw.ico
        vwnt.lib
        vwntoeimport.lib

    win9x
        vwft16.dll      - DLLs for DLLCC calls to 16-bit libraries
        vwft32.dll      - DLLs for DLLCC calls to 32-bit libraries



Running Multiple VisualWorks Installations
------------------------------------------

On Windows platforms, the VisualWorks.exe program, together with
VisualWorks.ini, can be associated with the image file extension
(.im) to select and execute the correct object engine for that
image.  Each image requires a specific object engine version in
order to run properly.  VisualWorks.ini contains the required
mappings from image version identifiers to object engines.

If you already have image files mapped to a copy of VisualWorks.exe,
copy the line from the VisualWorks.ini file provided with VWNC into
the VisualWorks.ini file that your configuration already invokes.


Using the VisualWorks Debug Object Engines
------------------------------------------

Updated information about and instructions for using the debug 
engines for all platforms is maintained at:

    http://wiki.cs.uiuc.edu/VisualWorks/debugging+at+the+virtual+machine+level
    
Please refer to this web site for information about these engines.


KNOWN BUGS AND LIMITATIONS
--------------------------

The visual.exe and vwconsole.exe engines can neither load primitive 
plugins nor export the engine's OE and UP primitive API, due to 
limitations in the Windows dynamic linking model.  vwnt.exe and 
vwntnsole.exe, which use vwnoe.dll, do not suffer from these limitations.



3/24/03  bb
5/8/03   em
10/14/03 em
6/2/04   bb/em
11/1/04  bb