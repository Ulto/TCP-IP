#if 0

TCP/IP Network Module


General Overview:
- Provides a library of routines to access the ethernet connection


Specific Operations:
- For use by a slave system to block / wait for an incoming connection
- For use by a host to connect to a slave
- For use by both host/slave to send/recv data packets of any length or format


Notes:
- if this is to be compiled under linux,
  then add:  #define _UNIX_

- if this is to be compiled under windows,
  then add:  wsock32.lib  to the project linker/input files


Initialize slave to receive:
- call:
  RecvInit(port number)
     where port number matches the transmiting application
     note: you will need to initiate the "slave" before starting the "host"

  NtwkWait()
     will block and wait for a host to connect to us

  NtwkRecv(length,buffer)
     pass in a pointer to a buffer, and the size of the largest possible block
     the function will return the number of bytes that have been transferred
     if there is more data, you should call NtwkRecv() again

- call:
  NtwkSend()
     to send a response,

- If error, or to close the connection
  call:
  NtwkExit()
     to terminate the connection


Initialize host to transmit:
- determine the ip address of the destination
  use:  ipconfig
  examine the IPv4 address

- determine the port number to connect to
  for general purpose host-slave messages, use 1500
  to "ping", use port 7

- call:
  SendInit(ip address, port number)
     where the ip address is the ascii text "192.168.0.141" or similar
     port number is (typically) 1500

  NtwkSend(length, buffer)
     and pass the buffer/size to be sent to the destination

- call:
  NtwkRecv()
     to wait for a response,

- If error, or to close the connection
  call:
  NtwkExit()
     to terminate the connection


#endif


/*
 * list of general error codes
 * used with the below network functions
 */
#define ERR_NONE          0   // no errors
#define ERR_BAD_IP       -1   // invalid network ip address
#define ERR_BAD_SEQ      -2   // wrong sequence / no socket conenction
#define ERR_NTWK_FAIL    -3   // misc network failure
#define ERR_CONN_FAIL    -4   // can not connect / bind / accept
#define ERR_SEND_RECV    -5   // send / recv fail

