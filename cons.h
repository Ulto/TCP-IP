/* attributes for ConsDisplayAttr function */
#define A_WHITE   FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN
#define A_BRIGHT  FOREGROUND_INTENSITY|A_WHITE
#define A_REVERSE BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN
#define A_UNDER   FOREGROUND_BLUE


/* console/video functions */
void ConsClear(void);
void ConsMoveCursor(int, int);
int  ConsDisplayText(int, int, char *);
int  ConsDisplayAttr(int, int, char *, int);
void ConsInit(void);
void ConsExit(void);
