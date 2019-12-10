#include "stdio.h"
#include "upload.h"
#include "input.h"
#include <conio.h>
#include "data.h"
#include "svga.h"
#include <string.h>
#include "mouse.h"
#include "hmi.h"
#include "check.h"
int KT_visual(KT_train *p,int (*length)[9],int page,int more)
{
	int i,j;
	setcolor(DARK_GRAY);
	if(!more)
	{
		for(i=0;i<9&&strcmp(p->start_time[i+(page-1)*9],"###");i++)
		for(j=0;j<7;j++)
		{
			if(page==1&&i==0&&j==2) continue;
			if(i>0&&length[i-1][j]==0&&page!=1) return (i-1);
			switch(j)
			{
				case 0:
					length[0][i]=strlen(p->station[i+(page-1)*9]);
					puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
					break;
				case 1:
					length[1][i]=strlen(p->city[i+(page-1)*9]);
					puthz(107,128+i*35,p->city[i+(page-1)*9],1,16,_BLACK);
					break;
				case 2:
					length[2][i]=strlen(p->arrive_time[i+(page-1)*9]);
					outtextxy(182,128+i*35,p->arrive_time[i+(page-1)*9]);
					break;
				case 3:
					length[3][i]=strlen(p->start_time[i+(page-1)*9]);
					outtextxy(242,128+i*35,p->start_time[i+(page-1)*9]);
					break;
				case 4:
					length[4][i]=strlen(p->hardseat_fee[i+(page-1)*9]);
					outtextxy(312,128+i*35,p->hardseat_fee[i+(page-1)*9]);
					break;
				case 5:
					length[5][i]=strlen(p->hardsleeper_fee[i+(page-1)*9]);
					outtextxy(357,128+i*35,p->hardsleeper_fee[i+(page-1)*9]);
					break;
				case 6:
					length[6][i]=strlen(p->softsleeper_fee[i+(page-1)*9]);
					outtextxy(402,128+i*35,p->softsleeper_fee[i+(page-1)*9]);
					break;
			}
		}
		//末站车次信息获取 
		if(!strcmp(p->start_time[i+(page-1)*9],"###")&&i!=9)
		{
			length[0][i]=strlen(p->station[i+(page-1)*9]);
			puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
			length[1][i]=strlen(p->city[i+(page-1)*9]);
			puthz(107,128+i*35,p->city[i+(page-1)*9],1,16,_BLACK);
			length[2][i]=strlen(p->arrive_time[i+(page-1)*9]);
			outtextxy(182,128+i*35,p->arrive_time[i+(page-1)*9]);
			return (i-1);
		}
		return 8;	
	}
	else
	{
		for(i=0;i<9&&strcmp(p->start_time[i+(page-1)*9],"###");i++)
		for(j=0;j<4;j++)
		{
			switch(j)
			{
				case 0:
					length[0][i]=strlen(p->station[i+(page-1)*9]);
					puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
					break;
				case 1:
					length[1][i]=strlen(p->hard_seat[i+(page-1)*9]);
					outtextxy(112,128+i*35,p->hard_seat[i+(page-1)*9]);
					break;
				case 2:
					length[2][i]=strlen(p->hard_sleeper[i+(page-1)*9]);
					outtextxy(172,128+i*35,p->hard_sleeper[i+(page-1)*9]);
					break;
				case 3:
					length[3][i]=strlen(p->soft_sleeper[i+(page-1)*9]);
					outtextxy(232,128+i*35,p->soft_sleeper[i+(page-1)*9]);
					break;
			}
		}
		if(!strcmp(p->start_time[i+(page-1)*9],"###")&&i!=9)
		{
			length[0][i]=strlen(p->station[i+(page-1)*9]);
			puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
			return i;
		}
		return 8;
	} 
}

