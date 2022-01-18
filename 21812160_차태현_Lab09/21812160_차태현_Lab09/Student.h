#ifndef  S_H
#define S_H

#include "Date.h"
#include "Telephone_Number.h"
#define MAX_NAME_LEN 20
#define NUM_STUDENTS 10

typedef struct //����ü Student ����
{
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double gpa;
}Student;

void printStudent(Student* pSt);//�л��������
void printStudents(Student* stArray, int num_students);//�л����� �迭 ���
void shuffleStudents(Student students[], int num_students);//�л����� ��ġ ����
void statisticsGPA(Student students[], int num_students);//������ �ִ� �ּ� ��հ����
Student* searchBestGPAStudent(Student students[], int num_students);//������ ���� �����л�����
Student* searchWorstGPAStudent(Student students[], int num_students);//������ ���峷�� �л�����
void sortStudents_by_ST_ID(Student students[], int num_students);//�й��� ��������
void sortStudents_by_GPA(Student students[], int num_students);//������ ��������
void sortStudents_by_name(Student students[], int num_students);//�̸��� ��������
void sortStudents_by_BirthDate(Student students[], int num_students);//���ϼ� ��������
void sortStudents_by_TelNumber(Student students[], int num_students);//��ȭ��ȣ�� ��������

#endif // ! S_H
