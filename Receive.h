#include "dataStruct.h"

#ifndef RECEIVE_H
#define RECEIVE_H

#define TEMP_FILE "\\Temp.file"

enum ErrorCodes  Receive_Open(struct fileTransfer*);
enum ErrorCodes  Receive_Write(struct fileTransfer*);
enum ErrorCodes  Receive_CompleteTransfer(struct fileTransfer*);
BOOL Receive_fileExists(struct fileTransfer*);
enum ErrorCodes Receive_UpdateTime(struct fileTransfer*);


#endif /* RECEIVE_H */
