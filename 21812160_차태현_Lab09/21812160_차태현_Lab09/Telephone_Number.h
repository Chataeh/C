#ifndef  T_H
#define T_H

typedef struct// ����üTel_Number ����
{
	unsigned short nation_code;
	unsigned short region_code;
	unsigned short switch_no;
	unsigned short line_no;
	
}Tel_Number;
void printTelephoneNumber(Tel_Number tel_no);//��ȭ��ȣ ���
int compareTelNumber(Tel_Number tn1, Tel_Number tn2);//��ȭ��ȣ �� ũ���
#endif // ! T_H
