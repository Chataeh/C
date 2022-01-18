#ifndef  T_H
#define T_H

typedef struct// 구조체Tel_Number 정의
{
	unsigned short nation_code;
	unsigned short region_code;
	unsigned short switch_no;
	unsigned short line_no;
	
}Tel_Number;
void printTelephoneNumber(Tel_Number tel_no);//전화번호 출력
int compareTelNumber(Tel_Number tn1, Tel_Number tn2);//전화번호 값 크기비교
#endif // ! T_H
