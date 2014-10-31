#include"ntwk.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int NTWK_Receive(struct fileTransfer *sptr)
{
	int errorNTWK = 0;
	int incomingLength = 0;

	/*Set port number*/
	sptr->ui.port = 1500;

	/*Initialize the slave to receive*/
	errorNTWK = RecvInit(sptr->ui.port);

	/*If no error, then Wait for connection*/
	if (errorNTWK == 0)
	{	
		/*Block and Wait for network connection*/
		NtwkWait();
	}
	
	/*If there is no error, enter recieve protocol*/
	if (errorNTWK == 0)
	{

		/*Receive Continuosly*/
		while (1)
		{
			/*Recieve data from the destination*/
			incomingLength = NtwkRecv(sptr->net.length, sptr->net.buffer);

			/*If incoming length is less then zero, then it's an error code.*/
			if (incomingLength < 0)
			{
				/*Set error code from length error*/
				errorNTWK = incomingLength;

				/*Break out of loop*/
				break;
			}

			/*Send packet to send program*/
			errorNTWK = NtwkSend(sptr->net.length, sptr->net.buffer);

			/*If error, then break out of loop*/
			if (errorNTWK < 0)
				break;
		}
	}

	if (errorNTWK == 0)
	{
		/*Exit Network*/
		errorNTWK = NtwkExit();
	}

	/*If error, then break out of loop*/
	if (errorNTWK < 0)
	{
		/*Create error code*/
		errorNTWK = 206 - errorNTWK;
	}
	return(errorNTWK);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int NTWK_Transmit(struct fileTransfer *sptr)
{
	int errorNTWK = 0;
	/*Initialize host to transmit*/
	/*Passing in ip address and port number*/
	errorNTWK = SendInit(sptr->ui.ipAddress, sptr->ui.port);

	/*If no error, then Wait for connection*/
	if (errorNTWK == 0)
	{
		/*Block and Wait for network connection*/
		NtwkWait();
	}

	/*If there is no error, enter recieve protocol*/
	if (errorNTWK == 0)
	{
		sptr->net.ourFile = fopen(sptr->ui.filePath, "r");
		/*If file is of no size*/
		if (NULL == sptr->net.ourFile)
		{
			// TODO: return a suitable error/perror
			return -1;
		}

		// obtain file size:
		fseek(sptr->net.ourFile, 0, SEEK_END);
		sptr->net.length = ftell(sptr->net.ourFile);
		rewind(sptr->net.ourFile);

		/*open file(send filename to dest)*/
		while (1)
		{
			/*Read the file and store size "length" into "buffer"*/
			fread(sptr->net.buffer, sizeof(char), sptr->net.length, sptr->net.ourFile);

			/*Send 1500 bytes to reciever*/
			errorNTWK = NtwkSend(sptr->net.length, sptr->net.buffer);

			/*If Error*/
			if (errorNTWK < 0)
				break;

			/*Call to wait for a response*/
			errorNTWK = NtwkRecv(sptr->net.length, sptr->net.buffer);

			/*If end of file , then break*/
			if (feof(sptr->net.ourFile))
			{
				break;
			}

			/*Error*/
			if (errorNTWK < 0)
				break;
		}
		fclose(sptr->net.ourFile);
	}

	if (errorNTWK == 0)
	{
		/*Exit Network*/
		errorNTWK = NtwkExit();
	}

	/*If error, then break out of loop*/
	if (errorNTWK < 0)
	{
		/*Create error code*/
		errorNTWK = 206 - errorNTWK;
	}
	return(errorNTWK);
}