int G_visual(G_train *p,int (*length)[9],int page,int more)
{
	int i,j;
	setcolor(DARK_GRAY);
	if(!more)
	{
		for(i=0;i<9&&strcmp(p->start_time[i+(page-1)*9],"###");i++)
		for(j=0;j<7;j++)
		{
			if(page==1&&i==0&&j==2) continue;
			if(i>0&&length[i-1][j]==0&&page!=1) return (i-1);
			switch(j)
			{
				case 0:
					length[0][i]=strlen(p->station[i+(page-1)*9]);
					puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
					break;
				case 1:
					length[1][i]=strlen(p->city[i+(page-1)*9]);
					puthz(107,128+i*35,p->city[i+(page-1)*9],1,16,_BLACK);
					break;
				case 2:
					length[2][i]=strlen(p->arrive_time[i+(page-1)*9]);
					outtextxy(182,128+i*35,p->arrive_time[i+(page-1)*9]);
					break;
				case 3:
					length[3][i]=strlen(p->start_time[i+(page-1)*9]);
					outtextxy(242,128+i*35,p->start_time[i+(page-1)*9]);
					break;
				case 4:
					length[4][i]=strlen(p->fclass_fee[i+(page-1)*9]);
					outtextxy(312,128+i*35,p->fclass_fee[i+(page-1)*9]);
					break;
				case 5:
					length[5][i]=strlen(p->sclass_fee[i+(page-1)*9]);
					outtextxy(357,128+i*35,p->sclass_fee[i+(page-1)*9]);
					break;
				case 6:
					length[6][i]=strlen(p->business_fee[i+(page-1)*9]);
					outtextxy(402,128+i*35,p->business_fee[i+(page-1)*9]);
					break;
			}
		}
		//末站车次信息获取 
		if(!strcmp(p->start_time[i+(page-1)*9],"###")&&i!=9)
		{
			length[0][i]=strlen(p->station[i+(page-1)*9]);
			puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
			length[1][i]=strlen(p->city[i+(page-1)*9]);
			puthz(107,128+i*35,p->city[i+(page-1)*9],1,16,_BLACK);
			length[2][i]=strlen(p->arrive_time[i+(page-1)*9]);
			outtextxy(182,128+i*35,p->arrive_time[i+(page-1)*9]);
			return (i-1);
		}
		return 8;
	}
	else
	{
		for(i=0;i<9&&strcmp(p->start_time[i+(page-1)*9],"###");i++)
		for(j=0;j<4;j++)
		{
			switch(j)
			{
				case 0:
					length[0][i]=strlen(p->station[i+(page-1)*9]);
					puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
					break;
				case 1:
					length[1][i]=strlen(p->f_seat[i+(page-1)*9]);
					outtextxy(112,128+i*35,p->f_seat[i+(page-1)*9]);
					break;
				case 2:
					length[2][i]=strlen(p->s_seat[i+(page-1)*9]);
					outtextxy(172,128+i*35,p->s_seat[i+(page-1)*9]);
					break;
				case 3:
					length[3][i]=strlen(p->b_seat[i+(page-1)*9]);
					outtextxy(232,128+i*35,p->b_seat[i+(page-1)*9]);
					break;
			}
		}
		if(!strcmp(p->start_time[i+(page-1)*9],"###")&&i!=9)
		{
			length[0][i]=strlen(p->station[i+(page-1)*9]);
			puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
			return i;
		}
		return 8;
	} 
}
int D_visual(D_train *p,int (*length)[9],int page,int more)
{
	int i,j;
	setcolor(DARK_GRAY);
	if(!more)
	{
		for(i=0;i<9&&strcmp(p->start_time[i+(page-1)*9],"###");i++)
		for(j=0;j<7;j++)
		{
			if(page==1&&i==0&&j==2) continue;
			if(i>0&&length[i-1][j]==0&&page!=1) return (i-1);
			switch(j)
			{
				case 0:
					length[0][i]=strlen(p->station[i+(page-1)*9]);
					puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
					break;
				case 1:
					length[1][i]=strlen(p->city[i+(page-1)*9]);
					puthz(107,128+i*35,p->city[i+(page-1)*9],1,16,_BLACK);
					break;
				case 2:
					length[2][i]=strlen(p->arrive_time[i+(page-1)*9]);
					outtextxy(182,128+i*35,p->arrive_time[i+(page-1)*9]);
					break;
				case 3:
					length[3][i]=strlen(p->start_time[i+(page-1)*9]);
					outtextxy(242,128+i*35,p->start_time[i+(page-1)*9]);
					break;
				case 4:
					length[4][i]=strlen(p->fclass_fee[i+(page-1)*9]);
					outtextxy(312,128+i*35,p->fclass_fee[i+(page-1)*9]);
					break;
				case 5:
					length[5][i]=strlen(p->sclass_fee[i+(page-1)*9]);
					outtextxy(357,128+i*35,p->sclass_fee[i+(page-1)*9]);
					break;
			}
		}
		//末站车次信息获取 
		if(!strcmp(p->start_time[i+(page-1)*9],"###")&&i!=9)
		{
			length[0][i]=strlen(p->station[i+(page-1)*9]);
			puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
			length[1][i]=strlen(p->city[i+(page-1)*9]);
			puthz(107,128+i*35,p->city[i+(page-1)*9],1,16,_BLACK);
			length[2][i]=strlen(p->arrive_time[i+(page-1)*9]);
			outtextxy(182,128+i*35,p->arrive_time[i+(page-1)*9]);
			return i;
		}
		return 8;	
	}
	else
	{
		for(i=0;i<9&&strcmp(p->start_time[i+(page-1)*9],"###");i++)
		for(j=0;j<4;j++)
		{
			switch(j)
			{
				case 0:
					length[0][i]=strlen(p->station[i+(page-1)*9]);
					puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
					break;
				case 1:
					length[1][i]=strlen(p->f_seat[i+(page-1)*9]);
					outtextxy(112,128+i*35,p->f_seat[i+(page-1)*9]);
					break;
				case 2:
					length[2][i]=strlen(p->s_seat[i+(page-1)*9]);
					outtextxy(172,128+i*35,p->s_seat[i+(page-1)*9]);
					break;
			}
		}
		if(!strcmp(p->start_time[i+(page-1)*9],"###")&&i!=9)
		{
			length[0][i]=strlen(p->station[i+(page-1)*9]);
			puthz(32,128+i*35,p->station[i+(page-1)*9],1,16,_BLACK);
			return (i-1);
		}
		return 8;	
	} 
}

