#include <stdio.h>

void printlnt_Bits(int a)
{
	int i;
	scanf_s("%d", &a);

	for (i = 31; i >= 0; i--)
	{
		printf("%d", (a >> i) & 1);

	}
}

