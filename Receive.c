#include "Receive.h"
#include "Error.h"

#include <sys/stat.h>




int Receive_Open(struct fileTransfer *RC)
{

	enum ErrorCodes rcv = OK;

	strcpy(RC->ui.destination, TEMP_FILE);

	if (Receive_fileExists(RC) == 1 && !RC->Overwrite) {
		// file already exists
		rcv = Receive_FileAlreadyExists;
	}
	else 
	{
		// file doesn't exist or overwrite flag is high
		RC->net.ourFile = fopen(RC->ui.destination, "w+");	/* Open a temporary file with Read/Write plus overwrite */
	}

	if (RC->net.ourFile == NULL)
		rcv = Receive_OpenFail;


	return(rcv);	/* No Errors, succesful open */
}

/************************************************************************************/
BOOL Receive_fileExists(struct fileTransfer *RC)
{
	struct stat buf;
	int i = stat(RC->ui.destination, &buf);
	/* File found */
	if (i == 0)
	{
		return 1;
	}
	return 0;
}

/************************************************************************************/
int Receive_Write(struct fileTransfer *RC)
{
	enum Errorcodes rcv = OK;
	size_t written;

	written = fwrite(RC->net.buffer, 1, RC->net.Bytes, RC->net.ourFile);

	if (written != RC->net.Bytes)
		rcv = Receive_FileWriteFail;

	return rcv;

}

/************************************************************************************/
int Receive_CompleteTransfer(struct fileTransfer *RC)
{
	int err;
	enum ErrorCodes rcv = OK;

	err = fclose(RC->net.ourFile);	/* Close the file */

	if (err != 0)
		rcv = Receive_CloseFail;
	else
	{
		err = rename(TEMP_FILE, RC->ui.fileName);	/* Rename the file */

		if (err != 0)
			rcv = Receive_RenameFail;
	}

	return rcv;	
}
