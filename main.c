/*
 * CMPET 457
 * Lab 4
 * Fall 2014
 *
 * See README.md for more information.
 *
 */


// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dataStruct.h"
#include "UI.h"


int main()
{
	// Declare & Initialize Data Structure(s)
	struct fileTransfer FT;
	memset(&FT, '\0', sizeof(FT));

	// User Interface
	UserInt(&FT);

	return 0;
} // END main
