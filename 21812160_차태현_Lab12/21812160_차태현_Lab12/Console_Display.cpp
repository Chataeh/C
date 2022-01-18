#include<stdio.h>
#include"ConsoleDisplay.h"

HANDLE consoleHandler;//전역변수

HANDLE initConsoleHandler()
{
	HANDLE stdCnslHndlr;
	stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleHandler = stdCnslHndlr;

	return consoleHandler;
}
void closeConsoleHandler(HANDLE hndlr)
{
	CloseHandle(hndlr);
}

int gotoxy(HANDLE consHndlr, int x, int y)//x좌표y좌표위치로 커서를 옮겨감
{
	if (consHndlr == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x),static_cast<short>(y) };//x,y short형으로 형변환후 좌표로 생성
	SetConsoleCursorPosition(consHndlr, coords);//출력창에 커서를 옮겨감
}