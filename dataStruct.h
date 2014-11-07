#include <Windows.h>
#include <stdio.h>

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#define BUFFSIZE 4096

struct userInt
{
	char subnet[16];
	char ipAddress[16];
	char filePath[100];
	char fileName[25];
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
	int length;
};

struct fileTransfer
{
	enum ErrorCode ERR;
	int command;

	struct userInt ui;
	struct network net;

};

struct errorDisplay
{
	enum ErrorCode ERR;
	char codeDisplay[50];

};

#endif /* DATASTRUCT_H */
