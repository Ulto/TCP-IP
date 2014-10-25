#include "cons.h"

#ifndef UI_H
#define UI_H

#define DELETEKEY			8		//delete character ascii value
#define TAB			    9		//tab character ascii value
#define ADDRESSMAX		12		//ip and subnet max length
#define CHECK		    251		//checkmark ascii value
#define WRONG		    "X"		//character string X
#define SECTIONSIZE		3		//size of each section of ip/subnet
#define GREEN		    2		//attribute value for green
#define RED			    4		//attribute value for red
#define WHITE		    7		//attribute value for white


void CreateMenu(int);
void UserInput(struct fileTransfer *info);
void DisplayIP(int curLocationY, int key, struct fileTransfer *info);
void DisplaySub(int curLocationY, int key, struct fileTransfer *info);
void DisplayLocal(int curLocationY, int key, struct fileTransfer *info);
void DisplayDest(int curLocationY, int key, struct fileTransfer *info);

#endif /* UI_H */
