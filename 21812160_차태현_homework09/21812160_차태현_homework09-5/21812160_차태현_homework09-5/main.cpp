/**
*�����̸�"21812160_������_homework09-5 ��
*���α׷��� ���� �� �⺻ ���:
* ����ü �ð��迭�� ���������ϴ� ���α׷�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 5��7��),
*���� ���� �� ����: 2021�� 5�� 7�� (������)
*/
#include <stdio.h>
#include "Time.h"//����� �������
#define NUM_TIMES 5
void main()
{
	Time t1, t2;
	Time times[NUM_TIMES];
	int incr_secs, diff_sec;
	t1 = t2 = inputTime();//�ð� �Է�
	printf("Input time t1 = "); printTime(&t1); printf("\n");
	printf("input seconds to increment : ");
	scanf("%d", &incr_secs);//���� �� �ð��Է�
	incrementTime(&t2, incr_secs);//������ �ʿ� ���� ���ο� �ð���
	printf("After incrementing %d secs, t2 = ", incr_secs); printTime(&t2); printf("\n");
	diff_sec = compareTime(&t1, &t2);//�� �ð��� �ð� ��
	printf("Difference between t1 and t2 is %d secs\n", diff_sec);
	times[0] = initTime(23, 59, 59);
	times[1] = initTime(9, 0, 5);
	times[2] = initTime(13, 30, 0);
	times[3] = initTime(3, 59, 59);
	times[4] = initTime(0, 0, 0);
	printf("\nBefore sorting times : \n");
	for (int i = 0; i < NUM_TIMES; i++)
	{
		printf("times[%d] = ", i); printTime(&times[i]); printf("\n");
	}
	selectSortTime(times, NUM_TIMES);//���������� ���
	printf("After selection sorting of times : \n");
	for (int i = 0; i < NUM_TIMES; i++)
	{
		printf("times[%d] = ", i); printTime(&times[i]); printf("\n");
	}
}