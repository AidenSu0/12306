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
#include "book.h" 
#include "order.h"
#include "mem.h"
/*======================*/ 
/*用户操作函数集*/
/*作者：苏新明*/
/*登录成功后，所有的用户外层操作*/ 
/*======================*/ 

/*登录预处理，读取用户信息*/
void f_login_loading(char *account,USER *user)
{
	FILE *fp;
	char accountpath[40]={"c:\\PRJ\\File\\account\\"};
	ORDER *Order,*pEnd;
	TIME _tm;
	char _tim[4][3]={{'\0','\0','\0'},{'\0','\0','\0'},{'\0','\0','\0'},{'\0','\0','\0'}};
	int tim[4],i,overTime=0,m=0,p=0;
	
	_gettime(&_tm);
	
	login_loading();
	strcat(accountpath,account);
	if((fp=fopen(accountpath,"r"))==NULL)
	{
		printf("Can't open file");
		getch();
		exit(0);
	}
	fread(user,sizeof(USER),1,fp);//读入账户信息 
	user->message[0][0]='\0';
	user->order=NULL;
	//此处可在读取阶段放置登录动画
	while(!feof(fp))//读入订单信息 
	{
		memset(_tim,'\0',12);
		if((Order=malloc(sizeof(ORDER)))==NULL)
		{
			printf("overflow!");
			getch();
			exit(1);
		}
		if((fread(Order,sizeof(ORDER),1,fp))!=1)//确保读入订单信息准确 
		{
			free(Order);
			break; 
		}
		/*删除已经发车车次*/
		for(i=0,p=0;i<16;i++)
		{
			if(Order->StartTime[i]>=48&&Order->StartTime[i]<=57)
			{
				_tim[0][p]=Order->StartTime[i];//月份
				p++;
			}
			else if(p) break;
		}
		for(p=0;i<16;i++)
		{
			if(Order->StartTime[i]>=48&&Order->StartTime[i]<=57)
			{
				_tim[1][p]=Order->StartTime[i];//日
				p++;
			}
			else if(p) break;
		}
		for(p=0;i<16;i++)
		{
			if(Order->StartTime[i]>=48&&Order->StartTime[i]<=57)
			{
				_tim[2][p]=Order->StartTime[i];//小时
				p++;
			}
			else if(p) break;
		}
		for(p=0;i<16;i++)
		{
			if(Order->StartTime[i]>=48&&Order->StartTime[i]<=57&&p<2)
			{
				_tim[3][p]=Order->StartTime[i];//分钟 
				p++;
			}
			else if(p) break;
		}
		for(i=0;i<4;i++)
		{
			tim[i]=atoi(_tim[i]);
		}
		/*是否超时判断*/ 
		overTime=(tim[0]<_tm.month)?((tim[0]==1&&_tm.month==12)?0:1):((tim[0]>_tm.month)?0:
			((tim[1]<_tm.day)?1:((tim[1]>_tm.day)?0:((tim[2]<_tm.hour)?1:((tim[2]>_tm.hour)?0:((tim[3]<_tm.min)?1:0))))));
			
		if(overTime)
		{
			free(Order);
			overTime=0;
			continue;
		}
		
		/*即将发车，获取消息提醒*/
		if(tim[0]==_tm.month&&(tim[1]==_tm.day||tim[1]==_tm.day+1))
		{
			strcpy(user->message[m],Order->TrainNum);
			strcpy(user->message[m+1],"");//添加结束符 
			m++;
		} 
		//加入订单信息 
		if(user->order==NULL)
		{
			user->order=Order;
		}
		else
		{
			pEnd->next=Order;
		} 
		pEnd=Order;
		pEnd->next=NULL;
	} 
	fclose(fp);
}

/*简单登录窗口*/ 
void login_loading()
{
	op_window(250,150,390,250);
	puthz(270,190,"登录中...",1,16,_BLACK);
}

