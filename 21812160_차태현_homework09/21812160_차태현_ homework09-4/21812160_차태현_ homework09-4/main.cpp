/**
*�����̸�" 21812160_������_homework09-4��
*���α׷��� ���� �� �⺻ ���:
*  ���Ҽ��� ���� �Է¹��� �� ���� �� �������� ����.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 5��7��),
*���� ���� �� ����: 2021�� 5�� 7�� (������)
*/
#include <stdio.h>
#include "Cmplx.h"//����� �������
void main()
{
	Cmplx cmplxs[7]; // ����ü �迭����
	cmplxs[0] = inputCmplx();//�迭 0�� ���Ҽ����Է�
	cmplxs[1] = inputCmplx();//�迭 1�� ���Ҽ����Է�
	printf("cmplxs[0] = "); printCmplx(cmplxs[0]); printf("\n");
	printf("cmplxs[1] = "); printCmplx(cmplxs[1]); printf("\n");
	cmplxs[2] = cmplxAdd(cmplxs[0], cmplxs[1]);//���Ҽ� ���ϱ�
	printf("cmplxs[2] = cmplxs[0] + cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" + "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[2]); printf("\n");
	cmplxs[3] = complxSubtract(cmplxs[0], cmplxs[1]);//���Ҽ� ����
	printf("cmplxs[3] = cmplxs[0] - cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" - "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[3]); printf("\n");
	cmplxs[4] = complxMultiply(cmplxs[0], cmplxs[1]);//���Ҽ� ����
	printf("cmplxs[4] = cmplxs[0] * cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" * "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[4]); printf("\n");
	cmplxs[5] = cmplxDivide(cmplxs[0], cmplxs[1]);//���Ҽ� ������
	printf("cmplxs[5] = cmplxs[0] / cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" / "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[5]); printf("\n");
	cmplxs[6] = complxMultiply(cmplxs[1], cmplxs[5]);
	printf("cmplxs[6] = cmplxs[1] * cmplxs[5] = \n ");
	printCmplx(cmplxs[1]); printf(" * "); printCmplx(cmplxs[5]); printf(" = "); printCmplx(cmplxs[6]); printf("\n");
	printf("Before sorting complexs: \n");
	for (int i = 0; i < 7; i++)//���Ҽ� ���
	{
		printf("cmplxs[%d] = ", i); printCmplx(cmplxs[i]);
		printf("\n");
	}
	quickSortCmplx(cmplxs, 7);//���������� ����
	printf("Sorted complexs: \n");
	for (int i = 0; i < 7; i++)//������ ���
	{
		printf("cmplxs[%d] = ", i); printCmplx(cmplxs[i]);
		printf("\n");
	}
}