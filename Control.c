#include "Control.h"
#include "dataStruct.h"
#include "Error.h"

enum Control(struct fileTransfer *FT)
{
	// Variable Declarations
    FILE *file_handle;
    enum ErrorCodes ntwk;
    char fileLocation[MAXFILESIZE + 1 + MAXFILELENGTH];

	// Create full file path.
	sprintf(fileLocation, "%s%s%s", FT->ui.filePath, "\", FT->ui.fileName);
	
    // Attempt to Open File
	file_handle = fopen(fileLocation, "r");

    // Check for File Handle
    if (file_handle == NULL)
    {
        // Could not open file, return error.
		ntwk = Control_OpenFail;
    }
	else // File has been opened, proceed.
	{
		// Store File Handle
		FT->net.ourFile = file_handle;

		// Call Network Function
		ntwk = NTWK_transmit(FT);
	}

    // Close File
    fclose(fhandle);
    
    // Return
    return(ntwk);
    
