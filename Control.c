#include "Control.h"
#include "dataStruct.h"
#include "Error.h"

enum Control(struct fileTransfer *FT)
{
    // Variable Declarations
    FILE *file_handle;
    enum ErrorCodes ntwk;

    // Attempt to Open File
	file_handle = fopen(FT->ui.filePath, "r");
					// Must concat path & name

    // Check for File Handle
    if (file_handle == NULL)
    {
        // Could not open file, return error.
		ntwk = Control_OpenFail;
    }
	else
	{

		// Store File Handle
		FT->net.ourFile = file_handle;

		// Call Network
		ntwk = NTWK_transmit(FT);
	}

    // Closefile
    fclose(fhandle);
    
    // return
    return(ntwk);
    
