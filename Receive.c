#include "Receive.h"
#include "Error.h"






int Receive_Open(struct fileTransfer *RC)
{
	strcpy(RC->ui.destination, TEMP_FILE);

	RC->net.ourFile = fopen(RC->ui.destination, "w+");	/* Open a temporary file with Read/Write plus overwrite */

	if (RC->net.ourFile == NULL)
		return(Receive_OpenFail);

	return(OK);	/* No Errors, succesful open */
}

/************************************************************************************/
int Receive_Write(struct fileTrasnfer *RC)
{




}

/************************************************************************************/
int Receive_CompleteTransfer(struct fileTransfer *RC)
{
	int err;

	err = fclose(RC->net.ourFile);	/* Close the file */

	if (err != 0)
		return(Receive_CloseFail);

	err = rename(TEMP_FILE, RC->ui.fileName);	/* Rename the file */

	if (err != 0)
		return(Receive_RenameFail);

	return(OK);	/* No Errors, succesful close and rename */
}
