#include<stdio.h>
#include"ConsoleDisplay.h"

HANDLE consoleHandler;//��������

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

int gotoxy(HANDLE consHndlr, int x, int y)//x��ǥy��ǥ��ġ�� Ŀ���� �Űܰ�
{
	if (consHndlr == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x),static_cast<short>(y) };//x,y short������ ����ȯ�� ��ǥ�� ����
	SetConsoleCursorPosition(consHndlr, coords);//���â�� Ŀ���� �Űܰ�
}