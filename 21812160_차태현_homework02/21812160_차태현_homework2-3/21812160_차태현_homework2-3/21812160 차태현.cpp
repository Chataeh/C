/**
*���ϸ�:���ִ� ������ ���� ���ʷ� ���.cpp��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� !~32765�� ������ �Է¹޾� ���ڸ� ���� ���ϴ� ���α׷��Դϴ�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��12��),
*���� ���� �� ����: 2021�� 3�� 12�� (������)
*
*/
#include <stdio.h>

int main()
{
	int array[5];

	int num;
	
	
	
	printf("1~32765������ ���� �Է��Ͻÿ�:");
	scanf_s("%d", &num);
	if ((num >= 1 && num <= 32765))
	{
		

		for (int i = 4; i >= 0; i--)
		{
			array[i]=num % 10;
			num=num / 10;
		}

		if (array[0] != 0)
		{
			printf("��:%d ", array[0]);
			printf("õ:%d ", array[1]);
			printf("��:%d ", array[2]);
			printf("��:%d ", array[3]);
			printf("��:%d", array[4]);

		}
		if (array[0] == 0 && array[1] != 0)
		{
			printf("õ:%d ", array[1]);
			printf("��:%d ", array[2]);
			printf("��:%d ", array[3]);
			printf("��:%d", array[4]);

		}

		if (array[0] == 0 && array[1] == 0 && array[2] != 0)
		{
			printf("��:%d ", array[2]);
			printf("��:%d ", array[3]);
			printf("��:%d", array[4]);

		}

		if (array[0] == 0 && array[1] == 0 && array[2] == 0 && array[3] != 0)
		{
			printf("��:%d ", array[3]);
			printf("��:%d", array[4]);

		}

		if (array[0] == 0 && array[1] == 0 && array[2] == 0 && array[3] == 0 && array[4] != 0)
		{
			printf("��:%d", array[4]);

		}
	}
	
	return 0;
}