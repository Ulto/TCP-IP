#include "Receive.h"
#include "Error.h"

#include <sys/stat.h>


FILE * rfile;

enum ErrorCodes Receive_Open(struct fileTransfer *RC)
{
	enum ErrorCodes rcv = OK;

	char filelocation[MAXFILESIZE + 1 + MAXFILELENGTH];
	strcpy(filelocation, RC->ui.destination);
	strcat(filelocation, TEMP_FILE);

	remove(filelocation);	/* Ensure that no lingering temp file exists. */ 

	rfile = fopen(filelocation, "wb");	/* Open a temporary file with Read/Write plus overwrite */
	
	if (rfile == NULL)
		rcv = Receive_OpenFail;


	return(rcv);	/* No Errors, succesful open */
}

/************************************************************************************/
enum ErrorCodes Receive_Write(struct fileTransfer *RC)
{
	enum Errorcodes rcv = OK;
	size_t written;

	/* Write data from buffer to file */
	written = fwrite(RC->net.buffer, 1, RC->net.Bytes, rfile);

	if (written != RC->net.Bytes)
		rcv = Receive_FileWriteFail;

	return rcv;

}

/************************************************************************************/
enum ErrorCodes Receive_CompleteTransfer(struct fileTransfer *RC)
{
	int err;
	char filelocation[MAXFILESIZE + 1 + MAXFILELENGTH];
	enum ErrorCodes rcv = OK;

	strcpy(filelocation, RC->ui.destination);

	err = fclose(rfile);	/* Close the file */

	if (err != 0)
		rcv = Receive_CloseFail;
	else
	{
		/* Now that the temp file was closed, lets rename the file */
		strcat(filelocation, TEMP_FILE);
		
		sprintf(RC->ui.destination, "%s%s%s", RC->ui.destination, "\\", RC->ui.fileName);
		remove(RC->ui.destination); /* Ensure that new file of the same name does not already exist. */
		err = rename(filelocation, RC->ui.destination);	/* Rename the file */

		if (err != 0)
			rcv = Receive_RenameFail;
		else
			rcv = Receive_UpdateTime(RC);
			 
	}

	return rcv;	
}

/************************************************************************************/
enum ErrorCodes Receive_UpdateTime(struct fileTransfer *RC)
{
	HANDLE fh;
	enum ErrorCodes rcv = Receive_UpdateTimeFail;
	
	// set a file's date/time info
	fh = CreateFile(RC->ui.destination, GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fh > 0)
	{
		SetFileTime(fh, &RC->net.creationDate, &RC->net.accessDate, &RC->net.modifyDate);
		CloseHandle(fh);
		rcv = Receive_Done;
	}

	return rcv;
}
