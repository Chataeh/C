#ifndef T_H
#define T_H

typedef struct {//�ð� ����ü
	int hour;
	int min;
	int sec;
} Time;
Time inputTime(void);//�ð��Է�
void printTime(const Time* tptr1);//�ð� ���
void incrementTime(Time* tptr2, int sec);//������ �ʿ� ���� �ð����
int compareTime(const Time* tptr1, const Time* tptr2);//�ð� �� ���
void selectSortTime(Time* tptr1, int size);//��������
Time initTime(int h, int m, int s);//�־��� ���� ����ü�� �Է�
#endif // !T_H


