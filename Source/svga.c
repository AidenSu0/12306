#include "svga.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#include <fcntl.h> 
#include <math.h>
#include <mem.h>
#include <math.h> 
#include "design.h"

/*===========================*/
/*svga函数库*/
/*作者：苏新明*/
/*与VGA模式画图函数重名，可兼容使用，为区分conio.h枚举颜色值，使用颜色请查sgva.h颜色宏定义*/
/*===========================*/ 
/*为兼容VGA模式设此全局变量*/
unsigned char COLOR;
unsigned char WRITEMODE;
char far *VRAMaddr=0xa0000000;

/*设置SVGA模式*/
void SetSVGAmode()
{
	union REGS regs;
	
	regs.x.ax=0x4f02;
	regs.x.bx=0x101;//设置成640x480分辨率256色模式
	int86(0x10,&regs,&regs);
	if(regs.x.ax != 0x004f) 
	{
		printf("Failed to set SVGA mode!");
		getch();
		exit(1);
	}
}


/*调制调色板颜色*/ 
void SetPalette()//默认蓝色主题色 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61级红色向紫色过渡梯度 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61级黑色向蓝色过渡梯度 
					colorvalue[62+j].r=0;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=j+3;
					break;
				case 2 ://61级蓝色向青色过渡梯度 
				    colorvalue[123+j].r=0;
					colorvalue[123+j].g=j;
					colorvalue[123+j].b=63;
					break;
				case 3 ://61级灰度 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*几种独立颜色*/
	//绿色
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//淡洋红色 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//淡蓝 
	colorvalue[247].r=45;
	colorvalue[247].g=45;
	colorvalue[247].b=63;
			
	//棕色 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//黄色 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//橙色 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//白色 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//淡红色 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//血红色 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//暗青色 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//深蓝色
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//淡蓝（原始背景色） 
	colorvalue[0].r=45;
	colorvalue[0].g=45;
	colorvalue[0].b=63; 
	
	/*将颜色写入调色板*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette1()//红黄主题色 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61级红色向紫色过渡梯度 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61级紫色向蓝色过渡梯度 
					colorvalue[62+j].r=63-j;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=63;
					break;
				case 2 ://61级红色向黄色过渡梯度 
				    colorvalue[123+j].r=63;
					colorvalue[123+j].g=j;
					colorvalue[123+j].b=0;
					break;
				case 3 ://61级灰度 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*几种独立颜色*/
	//绿色
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//淡洋红色 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//淡黄 
	colorvalue[247].r=63;
	colorvalue[247].g=45;
	colorvalue[247].b=30;
			
	//棕色 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//黄色 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//橙色 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//白色 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//淡红色 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//血红色 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//暗青色 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//深蓝色
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//淡黄（原始背景色） 
	colorvalue[0].r=63;
	colorvalue[0].g=45;
	colorvalue[0].b=30;
	
	/*将颜色写入调色板*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette2()//绿色主题色 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61级红色向紫色过渡梯度 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61级紫色向蓝色过渡梯度 
					colorvalue[62+j].r=63-j;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=63;
					break;
				case 2 ://61级绿向黄过渡梯度 
				    colorvalue[123+j].r=j;
					colorvalue[123+j].g=54;
					colorvalue[123+j].b=0;
					break;
				case 3 ://61级灰度 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*几种独立颜色*/
	//绿色
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//深 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//淡绿 
	colorvalue[247].r=43;
	colorvalue[247].g=57;
	colorvalue[247].b=38;
			
	//棕色 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//黄色 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//橙色 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//白色 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//淡红色 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//血红色 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//暗青色 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//深蓝色 
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//淡绿（原始背景色） 
	colorvalue[0].r=43;
	colorvalue[0].g=57;
	colorvalue[0].b=38;
	
	/*将颜色写入调色板*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette3()//红色主题色 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61级红色向紫色过渡梯度 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61级紫色向蓝色过渡梯度 
					colorvalue[62+j].r=63-j;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=63;
					break;
				case 2 ://61级红色向白色过渡梯度 
				    colorvalue[123+j].r=63;
					colorvalue[123+j].g=j;
					colorvalue[123+j].b=j;
					break;
				case 3 ://61级灰度 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*几种独立颜色*/
	//绿色
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//淡洋红色 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//淡红 
	colorvalue[247].r=63;
	colorvalue[247].g=50;
	colorvalue[247].b=50;
			
	//棕色 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//黄色 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//橙色 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//白色 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//淡红色 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//血红色 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//暗青色 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//深蓝色
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//淡红（原始背景色） 
	colorvalue[0].r=63;
	colorvalue[0].g=50;
	colorvalue[0].b=50;
	
	/*将颜色写入调色板*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette4()//黑白主题色 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://深灰 
					colorvalue[1+j].r=20;
					colorvalue[1+j].g=20;
					colorvalue[1+j].b=20;
					break; 
				case 1 ://深灰 
					colorvalue[62+j].r=30;
					colorvalue[62+j].g=30;
					colorvalue[62+j].b=30;
					break;
				case 2 ://61级黑色向白色过渡梯度 
				    colorvalue[123+j].r=(j>48)?58:(j+10);
					colorvalue[123+j].g=(j>48)?58:(j+10);
					colorvalue[123+j].b=(j>48)?58:(j+10);
					break;
				case 3 ://61级灰度 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*几种独立颜色*/
	//绿色
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//淡灰 
	colorvalue[246].r=50;
	colorvalue[246].g=50;
	colorvalue[246].b=50;
			
	//灰 
	colorvalue[247].r=40;
	colorvalue[247].g=40;
	colorvalue[247].b=40;
			
	//黑色 
	colorvalue[248].r=0;
	colorvalue[248].g=0;
	colorvalue[248].b=0;
			
	//黄色 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//橙色 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//白色 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//淡灰 
	colorvalue[252].r=50;
	colorvalue[252].g=50;
	colorvalue[252].b=50;
			
	//血红色 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//暗青色 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//深灰
	colorvalue[255].r=10; 
	colorvalue[255].g=10;
	colorvalue[255].b=10;
			
	//灰（原始背景色） 
	colorvalue[0].r=40;
	colorvalue[0].g=40;
	colorvalue[0].b=40;
	
	/*将颜色写入调色板*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}


/*画点函数*/ 
char putpixel(int x,int y,int color)
{
	char far *p=VRAMaddr;
	unsigned long int position;
	unsigned char page;
	
	if(x<0||x>640||y<0||y>480) return -1;
	
	position=(unsigned long int)y*640+x;//获取实际地址值 
	page=position>>16;//64k换页
	Selectpage(page);
	if(WRITEMODE)
	p[position]^=color;
	else 
	p[position]=color;
	return color; 
}

