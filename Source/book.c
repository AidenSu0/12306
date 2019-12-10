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
#include "detail.h"
/*=========================*/
/*车次搜索操作函数集*/
/*作者：苏新明*/ 
/*使用各种搜索和排序进行车次筛选*/
/*=========================*/ 


/*搜索信息键入函数*/
int f_book(USER *user,int *xnow,int *ynow,int *mark)
{
	int judge=2;
	int state=0,btnow=0,C_position=-1;
	int tab=0;
	char StStation[10];
	char FiStation[10];
	char choosemon[3]={'\0','\0','\0'},chooseday[3]={'\0','\0','\0'};
	int lengthSt=0,lengthFi=0,StTright=0;
	int GD=0,ST=0;
	memset(StStation,'\0',10);
	memset(FiStation,'\0',10);
	book();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_book(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 6://进入查询 
				*mark=0;
				if(choosemon[0]=='\0') break;
				judge=f_look(user,StStation,FiStation,GD,ST,choosemon,chooseday,xnow,ynow,mark);
				book();
				lengthSt=0;
				lengthFi=0;
				StTright=0;
				GD=0;
				ST=0;
				break;
			case 97://起始城市输入 
			    lengthSt=hz_input(xnow,ynow,200,165,280,195,StStation,&tab,lengthSt);
				break;
			case 98://终点城市输入 
			    lengthFi=hz_input(xnow,ynow,360,165,440,195,FiStation,&tab,lengthFi);
				break;  
			case 99://选择搜索时间 
			    StTright=timechoose(choosemon,chooseday,300,250,xnow,ynow,mark);
			    if(StTright)
			    {
			    	setcolor(_WHITE);
			    	bar(292,242,308,258);
			    	bar(332,242,348,258);
			    	setcolor(_BLACK);
			    	outtextxy(292,242,choosemon);
			    	outtextxy(332,242,chooseday);
				}
				break;
			case 100://选择高铁动车 
				select(xnow,ynow,260,290,&GD);
				break;
			case 101://选择学生票 
			    select(xnow,ynow,380,290,&ST);
				break; 
			case 102:
				*mark=0;
				judge=f_time_table(xnow,ynow,mark);
				book();
				judge=2; 
				break;	
	    }
		if(judge==3||judge==4||judge==5) 
		{
			return judge;
		}
		judge=2;
	}
}


	/*选择时间函数*/ 
int timechoose(char *choosemon,char *chooseday,int x,int y,int *xnow,int *ynow,int *mark)
{
	char *image;
	int state=0,btnow=0;
	int departline;
	char mon[2][3];
	char _mark[8][6];
	char nowday[8][6][3];
	int x1=x-20,x2=x+100,y1=y+30,y2=y+210;
	int X,Y,oldX=-1,oldY,part=-1,oldpart;
	
	//圆变色 
	redraw(*xnow,*ynow);
	setcolor(_PINK);
	circle(300,250,15);
	circle(340,250,15);
	getbk_mouse(*xnow,*ynow);
	draw_mouse(*xnow,*ynow);
	/*保存将被遮盖图像*/ 
	if((image=malloc(22806))==NULL)
	{
		printf("Error!");
		getch();
		exit(0);
	}
	getimage(x1-5,y1,x2,y2,image);
	
	visualtime(x1,y1,&departline,mon,_mark,nowday);
	/*选择查询日期*/ 
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		part=(*ynow-y1<departline*20&&*ynow-y1>20)?0:((*ynow-y1>departline*20+20&&*ynow<y2)?1:-1);  //在本月为part0  在下一月为part1 否则part为-1 
		X=(*xnow-x1)/20;                                                  //日历版块X位置 
		Y=(part==0)?((*ynow-y1)/20-1):((part==1)?((*ynow-y1)/20-2):-1);  //日历版块Y位置 
		if(X<6&&X>=0&&Y>=0&&_mark[Y][X]&&(oldX!=X||oldY!=Y))//改变日期 
		{
			redraw(*xnow,*ynow);
			if(oldX!=-1&&oldY!=-1)//第一次进入不还原上一次颜色 （上一次未变色） 
			{
				setcolor(BCTcolor(0));
				outtextxy(x1+oldX*20,(oldpart?((oldY+2)*20+y1):((oldY+1)*20+y1)),nowday[oldY][oldX]);
			}
			//画新位置颜色 
			setcolor(BCTcolor(60));
			outtextxy(x1+X*20,((*ynow-y1)/20*20+y1),nowday[Y][X]);
			oldX=X;
			oldY=Y;
			oldpart=part;
			getbk_mouse(*xnow,*ynow);
		    draw_mouse(*xnow,*ynow);
		}
		if(state&&part!=-1&&_mark[Y][X]&&X<6&&X>=0)
		{
			if(!part) //在本月部分 
			{
				strcpy(choosemon,mon[0]); 
			}
			else //在下月部分 
			{
				strcpy(choosemon,mon[1]);
			}
			strcpy(chooseday,nowday[Y][X]);
			redraw(*xnow,*ynow);//暂时隐藏鼠标 
			setcolor(_BLACK);//还原时间框的颜色 
	        circle(300,250,15);
	        circle(340,250,15);
			putimage(x1-5,y1,x2,y2,image); 
		    free(image);
		    getbk_mouse(*xnow,*ynow);
		    draw_mouse(*xnow,*ynow);
			return 1;//选择后退出 
		}
		if(*xnow<x1-15||*xnow>x2+15||*ynow<y-20||*ynow>y2+15)
		{
			redraw(*xnow,*ynow);
			setcolor(_BLACK);
	        circle(300,250,15);
	        circle(340,250,15);
			putimage(x1-5,y1,x2,y2,image);
			free(image);
			getbk_mouse(*xnow,*ynow);
		    draw_mouse(*xnow,*ynow);
			return 0; //未选择即退出 
		}
	}
}

