/**
*���ϸ�:��16���� ��ȯ.cpp��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� 16������ �Է¹޾� 10����, 8����, 2���� ǥ���� Bit-wise ���
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��9��),
*���� ���� �� ����: 2021�� 3�� 10�� (������)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���� ����
*������               2021��3�� 10�� Bitwise���κ� �߰�
* 
*============================================================================
*/
#include <stdio.h>
#define bits 32
void printlnt_Bits(int a)
{
	int i;
	
	for (i = bits-1; i >= 0; i--)
	{
		printf("%d", (a >> i) & 1); //�� ��Ʈ �� ��� �� ���
		if ((i%8) == 0) //8��Ʈ���� ����
		printf(" ");
	}
}



int main()
{
	int x, y;

	printf("Input first hexadecimal number in(0x00000000~0xFFFFFFFF):");
	scanf_s("%X", &x);

	printf("x=%#X = %d (in decimal) = %o (in octal)\n", x, x, x);
	printf("=(in bits)");
	printlnt_Bits(x);


	printf("\nInput second hexadecimal number in(0x00000000~0xFFFFFFFF):");
	scanf_s("%X", &y);

	printf("x=%#X = %d (in decimal) = %o (in octal)\n", y, y, y);
	printf("=(in bits)");
	printlnt_Bits(y);


	printf("\nx+y=%X\nx-y=%X\n", x + y, x - y);
	printlnt_Bits(x + y);
	printf("\n");
	printlnt_Bits(x - y);

	printf("\n\nBitwise AND : %#X & %#X => %#X\n  ", x, y, x & y);
	printlnt_Bits(x);
	printf("\n& ");
	printlnt_Bits(y);
	printf("\n-------------------------------------\n  ");
	printlnt_Bits(x & y);


	printf("\n\nBitwise OR : %#X | %#X => %#X\n  ", x, y, x | y);
	printlnt_Bits(x);
	printf("\n| ");
	printlnt_Bits(y);
	printf("\n-------------------------------------\n  ");
	printlnt_Bits(x | y);


	printf("\n\nBitwise XOR : %#X ^ %#X => %#X\n  ", x, y, x ^ y);
	printlnt_Bits(x);
	printf("\n^ ");
	printlnt_Bits(y);
	printf("\n-------------------------------------\n  ");
	printlnt_Bits(x ^ y);


	printf("\n\nBitwise Shift Left : %#X << 0X3 => %#X\n   ", x, x << 3);
	printf("\n<< ");
	printlnt_Bits(x);
	printf("\n--------------------------------------\n   ");
	printlnt_Bits(x << 3);


	printf("\n\nBitwise Shift Right : %#X >> 0X3 => %#X\n   ", y, y >> 3);
	printf("\n>> ");
	printlnt_Bits(y);
	printf("\n--------------------------------------\n   ");
	printlnt_Bits(y >> 3);

	printf("\n\nBitwise NOT : ~ %#X => %#X\n  ", y,~y);
	printf("\n~ ");
	printlnt_Bits(y);
	printf("\n-------------------------------------\n  ");
	printlnt_Bits(~y);
	return 0;
}