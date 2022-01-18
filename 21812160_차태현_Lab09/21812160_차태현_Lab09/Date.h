#ifndef D_H
#define D_H

typedef struct //구조체 Date정의
{
	int year;
	int month;
	int day;
}Date;
void printDate(Date date);//생년월일 출력
int compareDate(Date d1, Date d2);// 생일비교

#endif 
