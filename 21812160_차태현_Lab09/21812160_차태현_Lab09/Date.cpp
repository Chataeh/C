#include<stdio.h>
#include "Date.h"

void printDate(Date date)
{
	
	printf("(%4d,%2d,%2d)", date.year, date.month, date.day);//������� ���

}

int compareDate(Date d1, Date d2)//���� �������������� ���� ���� ��
{
	if (d1.year > d2.year)
		return 1;
	else if (d1.year < d2.year)
		return -1;
	else if ((d1.year = d2.year) && (d1.month > d2.month))
		return 1;
	else if ((d1.year = d2.year) && (d1.month < d2.month))
		return -1;
	else if ((d1.year = d2.year) && (d1.month = d2.month) && (d1.day > d2.day))
		return 1;
	else if ((d1.year = d2.year) && (d1.month = d2.month) && (d1.day < d2.day))
		return -1;
	else
		return 0;
}