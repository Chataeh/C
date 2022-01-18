#include<stdio.h>
#include"Students.h"

#define NUM_STUDENTS 10
Student students[NUM_STUDENTS] =
{
{ 21711000, "Kim, G-M", { 1990, 10, 5 }, { 82, 53, 805, 1234 }, 3.57 },
{ 21611075, "Yoon, S-M", { 1990, 4, 5 }, { 82, 53, 811, 1550 }, 4.37 },
{ 21411015, "Hwang, S-S", { 1989, 1, 10 }, { 82, 53, 817, 1005 }, 2.72 },
{ 21611054, "Lee, K-M", { 1991, 5, 15 }, { 82, 10, 9112, 9876 }, 3.35 },
{ 21611340, "Hong, G-M", { 1990, 2, 5 }, { 82, 55, 810, 5678 }, 3.89 },
{ 21712056, "Jang, S-M", { 1990, 3, 15 }, { 82, 10, 9112, 1600 }, 4.42 },
{ 21411017, "Park, S-S", { 1989, 7, 10 }, { 82, 34, 817, 1098 }, 4.12 },
{ 21511053, "Choi, Y-H", { 1992, 9, 25 }, { 82, 53, 845, 5764 }, 3.85 },
{ 21411017, "Shin, D-J", { 1988, 10, 3 }, { 82, 31, 817, 1038 }, 3.21 },
{ 21511053, "Kwak, S-B", { 1994, 11, 15 }, { 82, 2, 897, 8778 }, 4.45 },
};

void sortStudents_by_ST_ID(Student students[], int num_students)//�й������� ������������
{
	Student* pSt, * pSt_min;
	Student temp;
	int st_id_min;

	for (int i = 0; i < num_students; i++)//�������Ľ���
	{
		pSt_min = pSt = &students[i];//�ʱ� �ּҰ�����
		st_id_min = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pSt = &students[j];
			if (pSt->st_id < pSt_min->st_id)//�й����� �� �ּҰ�����
			{
				pSt_min = pSt;
				st_id_min = j;
			}
		}
		if (st_id_min != i)//�ʱ��� �ּҰ��� �ٸ��� ��ġ����
		{
			temp = students[i];
			students[i] = students[st_id_min];
			students[st_id_min] = temp;
		}
	}
}
void fprintDate(FILE* fout,Date date)
{

	fprintf(fout,"(%4d,%2d,%2d)", date.year, date.month, date.day);//������� �������

}

void fprintTelephoneNumber(FILE* fout, Tel_Number tel_no) //��ȭ��ȣ �������
{
	fprintf(fout,"(tel: +%2d - %03d - %04d - %04d)", tel_no.nation_code, tel_no.region_code, tel_no.switch_no, tel_no.line_no);
}

void fprintStudent(FILE* fout, Student* pSt)//�л� �����������
{
	fprintf(fout,"Student [ID:%08d,%-10s,GPA: %5.2lf,", pSt->st_id, pSt->name, pSt->gpa);
	fprintDate(fout,pSt->birth_date);
	fprintf(fout,",");
	fprintTelephoneNumber(fout,pSt->tel_number);
	fprintf(fout,"]");
}

void fprintStudents(FILE* fout, Student* stArray, int num_students)//�л����� �迭 �������
{
	for (int i = 0; i < num_students; i++)
	{
		fprintStudent(fout,stArray);
		fprintf(fout,"\n");
		stArray++;
	}
}

void printDate( Date date)
{

	printf("(%4d,%2d,%2d)", date.year, date.month, date.day);//������� ���

}

void printTelephoneNumber(Tel_Number tel_no) //��ȭ��ȣ ���
{
	printf("(tel: +%2d - %03d - %04d - %04d)", tel_no.nation_code, tel_no.region_code, tel_no.switch_no, tel_no.line_no);
}

void printStudent(Student* pSt)//�л� �������
{
	printf("Student [ID:%08d,%-10s,GPA: %5.2lf,", pSt->st_id, pSt->name, pSt->gpa);
	printDate(pSt->birth_date);
	printf(",");
	printTelephoneNumber(pSt->tel_number);
	printf("]");
}

void printStudents( Student* stArray, int num_students)//�л����� �迭 ���
{
	for (int i = 0; i < num_students; i++)
	{
		printStudent(stArray);
		printf("\n");
		stArray++;
	}
}