/*用户一级控制函数*/ 
int f_UserControl(char *account,int *xnow,int *ynow,int *mark)
{
	USER user;
	int judge=2;
	
	f_login_loading(account,&user);
	while(1)
	{
		switch(judge)
		{
			case 2:
				*mark=0;//车票预订 
				judge=f_book(&user,xnow,ynow,mark);
				break;
			case 3://我的订单 
				*mark=0;
				judge=f_my_order(&user,xnow,ynow,mark);
				break;
			case 4://购票身份 
				*mark=0;
				judge=f_identity(&user,xnow,ynow,mark);
				break;
			case 5://我的账户 
				*mark=0;
				judge=f_my_account(&user,xnow,ynow,mark);
				break;
		}
		if(judge==0)
		{
			return 0;
		}
	}
}

/*我的订单操作函数*/ 
int f_my_order(USER *user,int *xnow,int *ynow,int *mark)
{
	int judge=3,order_num=0,C_position=-1;
	int state=0,btnow=0,page=0;
	
	my_order();
	order_num=visual_order(page,user);//获取并显示订单信息 
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_my_order(&judge,C_position,*xnow,*ynow,state,order_num);
		switch(judge)
		{
			case 6://改签1 
				*mark=0; 
				reschedul(page*2,user,xnow,ynow,mark);
				my_order();
				order_num=visual_order(page,user);
				break;
			case 7://退票1
				*mark=0;
				refund(page*2,user);
				page=0;
				my_order();
				order_num=visual_order(page,user);
				break;
			case 8://改签2 
				*mark=0;
				reschedul(page*2+1,user,xnow,ynow,mark);
				my_order();
				order_num=visual_order(page,user);
				break;
			case 9://退票2 
				*mark=0;
				refund(page*2+1,user);
				page=0;
				my_order();
				order_num=visual_order(page,user);
				break;
			case 10://下一页 
				*mark=0;
				page++;
				my_order();
				order_num=visual_order(page,user); 
				break;
		}
		if(judge==2||judge==4||judge==5)//换模块 
		{
			return judge;
		}
		judge=3;
	}
}

    /*身份信息管理函数*/
int f_identity(USER *user,int *xnow,int *ynow,int *mark)
{
	int judge=4,num=0,i;
	int state=0,btnow=0,C_position=-1;
	
	identity();
	num=id_visual(user);
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_identity(&judge,C_position,*xnow,*ynow,state,num);
		if(judge==7)//添加新信息 
		{
				*mark=0;
				judge=f_add_identity(user,xnow,ynow,mark);
				identity();
				num=id_visual(user);
		}
		for(i=0;i<num;i++)//删除身份 
		{
			if(judge==8+i)
			{
				*mark=0;
				delete_id(i,user);
				identity();
				num=id_visual(user);//删除后重新显示 
				break;
			}
		}
		if(judge==2||judge==3||judge==5)
		{
			return judge;
		}
		judge=4;
	}
}

/*========================*/
/*身份操作模块*/
/*========================*/

/*添加身份函数*/
int f_add_identity(USER *user,int *xnow,int *ynow,int *mark)
{
	int judge=0,C_position=-1;
	int state=0,btnow=0,tab=0,St=0,sex=0;
	ID id;
	int len[7]={0,0,0,0,0,0,0};//初始化字符长度 
	
	add_identity();
	
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_add_identity(&judge,C_position,*xnow,*ynow,state,St);
		switch(judge)
		{
			case 4://关闭 
				*mark=0;
				return judge;
			case 6://保存信息 
				if(save_identity(user,&id,len,St))
				{
					*mark=0;
					return 4;
				}
				break;
				/*输入信息*/ 
			case 7:
				len[0]=nhz_input(xnow,ynow,250,55,420,85,id.identity_num,&tab,0,len[0]);
				if(tab==1)
				{
					judge++;
					continue;
				}
				break;
			case 8:
				len[1]=hz_input(xnow,ynow,250,105,420,135,id.name,&tab,len[1]);
				if(tab==1)
				{
					judge++;
					continue;
				}
				break;
			case 9:
				sex=choose_sex(xnow,ynow,250,155,mark);
				if(sex) len[2]=4; 
				break;
			case 10:
				St=choose_id(xnow,ynow,mark);
				redraw(*xnow,*ynow);
				if(St==2)//学生信息 
				{
					len[3]=4;
					add_info();
				}
				else//成人信息 
				{
					if(St) len[3]=4;
					setcolor(BCTcolor(40));
					bar(155,253,430,387);
				}
				getbk_mouse(*xnow,*ynow);
				draw_mouse(*xnow,*ynow);
				break;
			case 11:
				len[4]=hz_input(xnow,ynow,250,255,420,285,id.university,&tab,len[4]);
				if(tab==1)
				{
					judge++;
					continue;
				}
				break;
			case 12:
				len[5]=nhz_input(xnow,ynow,250,305,420,335,id.stu_num,&tab,0,len[5]);
				if(tab==1)
				{
					judge++;
					continue;
				}
				break;
			case 13:
				len[6]=nhz_input(xnow,ynow,250,355,420,385,id.entry_time,&tab,0,len[6]);
				break;	
		}
		tab=0;
		judge=0;
	}
}

