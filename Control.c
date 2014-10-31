#include "Control.h"
#include "dataStruct.h"
#include "Error.h"

int Control(struct fileTransfer *FT)
{
    // Variable Declarations
	FILE *file_handle;
	enum ErrorCodes ntwk;

    // Attempt to Open File
	file_handle = fopen(FT->ui.filePath, "r");

    // Check for File Handle
	if (file_handle == NULL)
	{
        // Could not open file, return error.
		return(Control_OpenFail);
	}

    // Store File Handle
	FT->net.ourFile;

    // Call Network
	ntwk = NTWK_transmit(FT);

    // Return
	return(ntwk);
}
