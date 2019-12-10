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
/*svga������*/
/*���ߣ�������*/
/*��VGAģʽ��ͼ�����������ɼ���ʹ�ã�Ϊ����conio.hö����ɫֵ��ʹ����ɫ���sgva.h��ɫ�궨��*/
/*===========================*/ 
/*Ϊ����VGAģʽ���ȫ�ֱ���*/
unsigned char COLOR;
unsigned char WRITEMODE;
char far *VRAMaddr=0xa0000000;

/*����SVGAģʽ*/
void SetSVGAmode()
{
	union REGS regs;
	
	regs.x.ax=0x4f02;
	regs.x.bx=0x101;//���ó�640x480�ֱ���256ɫģʽ
	int86(0x10,&regs,&regs);
	if(regs.x.ax != 0x004f) 
	{
		printf("Failed to set SVGA mode!");
		getch();
		exit(1);
	}
}


/*���Ƶ�ɫ����ɫ*/ 
void SetPalette()//Ĭ����ɫ����ɫ 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[62+j].r=0;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=j+3;
					break;
				case 2 ://61����ɫ����ɫ�����ݶ� 
				    colorvalue[123+j].r=0;
					colorvalue[123+j].g=j;
					colorvalue[123+j].b=63;
					break;
				case 3 ://61���Ҷ� 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*���ֶ�����ɫ*/
	//��ɫ
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//�����ɫ 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//���� 
	colorvalue[247].r=45;
	colorvalue[247].g=45;
	colorvalue[247].b=63;
			
	//��ɫ 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//��ɫ 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//��ɫ 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//��ɫ 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//����ɫ 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//Ѫ��ɫ 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//����ɫ 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//����ɫ
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//������ԭʼ����ɫ�� 
	colorvalue[0].r=45;
	colorvalue[0].g=45;
	colorvalue[0].b=63; 
	
	/*����ɫд���ɫ��*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette1()//�������ɫ 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[62+j].r=63-j;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=63;
					break;
				case 2 ://61����ɫ���ɫ�����ݶ� 
				    colorvalue[123+j].r=63;
					colorvalue[123+j].g=j;
					colorvalue[123+j].b=0;
					break;
				case 3 ://61���Ҷ� 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*���ֶ�����ɫ*/
	//��ɫ
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//�����ɫ 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//���� 
	colorvalue[247].r=63;
	colorvalue[247].g=45;
	colorvalue[247].b=30;
			
	//��ɫ 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//��ɫ 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//��ɫ 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//��ɫ 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//����ɫ 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//Ѫ��ɫ 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//����ɫ 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//����ɫ
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//���ƣ�ԭʼ����ɫ�� 
	colorvalue[0].r=63;
	colorvalue[0].g=45;
	colorvalue[0].b=30;
	
	/*����ɫд���ɫ��*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette2()//��ɫ����ɫ 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[62+j].r=63-j;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=63;
					break;
				case 2 ://61������ƹ����ݶ� 
				    colorvalue[123+j].r=j;
					colorvalue[123+j].g=54;
					colorvalue[123+j].b=0;
					break;
				case 3 ://61���Ҷ� 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*���ֶ�����ɫ*/
	//��ɫ
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//�� 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//���� 
	colorvalue[247].r=43;
	colorvalue[247].g=57;
	colorvalue[247].b=38;
			
	//��ɫ 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//��ɫ 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//��ɫ 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//��ɫ 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//����ɫ 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//Ѫ��ɫ 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//����ɫ 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//����ɫ 
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//���̣�ԭʼ����ɫ�� 
	colorvalue[0].r=43;
	colorvalue[0].g=57;
	colorvalue[0].b=38;
	
	/*����ɫд���ɫ��*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette3()//��ɫ����ɫ 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[1+j].r=63;
					colorvalue[1+j].g=0;
					colorvalue[1+j].b=j;
					break; 
				case 1 ://61����ɫ����ɫ�����ݶ� 
					colorvalue[62+j].r=63-j;
					colorvalue[62+j].g=0;
					colorvalue[62+j].b=63;
					break;
				case 2 ://61����ɫ���ɫ�����ݶ� 
				    colorvalue[123+j].r=63;
					colorvalue[123+j].g=j;
					colorvalue[123+j].b=j;
					break;
				case 3 ://61���Ҷ� 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*���ֶ�����ɫ*/
	//��ɫ
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//�����ɫ 
	colorvalue[246].r=63;
	colorvalue[246].g=0;
	colorvalue[246].b=50;
			
	//���� 
	colorvalue[247].r=63;
	colorvalue[247].g=50;
	colorvalue[247].b=50;
			
	//��ɫ 
	colorvalue[248].r=50;
	colorvalue[248].g=14;
	colorvalue[248].b=0;
			
	//��ɫ 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//��ɫ 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//��ɫ 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//����ɫ 
	colorvalue[252].r=63;
	colorvalue[252].g=32;
	colorvalue[252].b=32;
			
	//Ѫ��ɫ 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//����ɫ 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//����ɫ
	colorvalue[255].r=0; 
	colorvalue[255].g=0;
	colorvalue[255].b=50;
			
	//���죨ԭʼ����ɫ�� 
	colorvalue[0].r=63;
	colorvalue[0].g=50;
	colorvalue[0].b=50;
	
	/*����ɫд���ɫ��*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}

void SetPalette4()//�ڰ�����ɫ 
{
	Color colorvalue[256];
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<61;j++)
		{
			switch(i)
			{
				case 0 ://��� 
					colorvalue[1+j].r=20;
					colorvalue[1+j].g=20;
					colorvalue[1+j].b=20;
					break; 
				case 1 ://��� 
					colorvalue[62+j].r=30;
					colorvalue[62+j].g=30;
					colorvalue[62+j].b=30;
					break;
				case 2 ://61����ɫ���ɫ�����ݶ� 
				    colorvalue[123+j].r=(j>48)?58:(j+10);
					colorvalue[123+j].g=(j>48)?58:(j+10);
					colorvalue[123+j].b=(j>48)?58:(j+10);
					break;
				case 3 ://61���Ҷ� 
				    colorvalue[184+j].r=j;
					colorvalue[184+j].g=j;
					colorvalue[184+j].b=j; 
					break;
			}
		}
	}
	/*���ֶ�����ɫ*/
	//��ɫ
	colorvalue[245].r=0;
	colorvalue[245].g=50;
	colorvalue[245].b=0;
			
	//���� 
	colorvalue[246].r=50;
	colorvalue[246].g=50;
	colorvalue[246].b=50;
			
	//�� 
	colorvalue[247].r=40;
	colorvalue[247].g=40;
	colorvalue[247].b=40;
			
	//��ɫ 
	colorvalue[248].r=0;
	colorvalue[248].g=0;
	colorvalue[248].b=0;
			
	//��ɫ 
	colorvalue[249].r=63;
	colorvalue[249].g=63;
	colorvalue[249].b=40;
			
	//��ɫ 
	colorvalue[250].r=63;
	colorvalue[250].g=32;
	colorvalue[250].b=0;
			
	//��ɫ 
	colorvalue[251].r=63;
	colorvalue[251].g=63;
	colorvalue[251].b=63;
			
	//���� 
	colorvalue[252].r=50;
	colorvalue[252].g=50;
	colorvalue[252].b=50;
			
	//Ѫ��ɫ 
	colorvalue[253].r=50;
	colorvalue[253].g=0;
	colorvalue[253].b=0; 
			
	//����ɫ 
	colorvalue[254].r=0;
	colorvalue[254].g=37;
	colorvalue[254].b=37;
			
	//���
	colorvalue[255].r=10; 
	colorvalue[255].g=10;
	colorvalue[255].b=10;
			
	//�ң�ԭʼ����ɫ�� 
	colorvalue[0].r=40;
	colorvalue[0].g=40;
	colorvalue[0].b=40;
	
	/*����ɫд���ɫ��*/
	for(i=0;i<256;i++)
	{
		outportb(0x3c8,i);
		outportb(0x3c9,colorvalue[i].r);
		outportb(0x3c9,colorvalue[i].g);
		outportb(0x3c9,colorvalue[i].b);
    }
}


