#include "stdio.h"
#include "input.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "check.h"
#include "hmi.h"
#include "user.h"
#include "svga.h"
#include <alloc.h>
#include "mouse.h"
#include "hz.h"
#include <conio.h>
#include "gettime.h"
#include <mem.h>
#include "book.h"
#include "graph.h"
#include "bios.h"
#include "visual.h"
/*===========================*/ 
/*搜索结果展示函数*/
/*作者：苏新明*/
/*各种信息上载显示，包含四种直达，16中中转情况显示*/ 
/*===========================*/ 
void De_visual(StackNode *result,int s_num,int flag,int k)//直达结果显示 flag=1显示余票 flag=2显示价格 
{
	int x1=200,x2=640,y1=s_num*90+51,y2=y1+90;
	StackNode *temp=result;
	frm(x1,y1,x2,y2);
	setcolor(_BLACK);
	outtextxy(405,y1+46,temp->trainnum);
	puthz(x1+50,y1+36,temp->station,1,16,_BLACK);
	while(temp->next!=NULL)
	{
		temp=temp->next;
	}//当前temp被定位为结束车站 
	puthz(x2-90,y1+36,temp->station,1,16,_BLACK);
	if(*(result->trainnum)=='K'||*(result->trainnum)=='T')
	{
		DeKT_visual(result,temp,x1,y1,flag,k);
	}
	else if(*(result->trainnum)=='G')
	{
		DeG_visual(result,temp,x1,y1,flag,k);
	}
	else if(*(result->trainnum)=='D')
	{
		DeD_visual(result,temp,x1,y1,flag,k);
	}
	else if(*(result->trainnum)=='Z')
	{
		DeZ_visual(result,x1,y1,flag,k);
	}
}

