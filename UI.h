#include "cons.h"
#include "dataStruct.h"

#ifndef UI_H
#define UI_H

#define ADDRESSMAX		12		//ip and subnet max length
#define MAXFILESIZE		100		//maximum length of the file path
#define MAXFILELENGTH	25
#define SECTIONSIZE		3		//size of each section of ip/subnet

#define TAB			    9		//tab character ascii value
#define CHECK		    251		//checkmark ascii value
#define WRONG		    "X"		// x ascii value
#define DELETEKEY		8		//delete character ascii value
#define ENTERKEY		13
#define QUESTMARK		63
#define BACKSLASH		92

#define STARTLOC		22
#define BADCHAR			{ BACKSLASH, '*', '?', '"', '<', '>', '|', '^' }

#define RED			    4		//attribute value for red
#define GREEN		    2		//attribute value for green
#define WHITE		    7		//attribute value for white
#define BLUE			9

#define KEYCHECK		kbhit()
#define CORRECTDATA		ipFlag == 1 && subFlag == 1 && localFlag == 1 && destFlag == 1 && fileFlag == 1

#define CHECKMARK(id)	ConsDisplayAttr(9+id, 23, &done, GREEN)
#define RED_X(id)		ConsDisplayAttr(9+id, 23, WRONG, RED)


void CreateUIMenu(int);
void UserInput(struct fileTransfer *info);
int DisplayIP(int curLocationY, int key, struct fileTransfer *info, int doneFlag);
int DisplaySub(int curLocationY, int key, struct fileTransfer *info, int doneFlag);
int DisplayFile(int curLocationY, int key, struct fileTransfer *info, int doneFlag);
int DisplayLocal(int curLocationY, int key, struct fileTransfer *info, int doneFlag);
int DisplayDest(int curLocationY, int key, struct fileTransfer *info, int doneFlag);
extern int NTWK_Receive(struct fileTransfer *);
#endif /* UI_H */
