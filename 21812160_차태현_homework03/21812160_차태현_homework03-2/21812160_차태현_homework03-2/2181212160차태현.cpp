/**
*파일명:“calender.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 년도를 입력받아 달력을 출력하는프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 3월22일),
*최종 수정 및 보완: 2021년 3월 22일 (차태현)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완 내용
*차태현               2021/03/22   한달만 반복되는오류수정
*============================================================================
*/
#include<stdio.h>
#define WEEKDAY_AD01Jan01 MON // the weekday of AD Jan 1.
#define DAYS_PER_WEEK 7
#define NUM_MONTHS 13 
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTH {
	JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT,
	NOV, DEC
};
const char* weekDayName[DAYS_PER_WEEK] = { "SUN", "MON",
"TUE", "WED", "THR", "FRI", "SAT" };
const char* monthName[NUM_MONTHS] = { "", "January", "February",
"March", "April","May", "June", "July", "August", "September", "October",
"November", "December" };
bool isLeapYear(int y)

{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		return true;
	else
		return false;

}
int getDaysFromJan01AD01(int year, int month, int day)

{
	int daysFromAD01Jan01 = 0;
	int daysInyear;
	int daysInMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int y, m;

	for (y = 1; y < year; y++)
	{
		daysInyear = isLeapYear(y) ? 366 : 365;
		daysFromAD01Jan01 += daysInyear;
	}

	if (isLeapYear(year))
		daysInMonth[2] = 29;
	for (m = 1; m < month; m++)
	{
		daysFromAD01Jan01 += daysInMonth[m];
	}
	daysFromAD01Jan01 += day;

	return daysFromAD01Jan01;
}
void printCalendar(int year)
{
	int weekDay;
	int i,k;
	int daysFromJan01AD01 = 0;
	int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		
	daysFromJan01AD01 = getDaysFromJan01AD01(year, 1, 1);
	weekDay = (daysFromJan01AD01 )
		% DAYS_PER_WEEK;
	if (isLeapYear(year))
		daysInMonth[2] = 29;
	printf(">>>>>>> Calendar of %d <<<<<<<<\n", year);
	for (int month = JAN; month <= DEC; month++)
	{
		printf("%s\n", monthName[month]);
		printf("=====================================\n");
		for (int wk = SUN; wk <= SAT; wk++)
		{
			printf("%5s", weekDayName[wk]);
		}
		printf("\n-------------------------------------\n");

		   for (i = 0; i < weekDay; i++)
			    printf("     ");
		
			for (k = 1; k <= daysInMonth[month]; k++)
			{
				if (weekDay == 7)
				{
					printf("\n");
					weekDay = 0;
				}
				weekDay++;
				printf("%5d", k);
				
			}
		

		printf("\n=====================================\n");
	}
}
int main()
{  
	int year;
	scanf_s("%d", &year);
	printCalendar(year);
}