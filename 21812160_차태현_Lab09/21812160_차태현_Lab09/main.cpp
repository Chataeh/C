/**
*파일이름"21812160_차태현_Lab09 ”
*프로그램의 목적 및 기본 기능:
*  구조체를 사용하여 사람의 정보를 순서에 따라 출력.
*
*프로그램 작성자: 21812160 차태현(2021년 5월5일),
*최종 수정 및 보완: 2021년 5월 5일 (차태현)
*/
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"Date.h"//사용자 정의헤더
#include"Telephone_Number.h"//사용자 정의헤더
#include "Student.h"//사용자 정의헤더
#define MAX_NUM_STUDENTS 100

void main()
{
	int num_students = 0;
	int menu;
	Student* pST_GPA_max, * pST_GPA_min;
	extern Student students[];//다른 소스파일에있는 배열정보 받아오기
	for (int i = 0; i < MAX_NUM_STUDENTS; i++)//사람의 수세기
	{
		if (students[i].st_id == -1)
			break;
		else
			num_students++;
	}
	printf("Number of studetns = %d\n", num_students);
	while (1)
	{
		printf("\n");
		printf(" 1 : print student records\n");
		printf(" 2 : calculate statistics GPA (max, min, avg) of students' \n");
		printf(" 3 : search students of best GPA and worst GPA\n");
		printf(" 4 : sort students by student ID\n");
		printf(" 5 : sort students by GPA\n");
		printf(" 6 : sort students by name\n");
		printf(" 7 : sort students by date of birth\n");
		printf(" 8 : sort studetns by telephone number\n");
		printf("0 : Quit\n");
		printf("Input menu = ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		switch (menu)
		{
		case 1:
			printStudents(students, num_students);//학생정보 출력
			printf("\n");
			break;
		case 2:
			statisticsGPA(students, num_students);//성적의 최대 최소 평균값 출력
			break;
		case 3:
			pST_GPA_max = searchBestGPAStudent(students, num_students);//성적이 가장높은학생의 정보
			pST_GPA_min = searchWorstGPAStudent(students, num_students);//성적이 가장 낮은 학생의 정보
			printf("Student with best GPA : ");
			printStudent(pST_GPA_max);
			printf("\n");
			printf("Student with worst GPA : ");
			printStudent(pST_GPA_min);
			printf("\n");
			break;
		case 4:
			sortStudents_by_ST_ID(students, num_students);//학번 오름차순으로 정렬
			printf("After sorting students by increasing order of student ID:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 5:
			sortStudents_by_GPA(students, num_students);//성적 내림차순 정렬
			printf("After sorting students by decreasing order of GPA:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 6:
			sortStudents_by_name(students, num_students);//이름 오름차순 정렬
			printf("After sorting students by increasing order of student name:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
			
		case 7:
			sortStudents_by_BirthDate(students, num_students);//생년월일 오름차순 정렬
			printf("After sorting students by increasing order of student birth date:\n");
			printStudents(students, num_students);
			printf("\n");
			break;
		case 8:
			sortStudents_by_TelNumber(students, num_students);//전화번호 오름차순 정렬
			printf("After sorting students by increasing order of student's telephonenumber:\n");
				printStudents(students, num_students);
			printf("\n");
			break;
		default:
			break;
		}
		shuffleStudents(students, num_students); // 배열 섞기 
	}
}

