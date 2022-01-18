/**
*�����̸�"21812160_������_Lab10 ��
*���α׷��� ���� �� �⺻ ���:
*  ���ڿ�����, �л���������,�������� ���,��ȣȭ
*
*���α׷� �ۼ���: 21812160 ������(2021�� 5��13��),
*���� ���� �� ����: 2021�� 5�� 13�� (������)
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
	FILE* fin=NULL;//�б�� ����
	FILE* fout=NULL;//����� ����
	char** word_array;//���ڿ��� �ޱ�����
	int count=0,num=0;
	char data[MAX_WORD_LEN];//���Ϸκ��� �޾ƿ� ���ڿ�

	word_array = (char**)calloc(MAX_NUM_WORDS, sizeof(char*));//�����迭����
	for (int i = 0; i < MAX_NUM_WORDS; i++)
	{
		word_array[i] = (char*)calloc(MAX_WORD_LEN, sizeof(char));
	}

	fin = fopen("words.txt", "r");//�б���� ���Ͽ���
	fout = fopen("sorted_words.txt", "w");//������� ���Ͽ���

	while (fscanf(fin, "%s", &data) != EOF)//���Ϸκ��� ���ڿ��� �޾ƿ�
	{
		strcpy(word_array[count], data);
		count++;
	}
	selectionSortWords(word_array,count, MAX_WORD_LEN);//��������

	for (int j = 0; j < count; j++)
	{
		if ((num % 10 == 0) && (num != 0))//�ٹٲ޽���
			fprintf(fout, "\n");
		num++;
		
		fprintf(fout, "%20s", word_array[j]);//���Ͽ� ���
		
	}

	fclose(fin);//���ϴݱ�
	fclose(fout);
}

void test_RandomFileAccess_Student()
{
	FILE* fin = NULL;//�б�� ����
	FILE* fout = NULL;//����� ����
	char student_record[MAX_STRING_LEN] = " ";//���ڿ��� �������
	int record_len,cur_pos;//���ڿ� ���̿� Ŀ�����̵��ҰŸ�

	fout = fopen("students.txt", "w");//������� ���Ͽ���
	printf("Array of students at initialization : \n");
	printStudents(students, NUM_STUDENTS);//ȭ�鿡 �л��������
	printf("\n");
	sortStudents_by_ST_ID(students, NUM_STUDENTS);//��������
	printf("Storing sorted students by increasing order of student ID intoSortedStudent.txt ....\n");
	fprintStudents(fout, students, NUM_STUDENTS);//���Ͽ� ���ĵ��л����� ���
	printStudents(students, NUM_STUDENTS);
	fprintf(fout, "\n");
	fclose(fout);//���� �ݱ�

	fin = fopen("students.txt", "r");//�б���� ���Ͽ���
	fgets(student_record, MAX_STRING_LEN, fin);//���ڿ��Ѱ� �޾ƿ���
	record_len = strlen(student_record);//�޾ƿ� ���ڿ����� ���
	rewind(fin);//���Ͽ� Ŀ�� ó������ �ǵ�����
	printf("\nRandom access to Sorted_students.txt file (Student record length: %d) ...\n",record_len);

	for (int i = NUM_STUDENTS - 1; i >= 0; i--)
	{
		fseek(fin, (record_len+1)  * i, SEEK_SET);//Ŀ���� offset��ŭ�����δ�
		cur_pos = ftell(fin);
		printf("Current file_position : %3d\n", cur_pos);
		fgets(student_record, MAX_STRING_LEN, fin);//���ڿ��� ���Ϸκ��� �޾ƿ´�
		printf("Student (%2d): %s", i, student_record);
	}

	fclose(fin);//���ϴݱ�
}

void test_BinaryFileDump()
{
	FILE* fin, * fout;
	const char* fname ="students.txt";
	fin = fopen(fname, "rb");//�������� �б���ο���
	
	fout = fopen("Output.txt", "w");//���� ������ο���
	
	printf("Dumping binary file (%s) ... \n", fname);
	dumpBinaryFile(fin, fout);//2������ �����
	
	fclose(fin);//���ϴݱ�
	fclose(fout);
}

void test_simple_cipher_text()
{
	/*FILE* fin;
	FILE* T_fout;
	FILE* D_fout;

	fin = fopen("fp_msg.txt", "r");//���� �б���� ����
	T_fout = fopen("Ciphered.txt", "w");//���� ������� ����

	cipherText(fin, T_fout, 0x69);//��ȣȭ
	fclose(fin);//���ϴݱ�
	fclose(T_fout);//���ϴݱ�

	T_fout = fopen("Ciphered.txt", "r");//���� �б���� ����
	D_fout = fopen("Deciphered.txt", "w");//���� ������ο���

	deCipherText(T_fout, D_fout, 0x69);//��ȣȭ
	fclose(D_fout);//���ϴݱ�
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