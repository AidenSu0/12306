#ifndef __SVGA_H__
#define __SVGA_H__

#define PI 3.1415926
#define sqr2 (1.414)

#define setcolor(color) COLOR=color //设置颜色的宏定义 
#define RPTcolor(value) COLOR=1+value//红色向紫色过渡级（0~60） 
#define BBTcolor(value) COLOR=62+value//黑色向蓝色过渡级（0~60） 
#define BCTcolor(value) COLOR=123+value//蓝色向青色过渡级 （0~60） 
#define GTcolor(value) COLOR=184+value//灰度级（0~60） 


 /*常用颜色的宏定义*/ 
#define _RED 1
#define LIGHT_RED 252
#define LIGHT_BLUE 247
#define _BLACK 184
#define DARK_GRAY 200
#define LIGHT_GRAY 230
#define _GREEN 245
#define LIGHT_MAGENTA 246
#define _PINK 35
#define _BROWN 248
#define _YELLOW 249
#define _ORANGE 250
#define _WHITE 251
#define _PURPLE 61
#define _CYAN 254
#define BLOOD_RED 253
#define _BLUE 255
#define LIGHT_CYAN 183

/*设置写模式的宏定义*/ 
#define COPY_PUT 0
#define XOR_PUT 1
#define setwritemode(mode) WRITEMODE=mode


/*为兼容VGA模式设此全局变量*/
extern unsigned char COLOR;
extern unsigned char WRITEMODE;
extern char far *VRAMaddr;

//颜色值结构 
typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Color;

//填充点的栈结构 
struct G_Stack
{
	int x;
	int y; 
	char left;
	char right;
	char front;
	char back;
	struct G_Stack *next;
};


void SetSVGAmode();//设置256色模式 


void SetPalette();//自定义写入调色板 
void SetPalette1();
void SetPalette2();
void SetPalette3();
void SetPalette4(); 


void Selectpage(register char);//换页函数 


char putpixel(int x,int y,int color);//画点函数 


char getpixel(int x,int y);//取点函数 


void setbkcolor(int color);//设置背景颜色 


void line(int x1,int y1,int x2,int y2);//简单画线函数 


void rectangle(int x1,int y1,int x2,int y2);//画矩形函数 


void bar(int x1,int y1,int x2,int y2);//画实矩阵形函数 


void drawpoly(int n,int *p);//画多边形函数 


void floodfill(int x,int y,char border);//填充函数 
struct G_Stack *push(struct G_Stack *top,int X,int Y);//填充函数的入栈辅助 
struct G_Stack *pop(struct G_Stack *top);//填充函数的出栈辅助 


void circle(int centerx,int centery,int r);//画圆函数 


void fillcircle(int centerx,int centery,int r);//画实心圆函数 


void _arc(double start_angle,double end_angle,int centerx,int centery,int r);//画圆弧函数 


void ellips(int centerx,int centery,int a,int b);//画椭圆函数 


void fillellips(int centerx,int centery,int a,int b);//画实心椭圆函数 


int outtextxy(int x,int y,char *s);//输出西文函数 


void getimage(int x1,int y1,int x2,int y2,char *buf);//获取图像块信息


void putimage(int x1,int y1,int x2,int y2,char *buf);//在新位置放置图像块 


void cleardevice();//清屏函数 
void clearpart();//部分清屏 


void closegraph();//关闭图形系统 

#endif
