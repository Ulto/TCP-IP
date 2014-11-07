#include "Receive.h"
#include "Error.h"

#include <sys/stat.h>


FILE * rfile;

enum ErrorCodes Receive_Open(struct fileTransfer *RC)
{

	enum ErrorCodes rcv = OK;

	strcat(RC->ui.destination, TEMP_FILE);

	//if (Receive_fileExists(RC) == 1 && RC->Overwrite != 1) {
		// file already exists
	//	rcv = Receive_FileAlreadyExists;
	//}
	//else 
	//{
		// file doesn't exist or overwrite flag is high
		rfile = fopen(RC->ui.destination, "w+");	/* Open a temporary file with Read/Write plus overwrite */
	//}

	if (rfile == NULL)
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
enum ErrorCodes Receive_Write(struct fileTransfer *RC)
{
	enum Errorcodes rcv = OK;
	size_t written;

	written = fwrite(RC->net.buffer, 1, RC->net.Bytes, rfile);

	if (written != RC->net.Bytes)
		rcv = Receive_FileWriteFail;

	return rcv;

}

/************************************************************************************/
enum ErrorCodes Receive_CompleteTransfer(struct fileTransfer *RC)
{
	int err;
	enum ErrorCodes rcv = OK;

	err = fclose(rfile);	/* Close the file */

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