//取点函数  
char getpixel(int x,int y) 
{
	char far *p=VRAMaddr;
	unsigned long int position;
	unsigned char page;
	
	if(x<0||x>640||y<0||y>480) return -1;
	
	position=(unsigned long int)y*640+x;//获取实际地址值 
	page=position>>16;//64k换页
	Selectpage(page);
	
	return p[position]&0xff;
}


void Selectpage(char page)//SVGA256色换页函数 
{
	static char old_page=-1;
	union REGS regs;
	
	if(page!=old_page)
	{
		regs.x.ax=0x4f05;
		regs.x.bx=0;
		regs.x.dx=page;
		int86(0x10,&regs,&regs);
		old_page=page; 
	}
}


/*设置背景色*/ 
void setbkcolor(int color)
{
	Color bkcolor;
	/*从调色板读出颜色*/
	outportb(0x3c7,color);
	bkcolor.r=inportb(0x3c9);
	bkcolor.g=inportb(0x3c9);
	bkcolor.b=inportb(0x3c9);
	/*将颜色写入零号调色板*/ 
	outportb(0x3c8,0);
	outportb(0x3c9,bkcolor.r);
	outportb(0x3c9,bkcolor.g);
	outportb(0x3c9,bkcolor.b);
}


/*画线函数*/ 
void line(int x1,int y1,int x2,int y2)//用Bresenham法实现快速画线 
{
	int err=0,e,ne;//e表示进一的误差增量  ne表示不进一的误差增量 
	int dy,dx,ddx,ddy;
	int xinc,yinc;//位置增量 
	int x=x1,y=y1;
	
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	ddx=dx<<1;
	ddy=dy<<1;
	xinc=x2>x1?1:(x1==x2?0:-1);
	yinc=y2>y1?1:(y2==y1?0:-1);
	
	if(dx>dy)
	{
		//误差积累单位 
		e=ddy-ddx;
		ne=ddy;
		while(1)
		{
			putpixel(x,y,COLOR);
			if(x==x2) break;
			if(err+ddy>dx) 
			{
				y+=yinc;
				err+=e;
			}
			else 
			err+=ne;
			x+=xinc;
		} 
	}
	else 
	{
		e=ddx-ddy;
		ne=ddx;
		while(1)
		{
			putpixel(x,y,COLOR);
			if(y==y2) break;
			if(err+ddx>dy) 
			{
				x+=xinc;
				err+=e;
			}
			else 
			err+=ne;
			y+=yinc;
		} 
	}
}


