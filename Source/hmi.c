/*���н��漯���ļ�*/

#include <conio.h>
#include<stdio.h>
#include <stdlib.h>
#include "svga.h"
#include"hz.h"
#include "hmi.h"
#include <dos.h>
#include <alloc.h>
#include "design.h"

	/*����ɫ��ť����*/ 
void button1(int x1,int y1,int x2,int y2)
{
	int i,j;
	for(i=y2;i>=y1;i--)
	{
		for(j=x1;j<=x2;j++)
		{
			putpixel(j,i,BCTcolor(2*(y2-i)));
		}
	}
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);
}


    /*����Ϣ������*/
void info_bar(int x1,int y1,int x2,int y2)
{
	int i,j,center=(y1+y2)/2;
	for(i=center,j=center;i>y1&&j<y2;i--,j++)
	{
		setcolor(BCTcolor(40+i-center));
		line(x1,i,x2,i);
		line(x1,j,x2,j);
	}
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);
}
  
    /*����ɫ��ť����*/ 
void button2(int x1,int y1,int x2,int y2)
{
	int i,j;
	for(i=y2;i>=y1;i--)
	{
		for(j=x1;j<=x2;j++)
		{
			putpixel(j,i,GTcolor(y2-i));
		}
	}
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);
}
        
    /*���������*/
void input_frm(int x1,int y1,int x2,int y2)
{
	setcolor(_WHITE);
	bar(x1,y1,x2,y2);
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);
}

   /*������������*/
int Pro_bar(int al_len,int x1,int x2,int y,int percent)//percentȡ0��100 
{
	int newx=x1+al_len,nowx=x1+(x2-x1)*(unsigned long)percent/100,i;
	for(i=0;i<15;i++)
	{
		setcolor(i*4);
		line(newx,y+i,nowx,y+i);
	}
} 
    /*�����洰��*/
void warning_overflow(int x,int y)
{
	int i;
	setcolor(BCTcolor(30));
	bar(x+31,y+31,x+69,y+69);
	for(i=0;i<30;i++)
	{
		setcolor(BCTcolor(60-i));
		rectangle(x+i+1,y+i+1,x+99-i,y+99-i);
	}
	setcolor(_BLACK);
	rectangle(x,y,x+100,y+100);
	puthz(x+14,y+20,"��������!",1,16,_BLACK);
	delay(1000);
}

    /*����ɫ���ں���*/ 
void op_window(int x1,int y1,int x2,int y2)
{
	setcolor(BCTcolor(0));
	bar(x1,y1,x2,y1+21);
	setcolor(BCTcolor(40));
	bar(x1,y1+21,x2,y2);
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);	
	starry_sky(x1,y1+20,x2,y2);
}

    /*����ɫ���ں���*/ 
void op_window1(int x1,int y1,int x2,int y2)
{
	setcolor(GTcolor(55));
	bar(x1,y1,x2,y2);
	setcolor(BCTcolor(0));
	bar(x1,y1,x2,y1+20);
	shut(x2,y1);
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);
	texture(x1,y1+20,x2,y2);
}

    /*��ѡ�񴰿ں���*/ 
void choose_window(int x1,int y1)
{
	setcolor(BCTcolor(0));
	bar(x1,y1,x1+80,y1+20);
	setcolor(BCTcolor(30));
	bar(x1,y1+21,x1+80,y1+80);
	setcolor(GTcolor(25));
	circle(x1+20,y1+35,5);
	circle(x1+20,y1+65,5);
	setcolor(BCTcolor(60));
	line(x1,y1+50,x1+80,y1+50);
	shut(x1+80,y1);
	setcolor(_BLACK);
	rectangle(x1,y1,x1+80,y1+80);
}

    /*���رմ��ں���*/
void shut(int x,int y)
{
	setcolor(LIGHT_GRAY);
	bar(x-20,y+1,x-1,y+20);
	setcolor(_WHITE);
	line(x-5,y+5,x-15,y+15);
	line(x-15,y+5,x-5,y+15);
} 

    /*����ɫ�رմ��ں���*/
void Rshut(int x,int y)
{
	setcolor(_RED);
	bar(x-20,y+1,x-1,y+20);
	setcolor(_WHITE);
	line(x-5,y+5,x-15,y+15);
	line(x-15,y+5,x-5,y+15);
} 
    /*�����ش��ں���*/
void _return(int x,int y)
{
	setcolor(LIGHT_GRAY);
	bar(x+1,y+1,x+20,y+20);
	setcolor(_WHITE);
	line(x+15,y+10,x+5,y+10);
	line(x+10,y+5,x+5,y+10);
	line(x+10,y+15,x+5,y+10);
} 

   /*������ɫ���ش��ں���*/
void _Breturn(int x,int y)
{
	setcolor(LIGHT_BLUE);
	bar(x+1,y+1,x+20,y+20);
	setcolor(_WHITE);
	line(x+15,y+10,x+5,y+10);
	line(x+10,y+5,x+5,y+10);
	line(x+10,y+15,x+5,y+10);
} 
	/*������������*/ 
