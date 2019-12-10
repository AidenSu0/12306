#ifndef __DATA_H__
#define __DATA_H__

#define TURE 1
#define FALSE 0
/*快车特快火车记录*/
typedef struct
{
	char tra_num[6];//车次 
	char station[31][10];//30个站的名字 
	char city[31][10];//所在城市 
	char arrive_time[30][6];//到站时间 
	char start_time[31][6];//发车时间
	char hardseat_fee[30][4];//到下一站硬座费用（元）
	char hardsleeper_fee[30][4];//到下一站硬卧费用（元）
	char softsleeper_fee[30][4]; //到下一站软卧费用（元）
	char hard_seat[30][6];//到下一站硬座数
	char hard_sleeper[30][6];//到下一站硬卧数
	char soft_sleeper[30][6];//到下一站软卧数 
}KT_train; 

/*直达列车记录*/ 
typedef struct
{
	char tra_num[6];//车次 
	char station[2][10];//2个站的名字
	char city[2][10];//所在城市 
	char start_time[6];//始发时间 
	char arrive_time[6];//终点时间 
	char hardseat_fee[4];//到下一站硬座费用（元）
	char hardsleeper_fee[4];//到下一站硬卧费用（元）
	char softsleeper_fee[4]; //到下一站软卧费用（元）
	char hard_seat[6];//到下一站硬座数
	char hard_sleeper[6];//到下一站硬卧数
	char soft_sleeper[6];//到下一站软卧数  
}Z_train;
 
/*动车记录*/ 
typedef struct
{
	char tra_num[6];//车次 
	char station[31][10];//30个站的名字 
	char city[31][10];//所在城市 
	char arrive_time[30][6];//到站时间 
	char start_time[31][6];//发车时间
	char fclass_fee[30][4];//到下一站一等座费用（元）
	char sclass_fee[30][4];//到下一站二等座费用（元） 
	char f_seat[30][6];//到下一站一等座数
	char s_seat[30][6];//到下一站二等座数
}D_train;

/*高铁记录*/ 
typedef struct
{
	char tra_num[6];//车次 
	char station[31][10];//30个站的名字 
	char city[31][10];//所在城市 
	char arrive_time[30][6];//到站时间 
	char start_time[31][6];//发车时间
	char fclass_fee[30][4];//到下一站一等座费用（元）
	char sclass_fee[30][4];//到下一站二等座费用（元）
	char business_fee[30][4];//到下一站商务座费用（元） 
	char f_seat[30][6];//到下一站一等座数
	char s_seat[30][6];//到下一站二等座数
	char b_seat[30][6];//到下一站商务座数 
}G_train;


typedef struct
{
	int code;
	char city[10];
}CITYCODE;

int KT_save(char *T_num,KT_train *p,int page,int (*length)[9],int *lengthnum,int num,int k);
int Z_save(char *T_num,Z_train *p,int (*length)[2],int *lengthnum,int k);
int G_save(char *T_num,G_train *p,int page,int (*length)[9],int *lengthnum,int num,int k);
int D_save(char *T_num,D_train *p,int page,int (*length)[9],int *lengthnum,int num,int k);
int KT_read(char *T_num,KT_train *train,int num);
int Z_read(char *T_num,Z_train *train,int num);
int G_read(char *T_num,G_train *train,int num);
int D_read(char *T_num,D_train *train,int num);
int SearchTrain(char *T_num,int num);
int DeleteTrain(char *T_num,int num);

#endif

