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
#include "booking.h"

/*======================*/ 
/*进入购票函数集*/ 
/*作者：苏新明*/
/*选中搜索结果后的支付操作*/ 
/*======================*/


/*直达开始购票*/
void DEstart_book(StackNode *p,USER *user,int *xnow,int *ynow,int k)
{
	int mark=0,btnow=0,state=0,num,i;
	int judge=0,C_position=-1,idnum=0,buyer_num=0;
	StackNode **q=NULL,*r[2];
	int price[4]={0,0,0,0},seatnum[3]={0,0,0},consumer[10]={0,0,0,0,0,0,0,0,0,0};
	int kind=-1;//标志选择票种 
	r[0]=p;
	r[1]=NULL;
	

	idnum=DEstbook(user);//直达必要元素显示 
	DEdetail_visual(p,price,seatnum,k);//直达价格和座位显示与获取 
	now_visual(r,q,0,1,&num,k,0);//显示行程信息 
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_DEstbook(&judge,C_position,*xnow,*ynow,state,idnum);
		switch(judge)
		{
			case 1:
				return;
			case 2://立即支付 
				if(price[kind]*buyer_num!=0)
				{
					if(kind!=3&&seatnum[kind]<buyer_num)
					{
						break;
					}
					instant_bookDE(p,kind,user,consumer,xnow,ynow,k); 
				}
				break;		
		}
		for(i=0;i<4;i++)//选择票种 
		{
			if(judge==i+3)
			{
				kind=i;//选择票种标志 
				change_plan_1(buyer_num,price,i,*xnow,*ynow);//状态改变 
			}
		}
		for(i=0;i<idnum;i++)//选择购票人 
		{
			if(judge==7+i)
			{
				if(kind==-1)
				{
					buyer_num=change_plan_2(buyer_num,0,consumer,i,*xnow,*ynow,1);//选中购票人 
				}
				else
				{
					buyer_num=change_plan_2(buyer_num,price[kind],consumer,i,*xnow,*ynow,1);//撤销选中购票人 
				}
			}
		}
		judge=0;
	}
}

/*中转开始购票*/ 
void REstart_book(StackNode *p,USER *user,int *xnow,int *ynow,int k)
{
	int mark=0,btnow=0,state=0,start=0,idnum=0,buyer_num=0;
	int judge=0,C_position=-1,i=0,num=0,kind[2]={-1,-1},consumer[10]={0,0,0,0,0,0,0,0,0,0};
	StackNode *q=NULL,*r[3];
	int price[2][4]={{0,0,0,0},{0,0,0,0}},seatnum[2][3]={{0,0,0},{0,0,0}};
	
	r[0]=p;//第一程头指针保存 
	/*中转分割*//*此处操作目的在于使用book.c中的成熟代码，避免代码重复*/
	while(p!=NULL)
	{
		if(strcmp(p->last->trainnum,p->trainnum)&&i>0)//到中转节点 
		{
			if((q=(StackNode *)malloc(sizeof(StackNode)))==NULL)
			{
				printf("overflow");
				getch();
				exit(0);
			}
			/*下一程头站复制*/ 
			strcpy(q->station,p->station);
			strcpy(q->trainnum,p->trainnum);
			q->last=NULL;
			q->next=p->next;
			r[1]=q; //头指针保存 
			p->next=NULL;//断开中转 
			break;
		}
		p=p->next;
		i++;
	}
	r[2]=NULL;
	 
	idnum=REstbook(user);
	REdetail_visual(r[0],r[1],price,seatnum,k);
	now_visual(r,&q,0,1,&num,k,0);
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_REstbook(&judge,C_position,*xnow,*ynow,state,idnum);
		if(judge==1)//退出购票 
		{
			p->next=q->next;//连接中转，恢复结果 
			free(q);
			return;
		}
		else if(judge==2)//立即预定 
		{
			if(kind[0]!=-1&&kind[1]!=-1&&price[0][kind[0]]*buyer_num!=0&&price[1][kind[1]]*buyer_num!=0)//确定已有选择进入 
			{
				if((kind[0]!=3&&seatnum[0][kind[0]]<buyer_num)||(kind[1]!=3&&seatnum[1][kind[1]]<buyer_num))//余票不足 
				{
					break;
				}
				else
				{
					instant_bookRE(r[0],r[1],kind,user,consumer,xnow,ynow,k);
				}
			}
		}
		for(i=0;i<8;i++)//选择票种 
		{
			if(judge==3+i)
			{
				change_plan_3(buyer_num,price,i,kind,*xnow,*ynow);		
			}
		}
		for(i=0;i<idnum;i++)//选择购票人 
		{
			if(judge==11+i)
			{
				if(kind[0]!=-1&&kind[1]!=-1)
				{
					buyer_num=change_plan_2(buyer_num,price[0][kind[0]]+price[1][kind[1]],consumer,i,*xnow,*ynow,2);
				}
				else
				{
					buyer_num=change_plan_2(buyer_num,0,consumer,i,*xnow,*ynow,2);
				}
			}	
		}
		judge=0;
	}
}

	/*点击直达选择票种*/ 