void Z_visual(Z_train *p,int (*length)[2],int *lengthnum)
{
	int i,j;
	setcolor(DARK_GRAY);
	for(i=0;i<2;i++)
	for(j=0;j<7;j++)
	{
		if(j==3||(i==1&&(j==4||j==5||j==6))) continue;
		switch(j)
		{
			case 0:
				length[0][i]=strlen(p->station[i]);
				puthz(32,128+i*35,p->station[i],1,16,_BLACK);
				break;
			case 1:
				length[j][i]=strlen(p->city);
				puthz(107,128+i*35,p->city[i],1,16,_BLACK);
				break;
			case 2:
				if(i==0)
				{
					length[2][0]=strlen(p->start_time);
					outtextxy(182,128,p->start_time);	
				}
				else if(i==1)
				{
					length[2][1]=strlen(p->arrive_time);
					outtextxy(182,174,p->arrive_time);
				}
				break;
			case 4:
				length[4][i]=strlen(p->hardseat_fee);
				outtextxy(312,128+i*35,p->hardseat_fee);
				break;
			case 5:
				length[5][i]=strlen(p->hardsleeper_fee);
				outtextxy(357,128+i*35,p->hardsleeper_fee);
				break;
			case 6:
				length[6][i]=strlen(p->softsleeper_fee);
				outtextxy(402,128+i*35,p->softsleeper_fee);
				break;
		}
	}
	lengthnum[0]=strlen(p->hard_seat);
	outtextxy(552,128,p->hard_seat);
	lengthnum[1]=strlen(p->hard_sleeper);
	outtextxy(552,174,p->hard_sleeper);
	lengthnum[2]=strlen(p->soft_sleeper);
	outtextxy(552,209,p->soft_sleeper); 
}

