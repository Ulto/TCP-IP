#include"NTWK_header.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int NTWK_Receive(struct fileTransfer *sptr)
{
    int errorNTWK = 0;
    int incomingLength = 0;
    int firstRX = 1;

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

        /*Receive Continuously*/
        while (1)
        {
            /*Recieve data from the destination*/
            incomingLength = NtwkRecv(sizeof(*sptr), sptr);

            /*If incoming length is less then zero, then it's an error code.*/
            if (incomingLength < 0)
            {
                /*Set error code from length error*/
                errorNTWK = incomingLength;

                /*Break out of loop*/
                break;
            }

	if (sptr->net.Bytes == 0)
	{
		/* Transfer complete, close file */
		errorNTWK = Receive_CompleteTransfer(sptr);
	}
	else
	{

		/* If this is the first RX receive or Overwrite is true, Open the file */
		if (firstRX == 1 || sptr->Overwrite)
		{
			firstRX = 0;
			errorNTWK = Receive_Open(sptr);
			errorNTWK = Receive_Write(sptr);
		}
		else
		{
			errorNTWK = Receive_Write(sptr);
		}

	}	

        	/*Send packet to send program*/
        	errorNTWK = NtwkSend(sizeof(errorNTWK), &errorNTWK);

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
        sptr->ERR = 200 - errorNTWK;
    }
    return(sptr->ERR);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int NTWK_Transmit(struct fileTransfer *sptr)
{
    int errorNTWK = 0;
    /*Initialize host to transmit*/
    /*Passing in ip address and port number*/
    errorNTWK = SendInit(sptr->ui.ipAddress, sptr->ui.port);

    /*If there is no error, enter recieve protocol*/
	if (errorNTWK == ERR_NONE)
    {
        // obtain file size:
        fseek(sptr->net.ourFile, 0, SEEK_END);
        sptr->net.length = ftell(sptr->net.ourFile);
        rewind(sptr->net.ourFile);

        /*open file(send filename to dest)*/
        while (1)
        {
            /*Reads an array of count elements from measuring buffer, each one being the size of a character,
            from the file stream and stores them in the block of memory specified by buffer.*/
            (sptr->net.Bytes) = fread(sptr->net.buffer, sizeof(char), sizeof(sptr->net.buffer), sptr->net.ourFile);

            /*If there is no amount of data to be transmitted*//*Maybe get rid of this*/
            if (sptr->net.Bytes == 0)
                break;

            /*Send data structure to recieving computer and return errors*/
            errorNTWK = NtwkSend(sizeof(*sptr), sptr);

            /*If Error code is present*/
            if (errorNTWK < 0)
                break;

            /*Call to wait for a response*/
            errorNTWK = NtwkRecv(sizeof(sptr->ERR), &sptr->ERR);

            /*Error*/ 
            if (errorNTWK < 0  || sptr->ERR != OK)
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
        errorNTWK = 200 - errorNTWK;
    }
    return(errorNTWK);
}

