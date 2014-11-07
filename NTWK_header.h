#include"ntwk.h"
#include"dataStruct.h "
#include"Error.h"

/*Network recieve*/
int NTWK_Receive(struct fileTransfer *sptr);

/*Network transmit*/
int NTWK_Transmit(struct fileTransfer *sptr);

int SendInit(char *ip_addrs, int port);

int RecvInit(int port);

int NtwkWait(void);

int NtwkExit(void);

int NtwkSend(int length, unsigned char *datap);

int NtwkRecv(int length, unsigned char *datap);


