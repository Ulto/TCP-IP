#include "cons.h"

#ifndef UI_H
#define UI_H

#define ADDRESSMAX		12		//ip and subnet max length
#define MAXFILESIZE		100		//maximum length of the file path
#define SECTIONSIZE		3		//size of each section of ip/subnet

#define TAB			    9		//tab character ascii value
#define CHECK		    251		//checkmark ascii value
#define WRONG		    "X"		// x ascii value
#define DELETEKEY		8		//delete character ascii value

#define RED			    4		//attribute value for red
#define GREEN		    2		//attribute value for green
#define WHITE		    7		//attribute value for white

void CreateMenu(int);
void UserInput(struct fileTransfer *info);
void DisplayIP(int curLocationY, int key, struct fileTransfer *info);
void DisplaySub(int curLocationY, int key, struct fileTransfer *info);
void DisplayLocal(int curLocationY, int key, struct fileTransfer *info);
void DisplayDest(int curLocationY, int key, struct fileTransfer *info);
#endif /* UI_H */
