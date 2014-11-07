#include "dataStruct.h"

#ifndef CONTROL_H
#define CONTROL_H

enum Errorcodes Control(struct fileTransfer*);
extern int NTWK_Transmit(struct fileTransfer *sptr);

#endif /* CONTROL_H */