//画日历函数 
void visualtime(int x1,int y1,int *departline,char (*mon)[3],char (*_mark)[6],char (*nowday)[6][3])
{
	int x2=x1+120,y2=y1+180;
	int Line=0,i,words=0;
	TIME tim;
	
	memset(_mark,0,48);//初始化标志位数组 
	_gettime(&tim);//获取系统时间 
	itoa(tim.month,mon[0],10);//将月份转换为字符串 
	itoa(tim.month==12?1:tim.month+1,mon[1],10);
	/*已出票日期显示（一个月内）*/
		
	setcolor(BCTcolor(50));
	bar(x1-5,y1,x2,y2);
    /*当月显示*/ 
	setcolor(GTcolor(10));
	bar(x1-5,y1,x2,y1+20);
	setcolor(BCTcolor(60));
	outtextxy(x1,y1+2,mon[0]);
	puthz(x1+20,y1+2,"月",1,16,BCTcolor(60));
	Line++;
	setcolor(BCTcolor(0));
	for(i=tim.day;i<=days(tim.month,tim.year);i++,words++)
	{
		if(words==6)
		{
			Line++;
			words=0;
		}
		itoa(i,nowday[Line-1][words],10);
		outtextxy(x1+words*20,y1+Line*20,nowday[Line-1][words]);
		_mark[Line-1][words]=1;
	}
	words=0;
	Line++;
	*departline=Line;//月分隔行 
	/*下一月显示*/ 
	setcolor(GTcolor(10));
	bar(x1-5,y1+Line*20,x2,y1+Line*20+20);
	setcolor(BCTcolor(60));
	outtextxy(x1,y1+Line*20+2,mon[1]);
	puthz(x1+20,y1+Line*20+2,"月",1,16,BCTcolor(60));
	Line++;
	setcolor(BCTcolor(0));
	for(i=1;i<tim.day;i++,words++)
	{
		if(words==6)
		{
			Line++;
			words=0;
		}
		itoa(i,nowday[Line-2][words],10);
		outtextxy(x1+words*20,y1+Line*20,nowday[Line-2][words]);
		_mark[Line-2][words]=1;
	}
	setcolor(BCTcolor(0));
	rectangle(x1-5,y1,x2,y2);
} 

	/*进入查询函数*/ 
