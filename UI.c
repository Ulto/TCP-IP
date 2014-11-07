#include "UI.h"

int buttLoc = 0;

struct ErrorDisplay displayError[50] = {
	{ OK, "THE FILE HAS BEEN TRANSFERRED" },
	{ Control_OpenFail, "OPEN Error" },
	{ Ntwk_ERR_SEND_RECV, "Data didn't reach destination." },
	{ Ntwk_ERR_CONN_FAIL, "Failed to make connection network." },
	{ Ntwk_ERR_NTWK_FAIL, "Miscelaneous network failure." },
	{ Ntwk_ERR_BAD_SEQ, "No socket connection" },
	{ Ntwk_ERR_BAD_IP, "Invalid network ip address" },
	{ Receive_OpenFail, "The file failed to open on the target computer." },
	{ Receive_CloseFail, "The file failed to close on the target computer." },
	{ Receive_RenameFail, "The file failed to rename on the target computer." },
	{ Receive_FileAlreadyExists, "The file already exists on the target computer. Overwrite?" },
	{ Receive_FileWriteFail, "During a File write, the system failed to write all data." },
	{ -1, "" }
};

void UserInt(struct fileTransfer *info)
{
	int choice = 1;
	//initializes  console controls
	ConsInit();
	

	

	info->ui.port = 1500;


	while (choice != 0)
	{
		//clears the screen
		ConsClear();
		//calls the function to create the menu
		CreateUIMenu(0);
		do
		{
			while (!KEYCHECK);
			choice = getch();
			choice -= '0';

		} while (choice != 0 && choice != 1 && choice != 2);

		while (choice != 4)
		{
			switch (choice)
			{
			case 0:
				break;
			case 1:

				CreateUIMenu(2);
				NTWK_Receive(info);
				choice = 4;
				break;
			case 2:
#if 0
				CreateUIMenu(1);
				//gets the user input 
				UserInput(info);
				
				//
				//printf("%s\n%s\n%s\n%s\n%s\n", info->ui.ipAddress, info->ui.subnet, info->ui.fileName, info->ui.filePath, info->ui.destination);
#else
				strcpy(info->ui.fileName, "test.txt");
				strcpy(info->ui.filePath, "C:\\Users\\ddr5040\\Downloads");
				strcpy(info->ui.destination, "C:\\Users\\gzp5050\\Downloads");
				strcpy(info->ui.ipAddress, "128.118.255.194");
				strcpy(info->ui.subnet, "255.255.255.000");
#endif
				choice++;
				break;
			case 3:
				CreateUIMenu(3);
				StatusWindow(info);
				choice++;
				Sleep(5000);
				break;
			}
		}
	}


	//frees the console
	ConsExit();
}

/* CreateUIMenu(int menu)
* displays the menus
*
* input:
* menu: id of which menu to show
*
* return:
* none
*/
void CreateUIMenu(int menu)
{
	ConsClear();
	printf("    Welcome To Our File Transfer Program \n");
	printf("--------------------------------------------\n");
	switch (menu)
	{
	case 0:
		//creating the menu
		printf("What would you like to do?\n");
		printf("(0) Exit\n");
		printf("(1) Receiving\n");
		printf("(2) Sending\n");
		printf("Choice: ");
		break;
	case 1:
		//creating the menu
		printf("IP Address:           ___.___.___.___\n");
		printf("Subnet Mask:          ___.___.___.___\n");
		printf("Filename: \n");
		printf("Local File: \n");
		printf("Destination Location: \n");
		printf("Port: 1500\n\n\n");
		printf("Valid Data\n");
		printf("IP Address            [ ]\n");
		printf("Subnet MasK           [ ]\n");
		printf("Filename              [ ]\n");
		printf("Local File Path       [ ]\n");
		printf("Destination File Path [ ]\n");
		break;
	case 2:
		printf("Please check the other computer for status of the transfer\n");
		printf("Thank you,\n");
		printf("The 457 File Transfer Team\n");
		break;
	case 3:
		printf("Status Window\n");
		printf(" _____________________________________________________________________________\n");
		printf("|                                                                             |\n");
		printf("|                                                                             |\n");
		printf("|                                                                             |\n");
		printf(" -----------------------------------------------------------------------------\n");
		break;
	}

}

