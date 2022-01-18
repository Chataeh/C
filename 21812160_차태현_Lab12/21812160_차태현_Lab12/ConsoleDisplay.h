#ifndef C_H
#define C_H
#include<Windows.h>

HANDLE initConsoleHandler();
void closeConsoleHandler(HANDLE hndlr);
int gotoxy(HANDLE consoleHandler, int x, int y);

#endif // !C_H
