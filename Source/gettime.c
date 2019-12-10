#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "gettime.h"

/*===========================*/ 
/*ʱ���������*/
/*���ߣ�������*/ 
/*�ַ�ʱ��������ʱ�����������*/
/*===========================*/ 


/*��ȡ��ǰʱ�亯��*/
void _gettime(TIME *_time)
{
	time_t timep;
	struct tm *p;
	time(&timep);
//	timep+=2592000;//ʱ������ 
	p=gmtime(&timep);
	_time->day=p->tm_mday;
	_time->month=p->tm_mon+1; 
	_time->year=p->tm_year+1900;
	_time->hour=p->tm_hour-5;
	_time->min=p->tm_min;
}

/*����a1~a2�������������*/
int rand_num(int a1,int a2)
{
	static unsigned long i;
	srand((i++)*i);
	return (a1+rand()%(a2-a1));
} 

/*��õ�ǰ�·�����*/
int days(int month,int year)
{
	switch(month)
	{
		case 1:
			return 31;
		case 2:
			if((year/4==0&&year/100!=0)||year/400==0)
			{
				return 29;
			}
			else 
			{
				return 28;
			}
		case 3:
			return 31;
		case 4:
			return 30;
		case 5:
			return 31;
		case 6:
			return 30;
		case 7:
			return 31;
		case 8:
			return 31;
		case 9:
			return 30;
		case 10:
			return 31;
		case 11:
			return 30;
		case 12:
			return 31;
	}
	return 0;
} 

/*���㴿������������������(<1)*/
int TimeDistance_m(char *t1,char *t2,int *min)
{
	int i,j,flag=0; 
	int min_num=-1;//������ 
	char h[2][3],m[2][3];
	int _h[2],_m[2];
	int D_d=0; 
	for(i=0;t1[i]!='\0';i++)//ʱ��Сʱ����ӷ��� 
	{
		if(!flag)
		{
			if(t1[i]==':')//Сʱ���ӷָ� 
			{
				h[0][i]='\0';
				flag=1;
				j=0;
				continue;
			}
			h[0][i]=t1[i];
		}
		else
		{
			m[0][j]=t1[i];
			j++;
		}
	}
	m[0][2]='\0';
	flag=0;//��־��λ 
	for(i=0;t2[i]!='\0';i++)//ͬt1 
	{
		if(!flag)
		{
			if(t2[i]==':')
			{
				h[1][i]='\0';
				flag=1;
				j=0;
				continue;
			}
			h[1][i]=t2[i];
		}
		else
		{
			m[1][j]=t2[i];
			j++;
		}
	}
	m[1][2]='\0';
	for(i=0;i<2;i++)//ת��Ϊ����ģʽ 
	{
		_h[i]=atoi(h[i]);
		_m[i]=atoi(m[i]);
	}
	if((_h[1]*60+_m[1])-(_h[0]*60+_m[0])>=0) 
	{
		min_num=(_h[1]*60+_m[1])-(_h[0]*60+_m[0]);
	}
	else//������� 
	{
		min_num=(_h[1]*60+_m[1])-(_h[0]*60+_m[0])+1440;
		D_d=1;
	}
	*min=min_num;
	return D_d;
}

/*������Сʱ������������������(<45)*/
int TimeDistance_hm(int min_num,char *d_h_min)
{
	char h[3],m[3],d[3];
	int D_d=0,D_h=0,D_m=0;//���졢��ʱ����
	D_d=min_num/1440;
	D_h=(min_num-D_d*1440)/60;
	D_m=min_num%60;
	itoa(D_d,d,10);
	itoa(D_h,h,10);
	itoa(D_m,m,10);
	strcpy(d_h_min,d);
	strcat(d_h_min,"��");
	strcat(d_h_min,h);
	strcat(d_h_min,"Сʱ");
	strcat(d_h_min,m);
	strcat(d_h_min,"��"); 
	return D_d;
}
/*�������������Ҫ����������������ܼ���������һ��״̬*/
int daysDifference(int mon1,int day1,int mon2,int day2)
{
	int i,daynum=0;
	TIME _tm;
	_gettime(&_tm);
	if(mon2>=mon1)
	{
		for(i=mon1;i<mon2;i++)
		{
			daynum+=days(i,_tm.year);
		}
	}
	else//����״̬ 
	{
		for(i=mon1;i<13;i++)
		{
			daynum+=days(i,_tm.year);
		}
		for(i=1;i<mon2;i++)
		{
			daynum+=days(i,_tm.year+1);
		}
	}
	daynum+=day2-day1;
	return daynum;
}
