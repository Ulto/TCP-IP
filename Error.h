//header file for the error codes
#ifndef ERROR_H
#define ERROR_H

enum ErrorCodes{
    OK = 0,
	/* Zach Errors - 1xx */
	Control_OpenFail = 100,

	/* Chris Errors - 2xx */
	placeholder2 = 200,

	/* Greg Errors - 3xx */
	Receive_OpenFail = 300,     /* The file failed to open in the Receive Side */
    	Receive_CloseFail,          /* File failed to close in Receive Side */
	Receive_RenameFail,          /* File failed to rename in Receive Side */
	Receive_FileAlreadyExists,	/* File already exists in Receive Side */
	Receive_FileWriteFail		/* During a File write, the system failed to write all data */

};

#endif /* ERROR_H */