/* UserInput(struct fileTransfer *info)
* gets the data from the user
*
* input:
* *info: the data structure that holds all the data
*
* return:
* none
*/
void UserInput(struct fileTransfer *info)
{

	int curLocationY = 2;
	int key = 0;
	int ipFlag = 0;
	int localFlag = 0;
	int subFlag = 0;
	int destFlag = 0;
	int doneFlag = 0;
	int fileFlag = 0;

	RED_X(2);
	RED_X(3);
	RED_X(4);
	RED_X(5);
	RED_X(6);

	//moves the cursor to the first location
	ConsMoveCursor(curLocationY, STARTLOC);

	while (1)
	{
		//while the keyboard hasn't been pressed do nothing
		while (!KEYCHECK);
		//getting the key that was pressed
		key = getch();

		//if tab has been pressed /*will #define soon */
		if (key == TAB)
		{
			//move the line
			curLocationY++;
			//reached end of editable portion
			if (curLocationY == 7)
			{
				//move back to start
				curLocationY = 1;
			}
		}

		//based on which line call a different function
		switch (curLocationY)
		{
		case 1:
			//the done button line
			if (CORRECTDATA)
			{
				ConsDisplayAttr(17, 0, "__________", BLUE);
				ConsDisplayAttr(18, 0, "|  Done  |", BLUE);
				ConsDisplayAttr(19, 0, "----------", BLUE);
				break;
			}
			else
			{
				curLocationY = 2;
			}

		case 2:
			//the ip line
			ipFlag = DisplayIP(curLocationY, key, info, doneFlag);
			break;
		case 3:
			//the subnet line
			subFlag = DisplaySub(curLocationY, key, info, doneFlag);
			break;
		case 4:
			//the filename line
			fileFlag = DisplayFile(curLocationY, key, info, doneFlag);
			break;
		case 5:
			//the file path line
			localFlag = DisplayLocal(curLocationY, key, info, doneFlag);
			break;

		case 6:
			//the file destination line
			destFlag = DisplayDest(curLocationY, key, info, doneFlag);
			break;
		}
		if (key == ENTERKEY && curLocationY == 1)
		{
			break;
		}
		if (CORRECTDATA && curLocationY != 1)
		{
			ConsDisplayAttr(17, 0, "__________", WHITE);
			ConsDisplayAttr(18, 0, "|  Done  |", WHITE);
			ConsDisplayAttr(19, 0, "----------", WHITE);
			ConsMoveCursor(curLocationY, buttLoc);
			doneFlag = 1;
		}
		else
		{
			doneFlag = 0;
		}
	}

}

/* StatusWindow(struct fileTransfer *info)
* displays the status window and the error codes that are returned
*
* input:
* *info: the data structure that holds all the data
*
* return:
* none
*/
void StatusWindow(struct fileTransfer *info)
{
	int index;
	enum Errorcode ERR = Receive_CloseFail;
	ERR = Control(info);
	ConsMoveCursor(4, 2);
	printf("%d", ERR);
	for ( index = 0; displayError[index].ERR >= 0; index++)
	{
		if (displayError[index].ERR == ERR)
		{
			ConsMoveCursor(4, 2);
			printf("ERROR %d: %s", displayError[index].ERR, displayError[index].display);
		}
	}

	if (ERR == Receive_FileAlreadyExists)
	{

	}
}

