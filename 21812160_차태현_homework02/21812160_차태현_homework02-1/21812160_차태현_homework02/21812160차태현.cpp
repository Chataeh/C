/**
*���ϸ�:��trans second.cpp��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� �ʸ� �Է¹޾� �ð� �� �ʷ� ��ȯ�ϴ����α׷��Դϴ�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��11��),
*���� ���� �� ����: 2021�� 3�� 11�� (������)
*
*/
#include <stdio.h>

int main()
{
	int sec;
	int min, hour,trans;
	
	
	printf("�ʸ� �Է��Ͻÿ�:");
	scanf_s("%d", &sec);
	

	trans = sec % 60;// �� ���ϱ�
	min = (sec / 60) % 60;//�� ���ϱ�
	hour = (sec / 60) / 60; //�ð� ���ϱ�
	
	printf("%d�ʴ� %d�ð�%d��%d���Դϴ�", sec, hour, min, trans);


	return 0;
}