void title_bar()
{
	int i,j;
	setcolor(LIGHT_CYAN);
	bar(0,0,30,40);
	bar(610,440,640,480); 
	for(i=0;i<61;i++)
	{
		setcolor(BCTcolor(60-i));
		bar(30+10*i,0,30+10*(i+1),40);
	} 
	for(i=0;i<4;i++)
	{
		setcolor(GTcolor(40));
		bar(6+i*159,46,(i+1)*159-6,86);
		for(j=50;j<=90;j++)
		{
			setcolor(BCTcolor(j-50));
			line(2+i*159,j,(i+1)*159-10,j);
		}	
		setcolor(_BLACK);
		rectangle(2+i*159,50,(i+1)*159-10,90);	
	}
	
	for(i=0;i<61;i++)
	{
		setcolor(BCTcolor(i));
		bar(10*i,440,10*(i+1),480);
	}
	
	setcolor(_BLACK);
	line(0,40,640,40);
	line(0,440,640,440); 
	
	
	puthz(45,62,"��ƱԤ��",1,16,_WHITE);
	puthz(204,62,"�ҵĶ���",1,16,_WHITE);
	puthz(363,62,"��Ʊ���",1,16,_WHITE);
	puthz(522,62,"�ҵ��˻�",1,16,_WHITE);
	puthz(10,10,"��������",1,16,_PINK); 
	puthz(540,454,"��������",1,16,_PINK); 
	
	
}

	/*�����ݿ���*/ 
void cnt_frm(int *p)
{
	int i;

	setcolor(BCTcolor(50));
	rectangle(p[0]-68,50,p[0]+79,90);

	setcolor(_RED);
	drawpoly(9,p);
	for(i=0;i<18;i++)
	{
		p[i]+=4;
	}
	setcolor(DARK_GRAY);
	drawpoly(9,p);
}


/*��¼����*/ 
void log_in()
{
    cleardevice();
	setbkcolor(BCTcolor(30));
  
	input_frm(256,196,392,224);
	input_frm(256,236,392,264);
	starry_sky(0,0,640,180);
	falling_star(100,20,250,220);
	falling_star(500,50,600,150);
	button2(200,296,296,324);
	button2(380,296,476,324);
	button2(380,336,476,364);
	setcolor(_CYAN);
		
	puthz(182,102,"��·��Ʊϵͳ",3,16,GTcolor(40));	
	puthz(180,100,"��·��Ʊϵͳ",3,16,BCTcolor(60));
	setcolor(LIGHT_CYAN);
	puthz(224,200,"�˻�",1,16,_WHITE);
	puthz(224,240,"����",1,16,_WHITE);
    setcolor(_YELLOW);
	puthz(230,300,"ע��",1,16,_WHITE);
	puthz(410,300,"��½",1,16,_WHITE);
	puthz(600,438,"����",1,16,_WHITE);
	puthz(600,458,"�˳�",1,16,_WHITE);
	puthz(390,342,"����Ա��½",1,16,_WHITE);
}

void _help()
{
	setbkcolor(BCTcolor(30));
	cleardevice();
	_return(0,0);
	puthz(164,10,"��ӭʹ��12306��·��Ʊϵͳ",1,32,_WHITE);
	puthz(20,36,"һ�����ע��",1,16,_BLACK);
	puthz(52,56,"�û����ע�ᣬ�����˻������룬ȷ�����룬ע��ɹ��������˺�������ע�ᣬ��ʾע��ʧ�ܡ�",1,16,_BLACK);
	puthz(20,98,"�������Ԥ��",1,16,_BLACK);
	puthz(52,118,"ѡ�����ĳ���վ���յ�վ�������ѯ��ѡ�񳵴Σ�ȷ����Ʊ�ˣ�����ɹ���Ԥ���ɹ����������ҵ���Ϣ��鿴���ĳ�����Ϣ��",1,16,_BLACK);
	puthz(20,158,"������Ʊ���ǩ",1,16,_BLACK);
	puthz(52,178,"�������ҵĶ�����ȷ�����Ƿ���Ʊ���ǩ���˿���������������ڷ���������ԭ�˻���",1,16,_BLACK);
	puthz(20,218,"�ġ���ܰ��ʾ",1,16,_BLACK);
	puthz(52,242,"(1)ϵͳչʾ;�л���һ�εĲ����г���Ʊ��Ϣ����Ʊʱ������ֿ��Ǹ���Ӱ�컻�˵����أ�����Ը�е���������������ԭ�������󻻳˵ķ��գ���������ʵ�������ѡ���Ƿ�Ʊ����Ʊ�������ʱ�䣬��ʱ���ˡ�",1,16,_BLACK);
	puthz(52,302,"(2)�����ĳ�Ʊ�Ѿ����˵��췢��ʱ�䣬�������ҵ���Ϣ�￴����������Ϣ��",1,16,_BLACK);
	puthz(148,400,"12306ȫ��Ա��ף����;���",1,32,_RED);
	
	
}
  /*Ԥ������*/ 