int f_NewKT(int *xnow,int *ynow,int *btnow,int *mark,int page,KT_train* p)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int num=-1;//保存地名数 
	int length[7][9];
	int lengthnum[4]={0,0,0,0};//lengthnum[3]用来判断是否为修改模式 
	
	NewKT(page,0);
	for(i=0;i<7;i++)
	for(j=0;j<9;j++)
	{
		length[i][j]=0;
	}
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewKT(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(judge==27+i&&i<=num+1)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    if(num<i&&length[0][i]) num=i;
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {	
			    length[1][i]=hz_input(xnow,ynow,105,120+i*35,175,150+i*35,p->city[i+(page-1)*9],&tab,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
		    	
			    length[2][i]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->arrive_time[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,240,125+i*35,290,145+i*35,p->start_time[i+(page-1)*9],&tab,0,length[3][i]);
			    break;
		    }
		    else if(i<=num&&judge==63+i)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->hardseat_fee[i+(page-1)*9],&tab,0,length[4][i]);
			    break;
		    }
		    else if(i<=num&&judge==72+i)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->hardsleeper_fee[i+(page-1)*9],&tab,0,length[5][i]);
			    break;
		    }
		    else if(i<=num&&judge==81+i)
		    {
			    length[6][i]=nhz_input(xnow,ynow,400,125+i*35,430,145+i*35,p->softsleeper_fee[i+(page-1)*9],&tab,0,length[6][i]);
			    break;
		    }
		    else if(i<=num&&judge==90&&page==1)
		    {
			    lengthnum[0]=nhz_input(xnow,ynow,550,125,595,145,p->hard_seat[0],&tab,0,lengthnum[0]);
			    break; 
		    }
		    else if(i<=num&&judge==91&&page==1)
		    {
			    lengthnum[1]=nhz_input(xnow,ynow,550,160,595,180,p->hard_sleeper[0],&tab,0,lengthnum[1]);
		    	break;
		    }
		    else if(i<=num&&judge==92&&page==1)
		    {
			    lengthnum[2]=nhz_input(xnow,ynow,550,195,595,215,p->soft_sleeper[0],&tab,0,lengthnum[2]);
		    	break;
		    }
		}
		if(judge==23)  return(23);
		else if(judge==94&&num==8&&page<4) 
		{
			*mark=0;
			judge=f_NewKT(xnow,ynow,btnow,mark,++page,p);
			if(judge==23)
			{
				return 23;
			}
		}
		else if(judge==95&&num!=-1)
		{
			if(KT_save(p->tra_num,p,page,length,lengthnum,num,1))
			return(23);
		} 
		if(!tab) judge=26;	
		else judge++;
		tab=0;
	}
}

int f_NewZ(int *xnow,int *ynow,int *btnow,int *mark,Z_train *p)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int num=-1;//保存地名数 
	int length[7][2];
	int lengthnum[4]={0,0,0,0};
	
	NewZ();
	for(i=0;i<7;i++)
	for(j=0;j<2;j++)
	{
		length[i][j]=0;
	}
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewZ(&judge,*xnow,*ynow,state);
		for(i=0;i<2;i++)
		{
			if(judge==27+i&&i<=num+1)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i],&tab,length[0][i]);
			    if(num<i&&length[0][i]) num=i;
			    break;
		    }	    
		    else if(i<=num&&judge==36+i)
		    {	
			    length[1][i]=hz_input(xnow,ynow,105,120+i*35,175,150+i*35,p->city[i],&tab,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
		    	if(i==0)
			    length[2][0]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->start_time,&tab,0,length[2][0]);
			    else if(i==1)
			    length[2][1]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->arrive_time,&tab,0,length[2][1]);
			    break;
		    }
		    

		    else if(i<=num&&judge==63+i)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->hardseat_fee,&tab,0,length[4][i]);
			    break;
		    }
		    else if(i<=num&&judge==72+i)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->hardsleeper_fee,&tab,0,length[5][i]);
			    break;
		    }
		    else if(i<=num&&judge==81+i)
		    {
			    length[6][i]=nhz_input(xnow,ynow,400,125+i*35,430,145+i*35,p->softsleeper_fee,&tab,0,length[6][i]);
			    break;
		    }
		    else if(i<=num&&judge==90)
		    {
			    lengthnum[0]=nhz_input(xnow,ynow,550,125,595,145,p->hard_seat,&tab,0,lengthnum[0]);
			    break; 
		    }
		    else if(i<=num&&judge==91)
		    {
			    lengthnum[1]=nhz_input(xnow,ynow,550,160,595,180,p->hard_sleeper,&tab,0,lengthnum[1]);
		    	break;
		    }
		    else if(i<=num&&judge==92)
		    {
			    lengthnum[2]=nhz_input(xnow,ynow,550,195,595,215,p->soft_sleeper,&tab,0,lengthnum[2]);
		    	break;
		    }
		}
		if(judge==23)  return(23);
		else if(judge==95&&num!=-1)
		{
			if(Z_save(p->tra_num,p,length,lengthnum,1))
			return(23);
		}  
		if(!tab) judge=26;	
		else judge++;
		tab=0;	
	}
}
int f_NewG(int *xnow,int *ynow,int *btnow,int *mark,int page,G_train *p)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int num=-1;//保存地名数 
	int length[7][9];
	int lengthnum[4]={0,0,0,0};
	
	NewG(page,0);
	for(i=0;i<7;i++)
	for(j=0;j<9;j++)
	{
		length[i][j]=0;
	}
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewG(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(judge==27+i&&i<=num+1)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    if(num<i&&length[0][i]) num=i;
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
		    	
			    length[1][i]=hz_input(xnow,ynow,105,120+i*35,175,150+i*35,p->city[i+(page-1)*9],&tab,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
		    	
			    length[2][i]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->arrive_time[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,240,125+i*35,290,145+i*35,p->start_time[i+(page-1)*9],&tab,0,length[3][i]);
			    break;
		    }
		    else if(i<=num&&judge==63+i)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->fclass_fee[i+(page-1)*9],&tab,0,length[4][i]);
			    break;
		    }
		    else if(i<=num&&judge==72+i)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->sclass_fee[i+(page-1)*9],&tab,0,length[5][i]);
			    break;
		    }
		    else if(i<=num&&judge==81+i)
		    {
			    length[6][i]=nhz_input(xnow,ynow,400,125+i*35,430,145+i*35,p->business_fee[i+(page-1)*9],&tab,0,length[6][i]);
			    break;
		    }
		    else if(i<=num&&judge==90&&page==1)
		    {
			    lengthnum[0]=nhz_input(xnow,ynow,550,125,595,145,p->f_seat[0],&tab,0,lengthnum[0]);
			    break; 
		    }
		    else if(i<=num&&judge==91&&page==1)
		    {
			    lengthnum[1]=nhz_input(xnow,ynow,550,160,595,180,p->s_seat[0],&tab,0,lengthnum[1]);
		    	break;
		    }
		    else if(i<=num&&judge==92&&page==1)
		    {
			    lengthnum[2]=nhz_input(xnow,ynow,550,195,595,215,p->b_seat[0],&tab,0,lengthnum[2]);
		    	break;
		    }
		}
		if(judge==23)  return(23);
		else if(judge==94&&num==8&&page<4) 
		{
			*mark=0;
			judge=f_NewG(xnow,ynow,btnow,mark,++page,p);
			if(judge==23)
			{
				return 23;
			}
		}
		else if(judge==95&&num!=-1)
		{
			if(G_save(p->tra_num,p,page,length,lengthnum,num,1)) 
			return(23);
		} 
		if(!tab) judge=26;	
		else judge++;
		tab=0;	
	}
}