int f_look(USER *user,char *ss,char *fs,int GD,int ST,char *mon,char *day,int *xnow,int *ynow,int *mark)
{
	int De=0,Re=0,judge=0;
	int _mon,_day,num;
	TIME _tm;
	StackHead *head=NULL,*temp;
	StackNode *Der[30],*Rev[30],*rtemp;//存储直达与中转的方案头节点  
	
	look();
	while(judge!=2)//循环为多次搜索创建可能 
	{
		_gettime(&_tm);
		_mon=atoi(mon);
		_day=atoi(day);
		num=daysDifference(_tm.month,_tm.day,_mon,_day);
		head=Deep_search(ss,fs,GD,ST,num+1);//车站网络搜索 
		temp=head;

 	    while(temp!=NULL)
 		{
 			rtemp=temp->buttom;
 			while(rtemp!=NULL)//将搜索结果按直达和中转分类 
			{
				if(rtemp->next->next==NULL&&De<29)
				{
					Der[De]=temp->buttom;
					De++;
					break;
				}
			 	if(strcmp(rtemp->trainnum,rtemp->next->trainnum)&&Re<29)
			 	{
			 		Rev[Re]=temp->buttom;
			 		Re++;
		 		    break;
				}
				rtemp=rtemp->next;
			}
			temp=temp->nextHead;	
		} 
	
		Rev[Re]=NULL;//节点结束标志 
		Der[De]=NULL;
		judge=Re_operate(user,ss,fs,Der,Rev,mon,day,xnow,ynow,mark,num+1);
		De=0;//结果归零，重新规划 
		Re=0;
		destroyStackHead(head);//返回立即释放结果空间
	}
	*mark=0;
	return (2); 
}

/*对结果进行二次操作函数*/ 
int Re_operate(USER *user,char *ss,char *fs,StackNode **ResDer,StackNode **ResRev,char *mon,char *day,int *xnow,int *ynow,int *mark,int k) 
{
	int St_len=strlen(ss),Fi_len=strlen(fs);
	int Se[5]={0,0,0,0,0},C_position=-1;
	int i,mode=1,num=0,page=0;//模式1为直达，模式2为中转 
	int state=0,judge=0,tab=0,btnow=0,flag=0;
	StackNode *Der[30],*Rev[30];//结果保留值 

	setcolor(_BLACK);
	puthz(12,197,ss,1,16,_BLACK);
	puthz(122,197,fs,1,16,_BLACK);
	outtextxy(53,275,mon);
	outtextxy(85,275,day);
	puthz(69,275,"月",1,16,_BLACK);
	puthz(99,275,"日",1,16,_BLACK);
	memcpy(Der,ResDer,30*sizeof(StackNode *));//保证原始搜索信息不被破坏 
	memcpy(Rev,ResRev,30*sizeof(StackNode *));
	now_visual(Der,Rev,flag,mode,&num,k,page);
	while(judge!=2)
	{
		judge=0;//状态归位 防止持续刷新
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_Re_operate(&judge,C_position,num,*xnow,*ynow,state,flag,page);
		switch(judge)
		{
			case 3://直达方案 
				if(mode==2)	
				{
					ChangeVersion(xnow,ynow,Der,&num,&mode,flag,k);
					page=0;
				}
				break;
			case 4://中转方案 
				if(mode==1)	
				{
					ChangeVersion(xnow,ynow,Rev,&num,&mode,flag,k);
					page=0;
				}
				break;
			case 5://高级筛选 
				if(f_Adv_choose(xnow,ynow,Se))
				{
					*mark=0;
					memcpy(Der,ResDer,30*sizeof(StackNode *));
					memcpy(Rev,ResRev,30*sizeof(StackNode *));
					re_visual(Der,Rev,Se,flag,mode,&num,k);
					page=0;
					for(i=0;i<5;i++) Se[i]=0;//还原选择情形 
				}
				break;
			case 6://出发时间排序 
				T_sort(Der,k);
				T_sort(Rev,k);
				now_visual(Der,Rev,flag,mode,&num,k,page);
				break;
			case 7://耗时排序 
				TT_sort(Der,k);
				TT_sort(Rev,k);
				now_visual(Der,Rev,flag,mode,&num,k,page);
				break;
			case 8://改变显示方式 
				ChangeShowMode(&flag,xnow,ynow);
				now_visual(Der,Rev,flag,mode,&num,k,page);
				break;
			case 9://前一天 
				if(ShowLastDay(mon,day,k))
				{
					return 1;
				}
				break;
			case 10://后一天 
				if(ShowNextDay(mon,day,k))
				{
					return 1;
				}
				break;
			case 11:
				break;
			case 12://修改始发站 
				St_len=hz_input(xnow,ynow,10,190,80,220,ss,&tab,St_len);
				break;
			case 13://修改终点站 
				Fi_len=hz_input(xnow,ynow,120,190,190,220,fs,&tab,Fi_len);
				break;
			case 18://下一页 
			    redraw(*xnow,*ynow);
			    *mark=0;
			    page++;
				clearpart();
				now_visual(Der,Rev,flag,mode,&num,k,page); 
				break;
			case 19://重新搜索 
				clearpart();
				setcolor(_WHITE);
				fillcircle(450,35,3);
				setcolor(_RED);
				fillcircle(250,35,3);
				return 1;
			case 20://上一页
			    redraw(*xnow,*ynow);
			    *mark=0;
			    page--;
				clearpart();
				now_visual(Der,Rev,flag,mode,&num,k,page);
				break; 
		}
		for(i=0;i<4;i++)//点击搜索结果 
		{
			if(judge==14+i)
			{
				if(mode==1)
				{
					DEstart_book(Der[page*4+i],user,xnow,ynow,k);
				}
				else
				{
					REstart_book(Rev[page*4+i],user,xnow,ynow,k);
				}
				*mark=0;
				look();
				return 1;
			}
		}
	}
	return judge;	
}


	/*当前结果显示*/ 