/*画矩形函数*/ 
void rectangle(int x1,int y1,int x2,int y2)
{
	int i;
	for(i=x1;i<x2;i++) putpixel(i,y1,COLOR);
	for(i=y1;i<y2;i++) putpixel(x2,i,COLOR);
	for(i=x2;i>x1;i--) putpixel(i,y2,COLOR);
	for(i=y2;i>y1;i--) putpixel(x1,i,COLOR);  
}

/*画实矩形函数*/ 
void bar(int x1,int y1,int x2,int y2)
{
	int i,j;
	for(i=y1;i<=y2;i++)
	{
		for(j=x1;j<=x2;j++)
		putpixel(j,i,COLOR);
	}
}


/*画多边形函数*/
void drawpoly(int n,int *p)
{
	int i;
	for(i=0;i<n-1;i++)
	{
		line(p[i*2],p[i*2+1],p[i*2+2],p[i*2+3]);
	}
}

/*填充函数*/ 
/*经测试，bc不能满足经典泛洪填充的栈需求，虚拟系统的堆内存也很有限，故用改良的填充算法代之*/ 
/*注：鄙人能力有限，该函数在BC下仍有众多不足，仅能满足较简单图形的填充*/ 
void floodfill(int x,int y,char border) 
{
	struct G_Stack *top,*bottom;
	int tempx=x,tempy=y;
	int lastx=x,lasty=y;
	int ways=0,lastways=0;
	
	if((top=malloc(sizeof(struct G_Stack)))==NULL)//设置栈顶 
	{
		printf("ERROR!");
		getch();
		exit(1);
	}
	bottom=top;
	top=push(top,x,y);
	while(top!=bottom)
	{
	    putpixel(x,y,COLOR);
		if(x>0&&x<640&&y>0&&y<480)
		{
			/*注：此处填充方向也很重要  以下填充走向已测试为最省内存走向*/
			if(top->left!=COLOR&&top->left!=border)
			{
				/*栈点周围有通道 将通道像素点准备入栈*/
				if(tempx==x&&tempy==y) 
				{
					tempx=(top->x)-1;
					tempy=top->y;
				}
				ways++;//当前位置可通 
			}
		
		    if(top->right!=COLOR&&top->right!=border)
			{
				if(tempx==x&&tempy==y) 
				{
					tempx=(top->x)+1;
					tempy=top->y;
				}
				ways++;
			}
			
			if(top->front!=COLOR&&top->front!=border)
			{
				if(tempx==x&&tempy==y)
				{
					tempy=(top->y)-1;
					tempx=top->x;
				}
				ways++;
			}
			
			if(top->back!=COLOR&&top->back!=border)
			{
				if(tempx==x&&tempy==y)
				{
					tempy=(top->y)+1;
					tempx=top->x;
				}
				ways++;
			} 
			
			top=pop(top);//写完 该点出栈 
			if(lastways>ways)
			{
				
				top=push(top,lastx,lasty);//上一点通道数大于此点 可能为创建封闭区域处 入栈 
			}
			if(tempx!=x||tempy!=y)
			{
				top=push(top,tempx,tempy);//移动到新位置 入栈 
			}
			/*更新位置与状态参量*/ 
			lastx=x;
			lasty=y;
			x=tempx;
		  	y=tempy;
		  	lastways=ways;
		  	ways=0;
		}
	}
	free(top);//清空栈底 （顶） 
}
/*填充点辅助入栈函数*/ 
struct G_Stack *push(struct G_Stack *top,int X,int Y)
{
	struct G_Stack *p;
	
