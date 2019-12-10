#include<stdio.h>
#include<dos.h>
#include "svga.h"
#include "mouse.h"

/*存放鼠标图形*/ 
int arrows_mouse[14][9]={
{ 1,3,3,3,3,3,3,3,3},
{ 1,1,3,3,3,3,3,3,3},
{ 1,0,1,3,3,3,3,3,3},
{ 1,0,0,1,3,3,3,3,3},
{ 1,0,0,0,1,3,3,3,3},
{ 1,0,0,0,0,1,3,3,3},
{ 1,0,0,0,0,0,1,3,3},
{ 1,0,0,0,0,0,0,1,3},
{ 1,0,0,0,0,0,0,0,1},
{ 1,0,0,1,0,1,1,1,3},
{ 1,0,1,1,0,1,3,3,3},
{ 1,1,3,3,1,0,1,3,3},
{ 3,3,3,3,1,0,1,3,3},
{ 3,3,3,3,3,1,3,3,3},
};
/*存放被鼠标遮住的背景*/ 
int bk_mouse[14][9]={
{ 1,3,3,3,3,3,3,3,3},
{ 1,1,3,3,3,3,3,3,3},
{ 1,0,1,3,3,3,3,3,3},
{ 1,0,0,1,3,3,3,3,3},
{ 1,0,0,0,1,3,3,3,3},
{ 1,0,0,0,0,1,3,3,3},
{ 1,0,0,0,0,0,1,3,3},
{ 1,0,0,0,0,0,0,1,3},
{ 1,0,0,0,0,0,0,0,1},
{ 1,0,0,1,0,1,1,1,3},
{ 1,0,1,1,0,1,3,3,3},
{ 1,1,3,3,1,0,1,3,3},
{ 3,3,3,3,1,0,1,3,3},
{ 3,3,3,3,3,1,3,3,3},
};
/*===================*/
/*鼠标控制函数*/
/*作者：苏新明*/
/*将函数放在循环使用，返回鼠标点击状态*/
/*===================*/ 

int mouse_control(int *xnow,int *ynow,int *btnow,int *mark)
{
	int xold=*xnow,yold=*ynow,btold=*btnow;
	int state=0;
    readxy(xnow,ynow,btnow);
    if(btold==1&&*btnow==0) state=1;//按下松开后确定为点击一次，防止重复刷新 
    if(*mark==0)//换界面时鼠标操作 
    {
    	getbk_mouse(*xnow,*ynow);
	    draw_mouse(*xnow,*ynow);
	    *mark=1;
	    return state; 
	}
    if(xold!=*xnow||yold!=*ynow)//位置变动时重放 
    {
        redraw(xold,yold);
 	    getbk_mouse(*xnow,*ynow);
	    draw_mouse(*xnow,*ynow);
	}
	return state;//鼠标操作状态 确定电机并松开返回TURE 
}

void draw_mouse(int x,int y)
{
	
	register int i,j;
	

	for(i=0;i<9;i++)
	{
		for(j=0;j<14;j++)
		{
			if(arrows_mouse[j][i]==0) putpixel(x+i,y+j,_WHITE);
			else if(arrows_mouse[j][i]==1) putpixel(x+i,y+j,_BLACK);
		}	
	}
	
}

void getbk_mouse(int x,int y)
{
	register int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<14;j++)
		{
			bk_mouse[j][i]=getpixel(x+i,y+j);
		}
	}
}

void redraw(int x,int y)
{
	register int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<14;j++)
		{
			
			if(arrows_mouse[j][i]==0||arrows_mouse[j][i]==1)
			putpixel(x+i,y+j,bk_mouse[j][i]); 
		}
	}
}

void readxy(int *x,int *y,int *bt)
{
	union REGS regs;
	
	regs.x.ax=3;
	int86(51,&regs,&regs);
	*x=regs.x.cx;
	*y=regs.x.dx;
	*bt=regs.x.bx;
}
/*添加输入框，输入法中调用*/ 
void Add_frame(int *xnow,int *ynow,int x1,int y1,int x2,int y2)
{
	redraw(*xnow,*ynow);
	setwritemode(XOR_PUT);
	setcolor(0x33);
	rectangle(x1,y1,x2,y2);
	setwritemode(COPY_PUT);
	getbk_mouse(*xnow,*ynow);
	draw_mouse(*xnow,*ynow);
} 

