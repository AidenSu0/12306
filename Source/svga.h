#ifndef __SVGA_H__
#define __SVGA_H__

#define PI 3.1415926
#define sqr2 (1.414)

#define setcolor(color) COLOR=color //������ɫ�ĺ궨�� 
#define RPTcolor(value) COLOR=1+value//��ɫ����ɫ���ɼ���0~60�� 
#define BBTcolor(value) COLOR=62+value//��ɫ����ɫ���ɼ���0~60�� 
#define BCTcolor(value) COLOR=123+value//��ɫ����ɫ���ɼ� ��0~60�� 
#define GTcolor(value) COLOR=184+value//�Ҷȼ���0~60�� 


 /*������ɫ�ĺ궨��*/ 
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

/*����дģʽ�ĺ궨��*/ 
#define COPY_PUT 0
#define XOR_PUT 1
#define setwritemode(mode) WRITEMODE=mode


/*Ϊ����VGAģʽ���ȫ�ֱ���*/
extern unsigned char COLOR;
extern unsigned char WRITEMODE;
extern char far *VRAMaddr;

//��ɫֵ�ṹ 
typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Color;

//�����ջ�ṹ 
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


void SetSVGAmode();//����256ɫģʽ 


void SetPalette();//�Զ���д���ɫ�� 
void SetPalette1();
void SetPalette2();
void SetPalette3();
void SetPalette4(); 


void Selectpage(register char);//��ҳ���� 


char putpixel(int x,int y,int color);//���㺯�� 


char getpixel(int x,int y);//ȡ�㺯�� 


void setbkcolor(int color);//���ñ�����ɫ 


void line(int x1,int y1,int x2,int y2);//�򵥻��ߺ��� 


void rectangle(int x1,int y1,int x2,int y2);//�����κ��� 


void bar(int x1,int y1,int x2,int y2);//��ʵ�����κ��� 


void drawpoly(int n,int *p);//������κ��� 


void floodfill(int x,int y,char border);//��亯�� 
struct G_Stack *push(struct G_Stack *top,int X,int Y);//��亯������ջ���� 
struct G_Stack *pop(struct G_Stack *top);//��亯���ĳ�ջ���� 


void circle(int centerx,int centery,int r);//��Բ���� 


void fillcircle(int centerx,int centery,int r);//��ʵ��Բ���� 


void _arc(double start_angle,double end_angle,int centerx,int centery,int r);//��Բ������ 


void ellips(int centerx,int centery,int a,int b);//����Բ���� 


void fillellips(int centerx,int centery,int a,int b);//��ʵ����Բ���� 


int outtextxy(int x,int y,char *s);//������ĺ��� 


void getimage(int x1,int y1,int x2,int y2,char *buf);//��ȡͼ�����Ϣ


void putimage(int x1,int y1,int x2,int y2,char *buf);//����λ�÷���ͼ��� 


void cleardevice();//�������� 
void clearpart();//�������� 


void closegraph();//�ر�ͼ��ϵͳ 

#endif
