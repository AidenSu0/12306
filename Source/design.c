#include "design.h"
#include <math.h>
/*=========================*/
/*元素设计函数集*/ 
/*作者：苏新明*/
/*背景图与修饰图标函数*/
/*=========================*/ 


	/*火车*/ 
void _train(int x,int y)
{
	int i;
	x-=100;
	y-=100;
	/*范围确定*/ 
	for(i=0;i<440;i++)
	{
		if(i<100)
		{
			setcolor(BCTcolor(i/11));
		}
		else 
		{
			setcolor(BCTcolor(10+(i-100)/7));
		}
		line(x+100+i,y+100+i/4,x+100+i,y+210);	
	}
	/*构建造型*/ 
	setcolor(0);
	_arc(3*PI/4,3*PI/2,x+130,y+181,30);
	_arc(4*PI/9,3*PI/4,x+170,y+169,50);
	line(x+179,y+118,x+540,y+210);
	line(x+130,y+210,x+540,y+210);
	line(x+108,y+159,x+136,y+131); 
	floodfill(x+105,y+102,0);
	floodfill(x+102,y+201,0);
	
	/*画火车窗*/ 
	setcolor(LIGHT_CYAN); 
	_arc(2*PI/5,3*PI/4,x+171,y+176,50);
	_arc(4*PI/9,4*PI/5,x+210,y+164,30);
	_arc(4*PI/9,4*PI/5,x+210,y+165,30);
	line(x+215,y+134,x+540,y+210);
	line(x+215,y+135,x+540,y+210);
	line(x+186,y+127,x+163,y+150);
	line(x+136,y+140,x+126,y+150);
	line(x+163,y+150,x+126,y+150);
	floodfill(x+140,y+145,LIGHT_CYAN);
	
	_arc(4*PI/9,8*PI/9,x+215,y+174,30);
	line(x+220,y+144,x+240,y+149);
	line(x+240,y+149,x+240,y+169);
	line(x+188,y+163,x+240,y+169);
	floodfill(x+239,y+168,LIGHT_CYAN);
	
	line(x+270,y+156,x+370,y+176);
	line(x+270,y+172,x+370,y+187);
	line(x+270,y+156,x+270,y+172);
	line(x+370,y+176,x+370,y+187);
	floodfill(x+369,y+186,LIGHT_CYAN);
	
	line(x+390,y+181,x+440,y+191);
	line(x+390,y+189,x+440,y+196);
	line(x+390,y+181,x+390,y+189);
	line(x+440,y+191,x+440,y+196);
	floodfill(x+439,y+195,LIGHT_CYAN);
	
	line(x+450,y+193,x+480,y+199);
	line(x+450,y+198,x+480,y+202);
	line(x+450,y+193,x+450,y+198);
	line(x+480,y+199,x+480,y+202);
	floodfill(x+479,y+201,0);
	
	/*其他修饰部分*/ 
	line(x+485,y+201,x+540,y+210);
	line(x+485,y+202,x+540,y+210);
	
	line(x+113,y+160,x+107,y+170);
	line(x+123,y+160,x+117,y+170);
	line(x+113,y+160,x+123,y+160);
	line(x+107,y+170,x+117,y+170);
	
	line(x+140,y+160,x+130,y+170);
	line(x+150,y+160,x+140,y+170);
	line(x+140,y+160,x+150,y+160);
	line(x+130,y+170,x+140,y+170);
	
	_arc(145*PI/100,162*PI/100,x+123,y+50,135);
	_arc(145*PI/100,162*PI/100,x+123,y+51,135);
	_arc(145*PI/100,162*PI/100,x+123,y+52,135);
	line(x+170,y+176,x+540,y+210);
	line(x+170,y+177,x+540,y+210);
	line(x+170,y+178,x+540,y+210);
	
	_arc(3*PI/2,162*PI/100,x+143,y+70,135);
	/*画车轨*/ 
	for(i=0;i<440;i++)
	{
		putpixel(x+100+i,y+220,BCTcolor(i/8));
	}	
}

    /*流星*/
void falling_star(int x1,int y1,int x2,int y2)
{
	int i;
	int j;
	int startx=x1+2*(x2-x1)/3;
	int starty=y1+(y2-y1)/5;
	int endy=y2-(y2-y1)/5;
	int stdy=(endy-starty)/30;
	
	for(i=starty,j=startx;i<endy;i++,j--)
	{
		putpixel(j,i,BCTcolor(30+(i-starty)/stdy));
	}
	for(i=starty,j=startx+1;i<endy;i++,j--)
	{
		putpixel(j,i,BCTcolor(30+(i-starty)/stdy));
	}
	for(i=starty,j=startx-1;i<endy;i++,j--)
	{
		putpixel(j,i,BCTcolor(30+(i-starty)/stdy));
	}
}

   /*星空*/ 