void book()
{
	int polypoints[18]={70,100,70,120,20,120,20,390,610,390,610,120,90,120,90,100,70,100};
	cleardevice();
	setbkcolor(LIGHT_BLUE);
	title_bar();
    cnt_frm(polypoints);
	puthz(45,62,"��ƱԤ��",1,16,_BLUE);
	
	setcolor(_BLACK);	
	circle(320,180,20);
	setcolor(_WHITE);
	floodfill(320,180,_BLACK);
	setcolor(_BLACK);
	line(310,177,330,177);
	line(330,177,320,170);
	line(330,183,310,183);
	line(310,183,320,190);
	circle(300,250,15);
	circle(340,250,15);
	rectangle(260,290,270,300);
	rectangle(380,290,390,300);
	setcolor(_WHITE);
	floodfill(310,250,_BLACK);
	floodfill(350,250,_BLACK);
	floodfill(265,295,_BLACK);
	floodfill(385,295,_BLACK);
	setcolor(_BROWN);
	bar(202,167,282,197);
	bar(362,167,442,197);
	
	input_frm(200,165,280,195);
	input_frm(360,165,440,195);
	button1(260,315,376,345);
	
	puthz(298,322,"��ѯ",1,16,_WHITE);
	puthz(220,146,"��ʼ����",1,16,_BLACK);
	puthz(380,146,"�յ����",1,16,_BLACK);
	puthz(244,242,"����",1,16,_BLACK);
	outtextxy(320,244,".");
	outtextxy(212,288,"G/D");
	outtextxy(340,288,"St.");
	
}

/*�ҵĶ�������*/
void my_order()
{
	int polypoints[18]={229,100,229,120,20,120,20,390,610,390,610,120,249,120,249,100,229,100};
    cleardevice();
    setbkcolor(LIGHT_BLUE);
    title_bar();
    cnt_frm(polypoints);
	puthz(204,62,"�ҵĶ���",1,16,_BLUE);
	
	setcolor(LIGHT_MAGENTA);
	rectangle(30,130,130,160);
	bar(32,132,132,162);
	
	puthz(48,142,"�ҵĶ���",1,16,_BLACK);
	
}

  /*�����Ϣ����*/ 
void identity()
{
	int polypoints[18]={388,100,388,120,20,120,20,390,610,390,610,120,408,120,408,100,388,100};
    cleardevice();
	setbkcolor(LIGHT_BLUE);		
    title_bar();
	cnt_frm(polypoints);
	puthz(363,62,"��Ʊ���",1,16,_BLUE);
	setcolor(BCTcolor(40));
	bar(32,132,132,162);
	setcolor(BCTcolor(30));
	bar(34,134,134,164);
	setcolor(_BLACK);
//	line(320,160,320,340);
	button1(285,350,345,380);
	
	puthz(300,358,"����",1,16,_WHITE);
	puthz(46,142,"������ϵ��",1,16,_BLACK);
	
}

/*�ҵ��˻�����*/ 
void my_account()
{
	int i,j;
	int polypoints[18]={547,100,547,120,20,120,20,390,610,390,610,120,567,120,567,100,547,100};
	cleardevice();
	setbkcolor(LIGHT_BLUE);
	title_bar();
	cnt_frm(polypoints);
	
	puthz(522,62,"�ҵ��˻�",1,16,_BLUE);
	for(i=5;i<50;i++)
	{
		setcolor(BCTcolor(i));
		for(j=0;j<2;j++)
		{
			line(50,125+i*2+j,580,125+i*2+j);
		}
	}
	setcolor(BCTcolor(60));
	for(i=0;i<5;i++)
	{
		rectangle(49-i,134-i,581+i,226+i);
	}
	setcolor(_BLACK);
	rectangle(45,130,585,230);
	rectangle(50,135,580,225);
	setcolor(_YELLOW); 
	line(530,170,540,180);
	line(530,190,540,180);


	for(i=0;i<5;i++)
	{
		for(j=0;j<20;j++)
		{
			setcolor(BCTcolor(j));
			line(67+i*114+j,250,67+i*114+j,370);
			line(106+i*114-j,250,106+i*114-j,370);
		} 
	}
	
	puthz(70,148,"�˻�",2,16,_BLUE);
	puthz(460,172,"�����˻�",1,16,_WHITE);
	puthz(79,284,"ʱ",1,16,_WHITE);
	puthz(79,303,"��",1,16,_WHITE);
	puthz(79,322,"��",1,16,_WHITE);
	puthz(193,292,"��",1,16,_WHITE);
	puthz(193,311,"Ϣ",1,16,_WHITE);
	puthz(307,292,"��",1,16,_WHITE);
	puthz(307,311,"��",1,16,_WHITE);
	puthz(421,292,"��",1,16,_WHITE);
	puthz(421,311,"��",1,16,_WHITE);
	puthz(535,292,"��",1,16,_WHITE);
	puthz(535,311,"��",1,16,_WHITE);
	
}
 

/*ע�ᴰ��*/ 
void regist()
{
    op_window(200,100,500,380);
	input_frm(300,150,436,170);
	input_frm(300,210,436,230);
	input_frm(300,270,436,290);
	button1(320,330,400,350);
	shut(500,100);
	
	setcolor(_WHITE);
	puthz(236,152,"�����˻�",1,16,_WHITE);
	puthz(236,212,"��������",1,16,_WHITE);
	puthz(236,272,"ȷ������",1,16,_WHITE);
	puthz(348,332,"ȷ��",1,16,_WHITE);
}

/*�����ݴ���*/ 
void add_identity()
{
	int i;
	op_window(150,10,490,470);
	for(i=0;i<4;i++)
	{
		input_frm(250,55+i*50,420,85+i*50);
	}
	button1(320,415,400,445);
	shut(490,10);
	
	puthz(178,62,"���֤��:",1,16,_BLACK);
	puthz(210,112,"����:",1,16,_BLACK);
	puthz(210,162,"�Ա�:",1,16,_BLACK);
	puthz(210,212,"���:",1,16,_BLACK);
	puthz(344,422,"ȷ��",1,16,_WHITE);
}

