The two DLLs in this directory, vwft16.dll and vwft32.dll, support callbacks
into Smalltalk for 16-bit code on the Win95/Win98/WinME platforms.  These DLLs
are not needed on other Windows platforms such as Windows 2000, and are not
needed on Win95/Win98/WinME unless you wish to perform callbacks from 16-bit
code.  If you do need to do so simply copy these DLLs up into the bin/win
directory.

Note that these DLLs make cause problems with floating-point erropr detection
due to their being compiled against msvc40.dll.