int f_NewD(int *xnow,int *ynow,int *btnow,int *mark,int page,D_train *p)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int num=-1;//保存地名数 
	int length[7][9];
	int lengthnum[4]={0,0,0,0};
	
	NewD(page,0);
	for(i=0;i<7;i++)
	for(j=0;j<9;j++)
	{
		length[i][j]=0;
	}
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewD(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(judge==27+i&&i<=num+1)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    if(num<i&&length[0][i]) num=i;
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
		    	
			    length[1][i]=hz_input(xnow,ynow,105,120+i*35,175,150+i*35,p->city[i+(page-1)*9],&tab,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
		    	
			    length[2][i]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->arrive_time[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,240,125+i*35,290,145+i*35,p->start_time[i+(page-1)*9],&tab,0,length[3][i]);
			    break;
		    }
		    else if(i<=num&&judge==63+i)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->fclass_fee[i+(page-1)*9],&tab,0,length[4][i]);
			    break;
		    }
		    else if(i<=num&&judge==72+i)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->sclass_fee[i+(page-1)*9],&tab,0,length[5][i]);
			    break;
		    }
		    else if(i<=num&&judge==90&&page==1)
		    {
			    lengthnum[0]=nhz_input(xnow,ynow,550,125,595,145,p->f_seat[0],&tab,0,lengthnum[0]);
			    break; 
		    }
		    else if(i<=num&&judge==91&&page==1)
		    {
			    lengthnum[1]=nhz_input(xnow,ynow,550,160,595,180,p->s_seat[0],&tab,0,lengthnum[1]);
		    	break;
		    }
		}
		
		if(judge==23)  return(23);
		else if(judge==94&&num==8&&page<4) 
		{
			*mark=0;
			judge=f_NewD(xnow,ynow,btnow,mark,++page,p);
			if(judge==23)
			{
				return 23;
			}
		}
		
		else if(judge==95&&num!=-1)
		{
			if(D_save(p->tra_num,p,page,length,lengthnum,num,1))
			return(23);
		} 
		if(!tab) judge=26;	
		else judge++;
		tab=0;	
	}
}