void add_info()
{
	int i;
	
	for(i=4;i<7;i++)
	{
		input_frm(250,55+i*50,420,85+i*50);
	}
	puthz(210,262,"ѧУ:",1,16,_BLACK);
	puthz(210,312,"ѧ��:",1,16,_BLACK);
	puthz(178,362,"��ѧʱ��:",1,16,_BLACK);
}

/*���ô���*/ 
void  settings()
{
	int i;
	op_window(290,200,400,420);
	setcolor(_BROWN);
	for(i=2;i<6;i++)
	{
		line(291,180+i*40,399,180+i*40);
	}
	shut(400,200);
	
	setcolor(_WHITE);
	puthz(310,232,"�޸�����",1,16,_WHITE);
	puthz(310,272,"��������",1,16,_WHITE);
	puthz(310,312,"�ҵ�����",1,16,_WHITE);
	puthz(310,352,"�������",1,16,_WHITE);
	puthz(310,392,"�˳�",1,16,_WHITE);
}

/*ʱ�̱����*/ 
void time_table()
{
	setbkcolor(BCTcolor(30));
	cleardevice();
	input_frm(100,50,300,80);
	input_frm(340,50,370,80);
	input_frm(390,50,420,80);
	button2(450,50,530,80);
	_return(0,0);
	setcolor(_YELLOW);
	bar(0,460,640,480);
	
	setcolor(_WHITE);
	puthz(474,57,"��ѯ",1,16,_WHITE);
	puthz(100,28,"�����복��:",1,16,_BLACK);
	puthz(340,28,"����ʱ��:",1,16,_BLACK);
	puthz(372,54,"��",1,16,_BLACK);
	puthz(422,54,"��",1,16,_BLACK);
	puthz(50,462,"��ѯ��������ο�,�Ի�վʵ�����Ϊ׼!",1,16,GTcolor(20));
}

/*��ѯ����*/ 
void look()
{
	int i;
	cleardevice();
	setbkcolor(LIGHT_BLUE);
	setcolor(BCTcolor(0));
	bar(0,0,640,20);
	setcolor(BCTcolor(30));
	bar(0,21,200,480);
	setcolor(_YELLOW);
	bar(0,21,199,110);
	setcolor(_WHITE);
	bar(10,190,80,220);
	bar(120,190,190,220);
	fillcircle(100,205,15);
	setcolor(_BLACK);
	line(200,22,200,480);
	rectangle(10,190,80,220);
	rectangle(120,190,190,220);
	circle(100,205,15);
	line(90,200,110,200);
	line(90,210,110,210);
	line(110,200,100,195);
	line(90,210,100,215);
	
	setcolor(GTcolor(10));
	bar(201,440,640,480);
	setcolor(_WHITE);
	bar(201,21,640,50);
	line(20,260,180,260);
	line(20,310,180,310);
	line(20,346,180,346);
	line(20,160,180,160);
	setcolor(_WHITE);
	line(17,320,9,328);
	line(9,328,17,336);
	line(183,320,191,328);
	line(191,328,183,336);
	line(180,130,188,138);
	line(180,146,188,138);
	for(i=1;i<4;i++)
	{
		line(200+i*110,450,200+i*110,470);
	}
	setcolor(_BLACK);
	line(420,25,420,45);
	setcolor(_RED);
	fillcircle(250,35,3);
	_return(0,0);
	
	puthz(110,130,"��������",1,16,_WHITE);
	puthz(300,27,"ֱ��",1,16,GTcolor(20));
	puthz(500,27,"��ת",1,16,GTcolor(20));
	puthz(15,165,"��ʼ����",1,16,_BLACK);
	puthz(125,165,"�յ����",1,16,_BLACK);
	puthz(223,450,"�߼�ɸѡ",1,16,_WHITE);
	puthz(333,450,"����ʱ��",1,16,_WHITE);
	puthz(443,450,"���к�ʱ",1,16,_WHITE);
	puthz(553,450,"��ʾ",1,16,_WHITE);
	puthz(15,275,"ʱ��:",1,16,_BLACK);
	puthz(25,320,"ǰһ��",1,16,_WHITE);
	puthz(127,320,"��һ��",1,16,_WHITE);
	puthz(15,30,"�ͻ�����δʵ����Ʊ��",1,16,_BLACK);
	puthz(15,55,"�ܣ�������Ʊ�����¼",1,16,_BLACK);
	puthz(15,80,"12306�ٷ���վ��",1,16,_BLACK);
	puthz(15,400,"���",1,16,_BLACK);
	puthz(47,400,"����",1,16,_WHITE);
	puthz(79,400,"��ʼ��Ʊ",1,16,_BLACK);
}


/*��Ϣ����*/ 
void message()
{
	setbkcolor(BCTcolor(30));
	cleardevice();
	_return(0,0);
}

/*���ڽ���*/ 
void about()
{
	setbkcolor(BCTcolor(30));
	cleardevice();
	puthz(20,17,"12306��·��Ʊϵͳ�ǻ��пƼ���ѧ�Զ���ѧԺ��Ʒ��һվʽ���з���ƽ̨��Ϊ����ѧ���ṩ���ʵĻ𳵹�Ʊ����",1,16,_BLACK);
	setcolor(_WHITE);
	bar(20,56,340,80);
	puthz(24,60,"�ͷ����ߣ�8208208820 ��6:00-23:00��",1,16,_BLACK);
	setcolor(_WHITE);
	bar(20,84,340,108);
	puthz(24,88,"��ע����",1,16,_BLACK);
	_return(0,0);
	puthz(400,372,"��Ȩ���У�",1,16,_BLACK);
	puthz(464,392,"������",1,16,_BLACK);
	puthz(464,412,"ʩ�ѻ�",1,16,_BLACK);
	puthz(440,444,"�汾�ţ�2.0",1,16,_BLACK); 
}

