#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <wincon.h>

#include "cons.h"


static HANDLE ifh = (HANDLE)0;
static HANDLE ofh = (HANDLE)0;
static COORD curpos;



/* ConsInit -- call this before doing any console i/o */
void ConsInit(void)
{
	int rc;

	rc = AllocConsole();
	ifh = GetStdHandle(STD_INPUT_HANDLE);
	ofh = GetStdHandle(STD_OUTPUT_HANDLE);
}

/* ConsExit -- call this before exiting from "main" */
void ConsExit(void)
{
	ConsMoveCursor(24, 0);
	FreeConsole();
}


/* ConsClear -- clear screen and position cursor at lop left (home) */
/* note: this will clear a standard 25 x 80 screen space */
/*       and can be modified to clear a larger block */
void ConsClear(void)
{
	int rc;
	long int rc2;

	curpos.X = 0;
	curpos.Y = 0;
	rc = FillConsoleOutputCharacter(ofh, ' ', 25 * 80, curpos, &rc2);

	curpos.X = 0;
	curpos.Y = 0;
	rc = FillConsoleOutputAttribute(ofh, A_WHITE, 25 * 80, curpos, &rc2);

	ConsMoveCursor(0, 0);
}


/* ConsMoveCursor -- move cursor to a specific vert/horz coordinate */
/* where 0,0 is the top left screen position */
void ConsMoveCursor(int vv, int hh)
{
	int rc;

	curpos.X = hh;
	curpos.Y = vv;
	rc = SetConsoleCursorPosition(ofh, curpos);
	rc = SetConsoleTextAttribute(ofh, A_WHITE);
}



/* ConsDisplayText -- display text at a vert/horz coordinate */
/* note: this will not move the current cursor position */
int ConsDisplayText(int vv, int hh, char *textp)
{
	int rc, len = (int)strlen(textp);
	long int rc2;

	curpos.X = hh;
	curpos.Y = vv;
	rc = WriteConsoleOutputCharacter(ofh, textp, len, curpos, &rc2);

	return(len);
}

/* ConsDisplayAttr -- display text at a vert/horz coordinate (with color attributes) */
int ConsDisplayAttr(int vv, int hh, char *textp, int attr)
{
	int rc, len = (int)strlen(textp);
	long int rc2;

	curpos.X = hh;
	curpos.Y = vv;
	rc = SetConsoleCursorPosition(ofh, curpos);

	rc = SetConsoleTextAttribute(ofh, (WORD)attr);

	rc = WriteConsole(ofh, textp, len, &rc2, NULL);

	return(len);
}
