#include<stdio.h>
#include"Time.h"

Time inputTime(void)//시간 입력
{
	Time t;
	printf("input hour minute sec :");
	scanf("%d %d %d", &t.hour, &t.min,&t.sec);

	return t;
}

void printTime(const Time* tptr1)//시간 출력
{
	if (tptr1->hour >= 24)//24시간으로 표현
		printf("(%02d:%02d:%02d)", tptr1->hour - 24, tptr1->min, tptr1->sec);
	else
		printf("(%02d:%02d:%02d)", tptr1->hour, tptr1->min, tptr1->sec);
	
}
void incrementTime(Time* tptr2, int sec)//증가된 초에 따른 구조체값
{
	int S;
	
	S = tptr2->hour * 60 * 60 + tptr2->min * 60 + tptr2->sec + sec; //전체시간을 초로 바꿔줌
	tptr2->hour = S / 3600;//전체 초에대한 시간을 계산
	tptr2-> min = (S / 60) % 60;//전체 초에대한 분을계산
	tptr2->sec = S % 60;//전체 초에대한 초를계산
}

int compareTime(const Time* tptr1, const Time* tptr2)//두 값의 시간차
{
	int S1, S2,diff;

	S1= tptr1->hour * 60 * 60 + tptr1->min * 60 + tptr1->sec;//전체시간으로 변환
	S2 = tptr2->hour * 60 * 60 + tptr2->min * 60 + tptr2->sec;
	diff = S2 - S1;//초 단위 시간차 계산
	
	return diff;
}
int compare(const Time* tptr1, const Time* tptr2)//선택정렬을 위한 주어진 시간 값들의 크기비교
{
	if (tptr1->hour > tptr2->hour)//시간으로 판별이 날경우
		return 1;
	else if (tptr1->hour < tptr2->hour)
		return -1;
	else//시간이 같고 분이다른경우
	{
		if (tptr1->min > tptr2->min)
			return 1;
		else if (tptr1->min < tptr2->min)
			return -1;
		else//시간 분이 같고 초가다른경우
		{
			if (tptr1->sec > tptr2->sec)
				return 1;
			else if (tptr1->sec < tptr2->sec)
				return -1;
			else return 0;
		}
	}
}

void selectSortTime(Time *tptr1,int size)//선택정렬
{
	Time temp;//순서변환을 위한 정의
	Time* t;
	Time* min_t;
	int min;
	for(int i=0; i<size-1;i++)
	{
		min = i;//초기 값을 최소로 정하고시작
		min_t = &tptr1[i];
		for (int j = i + 1; j < size; j++)
		{
			t = &tptr1[j];
			if (compare(t,min_t) < 0)//기준값보다 더 작은값일 경우
			{
				min_t = t;
				min = j;
			}
		}
		if (min != i)//최소값이 바뀐경우 스왑
		{
			temp = tptr1[i];
			tptr1[i] = tptr1[min];
			tptr1[min] = temp;
		}
	}
}
Time initTime(int h, int m, int s)//주어진 시간 분 초에대한 구조체 반환
{
	Time t;
	t.hour = h;
	t.min = m;
	t.sec = s;

	return t;
}