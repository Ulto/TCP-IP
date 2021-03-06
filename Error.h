// Error Codes

#ifndef ERROR_H
#define ERROR_H

enum ErrorCodes{
    OK = 0,
	/* Zach Errors - 1xx */
	Control_OpenFail = 100,     /* Failed to open specified file. */

	/* Chris Errors - 2xx */
	placeholder2 = 200,
	Ntwk_ERR_SEND_RECV,         /* Data didn't reach destination */
	Ntwk_ERR_CONN_FAIL,         /* Failed to make connection to network */
	Ntwk_ERR_NTWK_FAIL,         /* Miscellaneous network failure */
	Ntwk_ERR_BAD_SEQ,           /* No socket connection */
	Ntwk_ERR_BAD_IP,            /* Invalid network ip address */

	/* Greg Errors - 3xx */
	Receive_OpenFail = 300,     /* The file failed to open in the Receive Side */
    	Receive_CloseFail,          /* File failed to close in Receive Side */
	Receive_RenameFail,         /* File failed to rename in Receive Side */
	Receive_FileAlreadyExists,  /* File already exists in Receive Side */
	Receive_FileWriteFail,      /* During a File write, the system failed to write all data */
	Receive_Done,               /* The file was successfully closed and renamed */
	Receive_UpdateTimeFail      /* Failed to update file times */

};

#endif /* ERROR_H */