int f_KTmore(int *xnow,int *ynow,int *btnow,int *mark,int page,KT_train *p,int num)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int length[4][9];
	int lengthnum[3]={1,1,1};

	more(page,'K');
	memset(length,0,36*sizeof(int)); 
	KT_visual(p,length,page,1);
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_more(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(i<=num&&judge==27+i)
		    {
		    	
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
			    length[1][i]=nhz_input(xnow,ynow,110,125+i*35,155,145+i*35,p->hard_seat[i+(page-1)*9],&tab,0,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
			    length[2][i]=nhz_input(xnow,ynow,170,125+i*35,215,145+i*35,p->hard_sleeper[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,230,125+i*35,275,145+i*35,p->soft_sleeper[i+(page-1)*9],&tab,0,length[3][i]);
			    tab=0;
			    break;
		    }
		}
		if(judge==23)  return(23);
		else if(judge==96) return 26;
		else if(judge==94&&num==8&&page<4) 
		{
			*mark=0;
			judge=f_ModifyKT(xnow,ynow,btnow,mark,++page,p);
			if(judge==23)
			{
				return 23;
			}
		}
		else if(judge==95)
		{
			if(KT_save(p->tra_num,p,page,length,lengthnum,num,1))
			return(23);
		}
		if(!tab) judge=26;	
		else judge++;
		tab=0;	
	}
	
}
int f_ModifyKT(int *xnow,int *ynow,int *btnow,int *mark,int page,KT_train *p)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int length[7][9];
	int lengthnum[4]={1,1,1,-1};
	int num=-1;
	
	NewKT(page,1);
	memset(length,0,63*sizeof(int)); 
	num=KT_visual(p,length,page,0);	
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewKT(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(i<=num+1&&judge==27+i)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    if(num<i&&length[0][i]) num=i;
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
		    	
			    length[1][i]=hz_input(xnow,ynow,105,120+i*35,175,150+i*35,p->city[i+(page-1)*9],&tab,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
		    	
			    length[2][i]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->arrive_time[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,240,125+i*35,290,145+i*35,p->start_time[i+(page-1)*9],&tab,0,length[3][i]);
			    break;
		    }
		    else if(i<=num&&judge==63+i)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->hardseat_fee[i+(page-1)*9],&tab,0,length[4][i]);
			    break;
		    }
		    else if(i<=num&&judge==72+i)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->hardsleeper_fee[i+(page-1)*9],&tab,0,length[5][i]);
			    break;
		    }
		    else if(i<=num&&judge==81+i)
		    {
			    length[6][i]=nhz_input(xnow,ynow,400,125+i*35,430,145+i*35,p->softsleeper_fee[i+(page-1)*9],&tab,0,length[6][i]);
			    break;
		    }
		    if(judge==23)  return(23);
	    	else if(judge==96)
	    	{
	        		*mark=0;
			        judge=f_KTmore(xnow,ynow,btnow,mark,page,p,num);
			        if(judge==26)//接受返回 
    	        	{
    	        		*mark=0;
	            		NewKT(page,1);
	                    KT_visual(p,length,page,0);
       	            }
	    	}
    		
	    	else if(judge==94&&num==8&&page<4) 
    		{
				*mark=0;
				judge=f_ModifyKT(xnow,ynow,btnow,mark,++page,p);
				if(judge==23)
				{
					return 23;
				}
    		}
    		else if(judge==95)
	    	{
	    		if(KT_save(p->tra_num,p,page,length,lengthnum,num,1))
    			return(23);
    		} 
		}
		if(!tab) judge=26;	
		else judge++;
		tab=0;
	}
}

