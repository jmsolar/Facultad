static char SccsId[] = "%W% %G%";
/**** Copyright (C) 1999 Cincom Systems, Inc.
/************************************************************************
 * File: ntVisualWorks.c
 * 
 * Engine Version Selector for VisualWorks image files on Windows.
 * This program should be installed as the default application for .im
 * files.  It then examines the .im file, determines its version and
 * executes the relevant engine for the image file's version.  The
 * correct engine is extracted from the Windows registry.
 * 
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <errno.h>

/* don't want to include all the hps.h stuff just to define this... */
#define bytesToQuanta(x) x

typedef char		 *oop;
typedef unsigned char byte;
typedef int			  oopInt;
typedef int			  bool;
typedef int			  fileHandle;

#include "imageFormat.h"

#ifndef TRUE
#	define TRUE 1
#	define FALSE 0
#endif

#ifndef DEBUG
#	define DEBUG 0
#endif

#define MAXCMDLINE 512
static char  commandLine[MAXCMDLINE];
#define MAXCMDPARMS 64
static char *argList[MAXCMDPARMS] = {0};

int
main(int argc, char *argv[])
{
	byte viSig[4];
	int argn = 0;
	FILE *ifp;
	char *programPath, *programName;
	char defaultImageName[MAX_PATH], safeImageName[MAX_PATH],
         iniName[MAX_PATH], executable[MAX_PATH+2];
	char *imageName = NULL;
	bool reportVersionOnly = FALSE;
	char errmess[2048];
	long majorVer, minorVer;
	int r;

	programPath = argv[0];
	if ((programName = strrchr(argv[0],'\\')))
		++programName;
	else
		programName = argv[0];

	/* simply look for image file.  Image file is first argument not beginning with a - */
	while (++argn < argc) {
		char *arg = argv[argn];
		if (*arg == '-') {
			int len = strlen(arg);
			char opt = ' ';
			char *val = "";
			if(len >= 2 && (arg[1] == 'v' || arg[1] == 'V'))
				reportVersionOnly = TRUE;
		}
		else {
			imageName = arg;
			break;
		}
	}

	if (!imageName) {
		strcpy(defaultImageName, programName);
		strcpy(defaultImageName + strlen(programName) - 3, "im"); /* replace exe with im */
		imageName = defaultImageName;
	}
    else if (strchr(imageName,' ')) {
        safeImageName[0] = '"';
        strcpy(safeImageName + 1, imageName);
        strcat(safeImageName, "\"");
        argv[argn] = safeImageName;
    }
	if (!(ifp = fopen(imageName, "rb"))) {
		sprintf(errmess,
				"Couldn't open image file %s (%s)",
				imageName,strerror(errno));
		MessageBox(0,errmess,programName,MB_OK);
		return 1;
	}
	if ((r = fseek(ifp, viSignatureOffset, SEEK_SET))) {
		sprintf(errmess,
				"Couldn't seek to %d in image file %s (%s)",
				viSignatureOffset, argv[argc-1],strerror(errno));
		fclose(ifp);
		MessageBox(0,errmess,programName,MB_OK);
		return 1;
	}
	if ((r = fread(viSig, 1, 4, ifp)) != 4) {
		sprintf(errmess,
				"Couldn't read image file %s (%s)",
				argv[argc-1],strerror(errno));
		fclose(ifp);
		MessageBox(0,errmess,programName,MB_OK);
		return 1;
	}
	(void)fclose(ifp);
	strcpy(iniName, programPath);
	strcpy(iniName + strlen(programPath) - 3, "INI"); /* replace exe with ini */

	if (!(ifp = fopen(iniName, "r"))) {
		sprintf(errmess,
				"Couldn't open ini file %s (%s)",
				iniName,strerror(errno));
		MessageBox(0,errmess,programName,MB_OK);
		return 1;
	}
	if (!strcmp(programName,"VISUALWORKS.EXE")
	 || !strcmp(programName,"VISUAL.EXE"))
		strcpy(programName,"VisualWorks");
	while (fscanf(ifp,"%d %d ", &majorVer, &minorVer) == 2
		&& fgets(executable, MAX_PATH+1, ifp)) {
		int i, j;
		i = strlen(executable);
		while (--i >= 0 && isspace(executable[i]))
			executable[i] = 0;
		if (majorVer == viSig[0]
		 && minorVer == viSig[1]) {
			argv[0] = executable;
			if (majorVer <= 25) { /* remove secret -z option. */
			    for (i = 1; i < argc; i++) {
			        if (argv[i][0] == '-'
			         && tolower(argv[i][1]) == 'z') {
			            for (j = i; j <= argc; j++)
			                argv[j-1] = argv[j];
			            argc--;
			        }
			    }
			}
            (void)fclose(ifp);
			execve(executable, argv, NULL);
			sprintf(errmess,
					"Couldn't execute %s (%s)",
					executable,strerror(errno));
			MessageBox(0,errmess,programName,MB_OK);
			return 1;
		}
	}
	(void)fclose(ifp);
	sprintf(errmess,
			"Couldn't find a virtual machine for image %s\n"
			"with type %d %d listed in %s.  If you have a\n"
			"suitable virtual machine then edit %s appropriately.\n\n"
			"Hit OK to edit VisualWorks.ini.",
			imageName,viSig[0],viSig[1],iniName,iniName);
	if (MessageBox(0,errmess,programName,MB_OKCANCEL) == IDOK) {
		STARTUPINFO         sui;
		PROCESS_INFORMATION pi;
		char runNotepad[MAX_PATH+10];

		GetStartupInfo(&sui);
		sui.dwFlags = 0;
		strcpy(runNotepad, "notepad ");
		strcat(runNotepad, iniName);
		(void)CreateProcess(0, runNotepad, 0, 0, 0,
							CREATE_NEW_PROCESS_GROUP | DETACHED_PROCESS,
							0, 0, &sui, &pi);
	}
	return 1;
}

