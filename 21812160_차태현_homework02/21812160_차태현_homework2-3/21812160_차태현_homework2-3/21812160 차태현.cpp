/**
*파일명:“최대 만단위 정수 차례로 출력.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 !~32765의 정수를 입력받아 각자리 값을 구하는 프로그램입니다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월12일),
*최종 수정 및 보완: 2021년 3월 12일 (차태현)
*
*/
#include <stdio.h>

int main()
{
	int array[5];

	int num;
	
	
	
	printf("1~32765사이의 수를 입력하시오:");
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
			printf("만:%d ", array[0]);
			printf("천:%d ", array[1]);
			printf("백:%d ", array[2]);
			printf("십:%d ", array[3]);
			printf("일:%d", array[4]);

		}
		if (array[0] == 0 && array[1] != 0)
		{
			printf("천:%d ", array[1]);
			printf("백:%d ", array[2]);
			printf("십:%d ", array[3]);
			printf("일:%d", array[4]);

		}

		if (array[0] == 0 && array[1] == 0 && array[2] != 0)
		{
			printf("백:%d ", array[2]);
			printf("십:%d ", array[3]);
			printf("일:%d", array[4]);

		}

		if (array[0] == 0 && array[1] == 0 && array[2] == 0 && array[3] != 0)
		{
			printf("십:%d ", array[3]);
			printf("일:%d", array[4]);

		}

		if (array[0] == 0 && array[1] == 0 && array[2] == 0 && array[3] == 0 && array[4] != 0)
		{
			printf("일:%d", array[4]);

		}
	}
	
	return 0;
}