int f_ModifyZ(int *xnow,int *ynow,int *btnow,int *mark,Z_train *p) 
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int length[7][2];
	int lengthnum[4]={1,1,1,-1};
	
	NewZ();
	memset(length,0,14*sizeof(int)); 
	Z_visual(p,length,lengthnum);	
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewZ(&judge,*xnow,*ynow,state);
		for(i=0;i<2;i++)
		{
			if(judge==27+i)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i],&tab,length[0][i]);
			    break;
		    }
		    else if(judge==36+i)
		    {
		    	length[1][i]=hz_input(xnow,ynow,105,120+i*35,140,150+i*35,p->city[i],&tab,length[1][i]);
		    	if(tab)
		    	{
		    		judge++;
				}
				break;
			}
		    else if(judge==45+i)
		    {
		    	if(judge==45)
		    	{
		    		length[2][0]=nhz_input(xnow,ynow,180,125,230,145,p->start_time,&tab,0,length[2][0]);
				}
				if(judge==46)
				{
					length[2][1]=nhz_input(xnow,ynow,180,160,230,180,p->arrive_time,&tab,0,length[2][1]);
			    }
				break;
		    }
		    else if(judge==63)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->hardseat_fee,&tab,0,length[4][i]);
			    break;
		    }
		    else if(judge==72)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->hardsleeper_fee,&tab,0,length[5][i]);
			    break;
		    }
		    else if(judge==81)
		    {
			    length[6][i]=nhz_input(xnow,ynow,400,125+i*35,430,145+i*35,p->softsleeper_fee,&tab,0,length[6][i]);
			    break;
		    }
		    else if(judge==90)
		    {
			    lengthnum[0]=nhz_input(xnow,ynow,550,125,595,145,p->hard_seat,&tab,0,lengthnum[0]);
			    break; 
		    }
		    else if(judge==91)
		    {
			    lengthnum[1]=nhz_input(xnow,ynow,550,160,595,180,p->hard_sleeper,&tab,0,lengthnum[1]);
		    	break;
		    }
		    else if(judge==92)
		    {
			    lengthnum[2]=nhz_input(xnow,ynow,550,195,595,215,p->soft_sleeper,&tab,0,lengthnum[2]);
		    	break;
		    }
		    if(judge==23)  return(23);
    		else if(judge==95)
	    	{
	    		if(Z_save(p->tra_num,p,length,lengthnum,1))
    			return(23);
    		} 
		}
		if(!tab) judge=26;	
		else judge++;
		tab=0;
	}
}
int f_Gmore(int *xnow,int *ynow,int *btnow,int *mark,int page,G_train *p,int num)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int length[4][9];
	int lengthnum[3]={1,1,1};

	more(page,'G');
	memset(length,0,36*sizeof(int)); 
	G_visual(p,length,page,1);
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_more(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(i<=num&&judge==27+i)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
			    length[1][i]=nhz_input(xnow,ynow,110,125+i*35,155,145+i*35,p->f_seat[i+(page-1)*9],&tab,0,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
			    length[2][i]=nhz_input(xnow,ynow,170,125+i*35,215,145+i*35,p->s_seat[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,230,125+i*35,275,145+i*35,p->b_seat[i+(page-1)*9],&tab,0,length[3][i]);
			    break;
		    }
		}
		if(judge==23)  return(23);
		else if(judge==96) return 26;
		else if(judge==94&&num==8&&page<4) 
		{
			*mark=0;
			judge=f_ModifyG(xnow,ynow,btnow,mark,++page,p);
			if(judge==23)
			{
				return 23;
			}
		}
		else if(judge==95)
		{
			if(G_save(p->tra_num,p,page,length,lengthnum,num,1))
			return(23);
		}
		if(!tab) judge=26;	
		else judge++;
		tab=0;	
	}
}

int f_ModifyG(int *xnow,int *ynow,int *btnow,int *mark,int page,G_train *p)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int length[7][9];
	int lengthnum[4]={1,1,1,-1};
	int num=-1;
	
	NewG(page,1);
	memset(length,0,63*sizeof(int)); 
	num=G_visual(p,length,page,0);	
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewG(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(judge==27+i&&i<=num+1)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    if(num<i&&length[0][i]) num=i;
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
		    	
			    length[1][i]=hz_input(xnow,ynow,105,120+i*35,175,150+i*35,p->city[i+(page-1)*9],&tab,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
		    	
			    length[2][i]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->arrive_time[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,240,125+i*35,290,145+i*35,p->start_time[i+(page-1)*9],&tab,0,length[3][i]);
			    break;
		    }
		    else if(i<=num&&judge==63+i)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->fclass_fee[i+(page-1)*9],&tab,0,length[4][i]);
			    break;
		    }
		    else if(i<=num&&judge==72+i)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->sclass_fee[i+(page-1)*9],&tab,0,length[5][i]);
			    break;
		    }
		    else if(i<=num&&judge==81+i)
		    {
			    length[6][i]=nhz_input(xnow,ynow,400,125+i*35,430,145+i*35,p->business_fee[i+(page-1)*9],&tab,0,length[6][i]);
			    break;
		    }
		}
	    if(judge==23)  return(23);
	   	else if(judge==96)
	   	{
	     	*mark=0;
		    judge=f_Gmore(xnow,ynow,btnow,mark,page,p,num);
		    if(judge==26)//接受返回 
           	{
           		*mark=0;
	       		NewG(page,1);
	            G_visual(p,length,page,0);
            }
	   	}
    		
	   	else if(judge==94&&num==8&&page<4) 
   		{
	    	*mark=0;
		    judge=f_ModifyG(xnow,ynow,btnow,mark,++page,p);
		    if(judge==23)
			{
				return 23;
			}
   		}
   		else if(judge==95)
	   	{
	   		if(G_save(p->tra_num,p,page,length,lengthnum,num,1))
    		return(23);
   		} 
		if(!tab) judge=26;	
		else judge++;
		tab=0;
	}
}

