#include "UI.h"

void UserInt(struct fileTransfer *info)
{
	//initializes  console controls
	ConsInit();
	//clears the screen
	ConsClear();
	//calls the function to create the menu
	CreateMenu();
	
	while (1)
	{	
		//gets the user input 
		UserInput();
	}

	//frees the console
	ConsExit();
}

void CreateMenu()
{
	//creating the menu
	printf("    Welcome To Our File Transfer Program \n");
	printf("--------------------------------------------\n");
	printf("IP Address: ___.___.___.___\n");
	printf("Subnet Mask: ___.___.___.___\n");
	printf("Local File: \n");
	printf("Destination Location: \n");
	printf("Port: 1500\n");
}

void UserInput()
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
			DisplayIP(curLocationY, key);
			break;
			//the subnet line
		case 3:
			DisplaySub(curLocationY, key);
			break;
			//the file path line
		case 4:
			DisplayLocal(curLocationY, key);
			break;
			//the file destination line
		case 5:
			DisplayDest(curLocationY, key);
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
*
* return:
* none
*/
void DisplayIP(int curLocationY, int key)
{
	int index;
	static int ipx = 12;
	int badFlag = 0;
	static int count = 0;
	static int maxcnt = 0;

	//moves cursor to current location
	ConsMoveCursor(curLocationY, ipx);
	//if its not a tab keypress
	if (key != 9)
	{
		//makes sure its a digit if not change color to red
		if (!isdigit(key))
		{
			ConsDisplayAttr(curLocationY, ipx, &key, 5);
			badFlag = 1;
		}
		//displays the character if its a number
		if (badFlag != 1)
		{
			ConsDisplayAttr(curLocationY, ipx, &key, 7);
		}
		//increase the x position of the cursor
		ipx++;
		//increases the count to determine where the . are
		count++;
		//if it hits its max of 3 move one space to skip the .
		if (count == 3)
		{
			count = 0;
			ipx++;
			ConsMoveCursor(curLocationY, ipx);
		}
	}
}

/* DisplaySub(int curLocationY, int key)
* displays the keys that are pressed into this line
*
* input:
* curLocation: line up/down position
* key: the character from the keyboard
*
* return:
* none
*/
void DisplaySub(int curLocationY, int key)
{
	int index;
	static int subx = 13;
	int badFlag = 0;
	static int count = 0;

	//moves cursor to current location
	ConsMoveCursor(curLocationY, subx);
	//if its not a tab keypress
	if (key != 9)
	{
		//makes sure its a digit if not change color to red
		if (!isdigit(key))
		{
			ConsDisplayAttr(curLocationY, subx, &key, 5);
			badFlag = 1;
		}
		//displays the character if its a number
		if (badFlag != 1)
		{
			ConsDisplayAttr(curLocationY, subx, &key, 7);
		}
		//increase the x position of the cursor
		subx++;
		//increases the count to determine where the . are
		count++;
		//if it hits its max of 3 move one space to skip the .
		if (count == 3)
		{
			count = 0;
			count++;
			ConsMoveCursor(curLocationY, subx);
		}
	}
}

/* DisplayLocal(int curLocationY, int key)
* displays the keys that are pressed into this line
*
* input:
* curLocation: line up/down position
* key: the character from the keyboard
*
* return:
* none
*/
void DisplayLocal(int curLocationY, int key)
{
	int index;
	static int localx = 12;
	int badFlag = 0;
	char badChar[] = { 92, ':', '*', '?', '"', '<', '>', '|' };

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
				ConsDisplayAttr(curLocationY, localx, &key, 5);
				badFlag = 1;
			}
		}
		//display non bad characters in white
		if (badFlag != 1)
		{
			ConsDisplayAttr(curLocationY, localx, &key, 7);
		}
		//increase the x position of the cursor
		localx++;
	}
}

/* DisplayDest(int curLocationY, int key)
* displays the keys that are pressed into this line
*
* input:
* curLocation: line up/down position
* key: the character from the keyboard
*
* return:
* none
*/
void DisplayDest(int curLocationY, int key)
{
	int index;
	static int destx = 22;
	int badFlag = 0;
	char badChar[] = { 92, ':', '*', '?', '"', '<', '>', '|' };

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
				ConsDisplayAttr(curLocationY, destx, &key, 5);
				badFlag = 1;
			}
		}
		//display non bad characters in white
		if (badFlag != 1)
		{
			ConsDisplayAttr(curLocationY, destx, &key, 7);
		}
		//increase the x position of the cursor
		destx++;
	}
}