/*��������*/
void feedback()
{
	cleardevice();
	setbkcolor(_WHITE);
	input_frm(100,30,540,340);
	input_frm(100,350,540,370);
	input_frm(100,380,540,400);
	button2(480,420,540,450);
	_return(0,0);
	
	puthz(100,8,"���������Ľ���",1,16,_RED);
	puthz(68,352,"����",1,16,_RED);
	puthz(36,382,"��ϵ�绰",1,16,_RED);
	puthz(494,427,"�ύ",1,16,_WHITE);
}

/*����Ա��¼*/ 
void manage()
{
	op_window(300,250,630,400);
	input_frm(400,320,536,340);
	button1(480,360,530,380);
	shut(630,250);
	
	setcolor(_WHITE);
	puthz(490,362,"ȷ��",1,16,_WHITE);
	//outtextxy(490,374,"OK");
	puthz(370,322,"��Կ",1,16,_WHITE);
	//outtextxy(370,334,"key:");
}

/*���ݹ������*/ 
void data()
{
	cleardevice();
	setbkcolor(BCTcolor(30));
	_return(0,0);
	button2(20,50,120,80);
	button2(20,100,120,130);
	button2(20,150,120,180);
	
	setcolor(_YELLOW);
	puthz(46,57,"�³���",1,16,_WHITE);
	//outtextxy(30,69,"NEW");
	puthz(54,107,"�༭",1,16,_WHITE);
	//outtextxy(30,119,"Edit");
	puthz(54,157,"ɾ��",1,16,_WHITE);
	//outtextxy(30,169,"Delete");
	puthz(280,12,"����ϵͳ",1,16,_ORANGE);
	//outtextxy(280,24,"Data System");
} 

/*���������ݽ���*/
void NewData()
{
	cleardevice();
	input_frm(100,10,540,40);
	button2(290,50,350,80);
	_return(0,0);
	puthz(303,57,"����",1,16,_WHITE);
}


void DeleteData()
{
	cleardevice();
	input_frm(100,10,540,40);
	button2(290,50,350,80);
	_return(0,0);
	
	puthz(303,58,"ɾ��",1,16,_WHITE);
} 


/*������Ϣ¼��ҳ*/
void NewKT(int page,int modify)//page��ʾ��Ϣҳ�� modifyΪ1��ʾ���޸�ģʽ�� 
{
	register int i,j;
	
	op_window(20,90,620,460);
	for(i=0;i<9;i++)
	{
		if(page>3&&i>2) return;
		input_frm(30,120+i*35,100,150+i*35);	
	}
	for(i=0;i<9;i++)
	{
		input_frm(105,120+i*35,175,150+i*35);
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<2;j++)
	    {
		    if(i==0&&j==0&&page==1) continue;
		    input_frm(180+j*60,125+i*35,230+j*60,145+i*35);
	    }
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<3;j++)
		input_frm(310+j*45,125+i*35,340+j*45,145+i*35);
	}
	if(page==1&&!modify)
	{
		for(i=0;i<3;i++)
		input_frm(550,125+i*35,595,145+i*35);
	}
	if(modify) button1(460,310,550,340);
	if(page<4) 
	button1(460,350,550,380);
	button1(460,390,550,420);
	 
	shut(620,90);
	
	setcolor(_WHITE);
	puthz(30,92,"վ��",1,16,_WHITE);
    puthz(86,92,"���ڳ���",1,16,_WHITE);
	puthz(152,92,"�ִ�ʱ��",1,16,_WHITE);
	puthz(216,92,"����ʱ��",1,16,_WHITE);
	puthz(286,92,"Ӳ����",1,16,_WHITE);
	puthz(335,92,"Ӳ�Է�",1,16,_WHITE);
	puthz(384,92,"���Է�",1,16,_WHITE); 

	if(page==1&&!modify)
	{
		puthz(460,125,"Ӳ����:",1,16,_WHITE);
		puthz(460,160,"Ӳ����:",1,16,_WHITE);
		puthz(460,195,"������:",1,16,_WHITE); 
	}
	if(modify) 
	puthz(470,319,"����",1,16,_WHITE);
	if(page<4)
	{
		puthz(470,359,"��һҳ",1,16,_WHITE);
	}
	puthz(470,397,"����",1,16,_WHITE);
}

