#ifndef D_H
#define D_H

typedef struct //����ü Date����
{
	int year;
	int month;
	int day;
}Date;
void printDate(Date date);//������� ���
int compareDate(Date d1, Date d2);// ���Ϻ�

#endif 
