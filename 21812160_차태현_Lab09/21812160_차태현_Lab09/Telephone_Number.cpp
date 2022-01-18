#include<stdio.h>
#include"Telephone_Number.h"

void printTelephoneNumber(Tel_Number tel_no) //전화번호 출력
{
	printf("(tel: +%2d - %03d - %04d - %04d)", tel_no.nation_code, tel_no.region_code, tel_no.switch_no, tel_no.line_no);
}

int compareTelNumber(Tel_Number tn1, Tel_Number tn2)//전화번호 오름차순정렬을 위한 전화번호값비교
{
	if (tn1.nation_code > tn2.nation_code)
		return 1;
	else if (tn1.nation_code < tn2.nation_code)
		return -1;
	else if ((tn1.nation_code = tn2.nation_code) && (tn1.region_code > tn2.region_code))
		return 1;
	else if ((tn1.nation_code = tn2.nation_code) && (tn1.region_code < tn2.region_code))
		return -1;
	else if ((tn1.nation_code = tn2.nation_code) && (tn1.region_code = tn2.region_code) && (tn1.switch_no > tn2.switch_no))
		return 1;
	else if ((tn1.nation_code = tn2.nation_code) && (tn1.region_code = tn2.region_code) && (tn1.switch_no < tn2.switch_no))
		return -1;
	else if ((tn1.nation_code = tn2.nation_code) && (tn1.region_code = tn2.region_code) && (tn1.switch_no = tn2.switch_no) && (tn1.line_no > tn2.line_no))
		return 1;
	else if ((tn1.nation_code = tn2.nation_code) && (tn1.region_code = tn2.region_code) && (tn1.switch_no = tn2.switch_no) && (tn1.line_no < tn2.line_no))
		return -1;
	else
		return 0;


}