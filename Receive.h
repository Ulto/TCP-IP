#include "dataStruct.h"

#ifndef RECEIVE_H
#define RECEIVE_H

#define TEMP_FILE "Temp.file"

enum Receive_Open(struct fileTransfer*);
enum Receive_Write(struct fileTransfer*);
enum Receive_CompleteTransfer(struct fileTransfer*);
BOOL Receive_fileExists(struct fileTransfer*);



#endif /* RECEIVE_H */