void change_plan_1(int buyer_num,int *price,int kind_click,int x,int y)
{
	int i,all_money=0;
	char _all_money[6];
	redraw(x,y);
	setcolor(BCTcolor(0));
	for(i=0;i<4;i++)//票种未选中消红 
	{
		line(400+200*(i%2),184+35*(i/2),400+200*(i%2),190+35*(i/2));
		line(394+200*(i%2),190+35*(i/2),400+200*(i%2),190+35*(i/2));
		line(400+200*(i%2),184+35*(i/2),394+200*(i%2),190+35*(i/2));
		floodfill(399+200*(i%2),189+35*(i/2),BCTcolor(0));
	}
	i=kind_click;
	/*票种选中标红*/ 
	setcolor(_RED);
	line(400+200*(i%2),184+35*(i/2),400+200*(i%2),190+35*(i/2));
	line(394+200*(i%2),190+35*(i/2),400+200*(i%2),190+35*(i/2));
	line(400+200*(i%2),184+35*(i/2),394+200*(i%2),190+35*(i/2));
	floodfill(399+200*(i%2),189+35*(i/2),_RED);
	getbk_mouse(x,y);
	draw_mouse(x,y);
	setcolor(_WHITE);
	bar(300,445,340,474);
	all_money=price[i]*buyer_num;//计算价格并显示 
	itoa(all_money,_all_money,10);
	puthz(300,452,_all_money,1,16,_RED);
}

	/*点击选择购票人*/ 
int change_plan_2(int buyer_num,int price,int *consumer,int buyer_click,int x,int y,int mode)
{
	int i,all_money=0;
	char _all_money[6];
	redraw(x,y);
	if(consumer[buyer_click])//取消选中该购票人 
	{
		setcolor(GTcolor(55));
		buyer_num--;
		consumer[buyer_click]=0;
	}
	else//选中该购票人 
	{
		setcolor(_RED);
		buyer_num++;
		consumer[buyer_click]=1;
	}
	fillcircle(370+(buyer_click%2)*220,290+(buyer_click/2)*35,5);
	all_money=price*buyer_num;//计算价格 
	itoa(all_money,_all_money,10);
	setcolor(_WHITE);
	if(mode==1)//中转模式价格显示 
	{
		bar(300,445,340,474);
		puthz(300,452,_all_money,1,16,_RED);
	}
	else//直达模式价格显示 
	{
		bar(100,445,140,474);
		puthz(100,452,_all_money,1,16,_RED);
	}
	getbk_mouse(x,y);
	draw_mouse(x,y);
	return buyer_num;
}

    /*点击中转选择票种*/
