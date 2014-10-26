
int NTWK_Receive(void)
{
	/*Initialize the slave to receive*/
	RecvInit(1500);

	/*Block and Wait for network connection*/
	NtwkWait();

	/*Receive Continuosly*/
	while (1)
	{
		/*Recieve data from the destination*/
		NtwkRecv(/*length*/, /*buffer*/);

		/*If error, then break out of loop*/
		if (/*error*/)
			break;

		/*Send packet to send program*/
		NtwkSend( /*length*/,  /*buffer*/);

		/*If error, then break out of loop*/
		if (/*error*/)
			break;
	}
	/*Exit Network*/
	NtwkExit();

	return(/*error*/);
}




int NTWK_Transmit(void)
{
	/*Initialize host to transmit*/
	SendInit( /*ip address*/ , /*port number*/ );

	/*open file(send filename to dest)*/

	while (1)
	{
		/*Read first 1500 bytes from file, then send*/

		/*Send 1500 bytes to reciever*/
		NtwkSend( /*length*/,  /*buffer*/);

		/*If Error*/
		if (/*error*/)
			break;

		/*Call to wait for a response*/
		NtwkRecv(/*length*/, /*buffer*/);

		/*Error*/
		if (/*error*/)
			break;
	}
	/*Error*/
	NtwkExit();

	return(/*error*/);
}
