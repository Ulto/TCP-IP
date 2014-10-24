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
    DATE creationDate;
    FILE *ourFile;
    char buffer[1500];
    int length;
};

struct fileTransfer
{
    int error;
    int command;

    struct userInt ui;
    struct network net;

};
