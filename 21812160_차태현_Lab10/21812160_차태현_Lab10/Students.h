#ifndef S
#define S

#define MAX_NAME_LEN 20

typedef struct //구조체 Date정의
{
	int year;
	int month;
	int day;
}Date;

typedef struct// 구조체Tel_Number 정의
{
	unsigned short nation_code;
	unsigned short region_code;
	unsigned short switch_no;
	unsigned short line_no;

}Tel_Number;

typedef struct //구조체 Student 정의
{
	int st_id;
	char name[MAX_NAME_LEN];
	Date birth_date;
	Tel_Number tel_number;
	double gpa;
}Student;

void sortStudents_by_ST_ID(Student students[], int num_students);//선택정렬
void fprintStudents(FILE* fout, Student* stArray, int num_students);//학생정보 배열 파일출력
void printStudents(Student* stArray, int num_students);//학생정보 배열 출력
#endif