void now_visual(StackNode **Der,StackNode **Rev,int flag,int mode,int *num,int k,int page)//返回1存在下一页  返回0不存在下一页
{
	int i;
	if(mode==1)//直达显示 
	{
		for(i=0;i<4&&Der[i+page*4]!=NULL;i++)
		{
			De_visual(Der[i+page*4],i,flag,k);
		}
		if(Der[i+page*4]!=NULL) 
		{
			puthz(590,422,"下一页",1,16,BCTcolor(0)); 
			i++;
		}
		if(page!=0)
		{
			puthz(202,422,"上一页",1,16,BCTcolor(0)); 
		}
	}
	else//中转显示 
	{
		for(i=0;i<4&&Rev[i+page*4]!=NULL;i++)
		{
			Re_visual(Rev[i+page*4],i,flag,k);
		}
		if(Rev[i+page*4]!=NULL) 
		{
			puthz(590,422,"下一页",1,16,BCTcolor(0)); 
			i++;
		}
		if(page!=0)
		{
			puthz(202,422,"上一页",1,16,BCTcolor(0));
		} 
	}
	if(i!=*num)
	{
		*num=i;
	}
} 

/*直达和中转切换*/
void ChangeVersion(int *xnow,int *ynow,StackNode **R,int *num,int *mode,int flag,int k)
{
	int i; 
	redraw(*xnow,*ynow);
	clearpart(); 
	if(*mode==1)//直达变中转 
	{
		for(i=0;i<4&&R[i]!=NULL;i++)
		{
			Re_visual(R[i],i,flag,k);
		}
		setcolor(_WHITE);
		fillcircle(250,35,3);
		setcolor(_RED);
		fillcircle(450,35,3);
		*mode=2;
	}
	else //中转变直达 
	{
		for(i=0;i<4&&R[i]!=NULL;i++)
		{
			De_visual(R[i],i,flag,k);
		}
		setcolor(_WHITE);
		fillcircle(450,35,3);
		setcolor(_RED);
		fillcircle(250,35,3);
		*mode=1;
	}
	if(R[i]!=NULL) 
	{
		puthz(590,422,"下一页",1,16,BCTcolor(0)); 
		i++;
	}
	*num=i;
	getbk_mouse(*xnow,*ynow);
	draw_mouse(*xnow,*ynow);
}


int frm(int x1,int y1,int x2,int y2)//结果框显示
{
	int i;
	for(i=0;i<=15;i++)
	{
		if(x1+i>x2-i||y1+i>y2-i)
		{
			return 0;//框全填充 
		}
		setcolor(BCTcolor(35+i));
		rectangle(x1+i,y1+i,x2-i,y2-i);
	}
	for(i=15;(x1+i<=x2-i)&&(y1+i<=y2-i);i++)
	{
		rectangle(x1+i,y1+i,x2-i,y2-i);
	} 
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);
	setcolor(BCTcolor(30));
	fillcircle(340,(y2+y1)/2,3);
	circle(500,(y2+y1)/2,3);
	line(343,(y2+y1)/2,497,(y2+y1)/2);
	return 1;
} 

