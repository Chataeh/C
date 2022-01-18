#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"Date.h"
#include"Telephone_Number.h"
#include "Student.h"

void printStudent(Student *pSt)//학생 정보출력
{
	printf("Student [ID:%08d,%-10s,GPA: %5.2lf,", pSt->st_id, pSt->name, pSt->gpa);
	printDate(pSt->birth_date);
	printf(",");
	printTelephoneNumber(pSt->tel_number);
	printf("]");
}

void printStudents(Student* stArray, int num_students)//학생정보 배열 출력
{
	for (int i = 0; i < num_students; i++)
	{
		printStudent(stArray);
		printf("\n");
		stArray++;
	}
}

void shuffleStudents(Student students[], int num_students)// 학생정보 섞기
{
	int st_1, st_2;
	Student st_temp;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < num_students; i++)
	{
		st_1 = rand() % num_students;
		st_2 = rand() % num_students;
		
		st_temp = students[st_1]; //st_1 ,st_2번째 배열 위치교환
		students[st_1] = students[st_2];
		students[st_2] = st_temp;
	}
}

void statisticsGPA(Student students[], int num_students)//성적의 최소,최대,평균값구하기
{
	Student* pSt, * pSt_max, * pSt_min;
	pSt = pSt_max = pSt_min = students;
	double GPA_max, GPA_min, GPA_avg, GPA_sum = 0.0;
	GPA_max = GPA_min = GPA_sum = pSt->gpa;
	for (int i = 1; i < num_students; i++)
	{
		pSt = &students[i];
		for (int j = i + 1; j <= num_students; j++)
		{
			if (pSt->gpa > pSt_max->gpa)//성적의 최대값
				GPA_max = students[i].gpa;
			if (pSt->gpa < pSt_min->gpa)//성적의 최솟값
				GPA_min = students[i].gpa;
		}
			GPA_sum += pSt->gpa;
	}
	GPA_avg = GPA_sum / (double)num_students;//성적의 평균값
	printf("GPA_max(%5.2lf),GPA_min(%5.2lf),GPA_avg(%5.2lf)\n", GPA_max, GPA_min, GPA_avg);
}

Student* searchBestGPAStudent(Student students[], int num_students)// 성적이 가장 높은 학생
{
	Student* pSt, * pSt_max;
	pSt = pSt_max = students;
	for (int i = 1; i < num_students; i++)
	{
		pSt = &students[i];
		if (pSt->gpa > pSt_max->gpa)//성적의 최대값보다 pSt의 성적값이 클때 pSt의 값이 성적이 가장 높은학생의정보	
			pSt_max = pSt;
	}
	return pSt_max;
}

Student* searchWorstGPAStudent(Student students[], int num_students)//성적이 가장 낮은 학생
{
	Student* pSt, * pSt_min;
	pSt= pSt_min = students;
	
	for (int i = 1; i < num_students; i++)
	{
		pSt = &students[i];
		if (pSt->gpa < pSt_min->gpa)//성적의 최소값보다 pSt의 성적값이 작때 pSt의 값이 성적이 가장 낮은학생의정보	
			pSt_min=pSt;
	}
	return pSt_min;
}

void sortStudents_by_ST_ID(Student students[],int num_students)//학번순으로 오름차순정렬
{
	Student* pSt, * pSt_min;
	Student temp;
	int st_id_min;

	for (int i = 0; i < num_students; i++)//선택정렬실행
	{
		pSt_min = pSt = &students[i];
		st_id_min = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pSt = &students[j];
			if (pSt->st_id < pSt_min->st_id)
			{
				pSt_min = pSt;
				st_id_min = j;
			}
		}
		if (st_id_min != i)
		{
			temp = students[i];
			students[i] = students[st_id_min];
			students[st_id_min] = temp;
		}
	}
}

void sortStudents_by_GPA(Student students[], int num_students)//성적 내림차순 정렬
{
	Student* pSt, * pSt_max;
	Student temp;
	int st_max;
	for (int i = 0; i < num_students; i++)//선택정렬실행
	{
		pSt_max = pSt = &students[i];
		st_max = i;
		for (int j = i + 1; j < num_students; j++)
			for (int j = i + 1; j < num_students; j++)
			{
				pSt = &students[j];
				if (pSt->gpa < pSt_max->gpa)
				{
					pSt_max = pSt;
					st_max = j;
				}
			}
		if (st_max != i)
		{
			temp = students[i];
			students[i] = students[st_max];
			students[st_max] = temp;
		}
	}
}

void sortStudents_by_name(Student students[], int num_students)//이름 오름차순 정렬
{
	Student* pSt, * pSt_min;
	Student temp;
	int st_name_min;

	for (int i = 0; i < num_students; i++)//선택정렬 실행
	{
		pSt_min = pSt = &students[i];
		st_name_min = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pSt = &students[j];
			if (strcmp(pSt->name, pSt_min->name) < 0)
			{
				pSt_min = pSt;
				st_name_min = j;
			}
		}
		if (st_name_min != i)
		{
			temp = students[i];
			students[i] = students[st_name_min];
			students[st_name_min] = temp;
		}
	}
}

void sortStudents_by_BirthDate(Student students[], int num_students)//생일 오름차순정렬
{
	Student* pSt, * pSt_min;
	Student temp;
	int st_date_min;

	for (int i = 0; i < num_students; i++)//선택정렬 실행
	{
		pSt_min = pSt = &students[i];
		st_date_min = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pSt = &students[j];
			if (compareDate(pSt->birth_date,pSt_min->birth_date)<0)//문자열값 비교
			{
				pSt_min = pSt;
				st_date_min = j;
			}
		}
		if (st_date_min != i)
		{
			temp = students[i];
			students[i] = students[st_date_min];
			students[st_date_min] = temp;
		}
	}
}

void sortStudents_by_TelNumber(Student students[], int num_students)//전화번호 오름차순 정렬
{
	Student* pSt, * pSt_min;
	Student temp;
	int st_telno_min;

	for (int i = 0; i < num_students; i++)//선택정렬
	{
		pSt_min = pSt = &students[i];
		st_telno_min = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pSt = &students[j];
			if (compareTelNumber(pSt->tel_number, pSt_min->tel_number) < 0)//전화번호 값비교
			{
				pSt_min = pSt;
				st_telno_min = j;
			}
		}
		if (st_telno_min != i)
		{
			temp = students[i];
			students[i] = students[st_telno_min];
			students[st_telno_min] = temp;
		}
	}
}