void starry_sky(int x1,int y1,int x2,int y2)
{
	int i;
	unsigned long all=(unsigned long)(y2-y1)*((float)(x2-x1)/300);//密度设置 
	int rx,ry,c,e,de,ty=1000/(y2-y1);
	for(i=0;i<all;i++)
	{
		rx=rand_num(x1,x2);
		ry=rand_num(y1,y2);
		c=rand_num(0,20);
		e=rand_num(0,4);
		de=rand_num(0,1000);
		if((ry-y1)*ty>de) continue;//由均匀概率分布下的递减判断实现渐隐效果
		if(ry-y1>70) e-=2;//进一步修正渐隐效果 
		else if(ry-y1>50) e--;
		putpixel(rx,ry,_WHITE);
		if(e>0)
		{
			putpixel(rx-1,ry,BCTcolor(40+c));
			putpixel(rx+1,ry,BCTcolor(40+c));
			putpixel(rx,ry-1,BCTcolor(40+c));
			putpixel(rx,ry+1,BCTcolor(40+c));
		}
		if(e>1)
		{
			putpixel(rx-1,ry-1,BCTcolor(40+c/2));
			putpixel(rx+1,ry+1,BCTcolor(40+c/2));
			putpixel(rx-1,ry+1,BCTcolor(40+c/2));
			putpixel(rx+1,ry-1,BCTcolor(40+c/2));
		}
		if(e>2)
		{
			putpixel(rx-2,ry,BCTcolor(40+c/3));
			putpixel(rx+2,ry,BCTcolor(40+c/3));
			putpixel(rx,ry-2,BCTcolor(40+c/3));
			putpixel(rx,ry+2,BCTcolor(40+c/3));
		}
	}
} 

	/*简单纹理生成*/
void texture(int x1,int y1,int x2,int y2)
{
	int c,rx,ry,i,j;
	int rdx,rdy;
	int all=((y2-y1)/30)*((x2-x1)/30); 
	for(i=0;i<all;i++)
	{
		rx=rand_num(x1,x2);
		ry=rand_num(y1,y2);
		c=rand_num(10,60);
		rdx=rand_num(0,2)-1;
		rdy=rand_num(0,2)-1;
		if(rdx*rdy<0) rdy=0;
		else if(rdx*rdy>0) rdx=0;
		for(j=c;j<60;j++)
		{
			rx+=rdx;
			ry+=rdy;
			if(rx<x1||rx>x2||ry<y1||ry>y2) break;
			putpixel(rx,ry,GTcolor(j));
		}	
	}
} 

	/*支付宝图标*/ 
void alipay(int x,int y)
{
	setcolor(BCTcolor(30));
	fillcircle(x,y,15);
	setcolor(_WHITE);
	bar(x-9,y-7,x+9,y-6);
	bar(x-1,y-10,x+1,y-3);
	bar(x-7,y-3,x+7,y-2);
	_arc(-3*PI/7,-PI/7,x-10,y-10,20);
	_arc(-3*PI/7,-PI/7,x-11,y-10,20);
	_arc(-3*PI/7,-PI/7,x-12,y-10,20);
	
	_arc(PI/2,3*PI/2,x-7,y+5,4);
	
	line(x-6,y+1,x+12,y+8);
	line(x-6,y+1,x+11,y+9);
	line(x-6,y+1,x+10,y+10);
	line(x-6,y+1,x+9,y+11);
	
	/*图像修复,转换杂色*/
	putpixel(x+9,y+10,COLOR); 
	putpixel(x+7,y+9,COLOR);
	putpixel(x+10,y+8,COLOR);
	putpixel(x+8,y+7,COLOR);
}

	/*微信支付图标*/ 
void WeChat_pay(int x,int y)
{
	setcolor(_GREEN);
	fillellips(x,y,15,11);
	setcolor(_WHITE);
	line(x-7,y-4,x-3,y);
	line(x-7,y-4,x-4,y+5);
	line(x-3,y,x+11,y-5);
	line(x-4,y+5,x+11,y-5);
	floodfill(x-3,y+1,_WHITE);
	
	setcolor(_GREEN);
	line(x-7,y-2,x-15,y+11);
	line(x-7,y+7,x-15,y+11);
	floodfill(x-11,y+8,_GREEN);
	
	/*修复图像，转换杂色*/
	putpixel(x-13,y+10,_GREEN);
	putpixel(x-13,y+9,_GREEN);
	putpixel(x+7,y-3,_WHITE);
	putpixel(x+5,y-2,_WHITE);
	putpixel(x+5,y-1,_WHITE);
} 


