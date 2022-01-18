#include<stdio.h>
#include"Time.h"

Time inputTime(void)//�ð� �Է�
{
	Time t;
	printf("input hour minute sec :");
	scanf("%d %d %d", &t.hour, &t.min,&t.sec);

	return t;
}

void printTime(const Time* tptr1)//�ð� ���
{
	if (tptr1->hour >= 24)//24�ð����� ǥ��
		printf("(%02d:%02d:%02d)", tptr1->hour - 24, tptr1->min, tptr1->sec);
	else
		printf("(%02d:%02d:%02d)", tptr1->hour, tptr1->min, tptr1->sec);
	
}
void incrementTime(Time* tptr2, int sec)//������ �ʿ� ���� ����ü��
{
	int S;
	
	S = tptr2->hour * 60 * 60 + tptr2->min * 60 + tptr2->sec + sec; //��ü�ð��� �ʷ� �ٲ���
	tptr2->hour = S / 3600;//��ü �ʿ����� �ð��� ���
	tptr2-> min = (S / 60) % 60;//��ü �ʿ����� �������
	tptr2->sec = S % 60;//��ü �ʿ����� �ʸ����
}

int compareTime(const Time* tptr1, const Time* tptr2)//�� ���� �ð���
{
	int S1, S2,diff;

	S1= tptr1->hour * 60 * 60 + tptr1->min * 60 + tptr1->sec;//��ü�ð����� ��ȯ
	S2 = tptr2->hour * 60 * 60 + tptr2->min * 60 + tptr2->sec;
	diff = S2 - S1;//�� ���� �ð��� ���
	
	return diff;
}
int compare(const Time* tptr1, const Time* tptr2)//���������� ���� �־��� �ð� ������ ũ���
{
	if (tptr1->hour > tptr2->hour)//�ð����� �Ǻ��� �����
		return 1;
	else if (tptr1->hour < tptr2->hour)
		return -1;
	else//�ð��� ���� ���̴ٸ����
	{
		if (tptr1->min > tptr2->min)
			return 1;
		else if (tptr1->min < tptr2->min)
			return -1;
		else//�ð� ���� ���� �ʰ��ٸ����
		{
			if (tptr1->sec > tptr2->sec)
				return 1;
			else if (tptr1->sec < tptr2->sec)
				return -1;
			else return 0;
		}
	}
}

void selectSortTime(Time *tptr1,int size)//��������
{
	Time temp;//������ȯ�� ���� ����
	Time* t;
	Time* min_t;
	int min;
	for(int i=0; i<size-1;i++)
	{
		min = i;//�ʱ� ���� �ּҷ� ���ϰ����
		min_t = &tptr1[i];
		for (int j = i + 1; j < size; j++)
		{
			t = &tptr1[j];
			if (compare(t,min_t) < 0)//���ذ����� �� �������� ���
			{
				min_t = t;
				min = j;
			}
		}
		if (min != i)//�ּҰ��� �ٲ��� ����
		{
			temp = tptr1[i];
			tptr1[i] = tptr1[min];
			tptr1[min] = temp;
		}
	}
}
Time initTime(int h, int m, int s)//�־��� �ð� �� �ʿ����� ����ü ��ȯ
{
	Time t;
	t.hour = h;
	t.min = m;
	t.sec = s;

	return t;
}