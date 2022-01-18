/**
*파일명:“16진수 변환.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 16진수를 입력받아 10진수, 8진수, 2진수 표현과 Bit-wise 계산
*
*프로그램 작성자: 21812160 차태현(2021년 3월9일),
*최종 수정 및 보완: 2021년 3월 10일 (차태현)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완 내용
*차태현               2021년3월 10일 Bitwise계산부분 추가
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
		printf("%d", (a >> i) & 1); //각 비트 값 계산 후 출력
		if ((i%8) == 0) //8비트마다 띄어쓰기
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