/* DisplayIP(int curLocationY, int key)
* displays the keys that are pressed into this line
*
* input:
* curLocation: line up/down position
* key: the character from the keyboard
* *info: the data structure that holds all the data
*
* return:
* none
*/
int DisplayIP(int curLocationY, int key, struct fileTransfer *info, int doneFlag)
{
	int index;
	char output[2];
	static int ipx = STARTLOC;
	int badFlag = 0;
	static int count = 0;
	static int maxcnt = 0;
	static int actualval = 0;
	static int maxflag = 0;
	static int goodGo[ADDRESSMAX] = { 0 };
	int valid = 0;
	int done = CHECK;
	int returndat = 0;
	int tempSize = 0;

	sprintf(output, "%c", key);

	//if delete key is pressed
	if (key == DELETEKEY)
	{
		//if its at the end of a section but not the end of the line
		if (count == 0 && maxcnt != 0)
		{
			//move back one
			ipx--;
			//jump over the .
			count = SECTIONSIZE;
		}
		//if its not at the end
		if (maxcnt != 0)
		{
			//removing one
			ipx--;
			count--;
			maxcnt--;
		}
		//moving back one and replacing the _
		ConsDisplayAttr(curLocationY, ipx, "_", WHITE);
		RED_X(curLocationY);
		ConsDisplayAttr(17, 0, "           ", WHITE);
		ConsDisplayAttr(18, 0, "           ", WHITE);
		ConsDisplayAttr(19, 0, "           ", WHITE);
		ConsMoveCursor(curLocationY, ipx);
	}
	else
	{
		//moves cursor to current location
		ConsMoveCursor(curLocationY, ipx);
		//if its not at the end of the line
		if (maxcnt != ADDRESSMAX)
		{
			//if its not a tab keypress
			if (key != TAB)
			{
				//makes sure its a digit if not change color to red
				if (!isdigit(key))
				{
					ConsDisplayAttr(curLocationY, ipx, output, RED);
					badFlag = 1;
					goodGo[maxcnt] = 0;
				}
				//displays the character if its a number
				if (badFlag != 1)
				{
					ConsDisplayAttr(curLocationY, ipx, output, WHITE);
					goodGo[maxcnt] = 1;
					info->ui.ipAddress[ipx - STARTLOC] = key;
				}
				//increase the x position of the cursor
				ipx++;
				//increases the count to determine where the . are
				count++;
				maxcnt++;
				//if the end of the section is reached
				if (count == SECTIONSIZE && maxcnt != ADDRESSMAX)
				{
					info->ui.ipAddress[ipx - STARTLOC] = '.';
					//goto the next section
					count = 0;
					//jump over the .
					ipx++;
					//finding the size of the section
					for (index = 2; index >= 0; index--)
					{
						tempSize = (tempSize * 10) + (info->ui.ipAddress[ipx - STARTLOC - index - 2] - '0');
					}
					//if the size for the section is too big, set color to red and set flag for bad characters
					if (tempSize >= MAXIPRANGE)
					{
						for (index = 2; index >= 0; index--)
						{
							//changing only the one character that needs changed instead of the whole array
							output[0] = info->ui.ipAddress[ipx - STARTLOC - index - 2];
							//changing color to red
							ConsDisplayAttr(curLocationY, ipx - index - 2, output, RED);
							//setting the bad flag to zero to indicate bad character
							goodGo[(maxcnt - index - 1)] = 0;
						}
					}
					ConsMoveCursor(curLocationY, ipx);
					//move the cursor
					ConsMoveCursor(curLocationY, ipx);

				}
				//if its at the end

			}
		}
		if (maxcnt == ADDRESSMAX)
		{
			ipx++;
			//finding the size of the section
			for (index = 2; index >= 0; index--)
			{
				tempSize = (tempSize * 10) + (info->ui.ipAddress[ipx - STARTLOC - index - 2] - '0');
			}
			//if the size for the section is too big, set color to red and set flag for bad characters
			if (tempSize >= MAXIPRANGE)
			{
				for (index = 2; index >= 0; index--)
				{
					//changing only the one character that needs changed instead of the whole array
					output[0] = info->ui.ipAddress[ipx - STARTLOC - index - 2];
					//changing color to red
					ConsDisplayAttr(curLocationY, ipx - index - 2, output, RED);
					//setting the bad flag to zero to indicate bad character
					goodGo[(maxcnt - index - 1)] = 0;
				}
			}
			ipx--;
			//check to make sure all the characters are valid
			for (index = 0; index < ADDRESSMAX; index++)
			{
				valid += goodGo[index];
			}
			//if valid
			if (valid == ADDRESSMAX)
			{
				//print green checkmark
				CHECKMARK(curLocationY);
				ConsMoveCursor(curLocationY, ipx);
				returndat = 1;
				buttLoc = ipx;
			}
			else
			{
				RED_X(curLocationY);

				ConsMoveCursor(curLocationY, ipx);
			}
		}
	}
	return returndat;
}

