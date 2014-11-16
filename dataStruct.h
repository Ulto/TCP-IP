#include <Windows.h>
#include <stdio.h>

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#define BUFFSIZE 	4096
#define MAXFILESIZE 	100
#define MAXFILELENGTH	25


struct userInt
{
	char subnet[16];
	char ipAddress[16];
	char filePath[MAXFILESIZE];
	char fileName[MAXFILELENGTH];
	char destination[100];
	int port;

};

struct network
{
	FILETIME creationDate;
	FILETIME accessDate;
	FILETIME modifyDate;
	FILE* ourFile;
	char buffer[BUFFSIZE];
	int Bytes;
	int length;

};

struct fileTransfer
{
	enum ErrorCode ERR;
	int command;

	struct userInt ui;
	struct network net;

};

#endif /* DATASTRUCT_H */
