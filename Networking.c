#include"NTWK_header.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
int NTWK_Receive(struct fileTransfer *sptr)
{
    /*Initialize variables*/
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
	    
	    /*If number of bytes is zero*/	
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
		    /*Remove first recieve flag*/
		    firstRX = 0;
		    
		    /*Call recieve functions to open and write a file*/
		    errorNTWK = Receive_Open(sptr);
		    errorNTWK = Receive_Write(sptr);
		}
		else
		{
		    /*Write data to the already open file*/
		    errorNTWK = Receive_Write(sptr);
		}
	    }	

            /*Send packet to send program*/
            errorNTWK = NtwkSend(sizeof(errorNTWK), &errorNTWK);

	    /*If error, then break out of loop*/
            if (errorNTWK != OK || errorNTWK == Receive_Done)
                break;
        }
    }
    
    /*If the recieving has been completed*/
    if (errorNTWK == Receive_Done)
    {
        /*Exit Network*/
        errorNTWK = NtwkExit();
    }

    /*If error, then break out of loop*/
    if (errorNTWK < 0)
    {
        /*Create error code from errorNTWK*/
        sptr->ERR = 200 - errorNTWK;
    }
    
    /*Close and exit out of network connection*/
    NtwkExit();
    
    /*Retunr the error*/
    return(sptr->ERR);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
int NTWK_Transmit(struct fileTransfer *sptr)
{
    /*Initialize local error variable*/
    int errorNTWK = 0;
    
    /*Initialize host to transmit*/
    errorNTWK = SendInit(sptr->ui.ipAddress, sptr->ui.port);

    /*If there is no error, enter recieve protocol*/
    if (errorNTWK == ERR_NONE)
    {
        /*Go to the end of the file*/
        fseek(sptr->net.ourFile, 0, SEEK_END);
        
        /*Set the length to the current position value*/
        sptr->net.length = ftell(sptr->net.ourFile);
        
        /*Return back to the first value of the file*/
        rewind(sptr->net.ourFile);

        /*Open file(send filename to dest)*/
        while (1)
        {
            /*Reads an array of count elements from measuring buffer, each one being the size of a character,
            from the file stream and stores them in the block of memory specified by buffer.*/
            (sptr->net.Bytes) = fread(sptr->net.buffer, sizeof(char), sizeof(sptr->net.buffer), sptr->net.ourFile);

            /*Send data structure to recieving computer and return errors*/
            errorNTWK = NtwkSend(sizeof(*sptr), sptr);

            /*If Error code is present*/
            if (errorNTWK < 0)
                break;

            /*Call to wait for a response*/
            sptr->net.Bytes = NtwkRecv(sizeof(sptr->ERR), &sptr->ERR);

            /*If an error is present, or bytes is less or equal to zero*/ 
            if (sptr->net.Bytes <= 0  || sptr->ERR != OK)
                break;
        }
        /*Close the file*/
        fclose(sptr->net.ourFile);
    }
    /*If no error has occured*/
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
   
    /*Exit the network connection*/
    NtwkExit();
    
    /*Return error*/
    return(sptr->ERR);
}

