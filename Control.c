#include "Control.h"
#include "Error.h"

enum Errorcodes Control(struct fileTransfer *FT)
{
	// Variable Declarations
    	FILE *file_handle;
    	enum ErrorCodes ntwk;
    	char fileLocation[MAXFILESIZE + 1 + MAXFILELENGTH];

	// Concatenate File Path & Name
	sprintf(fileLocation, "%s%s%s", FT->ui.filePath, "\\", FT->ui.fileName);
	
    	// Attempt to Open File
	file_handle = fopen(fileLocation, "rb");

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
		ntwk = NTWK_Transmit(FT);
		
		// Close File
    		fclose(file_handle);
    	
	}
    
    // Return Error / Status Code
    return(ntwk);
    
}
    
