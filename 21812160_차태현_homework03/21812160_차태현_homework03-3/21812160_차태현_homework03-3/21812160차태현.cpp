/**
*���ϸ�:��multiplication.cpp��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� 12�ܱ����� �������ϴ� ���α׷��̴�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��19��),
*���� ���� �� ����: 2021�� 3�� 19�� (������)
*
*/
#include <stdio.h>
#define size 12
int main()
{
	int x[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int array[12][12];
	int i, j;


	printf(">>> 12 X 12 Multiplication Table<<<\n\n");
	printf("      ��");
	for (i = 0; i < size; i++)
		printf("%5d", x[i]);
	printf("\n=======+============================================================\n");
	
	for (i = 0; i < size; i++)
	{
		printf("%5d ��", i+1);
		for (j = 0; j < size; j++)
		{
			array[i][j] = x[i] * (j+1);
			printf("%5d", array[i][j]);
		}
		printf("\n");
	
	}

	
	return 0;
}