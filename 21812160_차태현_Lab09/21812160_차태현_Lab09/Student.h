#ifndef  S_H
#define S_H

#include "Date.h"
#include "Telephone_Number.h"
#define MAX_NAME_LEN 20
#define NUM_STUDENTS 10

typedef struct //구조체 Student 정의
{
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double gpa;
}Student;

void printStudent(Student* pSt);//학생정보출력
void printStudents(Student* stArray, int num_students);//학생정보 배열 출력
void shuffleStudents(Student students[], int num_students);//학생정보 위치 섞기
void statisticsGPA(Student students[], int num_students);//성적의 최대 최소 평균값계산
Student* searchBestGPAStudent(Student students[], int num_students);//성적이 가장 높은학생정보
Student* searchWorstGPAStudent(Student students[], int num_students);//성적이 가장낮은 학생정보
void sortStudents_by_ST_ID(Student students[], int num_students);//학번순 오름차순
void sortStudents_by_GPA(Student students[], int num_students);//성적순 내림차순
void sortStudents_by_name(Student students[], int num_students);//이름순 오름차순
void sortStudents_by_BirthDate(Student students[], int num_students);//생일순 오름차순
void sortStudents_by_TelNumber(Student students[], int num_students);//전화번호순 오름차순

#endif // ! S_H