/*���㺯��*/ 
char putpixel(int x,int y,int color)
{
	char far *p=VRAMaddr;
	unsigned long int position;
	unsigned char page;
	
	if(x<0||x>640||y<0||y>480) return -1;
	
	position=(unsigned long int)y*640+x;//��ȡʵ�ʵ�ֵַ 
	page=position>>16;//64k��ҳ
	Selectpage(page);
	if(WRITEMODE)
	p[position]^=color;
	else 
	p[position]=color;
	return color; 
}

//ȡ�㺯��  
char getpixel(int x,int y) 
{
	char far *p=VRAMaddr;
	unsigned long int position;
	unsigned char page;
	
	if(x<0||x>640||y<0||y>480) return -1;
	
	position=(unsigned long int)y*640+x;//��ȡʵ�ʵ�ֵַ 
	page=position>>16;//64k��ҳ
	Selectpage(page);
	
	return p[position]&0xff;
}


void Selectpage(char page)//SVGA256ɫ��ҳ���� 
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


/*���ñ���ɫ*/ 
void setbkcolor(int color)
{
	Color bkcolor;
	/*�ӵ�ɫ�������ɫ*/
	outportb(0x3c7,color);
	bkcolor.r=inportb(0x3c9);
	bkcolor.g=inportb(0x3c9);
	bkcolor.b=inportb(0x3c9);
	/*����ɫд����ŵ�ɫ��*/ 
	outportb(0x3c8,0);
	outportb(0x3c9,bkcolor.r);
	outportb(0x3c9,bkcolor.g);
	outportb(0x3c9,bkcolor.b);
}