/*车次框的选择函数*/ 
void select(int *xnow,int *ynow,int x,int y,int *Select)
{
	if(!(*Select))//选中 
	{
		setcolor(_BLACK);
	    *Select=1;
	}
	else//撤销 
	{
		setcolor(_WHITE);
	    *Select=0;
	}
	redraw(*xnow,*ynow);
	line(x+1,y+6,x+4,y+9);
	line(x+4,y+9,x+9,y+4);
	getbk_mouse(*xnow,*ynow);
	draw_mouse(*xnow,*ynow);
}

/*高级筛选操作函数*/ 
int f_Adv_choose(int *xnow,int *ynow,int *Se)
{
	int judge=0,state=0,C_position=0;
	int btnow=0,mark=1;
	char *image;
	if((image=malloc(23331))==NULL)
	{
		printf("Error!");
		getch();
		exit(1);
	}
	getimage(200,200,300,430,image);
	Adv_choose();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_Adv_choose(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 1://关闭窗口 
				redraw(*xnow,*ynow);
			    putimage(200,200,300,430,image);
				free(image);
				getbk_mouse(*xnow,*ynow);
				draw_mouse(*xnow,*ynow);
				return 0;
				/*选择车种*/
			case 2:
			    select(xnow,ynow,220,250,Se);
			    break;
			case 3:
				select(xnow,ynow,220,280,Se+1);
				break;
			case 4:
				select(xnow,ynow,220,310,Se+2);
				break;
			case 5:
			    select(xnow,ynow,220,340,Se+3);
				break;
			case 6:
			    select(xnow,ynow,220,370,Se+4);
				break;
			case 7:
				free(image);
				return 1;    
		}
		judge=0;
	}
}


/*改变车票的显示模式*/
void ChangeShowMode(int *flag,int *xnow,int *ynow)
{
	redraw(*xnow,*ynow);
	setcolor(GTcolor(10));
	bar(550,450,620,466);
	setcolor(_WHITE);
	if(*flag==0)
	{
		puthz(553,450,"显示余票",1,16,_WHITE);
		*flag=1; 
	}
	else if(*flag==1)
	{
		puthz(553,450,"显示价格",1,16,_WHITE);
		*flag=2; 
	}
	else if(*flag==2)
	{
		puthz(553,450,"显示",1,16,_WHITE);
		*flag=0; 
	} 
	getbk_mouse(*xnow,*ynow);
	draw_mouse(*xnow,*ynow);
} 
 
 
/*对车种进行限制后的重新显示*/ 
void re_visual(StackNode **Der,StackNode **Rev,int *Se,int flag,int mode,int *num,int k)
{
    int i,j,r=0;
    int De,Re;
    char name[7]="KTDGZ";
    StackNode *temp;
    
    for(i=0;i<5;i++)//获取未选中车次 
    {
    	if(Se[i])
    	{
    		name[i]='\0';
		}
	}
    for(i=0;Der[i]!=NULL;i++);//获取结果数 
    De=i;
    for(i=0;Rev[i]!=NULL;i++);
    Re=i;
    for(i=0;i<De;i++)//重置结果数组 
    {
    	for(j=0;j<5;j++)
    	{
    		if(Der[i]->trainnum[0]==name[j])
    		{
    			r=1;
			}
		}
		if(r)//确定为未选中车种
		{
			De--;
			Der[i]=Der[De];
			Der[De]=NULL;
			i--;
			r=0;	
		}
	}
	for(i=0;i<Re;i++)
	{
		for(j=0;j<5;j++)//第一程选择 
		{
			if(Rev[i]->trainnum[0]==name[j])
			{
				r=1;
			}
		}
		if(!r)//若第一程通过进行第二程选择 
		{
			temp=Rev[i];
			while(temp->next!=NULL)
			{
				temp=temp->next;
			}
			temp=temp->last;
			for(j=0;j<5;j++)
			{
				if(temp->trainnum[0]==name[j])
				{
					r=1;
				}
			}
		}
		if(r)//确定为未选中车种 
		{
			Re--;
			Rev[i]=Rev[Re];
			Rev[Re]=NULL;
			i--;
			r=0;
		}
	}
	clearpart();
	now_visual(Der,Rev,flag,mode,num,k,0);
}

