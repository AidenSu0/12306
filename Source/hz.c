/*====================================================
x,y Ϊ������ʾ���ֵ�λ��
s ��ʾ������ʾ�ĺ���
flag ��ʾ����ѡ���ֵĴ�С������flag�Ĳ�ͬ���ò�ͬ�ĺ��ֿ�
part ��ʾ���ּ�ļ��һ��Ϊ16
color ��ʾ���ֵ���ɫ
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
	FILE *hzk_p;                                       //���庺�ֿ��ļ�ָ��
	unsigned char quma,weima;                 //���庺�ֵ������λ��
	unsigned long offset;                          //���庺�����ֿ��е�ƫ����
	unsigned char mask[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};  //�������飬������ʾ���ֵ����е�����
	int i,j,pos,fx,fy;

	char mat[32];  //16*16�ĺ�����Ҫ32���ֽڵ��������洢
	int y0=y;
	int x0=x;
	// hzk_p = fopen("c:\\myCCD\\SOURSE\\hz\\hzk16","rb");            //ʹ�����·��
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

			/*ʶ��ո񲢴�ӡ�ո�*/
			if (*s == ' ')
			{
				x = x + 8;
				s += 1;
				continue;  //��ֹ����ո�ͬʱ����
		    }
			/*ʶ���з�������*/
			if (*s == '\n')
			{
				x = x0;
				y0 += 20;
   			    s += 1;
				continue;   //��ֹ�������ͬʱ����
			}
			if (outputLetterNum(*s, x, y0,color) == 1)
			{
				x = x + 8;
				s += 1;
				continue;  //��ֹ������ֺ���ĸͬʱ����
		    }
			y=y0;
			quma=s[0]-0xa0;                      //�������
			weima=s[1]-0xa0;                     //���λ��
			offset=(94*(quma-1)+(weima-1))*32L;   //���Ҫ��ʾ�ĺ������ֿ��ļ��е�ƫ��
			fseek(hzk_p,offset,SEEK_SET);         //�ض�λ�ļ�ָ��
			fread (mat,32,1,hzk_p);            //�����ú��ֵľ����������,1ΪҪ���������
			for(fx=0;fx<flag;fx++)
			for(i=0;i<16;i++)
			{
				pos=2*i;       //16*16��������ÿһ���������ֽ�
				for(fy=0;fy<flag;fy++)
				for(j=0;j<16;j++)    //һ��һ�е�ɨ�裬��λ��Ϊ��1�ĵ���ʾ����
				{
					
					if((mask[j%8]&mat[pos+j/8])!=NULL)   //j%8ֻ����0��8֮��ѭ����j/8��0��1֮��ѭ��
					{
						{
							putpixel(j*(flag-1)+x+j+fx,i*(flag-1)+y+i+fy,color);
						} 
					}

				}
			}
			/*====================================================
				������һ��������ʾ��
			====================================================*/
			x+=part*flag;        //��x һ��ƫ����part
			s+=2;           //�������ŵ������룬2���ֽڣ�����Ҫ��2

		}
		x=x0;y0+=20; //һ�к�����ʾ���,���´���࿪ʼ������֣���yһ��ƫ����
	}
	fclose(hzk_p);
}
