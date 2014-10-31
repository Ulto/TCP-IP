#include "dataStruct.h"

#ifndef RECEIVE_H
#define RECEIVE_H

#define TEMP_FILE "Temp.file"

int Receive_Open(struct fileTransfer*);
int Receive_Write(struct fileTrasnfer *RC);
int Receive_CompleteTransfer(struct fileTransfer *RC);




#endif /* RECEIVE_H */