/*保存身份函数*/ 
int save_identity(USER *user,ID *id,int *len,int St)
{
	char path[50]={"C:\\PRJ\\File\\id\\"};
	FILE *fp;
	int i,maxjudge=(St==2)?7:4;
	
	setcolor(BCTcolor(40));
	bar(151,420,300,440);
	/*输入规范性判断*/ 
	if(len[0]==18)
	{
		for(i=0;i<18;i++)
		{
			if(id->identity_num[i]<48||id->identity_num[i]>57)
			{
				puthz(151,420,"身份证号不合法!",1,16,_RED);
				return 0;
			}
		}
	}
	else 
	{
		puthz(151,420,"身份证号位数错误!",1,16,_RED);
		return 0;
	}
	if(len[1]>2&&len[1]<9)
	{
		for(i=0;i<len[1];i++)
		{
			if(!((id->name[i])&0x80))
			{
				puthz(151,420,"名字不合法!",1,16,_RED);
				return 0;
			}
		}
	}
	else 
	{
		puthz(151,420,"名字长度不合法!",1,16,_RED);
		return 0;
	}
	for(i=0;i<maxjudge;i++)
	{
		if(len[i]==0)
		{
			puthz(151,420,"请完善你的信息!",1,16,_RED);
		    return 0;
		}
	}
	/*确认保存*/ 
	strcat(path,(id->identity_num)+10);
	if((fp=fopen(path,"w"))==NULL)
	{
		printf("Can't open file");
		getch();
		exit(1);
	}
	fwrite(id,sizeof(ID),1,fp);
	fclose(fp);
	for(i=0;i<9;i++)
	{
		if(user->AllIdentity[i][0]=='\0')//将身份添加到用户信息 
		{
			strcpy(user->AllIdentity[i],id->name);
			user->AllIdentity[i+1][0]='\0';
			break;
		}
	}
	if(i==9)
	{
		warning_overflow(270,150);//用户已满 
	}
	return 1;
}

	/*选择性别*/ 
int choose_sex(int *x,int *y,int x1,int y1,int *mark)
{
	char *image;
	int state=0,judge=-1,C_position=-1,btnow=0;
	int rx=*x+20,ry=*y;
	if((image=malloc(6561))==NULL)
	{
		printf("overflow");
		getch();
		exit(1);
	}
	getimage(rx,ry,rx+80,ry+80,image);
	choose_window(rx,ry);
	puthz(rx+40,ry+27,"男",1,16,_BLACK);
	puthz(rx+40,ry+57,"女",1,16,_BLACK);
	while(1)
	{
		state=mouse_control(x,y,&btnow,mark);
		C_position=check_choose(&judge,C_position,rx,ry,*x,*y,state);
		if(judge!=-1)
		{
			redraw(*x,*y);
			putimage(rx,ry,rx+80,ry+80,image);
			free(image);
			getbk_mouse(*x,*y);
			draw_mouse(*x,*y);
			switch(judge)
			{
				case 0:
					setcolor(_WHITE);
					bar(x1+2,y1+7,x1+18,y1+23);
					return 0;
				case 1:
					setcolor(_WHITE);
					bar(x1+2,y1+7,x1+18,y1+21);
					puthz(x1+2,y1+7,"男",1,16,_BLACK); 
					return 1;
				case 2:
					setcolor(_WHITE);
					bar(x1+2,y1+7,x1+18,y1+21);
					puthz(x1+2,y1+7,"女",1,16,_BLACK); 
					return 2;
			} 	
		}
	}
}