int f_Dmore(int *xnow,int *ynow,int *btnow,int *mark,int page,D_train *p,int num)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int length[4][9];
	int lengthnum[3]={1,1,1};

	more(page,'D');
	memset(length,0,36*sizeof(int)); 
	D_visual(p,length,page,1);
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_more(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(i<=num&&judge==27+i)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
			    length[1][i]=nhz_input(xnow,ynow,110,125+i*35,155,145+i*35,p->f_seat[i+(page-1)*9],&tab,0,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
			    length[2][i]=nhz_input(xnow,ynow,170,125+i*35,215,145+i*35,p->s_seat[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		}
		if(judge==23)  return(23);
		else if(judge==96) return 26;
		else if(judge==94&&num==8&&page<4) 
		{
			*mark=0;
			judge=f_ModifyD(xnow,ynow,btnow,mark,++page,p);
			if(judge==23)
			{
				return 23;
			}
		}
		else if(judge==95)
		{
			if(D_save(p->tra_num,p,page,length,lengthnum,num,1))
			return(23);
		}
		if(!tab) judge=26;	
		else judge++;
		tab=0;	
	}
}

int f_ModifyD(int *xnow,int *ynow,int *btnow,int *mark,int page,D_train *p)
{
	FILE *fp;
	int judge=26;
	int state=0;
	register int i,j;
	int tab=0;
	int length[7][9];
	int lengthnum[4]={1,1,1,-1};
	int num=-1;
	
	NewD(page,1);
	memset(length,0,63*sizeof(int));
	num=D_visual(p,length,page,0);	
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewD(&judge,*xnow,*ynow,state);
		for(i=0;i<9;i++)
		{
			if(judge==27+i&&i<=num+1)
		    {
			    length[0][i]=hz_input(xnow,ynow,30,120+i*35,100,150+i*35,p->station[i+(page-1)*9],&tab,length[0][i]);
			    if(num<i&&length[0][i]) num=i;
			    break;
		    }
		    else if(i<=num&&judge==36+i)
		    {
		    	
			    length[1][i]=hz_input(xnow,ynow,105,120+i*35,175,150+i*35,p->city[i+(page-1)*9],&tab,length[1][i]);
			    break;
		    }
		    else if(i<=num&&judge==45+i)
		    {
		    	
			    length[2][i]=nhz_input(xnow,ynow,180,125+i*35,230,145+i*35,p->arrive_time[i+(page-1)*9],&tab,0,length[2][i]);
			    break;
		    }
		    else if(i<=num&&judge==54+i)
		    {
			    length[3][i]=nhz_input(xnow,ynow,240,125+i*35,290,145+i*35,p->start_time[i+(page-1)*9],&tab,0,length[3][i]);
			    //len=nhz_input(xnow,ynow,240,125+i*35,290,145+i*35,p->start_time[i+(page-1)*9],&tab,0,len);
			    break;
		    }
		    else if(i<=num&&judge==63+i)
		    {
			    length[4][i]=nhz_input(xnow,ynow,310,125+i*35,340,145+i*35,p->fclass_fee[i+(page-1)*9],&tab,0,length[4][i]);
			    break;
		    }
		    else if(i<=num&&judge==72+i)
		    {
			    length[5][i]=nhz_input(xnow,ynow,355,125+i*35,385,145+i*35,p->sclass_fee[i+(page-1)*9],&tab,0,length[5][i]);
			    break;
		    }
		}
	    if(judge==23)  return(23);
	   	else if(judge==96)
	   	{
	     	*mark=0;
		    judge=f_Dmore(xnow,ynow,btnow,mark,page,p,num);
		    if(judge==26)//接受返回 
           	{
           		*mark=0;
	       		NewD(page,1);
	            D_visual(p,length,page,0);
            }
	   	}
    		
	   	else if(judge==94&&num==8&&page<4) 
   		{
	    	*mark=0;
		    judge=f_ModifyD(xnow,ynow,btnow,mark,++page,p);
		    if(judge==23)
			{
				return 23;
			}
   		}
   		else if(judge==95)
	   	{
	   		if(D_save(p->tra_num,p,page,length,lengthnum,num,1))
    		return(23);
   		} 
		if(!tab) judge=26;	
		else judge++;
		tab=0;
	}
}