/*按时间进行排序*/
void T_sort(StackNode **p,int k)
{
    KT_train KTtrain;
	G_train Gtrain;
	D_train Dtrain;
	Z_train Ztrain;
	StackNode *temp;
	int i,j,m=0,min1=0,min2=0;
	
	for(i=0;p[i]!=NULL&&i<29;i++)//结果指针的简单排序 
	{
		if(p[i]->trainnum[0]=='K'||p[i]->trainnum[0]=='T')
		{
			KT_read(p[i]->trainnum,&KTtrain,k);
			for(m=0;strcmp(KTtrain.station[m],p[i]->station);m++);
			TimeDistance_m("00:00",KTtrain.start_time[m],&min1);
		}
		else if(p[i]->trainnum[0]=='D')
		{
			D_read(p[i]->trainnum,&Dtrain,k);
			for(m=0;strcmp(Dtrain.station[m],p[i]->station);m++);
			TimeDistance_m("00:00",Dtrain.start_time[m],&min1);
		}
		else if(p[i]->trainnum[0]=='G')
		{
			G_read(p[i]->trainnum,&Gtrain,k);
			for(m=0;strcmp(Gtrain.station[m],p[i]->station);m++);
			TimeDistance_m("00:00",Gtrain.start_time[m],&min1);
		}
		else if(p[i]->trainnum[0]=='Z')
		{
			Z_read(p[i]->trainnum,&Ztrain,k);
			for(m=0;strcmp(Ztrain.station[m],p[i]->station);m++);
			TimeDistance_m("00:00",Ztrain.start_time,&min1);
		}
		for(j=i+1;p[j]!=NULL&&j<29;j++)
		{
			if(p[j]->trainnum[0]=='K'||p[j]->trainnum[0]=='T')
			{
				KT_read(p[j]->trainnum,&KTtrain,k);
				for(m=0;strcmp(KTtrain.station[m],p[j]->station);m++);
				TimeDistance_m("00:00",KTtrain.start_time[m],&min2);
			}
			else if(p[j]->trainnum[0]=='D')
			{
				D_read(p[j]->trainnum,&Dtrain,k);
				for(m=0;strcmp(Dtrain.station[m],p[j]->station);m++);
				TimeDistance_m("00:00",Dtrain.start_time[m],&min2);
			}
			else if(p[j]->trainnum[0]=='G')
			{
				G_read(p[j]->trainnum,&Gtrain,k);
				for(m=0;strcmp(Gtrain.station[m],p[j]->station);m++);
				TimeDistance_m("00:00",Gtrain.start_time[m],&min2);
			}
			else if(p[j]->trainnum[0]=='Z')
			{
				Z_read(p[j]->trainnum,&Ztrain,k);
				for(m=0;strcmp(Ztrain.station[m],p[j]->station);m++);
				TimeDistance_m("00:00",Ztrain.start_time,&min2);
			}
			if(min2<min1)//交换指针 
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
				min1=min2;//保存最短分钟数 
			}
		}
	}
}
/*旅行耗时排序*/
void TT_sort(StackNode **p,int k)
{
	int i,j,min1,min2;
	StackNode *temp;
	for(i=0;p[i]!=NULL&&i<29;i++)
	{
		min1=get_min(p[i],k);
		for(j=i+1;p[j]!=NULL&&j<29;j++)
		{
			min2=get_min(p[j],k);
			if(min2<min1)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
				min1=min2; 
			}
		}
	}
}