/*选择身份*/ 
int choose_id(int *x,int *y,int *mark)
{
	char *image;
	int state=0,judge=-1,C_position=-1,btnow=0;
	int rx=*x+20,ry=*y;
	if((image=malloc(6561))==NULL)
	{
		printf("overflow");
		getch();
		exit(1);
	}
	getimage(rx,ry,rx+80,ry+80,image);
	choose_window(rx,ry);
	puthz(rx+30,ry+27,"成人",1,16,_BLACK);
	puthz(rx+30,ry+57,"学生",1,16,_BLACK);
	while(1)
	{
		state=mouse_control(x,y,&btnow,mark);
		C_position=check_choose(&judge,C_position,rx,ry,*x,*y,state);
		if(judge!=-1)
		{
			redraw(*x,*y);
			putimage(rx,ry,rx+80,ry+80,image);
			free(image);
			getbk_mouse(*x,*y);
			draw_mouse(*x,*y);
			switch(judge)
			{
				case 0:
					setcolor(_WHITE);
					bar(251,206,291,234);
					return 0;
				case 1:
					setcolor(_WHITE);
					bar(251,206,291,234);
					puthz(252,212,"成人",1,16,_BLACK); 
					return 1;
				case 2:
					setcolor(_WHITE);
					bar(251,206,291,234);
					puthz(252,212,"学生",1,16,_BLACK); 
					return 2;
			} 	
		}
	}
}

/*显示身份函数*/ 
int id_visual(USER *user)
{
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<2;j++)
		{
			if(user->AllIdentity[i*2+j][0]!='\0')
			{
				info_bar(90+j*250,170+i*35,300+j*250,200+i*35);
				puthz(110+j*240,177+i*35,user->AllIdentity[i*2+j],1,16,_BLACK);
				setcolor(_RED);
				fillcircle(280+j*240,185+i*35,10);
				setcolor(_WHITE);
				bar(275+j*240,183+i*35,285+j*240,187+i*35);
			}
			else
			{
				return (i*2+j);
			}
		}
	}
}

	/*删除身份函数*/
void delete_id(int i,USER *user)
{
	int j;
	for(j=i;user->AllIdentity[j][0]!='\0';j++);
	strcpy(user->AllIdentity[i],user->AllIdentity[j-1]);
	user->AllIdentity[j-1][0]='\0';
	setcolor(_WHITE);
	bar(270,200,370,300);
	setcolor(_BLACK);
	rectangle(270,200,370,300);
	CK_right(320,235);
	puthz(288,280,"删除成功!",1,16,_BLACK);
	delay(1000); 
}

/*=========================*/
/*用户管理模块*/ 
/*=========================*/ 

/*账户管理一级控制*/
int f_my_account(USER *user,int *xnow,int *ynow,int *mark)
{
	int judge=5,C_position=-1;
	int state=0,btnow=0;
	
	my_account();
	puthz(250,165,user->account_name,1,16,GTcolor(20));
	puthz(150,200,user->signature,1,16,GTcolor(30));
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_my_account(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 8://时刻表 
				*mark=0;
				judge=f_time_table(xnow,ynow,mark);
				my_account();
				puthz(250,165,user->account_name,1,16,GTcolor(20));
				puthz(150,200,user->signature,1,16,GTcolor(30));
				break;
			case 9://消息 
				*mark=0;
				judge=f_message(user,xnow,ynow,mark);
				my_account();
				puthz(250,165,user->account_name,1,16,GTcolor(20));
				puthz(150,200,user->signature,1,16,GTcolor(30));
				break;
			case 10://设置 
				*mark=0;
				judge=f_settings(user,xnow,ynow,mark);
				if(judge==-1)
				{
					my_account();
					puthz(250,165,user->account_name,1,16,GTcolor(20));
					puthz(150,200,user->signature,1,16,GTcolor(30));
					*mark=0;
				}
				break;
			case 11:/*反馈*/ 
				*mark=0;
				judge=f_feedback(xnow,ynow,mark);
				my_account();
				puthz(250,165,user->account_name,1,16,GTcolor(20));
				puthz(150,200,user->signature,1,16,GTcolor(30));
				break;
			case 12://关于 
				*mark=0;
				judge=f_about(xnow,ynow,mark);
				my_account();
				puthz(250,165,user->account_name,1,16,GTcolor(20));
				puthz(150,200,user->signature,1,16,GTcolor(30));
				break;
		}
		if(judge==0)
		{
			return 0;
		}
		if(judge==2||judge==3||judge==4)
		{
			return judge;
		}
	}
}
/*时刻表函数*/ 
int f_time_table(int *xnow,int *ynow,int *mark)
{
	int judge=0,C_position=-1;
	int state=0,btnow=0,length[3]={0,0,0};
	char trainnum[25],mon[3],day[3];
	int tab=0;
	time_table();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_time_table(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 5:
				*mark=0;
				return judge;
			case 6:
				length[0]=nhz_input(xnow,ynow,100,50,300,80,trainnum,&tab,0,length[0]);
				break;
			case 7:
				length[1]=nhz_input(xnow,ynow,340,50,370,80,mon,&tab,0,length[1]);
				break;
			case 8:
				length[2]=nhz_input(xnow,ynow,390,50,420,80,day,&tab,0,length[2]);
				break;
			case 9:
				visual_TTB(trainnum,mon,day,xnow,ynow);
				redraw(*xnow,*ynow);
				setcolor(BCTcolor(30));
				bar(10,100,630,450);
				getbk_mouse(*xnow,*ynow);
				draw_mouse(*xnow,*ynow);
				break;
		}
		judge=0;
	}
}

