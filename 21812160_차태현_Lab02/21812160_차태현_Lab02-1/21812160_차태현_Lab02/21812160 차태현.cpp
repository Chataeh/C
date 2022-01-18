/**
*파일명:“Reverseoder”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 10자리내 10진수를 입력받아 역순으로 출력하는 프로그램입니다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월9일),
*최종 수정 및 보완: 2021년 3월 10일 (차태현)
*============================================================================
*/
#include <stdio.h>

int main(void)
{
	 unsigned int num;  // %연산은 int형에서만 가능하고 10자리 10진수를 모두 수용할 수 있는 범위의 자료형은 long long
	

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