void change_plan_3(int buyer_num,int (*price)[4],int kind_click,int *kind,int x,int y)
{
	int i,all_money=0;
	char _all_money[6];
	redraw(x,y);
	if(kind_click<4)//第一程票种处理 
	{
		setcolor(BCTcolor(0));
		for(i=0;i<4;i++)//消红 
		{
			line(184,110+i*35,190,160*(i/4)+110+i*35);
			line(190,104+i*35,190,110+i*35);
			line(184,110+i*35,190,104+i*35);
			floodfill(189,109+i*35,BCTcolor(0));
		}
		setcolor(_RED);//标红 
		{
			line(184,110+kind_click*35,190,110+kind_click*35);
			line(190,104+kind_click*35,190,110+kind_click*35);
			line(184,110+kind_click*35,190,104+kind_click*35);
			floodfill(189,109+kind_click*35,_RED);
		}
		kind[0]=kind_click;
	}
	else//第二程票种处理 
	{
		kind_click-=4;
		setcolor(BCTcolor(0));
		for(i=0;i<4;i++)//消红 
		{
			line(184,270+i*35,190,270+i*35);
			line(190,264+i*35,190,270+i*35);
			line(184,270+i*35,190,264+i*35);
			floodfill(189,269+i*35,BCTcolor(0));
		}
		setcolor(_RED);//标红 
		{
			line(184,270+kind_click*35,190,270+kind_click*35);
			line(190,264+kind_click*35,190,270+kind_click*35);
			line(184,270+kind_click*35,190,264+kind_click*35);
			floodfill(189,269+kind_click*35,_RED);
		}
		kind[1]=kind_click;
	}
	getbk_mouse(x,y);
	draw_mouse(x,y);
	setcolor(_WHITE);
	bar(100,445,140,474);
	/*计算价格并打印*/
	if(kind[0]!=-1&&kind[1]!=-1) 
		all_money=price[0][kind[0]]*buyer_num+price[1][kind[1]]*buyer_num;
	itoa(all_money,_all_money,10);
	puthz(100,452,_all_money,1,16,_RED);
}


/*订单处理*/ 
void instant_book(StackNode *p,int kind,USER *user,int *consumer,int k)
{
	int buyer_num=0,i;
	for(i=0;i<10;i++)//累加购票人 
	{
		if(consumer[i])
		{
			buyer_num++;
		}
	}
	change_data(p,kind,buyer_num,k,0);//更新余票信息 
	change_order(p,consumer,kind,user,k);//更新订单信息 
}

/*选择支付方式*/ 
int f_pay_method(int *xnow,int *ynow)
{
	int C_position=-1,btnow=0,mark=1,state=0,judge=0;
	pay_method();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_paymethod(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 1:
				return 0;//支付宝支付 
			case 2:
				return 1;//微信支付 
			case 3:
				return 2;//银行卡支付 
		}
	}
}

/*输入支付密码支付*/
int enter_password(int *xnow,int *ynow)
{
	int C_position=-1,btnow=0,mark=0,state=0,judge=0,len,tab;
	char str[6];
	paybypassword();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_pwEnter(&judge,C_position,*xnow,*ynow,state);
		switch(judge)
		{
			case 1://退出支付 
				return 0;
			case 2://密码输入 
				len=nhz_input(xnow,ynow,520,270,575,300,str,&tab,1,len);
				break;
			case 3://确认密码输入 
				if(len==6)
				{
					return 1;
				}
				break;
		}
	}
}

