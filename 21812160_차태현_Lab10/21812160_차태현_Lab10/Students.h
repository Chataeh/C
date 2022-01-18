#ifndef S
#define S

#define MAX_NAME_LEN 20

typedef struct //����ü Date����
{
	int year;
	int month;
	int day;
}Date;

typedef struct// ����üTel_Number ����
{
	unsigned short nation_code;
	unsigned short region_code;
	unsigned short switch_no;
	unsigned short line_no;

}Tel_Number;

typedef struct //����ü Student ����
{
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double gpa;
}Student;

void sortStudents_by_ST_ID(Student students[], int num_students);//��������
void fprintStudents(FILE* fout, Student* stArray, int num_students);//�л����� �迭 �������
void printStudents(Student* stArray, int num_students);//�л����� �迭 ���
#endif
