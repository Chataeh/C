/**
*파일명:“multiplication.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 12단까지의 곱셈을하는 프로그램이다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월19일),
*최종 수정 및 보완: 2021년 3월 19일 (차태현)
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
	printf("      ㅣ");
	for (i = 0; i < size; i++)
		printf("%5d", x[i]);
	printf("\n=======+============================================================\n");
	
	for (i = 0; i < size; i++)
	{
		printf("%5d ㅣ", i+1);
		for (j = 0; j < size; j++)
		{
			array[i][j] = x[i] * (j+1);
			printf("%5d", array[i][j]);
		}
		printf("\n");
	
	}

	
	return 0;
}