/* DisplaySub(int curLocationY, int key)
* displays the keys that are pressed into this line
*
* input:
* curLocation: line up/down position
* key: the character from the keyboard
* *info: the data structure that holds all the data
*
* return:
* none
*/
int DisplaySub(int curLocationY, int key, struct fileTransfer *info, int doneFlag)
{
	int index;
	char output[2];
	static int subx = STARTLOC;
	int badFlag = 0;
	static int count = 0;
	static int maxcnt = 0;
	int done = CHECK;
	static int goodGo[ADDRESSMAX] = { 0 };
	int valid = 0;
	int returndat = 0;
	int tempSize = 0;


	sprintf(output, "%c", key);

	//if delete key is pressed
	if (key == DELETEKEY)
	{
		//if its at the end of a section but not the end of the line
		if (count == 0 && maxcnt != 0)
		{
			//move back one
			subx--;
			//jump over the .
			count = SECTIONSIZE;
		}
		//if its not at the end
		if (maxcnt != 0)
		{
			//removing one
			subx--;
			count--;
			maxcnt--;
		}
		//moving back one and replacing the _
		ConsDisplayAttr(curLocationY, subx, "_", WHITE);
		RED_X(curLocationY);
		ConsDisplayAttr(17, 0, "           ", WHITE);
		ConsDisplayAttr(18, 0, "           ", WHITE);
		ConsDisplayAttr(19, 0, "           ", WHITE);
		ConsMoveCursor(curLocationY, subx);
	}
	else
	{
		//moves cursor to current location
		ConsMoveCursor(curLocationY, subx);
		//if its not at the end of the line
		if (maxcnt < ADDRESSMAX)
		{
			//if its not a tab keypress
			if (key != TAB)
			{
				//makes sure its a digit if not change color to red
				if (!isdigit(key))
				{
					ConsDisplayAttr(curLocationY, subx, output, RED);
					badFlag = 1;
					goodGo[maxcnt] = 0;
				}
				//displays the character if its a number
				if (badFlag != 1)
				{
					ConsDisplayAttr(curLocationY, subx, output, WHITE);
					goodGo[maxcnt] = 1;
					info->ui.subnet[subx - STARTLOC] = key;
				}
				//increase the x position of the cursor
				subx++;
				//increases the count to determine where the . are
				count++;
				maxcnt++;
				//if the end of the section is reached
				if (count == SECTIONSIZE && maxcnt != ADDRESSMAX)
				{
					info->ui.subnet[subx - STARTLOC] = '.';
					//goto the next section
					count = 0;
					//jump over the .
					subx++;
					//move the cursor

					//finding the size of the section
					for (index = 2; index >= 0; index--)
					{
						tempSize = (tempSize * 10) + (info->ui.subnet[subx - STARTLOC - index - 2] - '0');
					}
					//if the size for the section is too big, set color to red and set flag for bad characters
					if (tempSize >= MAXIPRANGE)
					{
						for (index = 2; index >= 0; index--)
						{
							//changing only the one character that needs changed instead of the whole array
							output[0] = info->ui.subnet[subx - STARTLOC - index - 2];
							//changing color to red
							ConsDisplayAttr(curLocationY, subx - index - 2, output, RED);
							//setting the bad flag to zero to indicate bad character
							goodGo[(maxcnt - index - 1)] = 0;
						}
					}
					ConsMoveCursor(curLocationY, subx);
				}
				//if its at the end

			}
		}

		if (maxcnt == ADDRESSMAX)
		{
			subx++;
			//finding the size of the section
			for (index = 2; index >= 0; index--)
			{
				tempSize = (tempSize * 10) + (info->ui.subnet[subx - STARTLOC - index - 2] - '0');
			}
			//if the size for the section is too big, set color to red and set flag for bad characters
			if (tempSize >= MAXIPRANGE)
			{
				for (index = 2; index >= 0; index--)
				{
					//changing only the one character that needs changed instead of the whole array
					output[0] = info->ui.subnet[subx - STARTLOC - index - 2];
					//changing color to red
					ConsDisplayAttr(curLocationY, subx - index - 2, output, RED);
					//setting the bad flag to zero to indicate bad character
					goodGo[(maxcnt - index - 1)] = 0;
				}
			}
			subx--;
			//check to make sure all the characters are valid
			for (index = 0; index < 12; index++)
			{
				valid += goodGo[index];
			}
			//if valid
			if (valid == ADDRESSMAX)
			{
				//print green checkmark
				CHECKMARK(curLocationY);
				ConsMoveCursor(curLocationY, subx);
				returndat = 1;
				buttLoc = subx;
			}
			else
			{
				RED_X(curLocationY);
				ConsDisplayAttr(17, 0, "           ", WHITE);
				ConsDisplayAttr(18, 0, "           ", WHITE);
				ConsDisplayAttr(19, 0, "           ", WHITE);
				ConsMoveCursor(curLocationY, subx);
			}
		}
	}
	return returndat;
}

