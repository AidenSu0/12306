#ifndef __GETTIME_H__
#define __GETTIME_H__


typedef struct
{
	int year;
	int month;
	int day;
	int hour;
	int min;
}TIME;

void _gettime(TIME *_time);/*��ȡ��ǰʱ�亯��*/
/*����a1~a2�������������*/
int rand_num(int a1,int a2);
int days(int month,int year);/*��õ�ǰ�·�����*/

/*���㴿������������������(<1)*/
int TimeDistance_m(char *t1,char *t2,int *min);
/*������Сʱ������������������(<45)*/
int TimeDistance_hm(int min_num,char *d_h_min);

int daysDifference(int mon1,int day1,int mon2,int day2);
#endif