void DeKT_visual(StackNode *result,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[3]={20000,20000,20000},fee[3]={0,0,0};
	char _seat[3][14];
	char _time[15];
	KT_train KTtrain;
	KT_read(result->trainnum,&KTtrain,k);
	for(i=0;strcmp(KTtrain.station[i],temp->station);i++)
	{
		if(!strcmp(KTtrain.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,KTtrain.start_time[i]);
			start=1; 
		}
		if(start)
		{
			if(strcmp(KTtrain.station[i+1],temp->station))
			{
				TimeDistance_m(KTtrain.start_time[i],KTtrain.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain.start_time[i],KTtrain.arrive_time[i+1],&min);
				time0+=min;
			}
			if(seat[0]>atoi(KTtrain.hard_seat[i])) seat[0]=atoi(KTtrain.hard_seat[i]);
			if(seat[1]>atoi(KTtrain.hard_sleeper[i])) seat[1]=atoi(KTtrain.hard_sleeper[i]);
			if(seat[2]>atoi(KTtrain.soft_sleeper[i])) seat[2]=atoi(KTtrain.soft_sleeper[i]);
			fee[0]+=atoi(KTtrain.hardseat_fee[i]);
			fee[1]+=atoi(KTtrain.hardsleeper_fee[i]);
			fee[2]+=atoi(KTtrain.softsleeper_fee[i]);
		}
	}
	outtextxy(550,y1+18,KTtrain.arrive_time[i]);
	TimeDistance_hm(time0,_time);
	puthz(370,y1+25,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"硬座:");
		strcpy(_seat[1],"硬卧:");
		strcpy(_seat[2],"软卧:");
		for(i=0;i<3;i++)
		{
			itoa(seat[i],_seat[i]+5,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
		puthz(510,y1+60,_seat[2],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"硬座:");
		strcpy(_seat[1],"硬卧:");
		strcpy(_seat[2],"软卧:");
		for(i=0;i<3;i++)
		{
	  	    itoa(fee[i],_seat[i]+5,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
		puthz(510,y1+60,_seat[2],1,16,_BLACK);
	}
}

void DeG_visual(StackNode *result,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[3]={20000,20000,20000},fee[3]={0,0,0};
	char _seat[3][14];
	char _time[15];
	G_train Gtrain;
	G_read(result->trainnum,&Gtrain,k);
	for(i=0;strcmp(Gtrain.station[i],temp->station);i++)
	{
		if(!strcmp(Gtrain.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Gtrain.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Gtrain.station[i+1],temp->station))
			{
				TimeDistance_m(Gtrain.start_time[i],Gtrain.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain.start_time[i],Gtrain.arrive_time[i+1],&min);
				time0+=min;
			}
			if(seat[0]>atoi(Gtrain.s_seat[i])) seat[0]=atoi(Gtrain.s_seat[i]);
			if(seat[1]>atoi(Gtrain.f_seat[i])) seat[1]=atoi(Gtrain.f_seat[i]);
			if(seat[2]>atoi(Gtrain.b_seat[i])) seat[2]=atoi(Gtrain.b_seat[i]);
			fee[0]+=atoi(Gtrain.sclass_fee[i]);
			fee[1]+=atoi(Gtrain.fclass_fee[i]);
			fee[2]+=atoi(Gtrain.business_fee[i]);
		}
	}
	outtextxy(550,y1+18,Gtrain.arrive_time[i]);
	TimeDistance_hm(time0,_time);
	puthz(370,y1+25,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"二等座:");
		strcpy(_seat[1],"一等座:");
		strcpy(_seat[2],"商务座:");
		for(i=0;i<3;i++)
		{
			itoa(seat[i],_seat[i]+7,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
		puthz(510,y1+60,_seat[2],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"二等座:");
		strcpy(_seat[1],"一等座:");
		strcpy(_seat[2],"商务座:");
		for(i=0;i<3;i++)
		{
			itoa(fee[i],_seat[i]+7,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
		puthz(510,y1+60,_seat[2],1,16,_BLACK);
	}
}

void DeD_visual(StackNode *result,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[3]={20000,20000,20000},fee[3]={0,0,0};
	char _seat[3][14];
	char _time[15];
	D_train Dtrain;
	D_read(result->trainnum,&Dtrain,k);
	for(i=0;strcmp(Dtrain.station[i],temp->station);i++)
	{
		if(!strcmp(Dtrain.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Dtrain.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Dtrain.station[i+1],temp->station))
			{
				TimeDistance_m(Dtrain.start_time[i],Dtrain.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain.start_time[i],Dtrain.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Dtrain.s_seat[i])) seat[0]=atoi(Dtrain.s_seat[i]);
			if(seat[1]>atoi(Dtrain.f_seat[i])) seat[1]=atoi(Dtrain.f_seat[i]);
			fee[0]+=atoi(Dtrain.sclass_fee[i]);
			fee[1]+=atoi(Dtrain.fclass_fee[i]);
		}
	}
	outtextxy(550,y1+18,Dtrain.arrive_time[i]);
	TimeDistance_hm(time0,_time);
	puthz(370,y1+25,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"二等座:");
		strcpy(_seat[1],"一等座:");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+7,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"二等座:");
		strcpy(_seat[1],"一等座:");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+7,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
	}
}

void DeZ_visual(StackNode *result,int x1,int y1,int flag,int k)
{
	int i;
	int time0=0,min=0;
	char _time[15];
	char _seat[3][14];
	Z_train Ztrain;
	
	Z_read(result->trainnum,&Ztrain,k);
	outtextxy(x1+50,y1+18,Ztrain.start_time);
	outtextxy(550,y1+18,Ztrain.arrive_time);
	TimeDistance_m(Ztrain.start_time,Ztrain.arrive_time,&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+25,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"硬座:");
		strcat(_seat[0],Ztrain.hard_seat);
		strcpy(_seat[1],"硬卧:");
		strcat(_seat[1],Ztrain.hard_sleeper);
		strcpy(_seat[2],"软卧:");
		strcat(_seat[2],Ztrain.soft_sleeper);
		for(i=0;i<3;i++)
		{
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
		puthz(510,y1+60,_seat[2],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"硬座:");
		strcat(_seat[0],Ztrain.hardseat_fee);
		strcpy(_seat[1],"硬卧:");
		strcat(_seat[1],Ztrain.hardsleeper_fee);
		strcpy(_seat[2],"软卧:");
		strcat(_seat[2],Ztrain.softsleeper_fee);
		for(i=0;i<3;i++)
		{
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+60,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
		puthz(510,y1+60,_seat[2],1,16,_BLACK);
	}
}

void Re_visual(StackNode *result,int s_num,int flag,int k)//16种中转组合显示 
{
	int x1=200,x2=640,y1=s_num*90+51,y2=y1+90;
	char s[14];// 
	StackNode *temp=result,*center=NULL;
	
	s[13]='\0';
	frm(x1,y1,x2,y2);
	puthz(x1+50,y1+36,result->station,1,16,_BLACK);
	while(temp->next!=NULL)
	{
		if(temp->last!=NULL&&strcmp(temp->last->trainnum,temp->trainnum))
		{
			center=temp;
			strcpy(s,temp->station);
			strcat(s,"中转"); 		
			puthz(380,y1+26,s,1,16,_BLACK);
		}
		temp=temp->next;
	}
	puthz(x2-90,y1+36,temp->station,1,16,_BLACK);
	setcolor(_BLACK);//初始化显示颜色 
	/*16种转车组合*/
	if((result->trainnum[0]=='K'||result->trainnum[0]=='T')&&(temp->last->trainnum[0]=='K'||temp->last->trainnum[0]=='T'))
	{
		KTReKT_visual(result,center,temp,x1,y1,flag,k);
	}
	else if((result->trainnum[0]=='K'||result->trainnum[0]=='T')&&temp->last->trainnum[0]=='G')
	{
		KTReG_visual(result,center,temp,x1,y1,flag,k);
	}
	else if((result->trainnum[0]=='K'||result->trainnum[0]=='T')&&temp->last->trainnum[0]=='D')
	{
		KTReD_visual(result,center,temp,x1,y1,flag,k);
	}
	else if((result->trainnum[0]=='K'||result->trainnum[0]=='T')&&temp->last->trainnum[0]=='Z')
	{
		KTReZ_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='G'&&(temp->last->trainnum[0]=='K'||temp->last->trainnum[0]=='T'))
	{
		GReKT_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='G'&&temp->last->trainnum[0]=='G')
	{
		GReG_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='G'&&temp->last->trainnum[0]=='D')
	{
		GReD_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='G'&&temp->last->trainnum[0]=='Z')
	{
		GReZ_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='D'&&(temp->last->trainnum[0]=='K'||temp->last->trainnum[0]=='T'))
	{
		DReKT_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='D'&&temp->last->trainnum[0]=='G')
	{
		DReG_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='D'&&temp->last->trainnum[0]=='D')
	{
		DReD_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='D'&&temp->last->trainnum[0]=='Z')
	{
		DReZ_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='Z'&&(temp->last->trainnum[0]=='K'||temp->last->trainnum[0]=='T'))
	{
		ZReKT_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='Z'&&temp->last->trainnum[0]=='G')
	{
		ZReG_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='Z'&&temp->last->trainnum[0]=='D')
	{
		ZReD_visual(result,center,temp,x1,y1,flag,k);
	}
	else if(result->trainnum[0]=='Z'&&temp->last->trainnum[0]=='Z')
	{
		ZReZ_visual(result,center,temp,x1,y1,flag,k);
	}
}


void KTReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15],DifferenceTime[2][6];
	KT_train KTtrain1,KTtrain2;
	KT_read(result->trainnum,&KTtrain1,k);
	KT_read(temp->last->trainnum,&KTtrain2,k);
	for(i=0;strcmp(KTtrain1.station[i],center->station);i++)
	{
		if(!strcmp(KTtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,KTtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(KTtrain1.station[i+1],center->station))
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(KTtrain1.hard_seat[i])) seat[0]=atoi(KTtrain1.hard_seat[i]);
			fee[0]+=atoi(KTtrain1.hardseat_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],KTtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(KTtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(KTtrain2.station[i],center->station))
		{
			start=1;
			strcpy(DifferenceTime[1],KTtrain2.start_time[i]);
		}
		if(start)
		{
			if(strcmp(KTtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(KTtrain2.hard_seat[i])) seat[1]=atoi(KTtrain2.hard_seat[i]);
			fee[1]+=atoi(KTtrain2.hardseat_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,KTtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}


void KTReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][22];
	char _time[15],DifferenceTime[2][6];
	KT_train KTtrain1;
	G_train Gtrain2;
	KT_read(result->trainnum,&KTtrain1,k);
	G_read(temp->last->trainnum,&Gtrain2,k);
	for(i=0;strcmp(KTtrain1.station[i],center->station);i++)
	{
		if(!strcmp(KTtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,KTtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(KTtrain1.station[i+1],center->station))
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(KTtrain1.hard_seat[i])) seat[0]=atoi(KTtrain1.hard_seat[i]);
			fee[0]+=atoi(KTtrain1.hardseat_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],KTtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(Gtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Gtrain2.station[i],center->station))
		{
			strcpy(DifferenceTime[1],Gtrain2.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Gtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Gtrain2.s_seat[i])) seat[1]=atoi(Gtrain2.s_seat[i]);
			fee[1]+=atoi(Gtrain2.sclass_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Gtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11+i*2,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11+i*2,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void KTReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][22];
	char _time[15],DifferenceTime[2][6];
	KT_train KTtrain1;
	D_train Dtrain2; 
	KT_read(result->trainnum,&KTtrain1,k);
	D_read(temp->last->trainnum,&Dtrain2,k);
	for(i=0;strcmp(KTtrain1.station[i],center->station);i++)
	{
		if(!strcmp(KTtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,KTtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(KTtrain1.station[i+1],center->station))
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(KTtrain1.hard_seat[i])) seat[0]=atoi(KTtrain1.hard_seat[i]);
			fee[0]+=atoi(KTtrain1.hardseat_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],KTtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(Dtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Dtrain2.station[i],center->station))
		{
			strcpy(DifferenceTime[1],Dtrain2.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Dtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Dtrain2.s_seat[i])) seat[1]=atoi(Dtrain2.s_seat[i]);
			fee[1]+=atoi(Dtrain2.sclass_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Dtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11+i*2,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11+i*2,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void KTReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15];
	KT_train KTtrain1;
	Z_train Ztrain2; 
	KT_read(result->trainnum,&KTtrain1,k);
	Z_read(temp->last->trainnum,&Ztrain2,k);
	for(i=0;strcmp(KTtrain1.station[i],center->station);i++)
	{
		if(!strcmp(KTtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,KTtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(KTtrain1.station[i+1],center->station))
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain1.start_time[i],KTtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(KTtrain1.hard_seat[i])) seat[0]=atoi(KTtrain1.hard_seat[i]);
			fee[0]+=atoi(KTtrain1.hardseat_fee[i]);
		}
	}
	TimeDistance_m(KTtrain1.arrive_time[i],Ztrain2.arrive_time,&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Ztrain2.arrive_time);
	if(seat[1]>atoi(Ztrain2.hard_seat)) seat[1]=atoi(Ztrain2.hard_seat);
	fee[1]+=atoi(Ztrain2.hardseat_fee);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11,10); 
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11,10); 
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
	}
}

void GReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15],DifferenceTime[2][6];
	G_train Gtrain1;
	KT_train KTtrain2;
	G_read(result->trainnum,&Gtrain1,k);
	KT_read(temp->last->trainnum,&KTtrain2,k);
	for(i=0;strcmp(Gtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Gtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Gtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Gtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Gtrain1.s_seat[i])) seat[0]=atoi(Gtrain1.s_seat[i]);
			fee[0]+=atoi(Gtrain1.sclass_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],Gtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(KTtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(KTtrain2.station[i],center->station))
		{
			start=1;
			strcpy(DifferenceTime[1],KTtrain2.start_time[i]);
		}
		if(start)
		{
			if(strcmp(KTtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(KTtrain2.hard_seat[i])) seat[1]=atoi(KTtrain2.hard_seat[i]);
			fee[1]+=atoi(KTtrain2.hardseat_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,KTtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13+(-2)*i,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13+(-2)*i,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void GReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15],DifferenceTime[2][6];
	G_train Gtrain1,Gtrain2;
	G_read(result->trainnum,&Gtrain1,k);
	G_read(temp->last->trainnum,&Gtrain2,k);
	for(i=0;strcmp(Gtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Gtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Gtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Gtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Gtrain1.s_seat[i])) seat[0]=atoi(Gtrain1.s_seat[i]);
			fee[0]+=atoi(Gtrain1.sclass_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],Gtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(Gtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Gtrain2.station[i],center->station))
		{
			start=1;
			strcpy(DifferenceTime[1],Gtrain2.start_time[i]);
		}
		if(start)
		{
			if(strcmp(Gtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Gtrain2.s_seat[i])) seat[1]=atoi(Gtrain2.s_seat[i]);
			fee[1]+=atoi(Gtrain2.sclass_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Gtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void GReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20],visual[10];
	char _time[15],DifferenceTime[2][6];
	G_train Gtrain1;
	D_train Dtrain2;
	G_read(result->trainnum,&Gtrain1,k);
	D_read(temp->last->trainnum,&Dtrain2,k);
	for(i=0;strcmp(Gtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Gtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Gtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Gtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Gtrain1.s_seat[i])) seat[0]=atoi(Gtrain1.s_seat[i]);
			fee[0]+=atoi(Gtrain1.sclass_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],Gtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(Dtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Dtrain2.station[i],center->station))
		{
			start=1;
			strcpy(DifferenceTime[1],Dtrain2.start_time[i]);
		}
		if(start)
		{
			if(strcmp(Dtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Dtrain2.s_seat[i])) seat[1]=atoi(Dtrain2.s_seat[i]);
			fee[1]+=atoi(Dtrain2.sclass_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Dtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void GReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15];
	G_train Gtrain1;
	Z_train Ztrain2; 
	G_read(result->trainnum,&Gtrain1,k);
	Z_read(temp->last->trainnum,&Ztrain2,k);
	for(i=0;strcmp(Gtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Gtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Gtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Gtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain1.start_time[i],Gtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Gtrain1.s_seat[i])) seat[0]=atoi(Gtrain1.s_seat[i]);
			fee[0]+=atoi(Gtrain1.sclass_fee[i]);
		}
	}
	TimeDistance_m(Gtrain1.arrive_time[i],Ztrain2.arrive_time,&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Ztrain2.arrive_time);
	if(seat[1]>atoi(Ztrain2.hard_seat)) seat[1]=atoi(Ztrain2.hard_seat);
	fee[1]+=atoi(Ztrain2.hardseat_fee);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13+(-2)*i,10); 
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13-2*i,10); 
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(374,y1+60,_seat[1],1,16,_BLACK);
	}
	
} 

void DReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15],DifferenceTime[2][6];
	D_train Dtrain1;
	KT_train KTtrain2; 
	D_read(result->trainnum,&Dtrain1,k);
	KT_read(temp->last->trainnum,&KTtrain2,k);
	for(i=0;strcmp(Dtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Dtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Dtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Dtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Dtrain1.s_seat[i])) seat[0]=atoi(Dtrain1.s_seat[i]);
			fee[0]+=atoi(Dtrain1.sclass_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],Dtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(KTtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(KTtrain2.station[i],center->station))
		{
			start=1;
			strcpy(DifferenceTime[1],KTtrain2.start_time[i]);
		}
		if(start)
		{
			if(strcmp(KTtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(KTtrain2.hard_seat[i])) seat[1]=atoi(KTtrain2.hard_seat[i]);
			fee[1]+=atoi(KTtrain2.hardseat_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,KTtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13-i*2,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13-2*i,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void DReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15],DifferenceTime[2][6];
	D_train Dtrain1,Dtrain2;
	D_read(result->trainnum,&Dtrain1,k);
	D_read(temp->last->trainnum,&Dtrain2,k);
	for(i=0;strcmp(Dtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Dtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Dtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Dtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Dtrain1.s_seat[i])) seat[0]=atoi(Dtrain1.s_seat[i]);
			fee[0]+=atoi(Dtrain1.sclass_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],Dtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(Dtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Dtrain2.station[i],center->station))
		{
			start=1;
			strcpy(DifferenceTime[1],Dtrain2.start_time[i]);
		}
		if(start)
		{
			if(strcmp(Dtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Dtrain2.s_seat[i])) seat[1]=atoi(Dtrain2.s_seat[i]);
			fee[1]+=atoi(Dtrain2.sclass_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Dtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}
void DReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15],DifferenceTime[2][6];
	D_train Dtrain1;
	G_train Gtrain2;
	D_read(result->trainnum,&Dtrain1,k);
	G_read(temp->last->trainnum,&Gtrain2,k);
	for(i=0;strcmp(Dtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Dtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Dtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Dtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Dtrain1.s_seat[i])) seat[0]=atoi(Dtrain1.s_seat[i]);
			fee[0]+=atoi(Dtrain1.sclass_fee[i]);
		}
	}
	strcpy(DifferenceTime[0],Dtrain1.arrive_time[i]);
	start=0;
	for(i=0;strcmp(Gtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Gtrain2.station[i],center->station))
		{
			start=1;
			strcpy(DifferenceTime[1],Gtrain2.start_time[i]);
		}
		if(start)
		{
			if(strcmp(Gtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Gtrain2.s_seat[i])) seat[1]=atoi(Gtrain2.s_seat[i]);
			fee[1]+=atoi(Gtrain2.sclass_fee[i]);
		}
	}
	TimeDistance_m(DifferenceTime[0],DifferenceTime[1],&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Gtrain2.arrive_time[i]);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13,10);
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13,10);
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void DReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15];
	D_train Dtrain1;
	Z_train Ztrain2; 
	D_read(result->trainnum,&Dtrain1,k);
	Z_read(temp->last->trainnum,&Ztrain2,k);
	for(i=0;strcmp(Dtrain1.station[i],center->station);i++)
	{
		if(!strcmp(Dtrain1.station[i],result->station))
		{
			outtextxy(x1+50,y1+18,Dtrain1.start_time[i]);
			start=1;
		}
		if(start)
		{
			if(strcmp(Dtrain1.station[i+1],center->station))
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain1.start_time[i],Dtrain1.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[0]>atoi(Dtrain1.s_seat[i])) seat[0]=atoi(Dtrain1.s_seat[i]);
			fee[0]+=atoi(Dtrain1.sclass_fee[i]);
		}
	}
	TimeDistance_m(Dtrain1.arrive_time[i],Ztrain2.arrive_time,&min);
	time0+=min;
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	outtextxy(550,y1+18,Ztrain2.arrive_time);
	if(seat[1]>atoi(Ztrain2.hard_seat)) seat[1]=atoi(Ztrain2.hard_seat);
	fee[1]+=atoi(Ztrain2.hardseat_fee);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+13+(-2)*i,10); 
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:二等座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+13-2*i,10); 
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	
} 

void ZReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15];
	KT_train KTtrain2;
	Z_train Ztrain1;
	KT_read(result->trainnum,&KTtrain2,k);
	Z_read(temp->last->trainnum,&Ztrain1,k);
	
	outtextxy(250,y1+18,Ztrain1.start_time);
	if(seat[0]>atoi(Ztrain1.hard_seat)) seat[0]=atoi(Ztrain1.hard_seat);
	fee[0]+=atoi(Ztrain1.hardseat_fee);
	for(i=0;strcmp(KTtrain2.station[i],center->station);i++)
	{
		if(!strcmp(KTtrain2.station[i],result->station))
		{
			TimeDistance_m(Ztrain1.start_time,KTtrain2.start_time[i],&min);
			time0+=min;
			start=1;
		}
		if(start)
		{
			if(strcmp(KTtrain2.station[i+1],center->station))
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(KTtrain2.start_time[i],KTtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(KTtrain2.hard_seat[i])) seat[1]=atoi(KTtrain2.hard_seat[i]);
			fee[0]+=atoi(KTtrain2.hardseat_fee[i]);
		}
	}
	outtextxy(550,y1+18,KTtrain2.arrive_time[i]); 
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11,10); 
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11,10); 
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

void ZReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15];
	G_train Gtrain2;
	Z_train Ztrain1;
	G_read(result->trainnum,&Gtrain2,k);
	Z_read(temp->last->trainnum,&Ztrain1,k);
	

	outtextxy(250,y1+18,Ztrain1.start_time);
	if(seat[0]>atoi(Ztrain1.hard_seat)) seat[0]=atoi(Ztrain1.hard_seat);
	fee[0]+=atoi(Ztrain1.hardseat_fee);
	for(i=0;strcmp(Gtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Gtrain2.station[i],center->station))
		{
			TimeDistance_m(Ztrain1.start_time,Gtrain2.start_time[i],&min);
			time0+=min;
			start=1;
		}
		if(start)
		{
			if(strcmp(Gtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Gtrain2.start_time[i],Gtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Gtrain2.s_seat[i])) seat[1]=atoi(Gtrain2.s_seat[i]);
			fee[1]+=atoi(Gtrain2.sclass_fee[i]);
		}
	}
	outtextxy(550,y1+18,Gtrain2.arrive_time[i]); 
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11+2*i,10); 
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11+2*i,10); 
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}
void ZReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,start=0,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15];
	D_train Dtrain2;
	Z_train Ztrain1;
	D_read(result->trainnum,&Dtrain2,k);
	Z_read(temp->last->trainnum,&Ztrain1,k);
	
	
	outtextxy(250,y1+18,Ztrain1.start_time);
	if(seat[0]>atoi(Ztrain1.hard_seat)) seat[0]=atoi(Ztrain1.hard_seat);
	fee[0]+=atoi(Ztrain1.hardseat_fee);
	for(i=0;strcmp(Dtrain2.station[i],temp->station);i++)
	{
		if(!strcmp(Dtrain2.station[i],center->station))
		{
			TimeDistance_m(Ztrain1.start_time,Dtrain2.start_time[i],&min);
			time0+=min;
			start=1;
		}
		if(start)
		{
			if(strcmp(Dtrain2.station[i+1],temp->station))
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.start_time[i+1],&min);
			    time0+=min;
			}
			else
			{
				TimeDistance_m(Dtrain2.start_time[i],Dtrain2.arrive_time[i+1],&min);
				time0+=min;
		    }
			if(seat[1]>atoi(Dtrain2.s_seat[i])) seat[1]=atoi(Dtrain2.s_seat[i]);
			fee[1]+=atoi(Dtrain2.sclass_fee[i]);
		}
	}
	outtextxy(550,y1+18,Dtrain2.arrive_time[i]); 
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11+2*i,10); 
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:二等座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11+2*i,10); 
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}


void ZReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k)
{
	int i,time0=0,min=0;//开始计时 
	int seat[2]={20000,20000},fee[2]={0,0};
	char _seat[2][20];
	char _time[15];
	Z_train Ztrain2,Ztrain1;
	Z_read(result->trainnum,&Ztrain2,k);
	Z_read(temp->last->trainnum,&Ztrain1,k);
	
	TimeDistance_m(Ztrain1.start_time,Ztrain2.arrive_time,&min);
	time0+=min;
	outtextxy(250,y1+18,Ztrain1.start_time);
	outtextxy(550,y1+18,Ztrain2.arrive_time);
	if(seat[0]>atoi(Ztrain1.hard_seat)) seat[0]=atoi(Ztrain1.hard_seat);
	fee[0]+=atoi(Ztrain1.hardseat_fee);
	if(seat[1]>atoi(Ztrain2.hard_seat)) seat[1]=atoi(Ztrain2.hard_seat);
	fee[1]+=atoi(Ztrain2.hardseat_fee);
	TimeDistance_hm(time0,_time);
	puthz(370,y1+46,_time,1,16,_BLACK);
	if(flag==1)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(seat[i],_seat[i]+11,10); 
			strcat(_seat[i],"张"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
	else if(flag==2)
	{
		strcpy(_seat[0],"第一程:硬座");
		strcpy(_seat[1],"第二程:硬座");
		for(i=0;i<2;i++)
		{
			itoa(fee[i],_seat[i]+11,10); 
			strcat(_seat[i],"元"); 
		}
		puthz(245,y1+62,_seat[0],1,16,_BLACK);
		puthz(450,y1+62,_seat[1],1,16,_BLACK);
	}
}

