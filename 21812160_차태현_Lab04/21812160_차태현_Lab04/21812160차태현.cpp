/*
* 프로그램이름:전자피아노
* 프로그램의 목적 및 기본기능:키보드를 통해 문자를입력받아 소리로 반환하여 피아노처럼 키보드를사용한는 프로그램
* 
* 프로그램 작성자:21812160 차태현(2021년03월23일)
* 
* 최종 수정 및 보완: 2021년 3월 23일
* 
*
*/ 
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

int mappingKey_to_Freq(char key, char alt);

int main(void)
{
	char ch;
	char alt_on = 0;
	int freq=0;
	int duration = 100;

	printf("\nSimple Electric Piano!!\n");
	printf("'A'~'J': octave 8 도 레 미 파  솔 라 시\n");
	printf("'Z'~'M': octave 7 도 레 미 파  솔 라 시\n");
	printf("'q'~'u': octave 6 도 레 미 파  솔 라 시\n");
	printf("'a'~'j': octave 5 도 레 미 파  솔 라 시\n");
	printf("'z'~'m': octave 4 도 레 미 파  솔 라 시\n");
	printf("input next key:\n");

	while ((ch=_getch()) != 27)
	{
		alt_on = 0;
		if (GetAsyncKeyState(VK_MENU) & 0x8000)
			alt_on = 1;

		freq = mappingKey_to_Freq(ch, alt_on);
		if (freq != -1)
		{
			printf("input key(%c):freq(%3d)\n", ch, freq);
			Beep(freq, duration);
		}
		else
		{
			printf("inputkey(%c) is wrong key input\n", ch);
		}
	}
	return 0;
}



int mappingKey_to_Freq(char key, char alt)
{
	int shift_on=0, index=0;

	

	int Key_to_Freq[2][2][26] =
	{
		{
				{523,392,330,660,1323,698,784,880,-1,988,-1,-1,494,440,-1,-1,1048,1396,588,1568,1976,349,1176,294,1760,262},
			{4186,3136,2637,5274,-1,5588,6272,7040,-1,7902,-1,-1,3951,3520,-1,-1,-1,-1,4699,-1,-1,2794,-1,2349,-1,2093}
		},
		{
			{554,415,330,660,1323,740,830,932,-1,988,-1,-1,494,466,-1,-1,1109,1480,622,1661,1976,370,1245,311,1865,277},
			{4432,3322,2637,5274,-1,5920,6645,7459,-1,7902,-1,-1,3951,3729,-1,-1,-1,-1,4978,-1,-1,2960,-1,2489,-1,2217}
		}
	};

	if ((key >= 'a') && (key <= 'z'))
	{
		shift_on = 0;
		index = key - 'a';
	}
	else if ((key >= 'A') && (key <= 'Z'))
	{
		shift_on = 1;
		index = key - 'A';
	}

	else
		return -1;
	return Key_to_Freq[alt][shift_on][index];
}