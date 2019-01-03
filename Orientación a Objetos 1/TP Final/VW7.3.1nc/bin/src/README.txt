@(#)README.src	58.10
Copyright (C) 1999-2004 Cincom Systems, Inc.  All Rights Reserved.

VisualWorks Release 7.3a VM source distribution
ParcPlace group, Cincom Systems, Inc., Santa Clara, California

This software distribution contains copyrighted material and trade secrets of
Cincom Systems, Inc.  It is furnished subject to a source license agreement and
may not be used, distributed or disclosed except as permitted by that agreement.
======================================================================

This directory contains the tree for the sources proper.

The implementation has six major subsystems, each of which has its
own subdirectory:

    ext     The platform-independent portion of the external interface

    mman    The memory manager

    plat    The platform-dependent portion of the unix/mac external interface

    platpc  The platform-dependent portion of the PC external interface

    prim    Primitives not associated with other subsystems

    stack   Native-code runtime support

    tran    Retargetable native code generator

There are also -- 

    dllcc30      dllcc test suite and example code

	doc       internal documentation for the image and virtual machine

    include      .h files shared between subsystems

    makefiles    the common set of subsystem and support makefiles
                 for Unix based platforms

    makeplat     subdirectories containing makefiles & support files
                 for all supported platforms.

    userprim     user-defined primitive support

    utilities    other support files and sources for GNU's C preprocessor,
                 used to generate dependencies and preprocess some files
                 for some platforms

    zlib         the zlib compression library used to decompress compressed
                 images packaged in the resources of single executables on
                 Windows and MacOS 7/8/9 platforms.

	../build     the build directory tree for current platforms

    ../mat       minimum acceptance tests (mat) documentation

    ../smoke     quick and simple engine smoke-tests