void NewG(int page,int modify)
{
	register int i,j;
	
	op_window(20,90,620,460);
	for(i=0;i<9;i++)
	{
		if(page>3&&i>2) return;
		input_frm(30,120+i*35,100,150+i*35);	
	}
	for(i=0;i<9;i++)
	{
		input_frm(105,120+i*35,175,150+i*35);
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<2;j++)
	    {
		    if(i==0&&j==0&&page==1) continue;
		    input_frm(180+j*60,125+i*35,230+j*60,145+i*35);
	    }
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<3;j++)
		input_frm(310+j*45,125+i*35,340+j*45,145+i*35);
	}
	if(page==1&&!modify)
	{
		for(i=0;i<3;i++)
		input_frm(550,125+i*35,595,145+i*35);
	}
	if(modify)
	button1(460,310,550,340); 
	if(page<4) 
	button1(460,350,550,380);
	button1(460,390,550,420);
	 
	shut(620,90);
	
	setcolor(_WHITE);
	puthz(30,92,"վ��",1,16,_WHITE);
    puthz(86,92,"���ڳ���",1,16,_WHITE);
	puthz(152,92,"�ִ�ʱ��",1,16,_WHITE);
	puthz(216,92,"����ʱ��",1,16,_WHITE);
	puthz(286,92,"һ����",1,16,_WHITE);
	puthz(335,92,"������",1,16,_WHITE);
	puthz(384,92,"������",1,16,_WHITE); 
	if(page==1&&!modify)
	{
		puthz(460,125,"һ������:",1,16,_WHITE);
		puthz(460,160,"��������:",1,16,_WHITE);
		puthz(460,195,"��������:",1,16,_WHITE); 
	}
	if(modify) 
	puthz(470,319,"����",1,16,_WHITE);
	if(page<4)
	{
		puthz(470,359,"��һҳ",1,16,_WHITE);
	}
	puthz(470,397,"����",1,16,_WHITE);
}

void NewD(int page,int modify)
{
	register int i,j;
	
	op_window(20,90,620,460);
	for(i=0;i<9;i++)
	{
		if(page>3&&i>2) return;
		input_frm(30,120+i*35,100,150+i*35);	
	}
	for(i=0;i<9;i++)
	{
		input_frm(105,120+i*35,175,150+i*35);
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<2;j++)
	    {
		    if(i==0&&j==0&&page==1) continue;
		    input_frm(180+j*60,125+i*35,230+j*60,145+i*35);
	    }
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<2;j++)
		input_frm(310+j*45,125+i*35,340+j*45,145+i*35);
	}
	if(page==1&&!modify)
	{
		for(i=0;i<2;i++)
		input_frm(550,125+i*35,595,145+i*35);
	}
	if(modify)
	button1(460,310,550,340);
	if(page<4) 
	button1(460,350,550,380);
	button1(460,390,550,420);
	 
	shut(620,90);
	
	setcolor(_WHITE);
	puthz(30,92,"վ��",1,16,_WHITE);
    puthz(86,92,"���ڳ���",1,16,_WHITE);
	puthz(152,92,"�ִ�ʱ��",1,16,_WHITE);
	puthz(216,92,"����ʱ��",1,16,_WHITE);
	puthz(286,92,"һ����",1,16,_WHITE);
	puthz(335,92,"������",1,16,_WHITE);
	if(page==1&&!modify)
	{
		puthz(460,125,"һ������:",1,16,_WHITE);
		puthz(460,160,"��������:",1,16,_WHITE);
	}
	if(modify) 
	puthz(470,319,"����",1,16,_WHITE);
	if(page<4)
	{
		puthz(470,359,"��һҳ",1,16,_WHITE);
	}
	puthz(470,397,"����",1,16,_WHITE);
}

void NewZ()
{
	int i,j;
	op_window(20,90,620,460);
	for(i=0;i<2;i++)
	{
		input_frm(30,120+i*35,100,150+i*35);	
	}
	for(i=0;i<2;i++)
	{
		input_frm(105,120+i*35,175,150+i*35);	
	}
	for(i=0;i<2;i++)
	{
		input_frm(180,125+i*35,230,145+i*35);
	}
	for(j=0;j<3;j++)
	input_frm(310+j*45,125,340+j*45,145);
	
	for(i=0;i<3;i++)
	input_frm(550,125+i*35,595,145+i*35);
	 
	button1(460,390,550,420);
	 
	shut(620,90);
	
	setcolor(_WHITE);
	puthz(30,92,"վ��",1,16,_WHITE);
	puthz(86,92,"���ڳ���",1,16,_WHITE);
	puthz(152,92,"ʱ��",1,16,_WHITE);
	puthz(286,92,"Ӳ����",1,16,_WHITE);
	puthz(335,92,"Ӳ�Է�",1,16,_WHITE);
	puthz(384,92,"���Է�",1,16,_WHITE); 
	puthz(460,125,"Ӳ����:",1,16,_WHITE);
	puthz(460,160,"Ӳ����:",1,16,_WHITE);
	puthz(460,195,"������:",1,16,_WHITE); 
	puthz(470,397,"����",1,16,_WHITE);
}

void ModifyData()
{
	cleardevice();
	input_frm(100,10,540,40);
	button2(290,50,350,80);
	_return(0,0);
	
	puthz(303,55,"�޸�",1,16,_WHITE);
}