/*直达的立即支付*/ 
void instant_bookDE(StackNode *p,int kind,USER *user,int *consumer,int *xnow,int *ynow,int k)
{
	int C_position=-1,btnow=0,mark=1,state=0,judge=0,Judge=0;
	char *image,*image1;
	
	if((image=(char *)malloc(21901))==NULL)//存储支付方式覆盖下图像 
	{
		printf("overflow");
		getch();
		exit(1);
	}
	if((image1=(char *)malloc(10101))==NULL)//存储细节支付方式下图像 
	{
		printf("overflow");
		getch();
		exit(1);
	}
	getimage(300,200,420,380,image);
	getimage(500,250,610,340,image1);
	pay();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_pay(&judge,C_position,*xnow,*ynow,state);
		if(judge==1)//退出支付方式 
		{
			redraw(*xnow,*ynow);
			putimage(500,250,610,340,image1);
			getbk_mouse(*xnow,*ynow);
			draw_mouse(*xnow,*ynow);
			break;
		}
		else if(judge==2||judge==3||judge==4)
		{
			if(judge==2||judge==3)//微信或支付宝支付 
			{
				pay_method();
				Judge=f_pay_method(xnow,ynow);
				if(Judge==1)//扫描二维码支付 
				{
					PayByQR();
					instant_book(p,kind,user,consumer,k);
					redraw(*xnow,*ynow);
					putimage(500,250,610,340,image1);
					getbk_mouse(*xnow,*ynow);
					draw_mouse(*xnow,*ynow);
					break;
				}
				else if(Judge==2)//输入支付密码支付 
				{
					if(enter_password(xnow,ynow))
					{
						instant_book(p,kind,user,consumer,k);
					}
					pay_OK();
					redraw(*xnow,*ynow);
					putimage(500,250,610,340,image1);
					getbk_mouse(*xnow,*ynow);
					draw_mouse(*xnow,*ynow);
					break;
				}
				else//退出支付 
				{
					redraw(*xnow,*ynow);
					putimage(500,250,610,340,image1);
					getbk_mouse(*xnow,*ynow);
					draw_mouse(*xnow,*ynow);
					break;
				}
			}
			else if(judge==4)//银行卡支付 
			{
				instant_book(p,kind,user,consumer,k);
				pay_OK();
				break;
			}
		}
	}
	redraw(*xnow,*ynow);
	putimage(300,200,420,380,image);
	getbk_mouse(*xnow,*ynow);
	draw_mouse(*xnow,*ynow);
	free(image);
	free(image1);
}

/*中转支付*/ 
void instant_bookRE(StackNode *p,StackNode *q,int *kind,USER *user,int *consumer,int *xnow,int *ynow,int k)
{
	int C_position=-1,btnow=0,mark=1,state=0,judge=0,Judge=0;
	char *image,*image1;
	/*编程结构同直达支付*/ 
	if((image=(char *)malloc(21901))==NULL)
	{
		printf("overflow");
		getch();
		exit(1);
	}
	if((image1=(char *)malloc(10101))==NULL)
	{
		printf("overflow");
		getch();
		exit(1);
	}
	getimage(300,200,420,380,image);
	getimage(500,250,610,340,image1);
	pay();
	while(1)
	{
		state=mouse_control(xnow,ynow,&btnow,&mark);
		C_position=check_pay(&judge,C_position,*xnow,*ynow,state);
		if(judge==1)
		{
			redraw(*xnow,*ynow);
			putimage(500,250,610,340,image1);
			getbk_mouse(*xnow,*ynow);
			draw_mouse(*xnow,*ynow);
			break;
		}
		else if(judge==2||judge==3||judge==4)
		{
			if(judge==2||judge==3)
			{
				pay_method();
				Judge=f_pay_method(xnow,ynow);
				if(Judge==1)
				{
					PayByQR();
					instant_book(p,kind[0],user,consumer,k);//第一程支付 
					instant_book(q,kind[1],user,consumer,k);//第二程支付
					redraw(*xnow,*ynow);
					putimage(500,250,610,340,image1);
					getbk_mouse(*xnow,*ynow);
					draw_mouse(*xnow,*ynow);
					break;
				}
				else if(Judge==2)
				{
					if(enter_password(xnow,ynow))
					{
						instant_book(p,kind[0],user,consumer,k);//第一程支付 
						instant_book(q,kind[1],user,consumer,k);//第二程支付
						pay_OK();
					}
					redraw(*xnow,*ynow);
					putimage(500,250,610,340,image1);
					getbk_mouse(*xnow,*ynow);
					draw_mouse(*xnow,*ynow);
					break;
				}
				else 
				{
					redraw(*xnow,*ynow);
					putimage(500,250,610,340,image1);
					getbk_mouse(*xnow,*ynow);
					draw_mouse(*xnow,*ynow);
					break;
				}
			}
			else if(judge==4)
			{
				instant_book(p,kind[0],user,consumer,k);
				instant_book(q,kind[1],user,consumer,k);
				pay_OK();
				break;
			}
		}
	}
	redraw(*xnow,*ynow);
	putimage(300,200,420,380,image);
	getbk_mouse(*xnow,*ynow);
	draw_mouse(*xnow,*ynow);
	free(image);
	free(image1); 
}