	if((p=malloc(sizeof(struct G_Stack)))==NULL)
	{
		printf("overflow!");
		getch();
		exit(1);
	}
	p->x=X;
	p->y=Y;
	p->left=getpixel(X-1,Y);
	p->right=getpixel(X+1,Y);
	p->front=getpixel(X,Y-1);
	p->back=getpixel(X,Y+1);
	p->next=top;
	return p;
}
/*填充点辅助出栈函数*/ 
struct G_Stack *pop(struct G_Stack *top)
{
	struct G_Stack *NewTop;
	
	NewTop=top->next;
	free(top);
	return NewTop;
}

/*画圆函数*/ 
void circle(int centerx,int centery,int r)
{
	int x,y,d;
	if(r>0)
	{
		y=r;
		d=3-(r<<1);//第二次画点时误差 （平方差差量） 
		for(x=0;x<=y;x++)//画八个八分之一圆
		{
			putpixel(centerx+x,centery+y,COLOR);
			putpixel(centerx+x,centery-y,COLOR);
			putpixel(centerx-x,centery+y,COLOR);
			putpixel(centerx-x,centery-y,COLOR);
			putpixel(centerx+y,centery-x,COLOR);
			putpixel(centerx+y,centery+x,COLOR);
			putpixel(centerx-y,centery+x,COLOR);
			putpixel(centerx-y,centery-x,COLOR);
			if(d<0) d+=x*4+6;//由x+1代x计算出的d'相对于d的增量
			else
			{
				d+=(x-y)*4+10;//由x+1代x y-1代y计算出的d'相对于d的增量 
				y--;
			} 
		}
	}
}

/*画圆弧函数*/ 
void _arc(double start_angle,double end_angle,int centerx,int centery,int r)
{
	float add_angle=(PI/4)*sqr2/r;//角度递增值（按最小增量计算）
	double angle; 
	int oldx=0,oldy=0,newx,newy;
	for(angle=start_angle;angle<=end_angle;angle+=add_angle)
	{
		newx=(int)(centerx+r*cos(angle));
		newy=(int)(centery-r*sin(angle));//向下为正方向 
		if(newx!=oldx||newy!=oldy)
		{
			putpixel(newx,newy,COLOR);
			/*经测试，可能由于dos系统浮点运算限制，会造成断弧现象，以下为补点操作*/
			if(fabs(newx-oldx)==2&&fabs(newy-oldy)==2)
			{
				putpixel((newx+oldx)/2,(newy+oldy)/2,COLOR); 
			}
			else if(fabs(newx-oldx)==2)
			{
				putpixel((newx+oldx)/2,newy,COLOR);
			}
			else if(fabs(newy-oldy)==2)
			{
				putpixel(newx,(newy+oldy)/2,COLOR);
			}
			oldx=newx;
			oldy=newy;
		}
	}
}


/*画实心圆函数*/ 
void fillcircle(int centerx,int centery,int r)
{
	circle(centerx,centery,r);
	floodfill(centerx,centery,COLOR);
}

 /*平凡画椭圆函数*/