/*获取单个结果车站间隔分钟数*/
int get_min(StackNode *rp,int k)
{
	KT_train KTtrain;
	G_train Gtrain;
	D_train Dtrain;
	Z_train Ztrain;
	char t[2][6];
	int i,flag=0,min=0,mintemp;
	
	while(rp->next!=NULL)//进行站间的时间累加 
	{
		if(rp->trainnum[0]=='K'||rp->trainnum[0]=='T')
		{
			KT_read(rp->trainnum,&KTtrain,k);
			for(i=0;strcmp(rp->station,KTtrain.station[i]);i++);
			strcpy(t[1],KTtrain.start_time[i]);
		}
		else if(rp->trainnum[0]=='G')
		{
			G_read(rp->trainnum,&Gtrain,k);
			for(i=0;strcmp(rp->station,Gtrain.station[i]);i++);
			strcpy(t[1],Gtrain.start_time[i]);
		}
		else if(rp->trainnum[0]=='D')
		{
			D_read(rp->trainnum,&Dtrain,k);
			for(i=0;strcmp(rp->station,Dtrain.station[i]);i++);
			strcpy(t[1],Dtrain.start_time[i]);
		}
		else if(rp->trainnum[0]=='Z')
		{
			Z_read(rp->trainnum,&Ztrain,k);
			for(i=0;strcmp(rp->station,Ztrain.station[i]);i++);
			strcpy(t[1],Ztrain.start_time);
		}
		if(flag)
		{
			TimeDistance_m(t[0],t[1],&mintemp);
			min+=mintemp;
		}
		rp=rp->next;
		strcpy(t[0],t[1]);
		flag=1;
	}
	if(flag==0)//只有两站情况 
	{
		if(rp->trainnum[0]=='K'||rp->trainnum[0]=='T')
		{
			KT_read(rp->trainnum,&KTtrain,k);
			for(i=0;strcmp(rp->station,KTtrain.station[i]);i++);
			strcpy(t[0],KTtrain.start_time[i]);
		}
		else if(rp->trainnum[0]=='G')
		{
			G_read(rp->trainnum,&Gtrain,k);
			for(i=0;strcmp(rp->station,Gtrain.station[i]);i++);
			strcpy(t[0],Gtrain.start_time[i]);
		}
		else if(rp->trainnum[0]=='D')
		{
			D_read(rp->trainnum,&Dtrain,k);
			for(i=0;strcmp(rp->station,Dtrain.station[i]);i++);
			strcpy(t[0],Dtrain.start_time[i]);
		}
		else if(rp->trainnum[0]=='Z')
		{
			Z_read(rp->trainnum,&Ztrain,k);
			for(i=0;strcmp(rp->station,Ztrain.station[i]);i++);
			strcpy(t[0],Ztrain.start_time);
		}
	}
	rp=rp->next;//到达终点站 
	/*获取终点站时间*/ 
	if(rp->last->trainnum[0]=='K'||rp->last->trainnum[0]=='T')
	{
		KT_read(rp->last->trainnum,&KTtrain,k);
		for(i=0;strcmp(rp->station,KTtrain.station[i]);i++);
		strcpy(t[1],KTtrain.arrive_time[i]);
	}
	else if(rp->last->trainnum[0]=='G')
	{
		G_read(rp->last->trainnum,&Gtrain,k);
		for(i=0;strcmp(rp->station,Gtrain.station[i]);i++);
		strcpy(t[1],Gtrain.arrive_time[i]);
	}
	else if(rp->last->trainnum[0]=='D')
	{
		D_read(rp->last->trainnum,&Dtrain,k);
		for(i=0;strcmp(rp->station,Dtrain.station[i]);i++);
		strcpy(t[1],Dtrain.arrive_time[i]);
	}
	else if(rp->last->trainnum[0]=='Z')
	{
		Z_read(rp->last->trainnum,&Ztrain,k);
		for(i=0;strcmp(rp->station,Ztrain.station[i]);i++);
		strcpy(t[1],Ztrain.arrive_time);
	}
	TimeDistance_m(t[0],t[1],&mintemp);
	min+=mintemp;
	return min;
}

/*上一天搜索*/ 
int ShowLastDay(char *mon,char *day,int k)
{
	int _mon,_day;
	TIME _tm;
	
	_gettime(&_tm);
	if(k==1)//没有上一天 
	{
		return 0;
	}
	/*修改日期*/ 
	else 
	{
		_mon=atoi(mon);
		_day=atoi(day);
		if(_day==1)
		{
			if(_mon==1)
			{
				_mon=12;
			}
			else 
			{
				_mon--;
			}
			_day=days(_mon,_tm.year);
		}
		else 
		{
			_day--;
		}
		/*清除时间的位置*/ 
		setcolor(BCTcolor(30));
		bar(53,275,69,289);
		bar(85,275,99,289);
	}
	itoa(_mon,mon,10);
	itoa(_day,day,10);
	return 1;
}


/*下一天搜索*/
int ShowNextDay(char *mon,char *day,int k)//同上一天结构 
{
	int _mon,_day;
	TIME _tm;
	
	_gettime(&_tm);
	if(k==days(_tm.month,_tm.year))
	{
		return 0;
	}
	else 
	{
		_mon=atoi(mon);
		_day=atoi(day);
		if(_day==days(_mon,_tm.year))
		{
			_day=1;
			if(_mon==12)
			{
				_mon=1;
			}
			else 
			{
				_mon++;
			}
		}
		else
		{
			_day++;
		}
		setcolor(BCTcolor(30));
		bar(53,275,69,289);
		bar(85,275,99,289);
	}
	itoa(_mon,mon,10);
	itoa(_day,day,10);
	return 1;
}