/*消息函数*/ 
int f_message(USER *user,int *xnow,int *ynow,int *mark)
{
	int judge=9,C_position=-1;
	int state=0,btnow=0,i;
	char remind[30]={"您订购的     次列车即将发车！"};
	message();
	for(i=0;i<300&&user->message[i][0]!='\0';i++)
	{
		info_bar(80,50+i*40,340,80+i*40);
		puthz(100,57+i*40,remind,1,16,_WHITE);
		puthz(164,57+i*40,user->message[i],1,16,_WHITE);
	}
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_message(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 5:
				*mark=0;
				return judge;
		}
	}
}

/*设置函数*/ 
int f_settings(USER *user,int *xnow,int *ynow,int *mark)
{
	int judge=10,C_position=-1;
	int state=0,btnow=0;
	char *image;
	
	if((image=malloc(24531))==NULL)
	{
		printf("overflow");
		getch();
		exit(1);
	}
	redraw(*xnow,*ynow);
	getimage(290,200,400,420,image);
	settings();
	
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_settings(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 5://返回 
				redraw(*xnow,*ynow);
				putimage(290,200,400,420,image);
				getbk_mouse(*xnow,*ynow);
				draw_mouse(*xnow,*ynow);
				free(image);
				return 5;
			case 6://修改密码 
				judge=change_password(user,xnow,ynow);
				free(image);
				return -1;
			case 7://更改主题 
				change_theme(xnow,ynow);
				free(image); 
				return -1;
			case 8://我的资料 
				profile(user,xnow,ynow);
				free(image);
				return -1;
				break;
			case 9://清除缓存（伪） 
				clear_data();
				redraw(*xnow,*ynow);
				putimage(290,200,400,420,image);
				getbk_mouse(*xnow,*ynow);
				draw_mouse(*xnow,*ynow);
				free(image);
				return 5;
			case 0://退出登录 
				*mark=0;
				free(image);
				save_user(user);
				return 0;
		}
		judge=10;
	}
}