void more(int page,char train)
{
	register int i,j;
	int full;
	
	if(train=='D') full=2;
	else full=3;
	
	op_window(20,90,620,460);
	for(i=0;i<9;i++)
	{
		if(page>3&&i>2) break;
		input_frm(30,120+i*35,100,150+i*35);	
	}
	for(i=0;i<9;i++)
	{
		if(page>3&&i>2) break;
		for(j=0;j<full;j++)
		input_frm(110+j*60,125+i*35,155+j*60,145+i*35);
	}
	if(page<4) 
	button1(460,310,550,340);
	button1(460,350,550,380);
	button1(460,390,550,420);
	 
	shut(620,90);
	
	setcolor(_WHITE);
	puthz(470,319,"����",1,16,_WHITE);
	puthz(30,92,"վ��",1,16,_WHITE);
	if(train=='K'||train=='T')
	{
		puthz(110,92,"Ӳ����",1,16,_WHITE);
		puthz(170,92,"Ӳ����",1,16,_WHITE);
		puthz(230,92,"������",1,16,_WHITE);
	}
	else if(train=='G')
	{
		puthz(110,92,"һ������",1,16,_WHITE);
		puthz(170,92,"��������",1,16,_WHITE);
		puthz(230,92,"��������",1,16,_WHITE);
	}
	else if(train=='D')
	{
		puthz(110,92,"һ������",1,16,_WHITE);
		puthz(170,92,"��������",1,16,_WHITE);
		puthz(230,92,"������",1,16,_WHITE);
	}
	if(page<4)
    puthz(470,359,"��һҳ",1,16,_WHITE);
	puthz(470,397,"����",1,16,_WHITE);
}

void Adv_choose()
{
	int i;
	setcolor(GTcolor(55));
	bar(200,220,300,430);
	setcolor(BCTcolor(0));
	bar(200,200,300,220);
	shut(300,200);
	button1(230,390,270,420);
	for(i=0;i<5;i++)
	{
		setcolor(_WHITE);
		bar(220,250+i*30,230,260+i*30);
		setcolor(BCTcolor(0));
		rectangle(220,250+i*30,230,260+i*30); 
	}
	setcolor(_BLACK);
	rectangle(200,200,300,430);
	puthz(240,247,"��(K)",1,16,_BLACK);
	puthz(240,277,"��(T)",1,16,_BLACK);
	puthz(240,307,"����(D)",1,16,_BLACK);
	puthz(240,337,"����(G)",1,16,_BLACK);
	puthz(240,367,"ֱ��(Z)",1,16,_BLACK);
	puthz(234,397,"ȷ��",1,16,_WHITE);
}

void start_book(int flag)
{
	if(flag==1)
	{
		op_window1(150,25,640,475);
	
		setcolor(BCTcolor(30));
		bar(151,240,639,270);
		bar(556,445,639,474);
		puthz(220,247,"��ѡ��Ʊ��:",1,16,_BLACK);
		setcolor(_WHITE);
		bar(151,445,560,474);
		puthz(210,452,"Ӧ�������:",1,16,_BROWN);
		puthz(332,452,"0Ԫ",1,16,_RED);
		puthz(568,452,"����Ԥ��",1,16,_WHITE);
		
	}
	else 
	{
		op_window1(0,25,640,475);
	
		setcolor(BCTcolor(30));
		bar(201,240,639,270);
		bar(556,445,639,474);
		puthz(220,247,"��ѡ��Ʊ��:",1,16,_BLACK);
		setcolor(_WHITE);
		bar(1,445,560,474);
		puthz(10,452,"Ӧ�������:",1,16,_BROWN);
		puthz(132,452,"0Ԫ",1,16,_RED);
		puthz(568,452,"����Ԥ��",1,16,_WHITE);
	}	
}

int DEstbook(USER *user)
{
	int i,j;
	start_book(1);
	
	for(i=0;i<4;i++)
	{
		setcolor(_WHITE);
		bar(210+200*(i%2),160+35*(i/2),360+200*(i%2),190+35*(i/2));
		setcolor(BCTcolor(0));
		bar(360+200*(i%2),160+35*(i/2),400+200*(i%2),190+35*(i/2));	
		puthz(364+200*(i%2),167+35*(i/2),"Ԥ��",1,16,_WHITE);
	}

	for(i=0;i<5;i++)
	{
		for(j=0;j<2;j++)
		{
			if(user->AllIdentity[i*2+j][0]!='\0')
			{
				info_bar(260+j*220,275+i*35,360+j*220,305+i*35);
				puthz(286+j*220,282+i*35,user->AllIdentity[i*2+j],1,16,_BLACK);
			}
			else 
			{
				return(i*2+j);
			}
		}
	}
}

int REstbook(USER *user)
{
	int i,j;
	
	start_book(2);
	
	for(i=0;i<4;i++)
	{
		setcolor(_WHITE);
		bar(10,80+i*35,150,110+i*35);
		setcolor(BCTcolor(0));
		bar(151,80+i*35,190,110+i*35);
		puthz(154,87+i*35,"Ԥ��",1,16,_WHITE);
	}
	for(i=0;i<4;i++)
	{
		setcolor(_WHITE);
		bar(10,240+i*35,190,270+i*35);
		setcolor(BCTcolor(0));
		bar(151,240+i*35,190,270+i*35);
		puthz(154,247+i*35,"Ԥ��",1,16,_WHITE);
	}
	puthz(10,57,"��һ��:",1,16,_BLACK);
	puthz(10,217,"�ڶ���:",1,16,_BLACK); 
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<2;j++)
		{
			if(user->AllIdentity[i*2+j][0]!='\0')
			{
				info_bar(260+j*220,275+i*35,360+j*220,305+i*35);
				puthz(286+j*220,282+i*35,user->AllIdentity[i*2+j],1,16,_BLACK);
			}
			else 
			{
				return(i*2+j);
			}
		}
	}
}