static char  exeName[MAX_PATH];

/* parse a command line into an array of string pointers */
int
parseCommandLine(char * cmdLine)
{
int i,j,len;
int state;

#define LOOK_FOR_DASH 1
#define FOUND_DASH 2
#define FOUND_SINGLE_QUOTE 3
#define FOUND_DOUBLE_QUOTE 4

	GetModuleFileName(NULL, exeName, MAX_PATH);
	argList[0] = exeName;
	len = strlen(cmdLine);
	if (len == 0)
		return 1;
	j = 1;
	state = LOOK_FOR_DASH;
	for(i = 0;i < len;i++) {
		switch (state) {
		case LOOK_FOR_DASH:
			if (cmdLine[i] == '-' || cmdLine[i] == '/') {
				cmdLine[i] = '-';
				state = FOUND_DASH;
				argList[j] = &(cmdLine[i]);
				j++;
				break;
			}
			if (cmdLine[i] == ' ')
				break;
			if (cmdLine[i] == '\'') {
				state = FOUND_SINGLE_QUOTE;
				i++;
				argList[j] = &(cmdLine[i]);
				j++;
				break;
			}
			if (cmdLine[i] == '"') {
				state = FOUND_DOUBLE_QUOTE;
				i++;
				argList[j] = &(cmdLine[i]);
				j++;
				break;
			}
			state = FOUND_DASH;
			argList[j] = &(cmdLine[i]);
			j++;
			break;
		case FOUND_DASH:
			if (cmdLine[i] == ' ') {
				cmdLine[i] = 0; /* mark end of string */
				state = LOOK_FOR_DASH;
			}
			break;
		case FOUND_SINGLE_QUOTE:
			if (cmdLine[i] == '\'') {
				cmdLine[i] = 0; /* mark end of string */
				state = LOOK_FOR_DASH;
			}
			break;
		 case FOUND_DOUBLE_QUOTE:
			if (cmdLine[i] == '"') {
				cmdLine[i] = 0; /* mark end of string */
				state = LOOK_FOR_DASH;
			}
			break;
		}
	}
	return j;
}

int WINAPI
WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	int argc = parseCommandLine(lpCmdLine);
	return main(argc, argList);
}
