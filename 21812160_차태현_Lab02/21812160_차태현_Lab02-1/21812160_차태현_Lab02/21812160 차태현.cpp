/**
*���ϸ�:��Reverseoder��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� 10�ڸ��� 10������ �Է¹޾� �������� ����ϴ� ���α׷��Դϴ�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��9��),
*���� ���� �� ����: 2021�� 3�� 10�� (������)
*============================================================================
*/
#include <stdio.h>

int main(void)
{
	 unsigned int num;  // %������ int�������� �����ϰ� 10�ڸ� 10������ ��� ������ �� �ִ� ������ �ڷ����� long long
	

	printf("Input positive decimal number (upto 10 digits):");
	scanf_s("%u", &num);
	printf("Digits in reverse order:");
	
	while (num != 0)
	{
		printf("%u ", num%10);
		
		num=num / 10;
		
		
	}

	
	return 0;
}