int DisplayFile(int curLocationY, int key, struct fileTransfer *info, int doneFlag)
{
	int index;
	char output[2];
	static int filex = STARTLOC;
	int badFlag = 0;
	char badChar[] = BADCHAR;
	static int maxcnt = 0;
	static int goodGo[MAXFILELENGTH];
	int valid = 0;
	int done = CHECK;
	int returndat = 0;

	sprintf(output, "%c", key);
	//if delete key is pressed
	if (key == DELETEKEY)
	{
		//if its not at the end
		if (maxcnt != 0)
		{
			//removing one
			filex--;
			maxcnt--;
			goodGo[maxcnt] = 0;
			info->ui.fileName[filex - STARTLOC] = '\0';
		}
		//moving back one and replacing the _
		ConsDisplayAttr(curLocationY, filex, " ", WHITE);
		ConsMoveCursor(curLocationY, filex);
	}
	else
	{
		if (maxcnt < MAXFILELENGTH)
		{
			//moves cursor to current location
			ConsMoveCursor(curLocationY, filex);
			//if its not a tab keypress
			if (key != TAB)
			{
				//making sure it is a valid character to be used in filenames
				for (index = 0; badChar[index] != '\0'; index++)
				{
					//if not, display char in red
					if (key == badChar[index])
					{
						ConsDisplayAttr(curLocationY, filex, output, RED);
						goodGo[maxcnt] = 0;
						badFlag = 1;
					}
				}
				//display non bad characters in white
				if (badFlag != 1)
				{
					ConsDisplayAttr(curLocationY, filex, output, WHITE);
					goodGo[maxcnt] = 1;
					info->ui.fileName[filex - STARTLOC] = key;
				}
				//increase the x position of the cursor
				filex++;
				maxcnt++;
			}
		}
	}

	//check to make sure all the characters are valid
	for (index = 0; index < MAXFILELENGTH; index++)
	{
		valid += goodGo[index];
	}
	//if valid
	if (valid == maxcnt && maxcnt != 0)
	{
		//print green checkmark
		CHECKMARK(curLocationY);
		ConsMoveCursor(curLocationY, filex);
		returndat = 1;
		buttLoc = filex;
	}
	else
	{
		//print red x
		RED_X(curLocationY);
		ConsDisplayAttr(17, 0, "           ", WHITE);
		ConsDisplayAttr(18, 0, "           ", WHITE);
		ConsDisplayAttr(19, 0, "           ", WHITE);
		ConsMoveCursor(curLocationY, filex);
	}
	return returndat;
}

