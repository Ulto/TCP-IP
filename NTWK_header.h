#include"ntwk.h"
#include"dataStruct.h "
#include"Error.h"

/*Network recieve*/
int NTWK_Receive(struct fileTransfer *sptr);

/*Network transmit*/
int NTWK_Transmit(struct fileTransfer *sptr);

extern int SendInit(char *ip_addrs, int port);

extern int RecvInit(int port);

extern int NtwkWait(void);

extern int NtwkExit(void);

extern int NtwkSend(int length, unsigned char *datap);

extern int NtwkRecv(int length, unsigned char *datap);
