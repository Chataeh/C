#include <stdio.h>
int printlnt_Bits(int num);

int printlnt_Bits(int num)
{
	
	while (num != 0)
	{
		printf("%#32d ", num % 2);

		num = num / 2;
		
		return 0;
	}

}
int main()
{

	int num;
	scanf_s("%d", &num);
	printflnt_Bits(num);
	

	return 0;
}