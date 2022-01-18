/**
*파일이름"21812160_차태현_Lab10 ”
*프로그램의 목적 및 기본 기능:
*  문자열정렬, 학생정보정렬,이진파일 출력,암호화
*
*프로그램 작성자: 21812160 차태현(2021년 5월13일),
*최종 수정 및 보완: 2021년 5월 13일 (차태현)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Mystring.h"
#include "Students.h"
#include "HandlingBinaryFile.h"
#include "Cipher.h"
#define MAX_NUM_WORDS 1000
#define MAX_WORD_LEN 20
#define NUM_STUDENTS 10
#define MAX_STRING_LEN 512
#define MAX_STR_LEN 100

extern Student students[NUM_STUDENTS];
void test_SelectionSortWords();
void test_RandomFileAccess_Student();
void test_BinaryFileDump();
void test_simple_cipher_text();
void main()
{
	int menu;
	while (1)
	{
		printf(" 1. Test selection sort for words\n");
		printf(" 2. Test random access file for students records\n");
		printf(" 3. Test binary file dump\n");
		printf(" 4. Test cipher text\n");
		printf(" 0. Quit\n");
		printf("Input menu : ");
		scanf("%d", &menu);
		if (menu == 0)
			break;
		switch (menu)
		{
		case 1:
		test_SelectionSortWords();
		break;
		case 2:
		test_RandomFileAccess_Student();
		break;
		case 3:
		test_BinaryFileDump();
		break;
		case 4:
		test_simple_cipher_text();
		break;
		default:
		break;
		}
	}
}

void test_SelectionSortWords()
{
	FILE* fin=NULL;//읽기용 파일
	FILE* fout=NULL;//쓰기용 파일
	char** word_array;//문자열을 받기위함
	int count=0,num=0;
	char data[MAX_WORD_LEN];//파일로부터 받아올 문자열

	word_array = (char**)calloc(MAX_NUM_WORDS, sizeof(char*));//동적배열생성
	for (int i = 0; i < MAX_NUM_WORDS; i++)
	{
		word_array[i] = (char*)calloc(MAX_WORD_LEN, sizeof(char));
	}

	fin = fopen("words.txt", "r");//읽기모드로 파일열기
	fout = fopen("sorted_words.txt", "w");//쓰기모드로 파일열기

	while (fscanf(fin, "%s", &data) != EOF)//파일로부터 문자열을 받아옴
	{
		strcpy(word_array[count], data);
		count++;
	}
	selectionSortWords(word_array,count, MAX_WORD_LEN);//선택정렬

	for (int j = 0; j < count; j++)
	{
		if ((num % 10 == 0) && (num != 0))//줄바꿈실행
			fprintf(fout, "\n");
		num++;
		
		fprintf(fout, "%20s", word_array[j]);//파일에 출력
		
	}

	fclose(fin);//파일닫기
	fclose(fout);
}

void test_RandomFileAccess_Student()
{
	FILE* fin = NULL;//읽기용 파일
	FILE* fout = NULL;//쓰기용 파일
	char student_record[MAX_STRING_LEN] = " ";//문자열을 담기위함
	int record_len,cur_pos;//문자열 길이와 커서가이동할거리

	fout = fopen("students.txt", "w");//쓰기모드로 파일열기
	printf("Array of students at initialization : \n");
	printStudents(students, NUM_STUDENTS);//화면에 학생정보출력
	printf("\n");
	sortStudents_by_ST_ID(students, NUM_STUDENTS);//선택정렬
	printf("Storing sorted students by increasing order of student ID intoSortedStudent.txt ....\n");
	fprintStudents(fout, students, NUM_STUDENTS);//파일에 정렬된학생정보 출력
	printStudents(students, NUM_STUDENTS);
	fprintf(fout, "\n");
	fclose(fout);//파일 닫기

	fin = fopen("students.txt", "r");//읽기모드로 파일열기
	fgets(student_record, MAX_STRING_LEN, fin);//문자열한개 받아오기
	record_len = strlen(student_record);//받아온 문자열길이 계산
	rewind(fin);//파일에 커서 처음으로 되돌리기
	printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n",record_len);

	for (int i = NUM_STUDENTS - 1; i >= 0; i--)
	{
		fseek(fin, (record_len+1)  * i, SEEK_SET);//커서를 offset만큼움직인다
		cur_pos = ftell(fin);
		printf("Current file_position : %3d\n", cur_pos);
		fgets(student_record, MAX_STRING_LEN, fin);//문자열을 파일로부터 받아온다
		printf("Student (%2d): %s", i, student_record);
	}

	fclose(fin);//파일닫기
}

void test_BinaryFileDump()
{
	FILE* fin, * fout;
	const char* fname ="students.txt";
	fin = fopen(fname, "rb");//이진파일 읽기모드로열기
	
	fout = fopen("Output.txt", "w");//파일 쓰기모드로열기
	
	printf("Dumping binary file (%s) ... \n", fname);
	dumpBinaryFile(fin, fout);//2진파일 입출력
	
	fclose(fin);//파일닫기
	fclose(fout);
}

void test_simple_cipher_text()
{
	/*FILE* fin;
	FILE* T_fout;
	FILE* D_fout;

	fin = fopen("fp_msg.txt", "r");//파일 읽기모드로 열기
	T_fout = fopen("Ciphered.txt", "w");//파일 쓰기모드로 열기

	cipherText(fin, T_fout, 0x69);//암호화
	fclose(fin);//파일닫기
	fclose(T_fout);//파일닫기

	T_fout = fopen("Ciphered.txt", "r");//파일 읽기모드로 열기
	D_fout = fopen("Deciphered.txt", "w");//파일 쓰기모드로열기

	deCipherText(T_fout, D_fout, 0x69);//복호화
	fclose(D_fout);//파일닫기
	fclose(T_fout);*/
	FILE* fp_msg, * fp_tx, * fp_rx, * fp_dump_msg, * fout;
	fp_msg = fopen("fp_msg.txt", "r");
	if (fp_msg == NULL)
	{
		printf("Error in file open - Message.txt !!\n");
		exit(-1);
	}
	fp_tx = fopen("Ciphered.txt", "w");
	if (fp_tx == NULL)
	{
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fout = fopen("Deciphered.txt", "w");
	if (fout == NULL)
	{
		printf("Error in file open - Output.txt !!\n");
		exit(-1);
	}
	printf("Generating cipher text with cipher-code (%#04x) ..\n", 0x69);
	cipherText(fp_msg, fp_tx, 0x69);
	fclose(fp_tx);
	rewind(fp_msg);
	fprintf(fout, "Binary dump of message.txt file: \n");
	dumpBinaryFile(fp_msg, fout);
	fp_tx = fopen("Ciphered.txt", "r");
	if (fp_tx == NULL)
	{
		printf("Error in file open - Transmit.txt !!\n");
		exit(-1);
	}
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Binary dump of ciphered document: \n");
	dumpBinaryFile(fp_tx, fout);
	rewind(fp_tx);
	printf("Generating de-ciphered text with cipher-code (%#04x) ..\n", 0x69);
	fprintf(fout, "\n=========================================\n");
	fprintf(fout, "Generating de-ciphered text with cipher-code (%#04x) ..\n", 0x69);
	deCipherText(fp_tx, fout, 0x69);
	fclose(fp_msg);
	fclose(fp_tx);
	fclose(fout);
}