void pay()
{
	op_window1(300,200,420,380);
	setcolor(_WHITE);
	shut(420,200);
	bar(301,221,419,250);
	bar(301,261,419,290);
	bar(301,301,419,330);
	bar(301,341,419,370);
	alipay(335,275);
	WeChat_pay(335,315);
	BankCard(335,355);
	puthz(305,227,"��ѡ��֧����ʽ",1,16,_BLACK);
	puthz(360,267,"֧����",1,16,_BLACK);
	puthz(368,307,"΢��",1,16,_BLACK);
	puthz(360,347,"���п�",1,16,_BLACK);
}

void pay_method()
{
	op_window(500,250,610,340);
	shut(610,250);
	setcolor(BCTcolor(25));
	bar(501,271,609,300);
	bar(501,311,609,339);
	puthz(520,277,"ɨ���ά��",1,16,_BLACK);
	puthz(520,317,"��������",1,16,_BLACK);	
}

void paybypassword()
{
	op_window(500,250,610,340);
	shut(610,250);
	input_frm(520,270,575,300);
	button1(540,305,580,335);
	puthz(505,252,"֧������",1,16,_WHITE);
	puthz(544,312,"֧��",1,16,_WHITE);
}

void PayByQR()
{
	ScanQRC(315,240);
	pay_OK();
}

void pay_OK()
{
	setcolor(_WHITE);
	bar(305,230,415,340);
	setcolor(_BLACK);
	rectangle(305,230,415,340);
	CK_right(360,285);
	puthz(328,320,"֧���ɹ�",1,16,GTcolor(30));
	delay(1000);
} 

void ticket(int x,int y)
{
	int i;
	for(i=0;i<5;i++)
	{
		setcolor(BCTcolor(i*10));
		rectangle(x+i,y+i,x+360-i,y+100-i);
	}
	setcolor(BCTcolor(45));
	bar(x+5,y+5,x+355,y+95); 
	setcolor(_BLACK);
	line(x+125,y+40,x+225,y+40);
	line(x+125,y+60,x+225,y+60);
	line(x+225,y+40,x+215,y+30);
	line(x+125,y+60,x+135,y+70);
	button2(x+390,y+13,x+442,y+43);
	button2(x+390,y+57,x+442,y+87);
	puthz(x+400,y+20,"��ǩ",1,16,_WHITE);
	puthz(x+400,y+64,"��Ʊ",1,16,_WHITE);
}

void Password()
{
	int i;
	op_window(0,0,280,330);
	shut(280,0);
	for(i=0;i<3;i++)
	{
		input_frm(130,60+i*60,265,90+i*60);
	}
	button1(180,290,240,320);
	
	puthz(10,67,"�����ʼ����:",1,16,_BLACK);
	puthz(26,127,"����������:",1,16,_BLACK);
	puthz(26,187,"ȷ��������:",1,16,_BLACK);
	puthz(192,297,"ȷ��",1,16,_WHITE);
}

void success_hint()
{
	int i;
	char temp[2];
	setcolor(_WHITE);
	bar(1,1,279,329);
	CK_right(140,100);
	puthz(50,150,"�޸�����ɹ�,3�����",1,16,GTcolor(30));
	puthz(110,175,"������...",1,16,GTcolor(30));
	delay(1000);
	for(i=2;i>0;i--)
	{
		itoa(i,temp,10);
		setcolor(_WHITE);
		bar(154,150,162,166);
		setcolor(GTcolor(30));
		outtextxy(154,150,temp);
		delay(1000);
	}
}

void theme()
{
	int i;
	op_window(420,250,524,420);
	shut(524,250);
	setcolor(BCTcolor(55));
	for(i=0;i<4;i++)
	{
		line(421,300+i*30,523,300+i*30);
	}
	puthz(440,277,"��ɫ����",1,16,_WHITE);
	puthz(440,307,"�ۺ����",1,16,_WHITE);
	puthz(440,337,"����Ũ",1,16,_WHITE);
	puthz(440,367,"�������",1,16,_WHITE);
	puthz(440,397,"ˮī��",1,16,_WHITE);
}

void my_profile()
{
	int i;
	op_window(0,0,300,460);
	shut(300,0);
	setcolor(_BLUE);
	line(10,35,290,35);
	for(i=0;i<4;i++)
	{
		input_frm(90,50+i*60,255,80+i*60);
		setcolor(_BLUE);
		line(10,95+i*60,290,95+i*60);
	}
	input_frm(90,290,255,350);
	setcolor(_BLUE);
	line(10,365,290,365);
	button1(200,380,250,410);
	puthz(42,57,"����:",1,16,_BLACK);
	puthz(42,117,"�Ա�:",1,16,_BLACK);
	puthz(10,177,"���֤��",1,16,_BLACK);
	puthz(10,237,"�ֻ�����:",1,16,_BLACK);
	puthz(10,297,"����ǩ��:",1,16,_BLACK);
	puthz(214,387,"����",1,16,_WHITE);
}

void success_submit()
{
	cleardevice();
	setbkcolor(_WHITE);
	CK_right(320,100);
	puthz(50,7,"��л���ı��������",1,16,GTcolor(20));
	delay(1500);
}

void clear_data()
{
	setcolor(_WHITE);
	bar(290,200,400,420);
	setcolor(GTcolor(25));
	rectangle(290,200,400,420);
	CK_right(345,270);
	puthz(313,340,"����ɹ�",1,16,GTcolor(30));
	delay(1000);
}
