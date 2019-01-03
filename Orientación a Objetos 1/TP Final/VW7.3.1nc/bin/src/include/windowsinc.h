/* SccsId is @(#)windowsinc.h	58.10 04/06/05 */
/************************************************************************
 * File:	windowsinc.h
 *
 * Include windows.h avoiding warnings due to collisions in HPS and Windows
 * defines.  Provide defines for NT compatibility on WinCE.
 *
 *	Copyright (C) 2004 Cincom Systems, Inc.
 *	Santa Clara, California.  All Rights Reserved.
 *
 *	UNPUBLISHED, CONFIDENTIAL AND PROPRIETARY.
 ************************************************************************/

#if !WINDOWSINC_H
#define WINDOWSINC_H 1

#ifdef max
	/* undefine max & min to avoid redefinition warning.  stdlib's definition
	 * is just as good.
	 */
#	undef max
#	undef min
#endif
#ifdef ASSERT
#	define OEASSERT ASSERT
#	undef ASSERT
#endif
#if UNDER_CE && SDKVERSION < 420 /* avoid bogus decls for missing functions */
#	define WSAAsyncSelect KillBillPartOne
#endif

#include <windows.h>

#if UNDER_CE && SDKVERSION < 420
#	undef WSAAsyncSelect
#endif
#undef ASSERT
#ifdef OEASSERT
#	define ASSERT OEASSERT
#endif
#ifndef max
#	define max(a, b) ((a) > (b) ? (a) : (b))
#	define min(a, b) ((a) < (b) ? (a) : (b))
#endif

#if UNDER_CE

#ifndef SW_SHOWMINIMIZED
#  define SW_SHOWMINIMIZED SW_HIDE
#endif
#ifndef WS_EX_APPWINDOW
# define WS_EX_APPWINDOW 0 /* not WS_EX_TOOLWINDOW, this flag hides the window from the toolbar */
#endif
#ifndef WS_OVERLAPPEDWINDOW
# define WS_OVERLAPPEDWINDOW WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
#endif
#ifndef CS_BYTEALIGNCLIENT
# define CS_BYTEALIGNCLIENT 0
#endif

#define CreateBitmapIndirect(b) CreateBitmap((b)->bmWidth, (b)->bmHeight, (b)->bmPlanes, (b)->bmBitsPixel, (b)->bmBits)
#define GdiFlush() TRUE
#define GetNextWindow(hWnd,nextPrevFlag) GetWindow(hWnd,nextPrevFlag)
#define GetSystemTimeAsFileTime(p) do { SYSTEMTIME	systime; \
	GetSystemTime(&systime); \
	SystemTimeToFileTime(&systime, p); \
} while(0)
#define IsIconic(x) FALSE
#define TextOut(g,x,y,buff,i) ExtTextOut(g, x, y, ETO_OPAQUE, NULL, buff, i, NULL)
#define PALETTEINDEX(i) ((COLORREF) (0x01000000 | (DWORD) (WORD) (i)))

extern void *bsearch(const void *, const void *, int, int, int (*)(const void *,const void *));
extern char *strerror(int);

/************************************************************************
 *	our own BITMAPINFO structure contains 256 colors					*
 ************************************************************************/

typedef struct tagBITMAPINFO256 {
	BITMAPINFOHEADER	bmiHeader;
	RGBQUAD				bmiColors[256];
} BITMAPINFO256;

#if SDKVERSION < 420
extern int WSAAsyncSelect(SOCKET, HWND, UINT, LONG);
#endif

#define CURSOR_NOTWORKING 1
#if CURSOR_NOTWORKING
# define SetCursorPos(x,y) 0
# if platform == platWinCEARM
#	define CreateCursor(g,hotX,hotY,CX,mCY, andBits, xorBits) (HCURSOR)1
#	define DestroyCursor(c) 0
#	define SetCursor(c) 0
# endif
#endif


#if 0
/************************************************************************
 *	external function definition										*
 ************************************************************************/

extern int		SetDIBits(HDC, HBITMAP, UINT, UINT, CONST VOID*, CONST BITMAPINFO*, UINT);
extern int		GetDIBits(HDC, HBITMAP, UINT, UINT, LPVOID, LPBITMAPINFO, UINT);
extern LONG		GetBitmapBits(HBITMAP, LONG, LPVOID);
extern void		swab(char*, char*, int);
extern char*	strdup(const char*);
extern void		rewind(FILE*);

# ifndef GlobalAlloc
#	define GlobalAlloc LocalAlloc
#	define GlobalLock LocalLock
#	define GlobalFree LocalFree
#	define GlobalUnlock LocalUnlock
# endif

#endif /* 0 */

#endif /* UNDER_CE */
#endif /* WINDOWSINC_H */
