#include <Windows.h>
#include <stdio.h>

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

struct userInt
{
    char subnet[16];
    char ipAddress[16];
    char filePath[100];
    char destination[100];
    int port;
};

struct network
{
	FILETIME creationDate;
	FILETIME accessDate;
	FILETIME modifyDate;
    FILE* ourFile;
    char buffer[2048];
    int length;
};

struct fileTransfer
{
    enum ErrorCodes ERR;
    int command;

    struct userInt ui;
    struct network net;

};

#endif /* DATASTRUCT_H */
