#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

struct date {
	long sec; //현재까지 흐른 초(sec)
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}d1;

int main(void)
{
	time_t t;
	t = time(NULL);
	d1.sec = t;
	printf("현재까지 흐른 시간: %lld\n", d1.sec);

	time_t current;
	struct tm* time;
	time = localtime(&t); //현재시간을 struct tm에 넣음
	
	d1.year = time->tm_year + 1900;
	d1.month = time->tm_mon + 1;
	d1.day = time->tm_mday;
	d1.hour = time->tm_hour;
	d1.min = time->tm_min;
	d1.sec = time->tm_sec;

	printf("현재시간 : %d년 %d월 %d일 %d시 %d분 %d초\n", d1.year, d1.month, d1.day, d1.hour, d1.min, d1.sec);

	return 0;
}