/* DisplayLocal(int curLocationY, int key)
* displays the keys that are pressed into this line
*
* input:
* curLocation: line up/down position
* key: the character from the keyboard
* *info: the data structure that holds all the data
*
* return:
* none
*/
int DisplayLocal(int curLocationY, int key, struct fileTransfer *info, int doneFlag)
{
	int index;
	char output[2];
	static int localx = STARTLOC;
	int badFlag = 0;
	char badChar[] = BADCHAR;
	static int maxcnt = 0;
	static int goodGo[MAXFILESIZE];
	int valid = 0;
	int done = CHECK;
	int returndat = 0;

	sprintf(output, "%c", key);
	//if delete key is pressed
	if (key == DELETEKEY)
	{
		//if its not at the end
		if (maxcnt != 0)
		{
			//removing one
			localx--;
			maxcnt--;
			goodGo[maxcnt] = 0;
			info->ui.filePath[localx - STARTLOC] = '\0';
		}
		//moving back one and replacing the _
		ConsDisplayAttr(curLocationY, localx, " ", WHITE);
		ConsMoveCursor(curLocationY, localx);
	}
	else
	{
		if (maxcnt < MAXFILESIZE)
		{
			//moves cursor to current location
			ConsMoveCursor(curLocationY, localx);
			//if its not a tab keypress
			if (key != TAB)
			{
				//making sure it is a valid character to be used in filenames
				for (index = 0; badChar[index] != '\0'; index++)
				{
					//if not, display char in red
					if (key == badChar[index])
					{
						ConsDisplayAttr(curLocationY, localx, output, RED);
						goodGo[maxcnt] = 0;
						badFlag = 1;
					}
				}
				//display non bad characters in white
				if (badFlag != 1)
				{
					ConsDisplayAttr(curLocationY, localx, output, WHITE);
					goodGo[maxcnt] = 1;
					info->ui.filePath[localx - STARTLOC] = key;
				}
				//increase the x position of the cursor
				localx++;
				maxcnt++;
			}
		}
	}

	//check to make sure all the characters are valid
	for (index = 0; index < MAXFILESIZE; index++)
	{
		valid += goodGo[index];
	}
	//if valid
	if (valid == maxcnt && maxcnt != 0)
	{
		//print green checkmark
		CHECKMARK(curLocationY);
		ConsMoveCursor(curLocationY, localx);
		returndat = 1;
		buttLoc = localx;
	}
	else
	{
		//print red x
		RED_X(curLocationY);
		ConsDisplayAttr(17, 0, "           ", WHITE);
		ConsDisplayAttr(18, 0, "           ", WHITE);
		ConsDisplayAttr(19, 0, "           ", WHITE);
		ConsMoveCursor(curLocationY, localx);
	}
	return returndat;
}

/* DisplayDest(int curLocationY, int key)
* displays the keys that are pressed into this line
*
* input:
* curLocation: line up/down position
* key: the character from the keyboard
* *info: the data structure that holds all the data
*
* return:
* none
*/
int DisplayDest(int curLocationY, int key, struct fileTransfer *info, int doneFlag)
{
	int index;
	static int destx = STARTLOC;
	char output[2];
	int badFlag = 0;
	char badChar[] = BADCHAR;
	static int maxcnt = 0;
	static int goodGo[MAXFILESIZE] = { 1 };
	int valid = 0;
	int done = CHECK;
	int returndat = 0;

	sprintf(output, "%c", key);
	//if delete key is pressed
	if (key == DELETEKEY)
	{
		//if its not at the end
		if (maxcnt != 0)
		{
			//removing one
			destx--;
			maxcnt--;
			goodGo[maxcnt] = 0;
			info->ui.destination[destx - STARTLOC] = '\0';
		}
		//moving back one and replacing the _
		ConsDisplayAttr(curLocationY, destx, " ", WHITE);
		ConsMoveCursor(curLocationY, destx);
	}
	else
	{
		if (maxcnt < MAXFILESIZE)
		{
			//moves cursor to current location
			ConsMoveCursor(curLocationY, destx);
			//if its not a tab keypress
			if (key != TAB)
			{
				//making sure it is a valid character to be used in filenames
				for (index = 0; badChar[index] != '\0'; index++)
				{
					//if not, display char in red
					if (key == badChar[index])
					{
						ConsDisplayAttr(curLocationY, destx, output, RED);
						goodGo[maxcnt] = 0;
						badFlag = 1;
					}
				}
				//display non bad characters in white
				if (badFlag != 1)
				{
					ConsDisplayAttr(curLocationY, destx, output, WHITE);
					info->ui.destination[destx - STARTLOC] = key;
					goodGo[maxcnt] = 1;
				}
				//increase the x position of the cursor
				destx++;
				maxcnt++;

			}
		}
	}

	//check to make sure all the characters are valid
	for (index = 0; index < MAXFILESIZE; index++)
	{
		valid += goodGo[index];
	}
	//if valid
	if (valid == maxcnt && maxcnt != 0)
	{
		//print green checkmark
		CHECKMARK(curLocationY);
		ConsMoveCursor(curLocationY, destx);
		returndat = 1;
		//creates the done button when the everything is correct
		buttLoc = destx;
	}
	else
	{
		//print red x
		RED_X(curLocationY);
		ConsDisplayAttr(17, 0, "           ", WHITE);
		ConsDisplayAttr(18, 0, "           ", WHITE);
		ConsDisplayAttr(19, 0, "           ", WHITE);
		ConsMoveCursor(curLocationY, destx);
	}
	return returndat;
}