/*改变车票系统内的余票数据,mode决定票数加减*/
void change_data(StackNode *p,int kind,int buyer_num,int k,int mode)
{
	int i,num;
	KT_train KTtrain;
	G_train Gtrain;
	D_train Dtrain;
	Z_train Ztrain;
	char path[35]={"C:\\PRJ\\File\\data"};
	char temp[3];
	FILE *fp;
	
	
	itoa(k,temp,10);
	strcat(path,temp);
	strcat(path,"\\");
	strcat(path,p->trainnum);
	if(p->trainnum[0]=='K'||p->trainnum[0]=='T')
	{
		KT_read(p->trainnum,&KTtrain,k);
		for(i=0;p!=NULL;i++)
		{
			if(!strcmp(KTtrain.station[i],p->station))
			{
				if(kind==0)
				{
					num=atoi(KTtrain.hard_seat[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,KTtrain.hard_seat[i],10);
				}
				else if(kind==1)
				{
					num=atoi(KTtrain.hard_sleeper[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,KTtrain.hard_sleeper[i],10);
				}
				else if(kind==2)
				{
					num=atoi(KTtrain.soft_sleeper[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,KTtrain.soft_sleeper[i],10);
				}
				p=p->next;
			}
		}
		if((fp=fopen(path,"w"))==NULL)
		{
			printf("Can't open file");
			getch();
			exit(1); 
		}
		fwrite(&KTtrain,sizeof(KT_train),1,fp);
		fclose(fp);
	}
	else if(p->trainnum[0]=='G')
	{
		G_read(p->trainnum,&Gtrain,k);
		for(i=0;p!=NULL;i++)
		{
			if(!strcmp(Gtrain.station[i],p->station))
			{
				if(kind==0)
				{
					num=atoi(Gtrain.s_seat[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,Gtrain.s_seat[i],10);
				}
				else if(kind==1)
				{
					num=atoi(Gtrain.f_seat[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,Gtrain.f_seat[i],10);
				}
				else if(kind==2)
				{
					num=atoi(Gtrain.b_seat[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,Gtrain.b_seat[i],10);
				}
				p=p->next;
			}
		}
		if((fp=fopen(path,"w"))==NULL)
		{
			printf("Can't open file");
			getch();
			exit(1); 
		}
		fwrite(&Gtrain,sizeof(G_train),1,fp);
		fclose(fp);
	}
	else if(p->trainnum[0]=='D')
	{
		D_read(p->trainnum,&Dtrain,k);
		for(i=0;p!=NULL;i++)
		{
			if(!strcmp(Dtrain.station[i],p->station))
			{
				if(kind==0)
				{
					num=atoi(Dtrain.s_seat[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,Dtrain.s_seat[i],10);
				}
				else if(kind==1)
				{
					num=atoi(Dtrain.f_seat[i]);
					if(mode) num+=buyer_num;
					else num-=buyer_num;
					itoa(num,Dtrain.f_seat[i],10);
				}
				p=p->next;
			}
		}
		if((fp=fopen(path,"w"))==NULL)
		{
			printf("Can't open file");
			getch();
			exit(1); 
		}
		fwrite(&Dtrain,sizeof(D_train),1,fp);
		fclose(fp);
	}
	else if(p->trainnum[0]=='Z')
	{
		Z_read(p->trainnum,&Ztrain,k);
		if(kind==0)
		{
			num=atoi(Ztrain.hard_seat);
			if(mode) num+=buyer_num;
			else num-=buyer_num;
			itoa(num,Ztrain.hard_seat,10);
		}
		else if(kind==1)
		{
			num=atoi(Ztrain.hard_sleeper);
			if(mode) num+=buyer_num;
			else num-=buyer_num;
			itoa(num,Ztrain.hard_sleeper,10);
		}
		else if(kind==2)
		{
			num=atoi(Ztrain.soft_sleeper);
			if(mode) num+=buyer_num;
			else num-=buyer_num;
			itoa(num,Ztrain.soft_sleeper,10);
		}
		if((fp=fopen(path,"w"))==NULL)
		{
			printf("Can't open file");
			getch();
			exit(1); 
		}
		fwrite(&Ztrain,sizeof(Z_train),1,fp);
		fclose(fp);
	}
}

/*处理订单*/
void change_order(StackNode *p,int *consumer,int kind,USER *user,int k)
{
	StackNode *reserve=p;
	ORDER *order;
	ORDER *tempOrder=user->order;
	int i;
	
	for(i=0;i<10;i++)
	{
		if(consumer[i])
		{
			p=reserve;//指针复原 
			if((order=malloc(sizeof(ORDER)))==NULL)
			{ 
				printf("overflow");
				getch();
				exit(1);
			}
			if(user->order==NULL)
			{
				user->order=order; 
				tempOrder=user->order;//重定位指针，避免出现野指针 
			}
			else
			{
				while(tempOrder->next!=NULL)
				{
					tempOrder=tempOrder->next;
				}
				tempOrder->next=order;
			}
			deal_ordertime(p,order,k);
			order->next=NULL; 
			strcpy(order->TrainNum,p->trainnum);
			if(p->trainnum[0]=='K'||p->trainnum[0]=='T'||p->trainnum[0]=='Z')
			{
				switch(kind)
				{
					case 0:
						strcpy(order->seat_kind,"硬座");
						break;
					case 1:
						strcpy(order->seat_kind,"硬卧");
						break;
					case 2:
						strcpy(order->seat_kind,"软卧"); 
						break;
					case 3:
						strcpy(order->seat_kind,"无座");
						break; 
				} 
			}
			else if(p->trainnum[0]=='G'||p->trainnum[0]=='D')
			{
				switch(kind)
				{
					case 0:
						strcpy(order->seat_kind,"二等座");
						break;
					case 1:
						strcpy(order->seat_kind,"一等座");
						break;
					case 2:
						strcpy(order->seat_kind,"商务座");
						break; 
					case 3:
						strcpy(order->seat_kind,"无座"); 
						break;
				}
			}
			strcpy(order->StartStation,p->station);
			while(p->next!=NULL)
			{
				p=p->next;
			}
			strcpy(order->FinalStation,p->station);
			strcpy(order->Identity,user->AllIdentity[i]);
		}
	}
} 


/*处理订单时间*/ 
void deal_ordertime(StackNode *p,ORDER *order,int k)
{
	TIME _tm;
	char temp[3];
	int mon1,day1,mon2,day2,_days,day;
	
	_gettime(&_tm);
	_days=days(_tm.month,_tm.year);
	if(_tm.day+k-1>_days)
	{
		mon1=(_tm.month==12)?1:(_tm.month+1);
		day1=_tm.day+k-1-_days;
		if(_tm.month==12)
		{
			_tm.year++;
		}
	}
	else
	{
		mon1=_tm.month;
		day1=_tm.day+k-1;
	}
	day=dayDifference(p,k);
	_days=days(mon1,_tm.year);
	if(day1+day>_days)
	{
		mon2=(mon1==12)?1:(mon1++);
		day2=day1+day-_days;
	}
	else
	{
		mon2=mon1;
		day2=day1+day;
	} 
	itoa(mon1,order->StartTime,10);
	itoa(mon2,order->FinalTime,10);
	strcat(order->StartTime,"月");
	strcat(order->FinalTime,"月");
	itoa(day1,temp,10);
	strcat(order->StartTime,temp);
	strcat(order->StartTime,"日");
	itoa(day2,temp,10);
	strcat(order->FinalTime,temp);
	strcat(order->FinalTime,"日");
	copy_detailTime(p,order->StartTime,order->FinalTime,k);
}

/*计算该订单车程经历天数*/
int dayDifference(StackNode *p,int k)
{
	KT_train KTtrain;
	G_train Gtrain;
	D_train Dtrain;
	Z_train Ztrain;
	int i;
	int day=0,min,start=0;

	if(p->trainnum[0]=='K'||p->trainnum[0]=='T')
	{
		KT_read(p->trainnum,&KTtrain,k);
		for(i=0;p->next!=NULL;i++)
		{
			if(!strcmp(p->station,KTtrain.station[i]))
			{
				start=1;
			}
			if(p->next->next==NULL)
			{
				day+=TimeDistance_m(KTtrain.start_time[i],KTtrain.arrive_time[i+1],&min);
				break;
			}
			if(start)
			{
				day+=TimeDistance_m(KTtrain.start_time[i],KTtrain.start_time[i+1],&min);
				p=p->next; 
			}
		}
	}
	else if(p->trainnum[0]=='G')
	{
		G_read(p->trainnum,&Gtrain,k);
		for(i=0;p->next!=NULL;i++)
		{
			if(!strcmp(p->station,Gtrain.station[i]))
			{
				start=1;
			}
			if(p->next->next==NULL)
			{
				day+=TimeDistance_m(Gtrain.start_time[i],Gtrain.arrive_time[i+1],&min);
				break;
			}
			if(start)
			{
				day+=TimeDistance_m(Gtrain.start_time[i],Gtrain.start_time[i+1],&min);
				p=p->next;
			}
		}
	} 
	else if(p->trainnum[0]=='D')
	{
		D_read(p->trainnum,&Dtrain,k);
		for(i=0;p->next!=NULL;i++)
		{
			if(!strcmp(p->station,Dtrain.station[i]))
			{
				start=1;
			}
			if(p->next->next==NULL)
			{
				day+=TimeDistance_m(Dtrain.start_time[i],Dtrain.arrive_time[i+1],&min);
				break;
			}
			if(start)
			{
				day+=TimeDistance_m(Dtrain.start_time[i],Dtrain.start_time[i+1],&min);
				p=p->next;
			}
		}
	} 
	else if(p->trainnum[0]=='Z')
	{
		Z_read(p->trainnum,&Ztrain,k);
		day+=TimeDistance_m(Ztrain.start_time,Ztrain.arrive_time,&min);
	} 
	return day;
}


   /*从车票库复制车程时间*/
void copy_detailTime(StackNode *p,char *st_time,char *fi_time,int k)
{
	KT_train KTtrain;
	G_train Gtrain;
	D_train Dtrain;
	Z_train Ztrain;
	int i,start=0;
	
	if(p->trainnum[0]=='K'||p->trainnum[0]=='T')
	{
		KT_read(p->trainnum,&KTtrain,k);;
		for(i=0;p->next!=NULL;i++)
		{
			if(!strcmp(p->station,KTtrain.station[i])&&!start)
			{
				start=1;
				strcat(st_time,KTtrain.start_time[i]);
			}
			if(start)
			{
				p=p->next;
			}
		}
		strcat(fi_time,KTtrain.arrive_time[i]);
	} 
	else if(p->trainnum[0]=='G')
	{
		G_read(p->trainnum,&Gtrain,k);;
		for(i=0;p->next!=NULL;i++)
		{
			if(!strcmp(p->station,Gtrain.station[i])&&!start)
			{
				start=1;
				strcat(st_time,Gtrain.start_time[i]);
			}
			if(start)
			{
				p=p->next;
			}
		}
		strcat(fi_time,Gtrain.arrive_time[i]);
	}
	else if(p->trainnum[0]=='D')
	{
		D_read(p->trainnum,&Dtrain,k);;
		for(i=0;p->next!=NULL;i++)
		{
			if(!strcmp(p->station,Dtrain.station[i])&&!start)
			{
				start=1;
				strcat(st_time,Dtrain.start_time[i]);
			}
			if(start)
			{
				p=p->next;
			}
		}
		strcat(fi_time,Dtrain.arrive_time[i]);
	}
	else if(p->trainnum[0]=='Z')
	{
		Z_read(p->trainnum,&Ztrain,k);
		strcat(st_time,Ztrain.start_time);
		strcat(fi_time,Ztrain.arrive_time);
	}
}