/*反馈函数*/ 
int f_feedback(int *xnow,int *ynow,int *mark)
{
	int judge=11,C_position=-1;
	int state=0,btnow=0,tab=0,i;
	int len[3]={0,0,0};
	FILE *fp,*pfp;
	char advice[600],email[60],phonenum[60];
	char path[50]={"c:\\PRJ\\File\\advice\\"},temp[5];
	feedback();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_feedback(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 5:
				*mark=0;
				return judge;
			case 6:
				len[0]=hz_input(xnow,ynow,100,30,540,340,advice,&tab,len[0]);
				if(tab) judge++;
				else break;
			case 7:
				len[1]=nhz_input(xnow,ynow,100,350,540,370,email,&tab,0,len[1]);
				if(tab) judge++;
				else break;
			case 8:
				len[2]=nhz_input(xnow,ynow,100,380,540,400,phonenum,&tab,0,len[2]);
				break;
			case 9:
				if(len[0]==0)
				{
					setcolor(_WHITE); 
					bar(100,450,270,470);
					puthz(100,450,"请输入您的建议！",1,16,_RED);
					break;
				}
				else if(len[1]==0)
				{
					setcolor(_WHITE); 
					bar(100,450,270,470);
					puthz(100,450,"请输入正确的邮箱！",1,16,_RED);
					break;
				} 
				else if(len[2]!=11||phonenum[0]!='1')
				{
					setcolor(_WHITE); 
					bar(100,450,270,470);
					puthz(100,450,"请输入正确的手机号码！",1,16,_RED);
					break;
				}
				if((fp=fopen("c:\\PRJ\\File\\advice\\num.dat","r+"))==NULL)
				{
					printf("can't open file");
					getch();
					exit(1);
				}
				for(i=0;i<300;i++)
				{
					fgets(temp,5,fp);
					if(feof(fp))
					{
						break;
					}
				}
				itoa(i,temp,10);
				strcat(path,temp);
				if((pfp=fopen(path,"w"))==NULL)
				{
					printf("can't open file");
					getch();
					exit(1);
				}
				strcat(temp,"\n");
				fputs(temp,fp);
				fclose(fp);
				fputs(advice,pfp);
				fputc('\n',pfp);
				fputs(email,pfp);
				fputc('\n',pfp);
				fputs(phonenum,pfp);
				fputc('\n',pfp);
				fclose(pfp);
				success_submit();
				*mark=0;
				return 5;
		}
		judge=11;
	}
}

/*关于函数*/
int f_about(int *xnow,int *ynow,int *mark)
{
	int judge=12,C_position=-1;
	int state=0,btnow=0;
	
	about();
	
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,mark);
		C_position=check_about(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 5:
				*mark=0;
				return judge;
		}
	}
}

void save_user(USER *user)
{
	FILE *fp;
	ORDER *order=user->order,*temp;
	char path[50]={"c:\\PRJ\\File\\account\\"};
	
	strcat(path,user->account_name);
	if((fp=fopen(path,"w"))==NULL)
	{
		printf("Can't open file");
		getch();
		exit(1);
	}
	fwrite(user,sizeof(USER),1,fp);
	while(order!=NULL)
	{
		fwrite(order,sizeof(ORDER),1,fp);
		order=order->next;
	}
	fclose(fp);
	while(user->order!=NULL)
	{
		temp=user->order;
		user->order=temp->next;
		free(temp);//释放订单内存 
	} 
}

/*时刻表判断*/ 
void visual_TTB(char *trainnum,char *mon,char *day,int *xnow,int *ynow)
{
	TIME _tm;
	FILE *fp;
	int num,day_,_mon,_day,btnow=0,state=0,mark=1,judge=0,C_position=-1;
	
	_gettime(&_tm);
	day_=days(_tm.month,_tm.year);
	_mon=atoi(mon);
	_day=atoi(day);
	if(_day<_tm.day)
	{
		num=day_+_day-_tm.day;
	}
	else
	{
		num=_day-_tm.day;
	}
	if(_mon>_tm.month+1||_mon<_tm.month||(_day>_tm.day&&_mon!=_tm.month))
	{
		setcolor(BCTcolor(20));
		bar(250,100,390,200);
		puthz(300,140,"请规范输入",1,16,_BROWN);
		delay(2000);
		return;
	}
	else
	{
		op_window(10,100,630,450);
		shut(630,100);
		if(!TTB(trainnum,num+1))
		{
			setcolor(BCTcolor(20));
			bar(250,100,390,200);
			puthz(300,140,"请规范输入",1,16,_BROWN);
			delay(2000);
			return;
		}	
		while(1)
		{
			state=mouse_control(xnow,ynow,&btnow,&mark);
			C_position=check_TTB(&judge,C_position,*xnow,*ynow,state);
			if(judge==1)
			{
				return;
			}
		}
	}
}

