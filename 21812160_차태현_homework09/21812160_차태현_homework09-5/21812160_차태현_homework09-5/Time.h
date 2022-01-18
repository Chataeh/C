#ifndef T_H
#define T_H

typedef struct {//시간 구조체
	int hour;
	int min;
	int sec;
} Time;
Time inputTime(void);//시간입력
void printTime(const Time* tptr1);//시간 출력
void incrementTime(Time* tptr2, int sec);//증가된 초에 따른 시간출력
int compareTime(const Time* tptr1, const Time* tptr2);//시간 차 출력
void selectSortTime(Time* tptr1, int size);//선택정렬
Time initTime(int h, int m, int s);//주어진 값을 구조체에 입력
#endif // !T_H