void ellips(int centerx,int centery,int a,int b)//a为虚半轴，b为实半轴
{
	float errR,errB,errRB;
	int x=0,y=-b;
	int a2=a*a,b2=b*b;
	putpixel(centerx,centery+b,COLOR);//先画顶点 
	putpixel(centerx,centery-b,COLOR);
	putpixel(centerx+a,centery,COLOR);
	putpixel(centerx-a,centery,COLOR);
	while(y<0||x<a)
	{
		errR=fabs((float)(x+1)*(x+1)/a2+(float)(y*y)/b2-1);
		errRB=fabs((float)(x+1)*(x+1)/a2+(float)(y+1)*(y+1)/b2-1);
		errB=fabs((float)(x*x)/a2+(float)(y+1)*(y+1)/b2-1);
		if(errR<=errRB&&errR<=errB) 
		{
			x++;
		} 
		else if(errRB<=errR&&errRB<=errB)
		{
			x++;
			y++;
		}
		else
		{
			y++;
		}
		putpixel(centerx+x,centery+y,COLOR);
		putpixel(centerx-x,centery+y,COLOR);
		putpixel(centerx-x,centery-y,COLOR);
		putpixel(centerx+x,centery-y,COLOR);
	}
} 


/*画实心椭圆函数*/
void fillellips(int centerx,int centery,int a,int b)
{
	ellips(centerx,centery,a,b);
	floodfill(centerx,centery,COLOR);
}


/*西文输入函数*/ 
int outtextxy(int x,int y,char *s)//8x16点阵字库 
{
	FILE *asc=NULL;
	int i,j,k;
	char *mat,*temp;
	int len;
	long offset;
	int mask;
	
	len=strlen(s);
	if(!len) return 0;//空字符串不执行操作 
	if((asc=fopen("C:\\PRJ\\hz\\ASC16","rb"))==NULL)
	{
		printf("outtextxy can't open asc16!");
		getch();
		exit(1); 
	}
	
	if((mat=(char *)malloc(16*sizeof(char)*len))==NULL)//存放点阵 
	{
		printf("Failed!");
		fclose(asc);
		getch();
		exit(1);
	}
	temp=mat;
	for(i=0;i<len;i++)
	{
		offset=(long)16*s[i];//计算字符的文件偏移 
		fseek(asc,offset,SEEK_SET);
		fread(temp,sizeof(char),16,asc);//将所有字符点阵存入mat 
		temp+=16;
	}
	fclose(asc);
	for(i=0;i<len;i++)//通过放点显示字符 
	{
		for(j=0;j<16;j++)
		{
			mask=0x80;
			for(k=0;k<8;k++)
			{
				if(mat[i*16+j]&mask)
				putpixel(x+8*i+k,y+j,COLOR);
				mask>>=1;
			}
		}
	}
	free(mat);
	return len;
}

/*仅实现低效率的图像块处理函数*/
/*同一个段内使用最大输出值为65535，故大图像无法使用getimage*/
/*本购票系统无需使用大图像处理，故垮段操作未实现*/ 
void getimage(int x1,int y1,int x2,int y2,char *buf)
{
	int i,j;
	int hight=y2-y1+1;
	int width=x2-x1+1;
	for(i=0;i<hight;i++)
	{
		for(j=0;j<width;j++)
		{
			buf[(unsigned long)i*width+j]=getpixel(j+x1,i+y1);
		}
	} 
}

/*该函数未使用块传送，仅是低效的画点，需与getimage()配合使用*/
void putimage(int x1,int y1,int x2,int y2,char *buf)
{
	int i,j;
	int hight=y2-y1+1;
	int width=x2-x1+1;
	for(i=0;i<hight;i++)
	{
		for(j=0;j<width;j++)
		{
			putpixel(j+x1,i+y1,buf[(unsigned long)i*width+j]);
		}
	} 
}

void cleardevice()//清除屏幕 
{
	unsigned long i,j;
	char far *p=VRAMaddr;
	for(i=0;i<5;i++)
	{
		Selectpage(i);
		if(i==4)
		{
			memset(i*65535+p,0,45058);
			break;
		}
		memset(i*65535+p,0,65535);
	}
	_train(100,200);//默认背景图 
}

/*重新搜索时使用（后期加入函数）*/ 
void clearpart()
{
	setcolor(0);
	bar(200,51,640,439);
}

/*关闭图形模式函数(不是很好)*/ 
void closegraph()
{
	setmode(3);//设置为文本模式 
}