/*时刻表显示*/ 
int TTB(char *trainnum,int num)
{
	int page,i;
	KT_train KTtrain;
	G_train Gtrain;
	D_train Dtrain;
	Z_train Ztrain;
	
	if(trainnum[0]=='K'||trainnum[1]=='T')
	{
		if(!KT_read(trainnum,&KTtrain,num))
		{
			return 0;
		}
		for(page=0;page<3;page++)
		{
			puthz(30+page*200,122,"车站名称",1,16,_BLACK);
			puthz(110+page*200,122,"到时",1,16,_BLACK);
			puthz(160+page*200,122,"发时",1,16,_BLACK);
			for(i=0;i<10;i++)
			{
				setcolor(_BROWN); 
				fillcircle(20+page*200,158+i*30,5);
				puthz(30+page*200,150+i*30,KTtrain.station[i+page*10],1,16,_BLACK);
				puthz(160+page*200,150+i*30,KTtrain.start_time[i+page*10],1,16,_BLACK);
				if(i==0&&page==0) continue;
				puthz(110+page*200,150+i*30,KTtrain.arrive_time[i+page*10],1,16,_BLACK);
				if(!strcmp(KTtrain.start_time[i+page*10],"###"))  return 1;
			}
		}
	}
	else if(trainnum[0]=='D')
	{
		if(!D_read(trainnum,&Dtrain,num))
		{
			return 0;
		}
		for(page=0;page<3;page++)
		{
			puthz(30+page*200,122,"车站名称",1,16,_BLACK);
			puthz(110+page*200,122,"到时",1,16,_BLACK);
			puthz(160+page*200,122,"发时",1,16,_BLACK);
			for(i=0;i<10;i++)
			{
				setcolor(_BROWN);
				fillcircle(20+page*200,158+i*30,5);
				puthz(30+page*200,150+i*30,Dtrain.station[i+page*10],1,16,_BLACK);
				puthz(160+page*200,150+i*30,Dtrain.start_time[i+page*10],1,16,_BLACK);
				if(i==0&&page==0) continue;
				puthz(110+page*200,150+i*30,Dtrain.arrive_time[i+page*10],1,16,_BLACK);
				if(!strcmp(Dtrain.start_time[i+page*10],"###"))  return 1;
			}
		}
	}
	else if(trainnum[0]=='G')
	{
		if(!G_read(trainnum,&Gtrain,num))
		{
			return 0;
		}
		for(page=0;page<3;page++)
		{
			puthz(30+page*200,122,"车站名称",1,16,_BLACK);
			puthz(110+page*200,122,"到时",1,16,_BLACK);
			puthz(160+page*200,122,"发时",1,16,_BLACK);
			for(i=0;i<10;i++)
			{
				setcolor(_BROWN); 
				fillcircle(20+page*200,158+i*30,5);
				puthz(30+page*200,150+i*30,Gtrain.station[i+page*10],1,16,_BLACK);
				puthz(160+page*200,150+i*30,Gtrain.start_time[i+page*10],1,16,_BLACK);
				if(i==0&&page==0) continue;
				puthz(110+page*200,150+i*30,Gtrain.arrive_time[i+page*10],1,16,_BLACK);
				if(!strcmp(Gtrain.start_time[i+page*10],"###"))  return 1;
			}
		}
	}
	else if(trainnum[0]=='Z')
	{
		if(!Z_read(trainnum,&Ztrain,num))
		{
			return 0;
		}
		puthz(30,122,"车站名称",1,16,_BLACK);
		puthz(110,122,"到时",1,16,_BLACK);
		puthz(160,122,"发时",1,16,_BLACK);
		puthz(30,150,Ztrain.station[0],1,16,_BLACK);
		puthz(30,180,Ztrain.station[1],1,16,_BLACK);
		puthz(160,150,Ztrain.start_time,1,16,_BLACK);
		puthz(110,180,Ztrain.arrive_time,1,16,_BLACK);
		return 1;
	}
}