/*银行卡图标*/
void BankCard(int x,int y)
{
	setcolor(GTcolor(40));
	bar(x-11,y-6,x+19,y+14);
	setcolor(BCTcolor(30));
	line(x+9,y+11,x+12,y+11);
	setcolor(_ORANGE);
	line(x+14,y+11,x+17,y+11);
	setcolor(_ORANGE);
	bar(x-19,y-14,x+11,y+6);
	setcolor(_BLACK);
	bar(x-14,y-9,x+6,y-5);
	line(x-9,y+3,x+6,y+3);
	setcolor(_WHITE);
	bar(x-15,y-3,x,y);
}

/*二维码，以二维码左上角为标准*/
void QRCode(int x,int y)
{
	int i,rx,ry;
	/*生成二维码*/
	setcolor(_WHITE);
	bar(x-5,y-5,x+95,y+95);
	for(i=0;i<500;i++)
	{
		rx=x+3*rand_num(0,30);
		ry=y+3*rand_num(0,30);
		putpixel(rx,ry,_BLACK);
		putpixel(rx+1,ry,_BLACK);
		putpixel(rx,ry+1,_BLACK);
		putpixel(rx+1,ry+1,_BLACK);
		putpixel(rx+1,ry+2,_BLACK);
		putpixel(rx+2,ry+1,_BLACK);
		putpixel(rx,ry+2,_BLACK);
		putpixel(rx+2,ry,_BLACK);
		putpixel(rx+2,ry+2,_BLACK);
	}
	setcolor(_WHITE);
	bar(x,y,x+23,y+23);
	bar(x+67,y,x+90,y+23);
	bar(x,y+67,x+23,y+90); 
	
	setcolor(_BLACK);
	bar(x+7,y+7,x+14,y+14);
	bar(x+76,y+7,x+83,y+14);
	bar(x+7,y+77,x+14,y+84);

	for(i=0;i<3;i++)
	{
		rectangle(x+i,y+i,x+20-i,y+20-i);
		rectangle(x+70+i,y+i,x+90-i,y+20-i);
		rectangle(x+i,y+70+i,x+20-i,y+90-i);
	}
}

	/*扫描二维码动画*/
void ScanQRC(int x,int y)
{
	int i,j,k,d;
	char image[2][109];
	
	QRCode(x,y);
	setcolor(_YELLOW);
	rectangle(x-10,y-10,x+100,y+100);
	setcolor(BCTcolor(30));
	for(i=0;i<2;i++)//画四个角 
	{
		for(j=0;j<2;j++)
		{
			bar(x-9+79*i,y-9+105*j,x+10+89*i,y-6+105*j);
			bar(x-9+105*i,y-9+89*j,x-6+105*i,y+10+89*j);
		}
	}
	for(k=0;k<3;k++)//扫描过程 
	{
		for(j=0;j<109;j++)
		{
			image[0][j]=getpixel(x-9+j,y-9);
			image[1][j]=getpixel(x-9+j,y-8);
			putpixel(x-9+j,y-9,BCTcolor(5+fabs(55-j)));
			putpixel(x-9+j,y-8,BCTcolor(5+fabs(55-j)));
		}
		for(i=0;i<107;i++)
		{
			for(j=0;j<109;j++)
			{
				putpixel(x-9+j,y-9+i,image[i%2][j]);
				image[i%2][j]=getpixel(x-9+j,y-7+i);
				putpixel(x-9+j,y-7+i,BCTcolor(fabs(55-j)));
				for(d=0;d<3000;d++);//延时处理 
			}
			if(i==106)
			{
				for(j=0;j<109;j++)
				{
					putpixel(x-9+j,y+98,image[1][j]);
					putpixel(x-9+j,y+99,image[0][j]);
				}
			}
		}
		
	}
}
/*检测正常*/
void CK_right(int x,int y)
{
	setcolor(_GREEN);
	fillcircle(x,y,25);
	fillcircle(x+25,y+25,3);
	setcolor(_WHITE);
	line(x-13,y-7,x-2,y+2);
	line(x-13,y-7,x-2,y+14);
	line(x-2,y+2,x+16,y-16);
	line(x-2,y+14,x+16,y-16);
	floodfill(x-2,y+5,_WHITE);
} 
