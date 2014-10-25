#include "UI.h"

void UserInt(struct fileTransfer *info)
{
	int choice;
	//initializes  console controls
	ConsInit();
	//clears the screen
	ConsClear();
	//calls the function to create the menu
	CreateMenu(0);

	while (!kbhit());
	choice = getch();

	switch (choice-'0')
	{
	case 1:
		CreateMenu(2);
		//Recieving(&info);
		break;
	case 2:
		CreateMenu(1);
		while (1)
		{
			//gets the user input 
			UserInput(info);
		}
		break;
	}

	//frees the console
	ConsExit();
}

void CreateMenu(int menu)
{
	ConsClear();
	printf("    Welcome To Our File Transfer Program \n");
	printf("--------------------------------------------\n");
	switch (menu)
	{
	case 0:
		//creating the menu
		printf("What would you like to do?\n");
		printf("(1) Receiving\n");
		printf("(2) Sending\n");
		printf("Choice: ");
		break;
	case 1:
		//creating the menu
		printf("IP Address: ___.___.___.___\n");
		printf("Subnet Mask: ___.___.___.___\n");
		printf("Local File: \n");
		printf("Destination Location: \n");
		printf("Port: 1500\n");
		break;
	case 2:
		printf("Please check the other computer for status of the transfer\n");
		printf("Thank you,\n");
		printf("The 457 File Transfer Team\n");
		break;
	}

}

void UserInput(struct fileTransfer *info)
{

	int curLocationY = 2;
	int key = 0;

	//moves the cursor to the first location
	ConsMoveCursor(curLocationY, 12);

	while (1)
	{
		//while the keyboard hasn't been pressed do nothing
		while (!kbhit());
		//getting the key that was pressed
		key = getch();

		//if tab has been pressed /*will #define soon */
		if (key == 9)
		{
			//move the line
			curLocationY++;
			//reached end of editable portion
			if (curLocationY == 6)
			{
				//move back to start
				curLocationY = 2;
			}
		}

		//based on which line call a different function
		switch (curLocationY)
		{
			//the ip line
		case 2:
			DisplayIP(curLocationY, key, info);
			break;
			//the subnet line
		case 3:
			DisplaySub(curLocationY, key, info);
			break;
			//the file path line
		case 4:
			DisplayLocal(curLocationY, key, info);
			break;
			//the file destination line
		case 5:
			DisplayDest(curLocationY, key, info);
			break;
		}

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
void DisplayIP(int curLocationY, int key, struct fileTransfer *info)
{
	int index;
	char output[2];
	static int ipx = ADDRESSMAX;
	int badFlag = 0;
	static int count = 0;
	static int maxcnt = 0;
	static int actualval = 0;
	static int maxflag = 0;
	static int goodGo[ADDRESSMAX] = { 0 };
	int valid = 0;
	int done = CHECK;

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
				}
				//increase the x position of the cursor
				ipx++;
				//increases the count to determine where the . are
				count++;
				maxcnt++;
				//if the end of the section is reached
				if (count == SECTIONSIZE)
				{
					//goto the next section
					count = 0;
					//jump over the .
					ipx++;
					//move the cursor
					ConsMoveCursor(curLocationY, ipx);
				}
				//if its at the end
				if (maxcnt == ADDRESSMAX)
				{
					//check to make sure all the characters are valid
					for (index = 0; index < ADDRESSMAX; index++)
					{
						valid += goodGo[index];
					}
					//if valid
					if (valid == ADDRESSMAX)
					{
						//print green checkmark
						ConsDisplayAttr(curLocationY, ipx, &done, GREEN);
					}
					else
					{
						//print red x
						ConsDisplayAttr(curLocationY, ipx, WRONG, RED);
					}
				}
			}
		}
	}
	
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
void DisplaySub(int curLocationY, int key, struct fileTransfer *info)
{
	int index;
	char output[2];
	static int subx = 13;
	int badFlag = 0;
	static int count = 0;
	static int maxcnt = 0;
	int done = CHECK;
	static int goodGo[ADDRESSMAX] = { 0 };
	int valid = 0;

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
				}
				//increase the x position of the cursor
				subx++;
				//increases the count to determine where the . are
				count++;
				maxcnt++;
				//if the end of the section is reached
				if (count == SECTIONSIZE)
				{
					//goto the next section
					count = 0;
					//jump over the .
					subx++;
					//move the cursor
					ConsMoveCursor(curLocationY, subx);
				}
				//if its at the end
				if (maxcnt == ADDRESSMAX)
				{
					//check to make sure all the characters are valid
					for (index = 0; index < 12; index++)
					{
						valid += goodGo[index];
					}
					//if valid
					if (valid == ADDRESSMAX)
					{
						//print green checkmark
						ConsDisplayAttr(curLocationY, subx, &done, GREEN);
					}
					else
					{
						//print red x
						ConsDisplayAttr(curLocationY, subx, WRONG, RED);
					}
				}
			}
		}
	}
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
void DisplayLocal(int curLocationY, int key, struct fileTransfer *info)
{
	int index;
	char output[2];
	static int localx = 12;
	int badFlag = 0;
	char badChar[] = { 92, ':', '*', '?', '"', '<', '>', '|' };
	static int maxcnt = 0;
	static int goodGo[MAXFILESIZE];
	int valid = 0;
	int done = CHECK;

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
			if (key != 9)
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
				}
				//increase the x position of the cursor
				localx++;
				maxcnt++;
				//if its at the end
				if (maxcnt == MAXFILESIZE)
				{
					//check to make sure all the characters are valid
					for (index = 0; index < MAXFILESIZE; index++)
					{
						valid += goodGo[index];
					}
					//if valid
					if (valid == MAXFILESIZE)
					{
						//print green checkmark
						ConsDisplayAttr(curLocationY, localx, &done, GREEN);
					}
					else
					{
						//print red x
						ConsDisplayAttr(curLocationY, localx, WRONG, RED);
					}
				}
			}
		}
	}
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
void DisplayDest(int curLocationY, int key, struct fileTransfer *info)
{
	int index;
	static int destx = 22;
	char output[2];
	int badFlag = 0;
	char badChar[] = { 92, ':', '*', '?', '"', '<', '>', '|' };
	static int maxcnt = 0;
	static int goodGo[MAXFILESIZE];
	int valid = 0;
	int done = CHECK;

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
			if (key != 9)
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
					goodGo[maxcnt] = 1;
				}
				//increase the x position of the cursor
				destx++;
				maxcnt++;
				if (maxcnt == MAXFILESIZE)
				{
					//check to make sure all the characters are valid
					for (index = 0; index < MAXFILESIZE; index++)
					{
						valid += goodGo[index];
					}
					//if valid
					if (valid == MAXFILESIZE)
					{
						//print green checkmark
						ConsDisplayAttr(curLocationY, destx, &done, GREEN);
					}
					else
					{
						//print red x
						ConsDisplayAttr(curLocationY, destx, WRONG, RED);
					}
				}
			}
		}
	}
}