/*更改密码*/ 
int change_password(USER *user,int *xnow,int *ynow)
{
	int mark=1,btnow=0,state=0,C_position=-1,tab=0,all=0;
	int len[3]={0,0,0},judge=0,i,pos=-1,right1=0,right2=0;
	char ogl_pw[20],new_pw[20],renew_pw[20];
	char acc[18],pw[300][18],temp[18];
	FILE *fp,*pfp;
	Password();
	strcpy(temp,user->account_name);
	strcat(temp,"\n");
	fp=fopen("c:\\PRJ\\File\\account.dat","r");
	pfp=fopen("c:\\PRJ\\File\\key.dat","r");
	for(i=0;!feof(fp)&&!feof(pfp);i++)
	{
		fgets(acc,18,fp);
		if(!strcmp(temp,acc)&&pos==-1)
		{
			pos=i;
		}
		fgets(pw[i],18,pfp);
	} 
	all=i;
	fclose(fp);
	fclose(pfp);
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_password(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 1:
				return 1;
			case 2:
				len[0]=nhz_input(xnow,ynow,130,60,265,90,ogl_pw,&tab,0,len[0]);
				strcat(ogl_pw,"\n");
				if(strcmp(ogl_pw,pw[pos]))
				{
					puthz(130,97,"密码不正确!",1,16,_RED);
					right1=0;
				}
				else
				{
					setcolor(BCTcolor(40));
					bar(130,95,230,85);
					right1=1;
				}
			case 3:
				len[1]=nhz_input(xnow,ynow,130,120,265,150,new_pw,&tab,1,len[1]);
			case 4:
				len[2]=nhz_input(xnow,ynow,130,180,265,210,renew_pw,&tab,1,len[2]);
				if(strcmp(new_pw,renew_pw))
				{
					puthz(130,217,"密码不匹配!",1,16,_RED);
					right2=0;
				}
				else
				{
					setcolor(BCTcolor(40));
					bar(130,215,230,235);
					right2=1;
				}
				break;
			case 6:
				if(right1&&right2)
				{
					strcpy(pw[pos],new_pw);
					strcat(pw[pos],"\n");
					fp=fopen("c:\\PRJ\\File\\key.dat","w");
					for(i=0;i<all;i++)
					{
						fputs(pw[i],fp);
					}
					fclose(fp);
					success_hint();
					return 6;
				}
				break;
		}
		judge=0;
	}
}

/*更换主题*/
void change_theme(int *xnow,int *ynow)
{
	int C_position=-1,btnow=0,state=0,judge=0,mark=1;
	theme();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_theme(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 1:
				return;
			case 2:
				SetPalette();
				break;
			case 3:
				SetPalette3();
				break;
			case 4:
				SetPalette1();
				break;
			case 5:
				SetPalette2();
				break;
			case 6:
				SetPalette4();
				break;
		}
		judge=0;
	}
}

/*我的资料函数*/ 
void profile(USER *user,int *xnow,int *ynow)
{
	int judge=0,state=0,btnow=0,C_position=-1,mark=1;
	int len[4],tab=0,i;
	char temp[21];
	int sex=0;
	
	my_profile();
	/*资料上载*/ 
	len[0]=strlen(user->name);
	len[1]=strlen(user->idnum);
	len[2]=strlen(user->phone_num);
	len[3]=strlen(user->signature); 
	puthz(92,57,user->name,1,16,_BLACK);
	puthz(92,117,user->sex,1,16,_BLACK);
	puthz(92,177,user->idnum,1,16,_BLACK);
	puthz(92,237,user->phone_num,1,16,_BLACK);
	if(len[3]>20)
	{
		for(i=0;i<20;i++)
		{
			temp[i]=user->signature[i];
		}
		temp[20]='\0';
		puthz(92,297,temp,1,16,_BLACK);
		puthz(92,327,&(user->signature[20]),1,16,_BLACK);
	}
	else 
	{
		puthz(92,297,user->signature,1,16,_BLACK); 
	}
	/*资料修改*/ 
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_profile(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 1:
				return;
			case 2:
				len[0]=hz_input(xnow,ynow,90,50,255,80,user->name,&tab,len[0]);
				if(tab)
				{
					judge++;
				}
				else break;
			case 3:
				sex=choose_sex(xnow,ynow,90,110,&mark);
				if(sex==1)
				{
					strcpy(user->sex,"男"); 
				} 
				else if(sex==2)
				{
					strcpy(user->sex,"女"); 
				}
				break;
			case 4:
				len[1]=nhz_input(xnow,ynow,90,170,255,200,user->idnum,&tab,0,len[1]);
				if(tab)
				{
					judge++;
				}
				else break;
			case 5:
				len[2]=nhz_input(xnow,ynow,90,230,255,260,user->phone_num,&tab,0,len[2]);
				if(tab)
				{
					judge++;
				}
				else break;
			case 6:
				len[3]=hz_input(xnow,ynow,90,290,255,350,user->signature,&tab,len[3]);
				break; 
			case 7:
				return;
		}
		tab=0;
		judge=0;
	}
}
