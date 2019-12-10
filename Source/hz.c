/*====================================================
x,y 为所需显示汉字的位置
s 表示所需显示的汉字
flag 表示所需选择汉字的大小，根据flag的不同调用不同的汉字库
part 表示汉字间的间距一般为16
color 表示汉字的颜色
======================================================*/
#include"hz.h"
#include<stdio.h>
#include "svga.h"
#include<stdlib.h>
#include<conio.h>


int  outputLetterNum(char ch,int x,int y,int color)
{
	if (31<ch&&127>ch)
	{
		char temp[2] = { '\0','\0' };
		temp[0] = ch;
		setcolor(color);
		outtextxy(x,y,temp);
		return 1;
	}
	else return 0;

}


void puthz(int x, int y,char *s,int flag,int part,int color)
{
	FILE *hzk_p;                                       //定义汉字库文件指针
	unsigned char quma,weima;                 //定义汉字的区码和位码
	unsigned long offset;                          //定义汉字在字库中的偏移量
	unsigned char mask[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};  //功能数组，用于显示汉字点阵中的亮点
	int i,j,pos,fx,fy;

	char mat[32];  //16*16的汉字需要32个字节的数组来存储
	int y0=y;
	int x0=x;
	// hzk_p = fopen("c:\\myCCD\\SOURSE\\hz\\hzk16","rb");            //使用相对路径
	hzk_p = fopen("c:\\PRJ\\hz\\hzk16", "rb");
	if(hzk_p==NULL)
	{
	    outtextxy(10,10,"Can't open hzk16 file!Press any key to quit...");
	    getch();
	    exit(1);
	}
	while(*s!=NULL)
	{
	
		while (x<640-flag*16 && (*s!=NULL))
		{

			/*识别空格并打印空格*/
			if (*s == ' ')
			{
				x = x + 8;
				s += 1;
				continue;  //防止多个空格同时出现
		    }
			/*识别换行符并换行*/
			if (*s == '\n')
			{
				x = x0;
				y0 += 20;
   			    s += 1;
				continue;   //防止多个换行同时出现
			}
			if (outputLetterNum(*s, x, y0,color) == 1)
			{
				x = x + 8;
				s += 1;
				continue;  //防止多个数字和字母同时出现
		    }
			y=y0;
			quma=s[0]-0xa0;                      //求出区码
			weima=s[1]-0xa0;                     //求出位码
			offset=(94*(quma-1)+(weima-1))*32L;   //求出要显示的汉字在字库文件中的偏移
			fseek(hzk_p,offset,SEEK_SET);         //重定位文件指针
			fread (mat,32,1,hzk_p);            //读出该汉字的具体点阵数据,1为要读入的项数
			for(fx=0;fx<flag;fx++)
			for(i=0;i<16;i++)
			{
				pos=2*i;       //16*16矩阵中有每一行有两个字节
				for(fy=0;fy<flag;fy++)
				for(j=0;j<16;j++)    //一行一行地扫描，将位上为了1的点显示出来
				{
					
					if((mask[j%8]&mat[pos+j/8])!=NULL)   //j%8只能在0—8之间循环，j/8在0，1之间循环
					{
						{
							putpixel(j*(flag-1)+x+j+fx,i*(flag-1)+y+i+fy,color);
						} 
					}

				}
			}
			/*====================================================
				以上是一个汉字显示完
			====================================================*/
			x+=part*flag;        //给x 一个偏移量part
			s+=2;           //汉字里存放的是内码，2个字节，所以要加2

		}
		x=x0;y0+=20; //一行汉字显示完后,重新从左侧开始输出汉字，给y一个偏移量
	}
	fclose(hzk_p);
}
