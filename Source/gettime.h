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

void _gettime(TIME *_time);/*获取当前时间函数*/
/*产生a1~a2以内随机数函数*/
int rand_num(int a1,int a2);
int days(int month,int year);/*获得当前月份天数*/

/*计算纯分钟数，返回天数差(<1)*/
int TimeDistance_m(char *t1,char *t2,int *min);
/*计算天小时分钟数，返回天数差(<45)*/
int TimeDistance_hm(int min_num,char *d_h_min);

int daysDifference(int mon1,int day1,int mon2,int day2);
#endif