/*���ߺ���*/ 
void line(int x1,int y1,int x2,int y2)//��Bresenham��ʵ�ֿ��ٻ��� 
{
	int err=0,e,ne;//e��ʾ��һ���������  ne��ʾ����һ��������� 
	int dy,dx,ddx,ddy;
	int xinc,yinc;//λ������ 
	int x=x1,y=y1;
	
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	ddx=dx<<1;
	ddy=dy<<1;
	xinc=x2>x1?1:(x1==x2?0:-1);
	yinc=y2>y1?1:(y2==y1?0:-1);
	
	if(dx>dy)
	{
		//�����۵�λ 
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


/*�����κ���*/ 
void rectangle(int x1,int y1,int x2,int y2)
{
	int i;
	for(i=x1;i<x2;i++) putpixel(i,y1,COLOR);
	for(i=y1;i<y2;i++) putpixel(x2,i,COLOR);
	for(i=x2;i>x1;i--) putpixel(i,y2,COLOR);
	for(i=y2;i>y1;i--) putpixel(x1,i,COLOR);  
}

/*��ʵ���κ���*/ 
void bar(int x1,int y1,int x2,int y2)
{
	int i,j;
	for(i=y1;i<=y2;i++)
	{
		for(j=x1;j<=x2;j++)
		putpixel(j,i,COLOR);
	}
}


/*������κ���*/
void drawpoly(int n,int *p)
{
	int i;
	for(i=0;i<n-1;i++)
	{
		line(p[i*2],p[i*2+1],p[i*2+2],p[i*2+3]);
	}
}

/*��亯��*/ 
/*�����ԣ�bc�������㾭�䷺������ջ��������ϵͳ�Ķ��ڴ�Ҳ�����ޣ����ø���������㷨��֮*/ 
/*ע�������������ޣ��ú�����BC�������ڶ಻�㣬��������ϼ�ͼ�ε����*/ 
void floodfill(int x,int y,char border) 
{
	struct G_Stack *top,*bottom;
	int tempx=x,tempy=y;
	int lastx=x,lasty=y;
	int ways=0,lastways=0;
	
	if((top=malloc(sizeof(struct G_Stack)))==NULL)//����ջ�� 
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
			/*ע���˴���䷽��Ҳ����Ҫ  ������������Ѳ���Ϊ��ʡ�ڴ�����*/
			if(top->left!=COLOR&&top->left!=border)
			{
				/*ջ����Χ��ͨ�� ��ͨ�����ص�׼����ջ*/
				if(tempx==x&&tempy==y) 
				{
					tempx=(top->x)-1;
					tempy=top->y;
				}
				ways++;//��ǰλ�ÿ�ͨ 
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
			
			top=pop(top);//д�� �õ��ջ 
			if(lastways>ways)
			{
				
				top=push(top,lastx,lasty);//��һ��ͨ�������ڴ˵� ����Ϊ����������� ��ջ 
			}
			if(tempx!=x||tempy!=y)
			{
				top=push(top,tempx,tempy);//�ƶ�����λ�� ��ջ 
			}
			/*����λ����״̬����*/ 
			lastx=x;
			lasty=y;
			x=tempx;
		  	y=tempy;
		  	lastways=ways;
		  	ways=0;
		}
	}
	free(top);//���ջ�� ������ 
}
/*���㸨����ջ����*/ 
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
/*���㸨����ջ����*/ 
struct G_Stack *pop(struct G_Stack *top)
{
	struct G_Stack *NewTop;
	
	NewTop=top->next;
	free(top);
	return NewTop;
}

/*��Բ����*/ 
void circle(int centerx,int centery,int r)
{
	int x,y,d;
	if(r>0)
	{
		y=r;
		d=3-(r<<1);//�ڶ��λ���ʱ��� ��ƽ��������� 
		for(x=0;x<=y;x++)//���˸��˷�֮һԲ
		{
			putpixel(centerx+x,centery+y,COLOR);
			putpixel(centerx+x,centery-y,COLOR);
			putpixel(centerx-x,centery+y,COLOR);
			putpixel(centerx-x,centery-y,COLOR);
			putpixel(centerx+y,centery-x,COLOR);
			putpixel(centerx+y,centery+x,COLOR);
			putpixel(centerx-y,centery+x,COLOR);
			putpixel(centerx-y,centery-x,COLOR);
			if(d<0) d+=x*4+6;//��x+1��x�������d'�����d������
			else
			{
				d+=(x-y)*4+10;//��x+1��x y-1��y�������d'�����d������ 
				y--;
			} 
		}
	}
}

/*��Բ������*/ 
void _arc(double start_angle,double end_angle,int centerx,int centery,int r)
{
	float add_angle=(PI/4)*sqr2/r;//�Ƕȵ���ֵ������С�������㣩
	double angle; 
	int oldx=0,oldy=0,newx,newy;
	for(angle=start_angle;angle<=end_angle;angle+=add_angle)
	{
		newx=(int)(centerx+r*cos(angle));
		newy=(int)(centery-r*sin(angle));//����Ϊ������ 
		if(newx!=oldx||newy!=oldy)
		{
			putpixel(newx,newy,COLOR);
			/*�����ԣ���������dosϵͳ�����������ƣ�����ɶϻ���������Ϊ�������*/
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


/*��ʵ��Բ����*/ 
void fillcircle(int centerx,int centery,int r)
{
	circle(centerx,centery,r);
	floodfill(centerx,centery,COLOR);
}

 /*ƽ������Բ����*/
void ellips(int centerx,int centery,int a,int b)//aΪ����ᣬbΪʵ����
{
	float errR,errB,errRB;
	int x=0,y=-b;
	int a2=a*a,b2=b*b;
	putpixel(centerx,centery+b,COLOR);//�Ȼ����� 
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


/*��ʵ����Բ����*/
void fillellips(int centerx,int centery,int a,int b)
{
	ellips(centerx,centery,a,b);
	floodfill(centerx,centery,COLOR);
}


/*�������뺯��*/ 
int outtextxy(int x,int y,char *s)//8x16�����ֿ� 
{
	FILE *asc=NULL;
	int i,j,k;
	char *mat,*temp;
	int len;
	long offset;
	int mask;
	
	len=strlen(s);
	if(!len) return 0;//���ַ�����ִ�в��� 
	if((asc=fopen("C:\\PRJ\\hz\\ASC16","rb"))==NULL)
	{
		printf("outtextxy can't open asc16!");
		getch();
		exit(1); 
	}
	
	if((mat=(char *)malloc(16*sizeof(char)*len))==NULL)//��ŵ��� 
	{
		printf("Failed!");
		fclose(asc);
		getch();
		exit(1);
	}
	temp=mat;
	for(i=0;i<len;i++)
	{
		offset=(long)16*s[i];//�����ַ����ļ�ƫ�� 
		fseek(asc,offset,SEEK_SET);
		fread(temp,sizeof(char),16,asc);//�������ַ��������mat 
		temp+=16;
	}
	fclose(asc);
	for(i=0;i<len;i++)//ͨ���ŵ���ʾ�ַ� 
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

/*��ʵ�ֵ�Ч�ʵ�ͼ��鴦����*/
/*ͬһ������ʹ��������ֵΪ65535���ʴ�ͼ���޷�ʹ��getimage*/
/*����Ʊϵͳ����ʹ�ô�ͼ�����ʿ�β���δʵ��*/ 
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

/*�ú���δʹ�ÿ鴫�ͣ����ǵ�Ч�Ļ��㣬����getimage()���ʹ��*/
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

void cleardevice()//�����Ļ 
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
	_train(100,200);//Ĭ�ϱ���ͼ 
}

/*��������ʱʹ�ã����ڼ��뺯����*/ 
void clearpart()
{
	setcolor(0);
	bar(200,51,640,439);
}

/*�ر�ͼ��ģʽ����(���Ǻܺ�)*/ 
void closegraph()
{
	setmode(3);//����Ϊ�ı�ģʽ 
}
