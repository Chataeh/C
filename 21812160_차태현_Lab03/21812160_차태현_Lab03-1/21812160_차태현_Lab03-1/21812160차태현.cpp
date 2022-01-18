/**
*파일명:“Find weekday.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 년원일을 입력받아 1년 1월1일부터 며칠이지났는가와 요일을 알려주는프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 3월17일),
*최종 수정 및 보완: 2021년 3월 17일 (차태현)
*/
#include <stdio.h>
#include <stdbool.h>

bool isLeapYear(int y)
{
	
	if ((y % 4 == 0 && y %100 != 0) || y % 400 == 0)

		return true;
	else
		return false;
}

int getDaysFromJan01AD01(int year, int month, int day)
{
	int daysFromAD01Jan01=0;
	int daysInyear;
	int daysInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int y , m ;
	for (y = 1; y < year; y++)
	{
		daysInyear = isLeapYear(y) ? 366 : 365;
		daysFromAD01Jan01 += daysInyear;
	}
    if(isLeapYear(year))
		daysInMonth[2]=29;
	for (m = 1; m < month; m++)
	{
		daysFromAD01Jan01 += daysInMonth[m];
	}

	daysFromAD01Jan01 += day;
	
	
	return daysFromAD01Jan01;

	
}

int main(void)
{
	int year, month, day;
	int i;
	printf("Input year, month, day to check:");
	scanf_s("%d %d %d",&year,&month,&day);
	
	if (month == 1)
		printf("The week day of January %d, %d is %d-th day from Jan 1,1", day,year, getDaysFromJan01AD01(year, month, day) );
	else if (month == 2)
		printf("The week day of February %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 3)
		printf("The week day of March %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 4)
		printf("The week day of April %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 5)
		printf("The week day of May %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 6)
		printf("The week day of Jun %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 7)
		printf("The week day of July %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 8)
		printf("The week day of August %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 9)
		printf("The week day of September %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 10)
		printf("The week day of October %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 11)
		printf("The week day of November %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));
	else if (month == 12)
		printf("The week day of December %d, %d is %d-th day from Jan 1,1", day, year, getDaysFromJan01AD01(year, month, day));



	if (getDaysFromJan01AD01(year, month, day) % 7 == 1)
	    printf("(MON)");
	else if (getDaysFromJan01AD01(year, month, day) % 7 == 2)
		printf("(TUE)");
	else if (getDaysFromJan01AD01(year, month, day) % 7 == 3)
		printf("(WED)");
	else if (getDaysFromJan01AD01(year, month, day) % 7 == 4)
		printf("(THR)");
	else if (getDaysFromJan01AD01(year, month, day) % 7 == 5)
		printf("(FRI)");
	else if (getDaysFromJan01AD01(year, month, day) % 7 == 6)
		printf("(SAT)");
	else if (getDaysFromJan01AD01(year, month, day) % 7 == 0)
		printf("(SUN)");

	printf("\n\n");


	for (i = 0; i < 11; i++)
	{
		year = 2011 + i;


		printf("The week day of January 1, %d is %d-th day from Jan 1,1", year, getDaysFromJan01AD01(year,1, 1));

		if (getDaysFromJan01AD01(year, 1, 1) % 7 == 1)
			printf("(MON)");
		else if (getDaysFromJan01AD01(year, 1, 1) % 7 == 2)
			printf("(TUE)");
		else if (getDaysFromJan01AD01(year, 1, 1) % 7 == 3)
			printf("(WED)");
		else if (getDaysFromJan01AD01(year, 1, 1) % 7 == 4)
			printf("(THR)");
		else if (getDaysFromJan01AD01(year, 1, 1) % 7 == 5)
			printf("(FRI)");
		else if (getDaysFromJan01AD01(year, 1, 1) % 7 == 6)
			printf("(SAT)");
		else if (getDaysFromJan01AD01(year, 1, 1) % 7 == 0)
			printf("(SUN)");


		printf("\n");
	}

	return 0;
}