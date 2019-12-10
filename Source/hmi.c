/*所有界面集合文件*/

#include <conio.h>
#include<stdio.h>
#include <stdlib.h>
#include "svga.h"
#include"hz.h"
#include "hmi.h"
#include <dos.h>
#include <alloc.h>
#include "design.h"

	/*画蓝色按钮函数*/ 
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


    /*画消息条函数*/
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
  
    /*画黑色按钮函数*/ 
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
        
    /*画输入框函数*/
void input_frm(int x1,int y1,int x2,int y2)
{
	setcolor(_WHITE);
	bar(x1,y1,x2,y2);
	setcolor(_BLACK);
	rectangle(x1,y1,x2,y2);
}

   /*画进度条函数*/
int Pro_bar(int al_len,int x1,int x2,int y,int percent)//percent取0到100 
{
	int newx=x1+al_len,nowx=x1+(x2-x1)*(unsigned long)percent/100,i;
	for(i=0;i<15;i++)
	{
		setcolor(i*4);
		line(newx,y+i,nowx,y+i);
	}
} 
    /*画警告窗口*/
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
	puthz(x+14,y+20,"容量已满!",1,16,_BLACK);
	delay(1000);
}

    /*画青色窗口函数*/ 
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

    /*画暗色窗口函数*/ 
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

    /*画选择窗口函数*/ 
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

    /*画关闭窗口函数*/
void shut(int x,int y)
{
	setcolor(LIGHT_GRAY);
	bar(x-20,y+1,x-1,y+20);
	setcolor(_WHITE);
	line(x-5,y+5,x-15,y+15);
	line(x-15,y+5,x-5,y+15);
} 

    /*画红色关闭窗口函数*/
void Rshut(int x,int y)
{
	setcolor(_RED);
	bar(x-20,y+1,x-1,y+20);
	setcolor(_WHITE);
	line(x-5,y+5,x-15,y+15);
	line(x-15,y+5,x-5,y+15);
} 
    /*画返回窗口函数*/
void _return(int x,int y)
{
	setcolor(LIGHT_GRAY);
	bar(x+1,y+1,x+20,y+20);
	setcolor(_WHITE);
	line(x+15,y+10,x+5,y+10);
	line(x+10,y+5,x+5,y+10);
	line(x+10,y+15,x+5,y+10);
} 

   /*画淡蓝色返回窗口函数*/
void _Breturn(int x,int y)
{
	setcolor(LIGHT_BLUE);
	bar(x+1,y+1,x+20,y+20);
	setcolor(_WHITE);
	line(x+15,y+10,x+5,y+10);
	line(x+10,y+5,x+5,y+10);
	line(x+10,y+15,x+5,y+10);
} 
	/*画标题栏函数*/ 
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
	
	
	puthz(45,62,"车票预定",1,16,_WHITE);
	puthz(204,62,"我的订单",1,16,_WHITE);
	puthz(363,62,"购票身份",1,16,_WHITE);
	puthz(522,62,"我的账户",1,16,_WHITE);
	puthz(10,10,"风里雨里",1,16,_PINK); 
	puthz(540,454,"中铁等你",1,16,_PINK); 
	
	
}

	/*画内容框函数*/ 
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


/*登录界面*/ 
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
		
	puthz(182,102,"铁路订票系统",3,16,GTcolor(40));	
	puthz(180,100,"铁路订票系统",3,16,BCTcolor(60));
	setcolor(LIGHT_CYAN);
	puthz(224,200,"账户",1,16,_WHITE);
	puthz(224,240,"密码",1,16,_WHITE);
    setcolor(_YELLOW);
	puthz(230,300,"注册",1,16,_WHITE);
	puthz(410,300,"登陆",1,16,_WHITE);
	puthz(600,438,"帮助",1,16,_WHITE);
	puthz(600,458,"退出",1,16,_WHITE);
	puthz(390,342,"管理员登陆",1,16,_WHITE);
}

void _help()
{
	setbkcolor(BCTcolor(30));
	cleardevice();
	_return(0,0);
	puthz(164,10,"欢迎使用12306铁路购票系统",1,32,_WHITE);
	puthz(20,36,"一、如何注册",1,16,_BLACK);
	puthz(52,56,"用户点击注册，输入账户和密码，确认密码，注册成功，若该账号以有人注册，显示注册失败。",1,16,_BLACK);
	puthz(20,98,"二、如何预定",1,16,_BLACK);
	puthz(52,118,"选择您的出发站和终点站，点击查询，选择车次，确定购票人，付款成功即预定成功，您可在我的消息里查看您的车次信息。",1,16,_BLACK);
	puthz(20,158,"三、退票与改签",1,16,_BLACK);
	puthz(52,178,"您可在我的订单中确定您是否退票或改签，退款会在两个工作日内返还到您的原账户。",1,16,_BLACK);
	puthz(20,218,"四、温馨提示",1,16,_BLACK);
	puthz(52,242,"(1)系统展示途中换乘一次的部分列车余票信息，购票时请您充分考虑各种影响换乘的因素，并自愿承担因自身或第三方等原因导致延误换乘的风险，请您根据实际情况，选择是否购票，购票后合理安排时间，及时换乘。",1,16,_BLACK);
	puthz(52,302,"(2)当您的车票已经过了当天发车时间，您将在我的消息里看不到车次信息。",1,16,_BLACK);
	puthz(148,400,"12306全体员工祝您旅途愉快",1,32,_RED);
	
	
}
  /*预定界面*/ 
void book()
{
	int polypoints[18]={70,100,70,120,20,120,20,390,610,390,610,120,90,120,90,100,70,100};
	cleardevice();
	setbkcolor(LIGHT_BLUE);
	title_bar();
    cnt_frm(polypoints);
	puthz(45,62,"车票预定",1,16,_BLUE);
	
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
	
	puthz(298,322,"查询",1,16,_WHITE);
	puthz(220,146,"起始城市",1,16,_BLACK);
	puthz(380,146,"终点城市",1,16,_BLACK);
	puthz(244,242,"日期",1,16,_BLACK);
	outtextxy(320,244,".");
	outtextxy(212,288,"G/D");
	outtextxy(340,288,"St.");
	
}

/*我的订单界面*/
void my_order()
{
	int polypoints[18]={229,100,229,120,20,120,20,390,610,390,610,120,249,120,249,100,229,100};
    cleardevice();
    setbkcolor(LIGHT_BLUE);
    title_bar();
    cnt_frm(polypoints);
	puthz(204,62,"我的订单",1,16,_BLUE);
	
	setcolor(LIGHT_MAGENTA);
	rectangle(30,130,130,160);
	bar(32,132,132,162);
	
	puthz(48,142,"我的订单",1,16,_BLACK);
	
}

  /*身份消息界面*/ 
void identity()
{
	int polypoints[18]={388,100,388,120,20,120,20,390,610,390,610,120,408,120,408,100,388,100};
    cleardevice();
	setbkcolor(LIGHT_BLUE);		
    title_bar();
	cnt_frm(polypoints);
	puthz(363,62,"购票身份",1,16,_BLUE);
	setcolor(BCTcolor(40));
	bar(32,132,132,162);
	setcolor(BCTcolor(30));
	bar(34,134,134,164);
	setcolor(_BLACK);
//	line(320,160,320,340);
	button1(285,350,345,380);
	
	puthz(300,358,"增加",1,16,_WHITE);
	puthz(46,142,"常用联系人",1,16,_BLACK);
	
}

/*我的账户界面*/ 
void my_account()
{
	int i,j;
	int polypoints[18]={547,100,547,120,20,120,20,390,610,390,610,120,567,120,567,100,547,100};
	cleardevice();
	setbkcolor(LIGHT_BLUE);
	title_bar();
	cnt_frm(polypoints);
	
	puthz(522,62,"我的账户",1,16,_BLUE);
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
	
	puthz(70,148,"账户",2,16,_BLUE);
	puthz(460,172,"管理账户",1,16,_WHITE);
	puthz(79,284,"时",1,16,_WHITE);
	puthz(79,303,"刻",1,16,_WHITE);
	puthz(79,322,"表",1,16,_WHITE);
	puthz(193,292,"消",1,16,_WHITE);
	puthz(193,311,"息",1,16,_WHITE);
	puthz(307,292,"设",1,16,_WHITE);
	puthz(307,311,"置",1,16,_WHITE);
	puthz(421,292,"反",1,16,_WHITE);
	puthz(421,311,"馈",1,16,_WHITE);
	puthz(535,292,"关",1,16,_WHITE);
	puthz(535,311,"于",1,16,_WHITE);
	
}
 

/*注册窗口*/ 
void regist()
{
    op_window(200,100,500,380);
	input_frm(300,150,436,170);
	input_frm(300,210,436,230);
	input_frm(300,270,436,290);
	button1(320,330,400,350);
	shut(500,100);
	
	setcolor(_WHITE);
	puthz(236,152,"输入账户",1,16,_WHITE);
	puthz(236,212,"输入密码",1,16,_WHITE);
	puthz(236,272,"确认密码",1,16,_WHITE);
	puthz(348,332,"确认",1,16,_WHITE);
}

/*添加身份窗口*/ 
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
	
	puthz(178,62,"身份证号:",1,16,_BLACK);
	puthz(210,112,"姓名:",1,16,_BLACK);
	puthz(210,162,"性别:",1,16,_BLACK);
	puthz(210,212,"身份:",1,16,_BLACK);
	puthz(344,422,"确认",1,16,_WHITE);
}

void add_info()
{
	int i;
	
	for(i=4;i<7;i++)
	{
		input_frm(250,55+i*50,420,85+i*50);
	}
	puthz(210,262,"学校:",1,16,_BLACK);
	puthz(210,312,"学号:",1,16,_BLACK);
	puthz(178,362,"入学时间:",1,16,_BLACK);
}

/*设置窗口*/ 
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
	puthz(310,232,"修改密码",1,16,_WHITE);
	puthz(310,272,"更换主题",1,16,_WHITE);
	puthz(310,312,"我的资料",1,16,_WHITE);
	puthz(310,352,"清除缓存",1,16,_WHITE);
	puthz(310,392,"退出",1,16,_WHITE);
}

/*时刻表界面*/ 
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
	puthz(474,57,"查询",1,16,_WHITE);
	puthz(100,28,"请输入车次:",1,16,_BLACK);
	puthz(340,28,"出发时间:",1,16,_BLACK);
	puthz(372,54,"月",1,16,_BLACK);
	puthz(422,54,"日",1,16,_BLACK);
	puthz(50,462,"查询结果仅供参考,以火车站实际情况为准!",1,16,GTcolor(20));
}

/*查询界面*/ 
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
	
	puthz(110,130,"重新搜索",1,16,_WHITE);
	puthz(300,27,"直达",1,16,GTcolor(20));
	puthz(500,27,"中转",1,16,GTcolor(20));
	puthz(15,165,"起始城市",1,16,_BLACK);
	puthz(125,165,"终点城市",1,16,_BLACK);
	puthz(223,450,"高级筛选",1,16,_WHITE);
	puthz(333,450,"出发时间",1,16,_WHITE);
	puthz(443,450,"旅行耗时",1,16,_WHITE);
	puthz(553,450,"显示",1,16,_WHITE);
	puthz(15,275,"时间:",1,16,_BLACK);
	puthz(25,320,"前一天",1,16,_WHITE);
	puthz(127,320,"后一天",1,16,_WHITE);
	puthz(15,30,"客户端暂未实现抢票功",1,16,_BLACK);
	puthz(15,55,"能，如需抢票，请登录",1,16,_BLACK);
	puthz(15,80,"12306官方网站！",1,16,_BLACK);
	puthz(15,400,"点击",1,16,_BLACK);
	puthz(47,400,"这里",1,16,_WHITE);
	puthz(79,400,"开始抢票",1,16,_BLACK);
}


/*消息界面*/ 
void message()
{
	setbkcolor(BCTcolor(30));
	cleardevice();
	_return(0,0);
}

/*关于界面*/ 
void about()
{
	setbkcolor(BCTcolor(30));
	cleardevice();
	puthz(20,17,"12306铁路订票系统是华中科技大学自动化学院出品的一站式出行服务平台，为华科学子提供优质的火车购票服务。",1,16,_BLACK);
	setcolor(_WHITE);
	bar(20,56,340,80);
	puthz(24,60,"客服热线：8208208820 （6:00-23:00）",1,16,_BLACK);
	setcolor(_WHITE);
	bar(20,84,340,108);
	puthz(24,88,"关注我们",1,16,_BLACK);
	_return(0,0);
	puthz(400,372,"版权所有：",1,16,_BLACK);
	puthz(464,392,"苏新明",1,16,_BLACK);
	puthz(464,412,"施佳华",1,16,_BLACK);
	puthz(440,444,"版本号：2.0",1,16,_BLACK); 
}

/*反馈界面*/
void feedback()
{
	cleardevice();
	setbkcolor(_WHITE);
	input_frm(100,30,540,340);
	input_frm(100,350,540,370);
	input_frm(100,380,540,400);
	button2(480,420,540,450);
	_return(0,0);
	
	puthz(100,8,"请输入您的建议",1,16,_RED);
	puthz(68,352,"邮箱",1,16,_RED);
	puthz(36,382,"联系电话",1,16,_RED);
	puthz(494,427,"提交",1,16,_WHITE);
}

/*管理员登录*/ 
void manage()
{
	op_window(300,250,630,400);
	input_frm(400,320,536,340);
	button1(480,360,530,380);
	shut(630,250);
	
	setcolor(_WHITE);
	puthz(490,362,"确认",1,16,_WHITE);
	//outtextxy(490,374,"OK");
	puthz(370,322,"密钥",1,16,_WHITE);
	//outtextxy(370,334,"key:");
}

/*数据管理界面*/ 
void data()
{
	cleardevice();
	setbkcolor(BCTcolor(30));
	_return(0,0);
	button2(20,50,120,80);
	button2(20,100,120,130);
	button2(20,150,120,180);
	
	setcolor(_YELLOW);
	puthz(46,57,"新车次",1,16,_WHITE);
	//outtextxy(30,69,"NEW");
	puthz(54,107,"编辑",1,16,_WHITE);
	//outtextxy(30,119,"Edit");
	puthz(54,157,"删除",1,16,_WHITE);
	//outtextxy(30,169,"Delete");
	puthz(280,12,"数据系统",1,16,_ORANGE);
	//outtextxy(280,24,"Data System");
} 

/*创建新数据界面*/
void NewData()
{
	cleardevice();
	input_frm(100,10,540,40);
	button2(290,50,350,80);
	_return(0,0);
	puthz(303,57,"创建",1,16,_WHITE);
}


void DeleteData()
{
	cleardevice();
	input_frm(100,10,540,40);
	button2(290,50,350,80);
	_return(0,0);
	
	puthz(303,58,"删除",1,16,_WHITE);
} 


/*创建消息录入页*/
void NewKT(int page,int modify)//page表示消息页数 modify为1表示在修改模式下 
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
	puthz(30,92,"站名",1,16,_WHITE);
    puthz(86,92,"所在城市",1,16,_WHITE);
	puthz(152,92,"抵达时间",1,16,_WHITE);
	puthz(216,92,"发车时间",1,16,_WHITE);
	puthz(286,92,"硬座费",1,16,_WHITE);
	puthz(335,92,"硬卧费",1,16,_WHITE);
	puthz(384,92,"软卧费",1,16,_WHITE); 

	if(page==1&&!modify)
	{
		puthz(460,125,"硬座数:",1,16,_WHITE);
		puthz(460,160,"硬卧数:",1,16,_WHITE);
		puthz(460,195,"软卧数:",1,16,_WHITE); 
	}
	if(modify) 
	puthz(470,319,"更多",1,16,_WHITE);
	if(page<4)
	{
		puthz(470,359,"下一页",1,16,_WHITE);
	}
	puthz(470,397,"保存",1,16,_WHITE);
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
	puthz(30,92,"站名",1,16,_WHITE);
    puthz(86,92,"所在城市",1,16,_WHITE);
	puthz(152,92,"抵达时间",1,16,_WHITE);
	puthz(216,92,"发车时间",1,16,_WHITE);
	puthz(286,92,"一等座",1,16,_WHITE);
	puthz(335,92,"二等座",1,16,_WHITE);
	puthz(384,92,"商务座",1,16,_WHITE); 
	if(page==1&&!modify)
	{
		puthz(460,125,"一等座数:",1,16,_WHITE);
		puthz(460,160,"二等座数:",1,16,_WHITE);
		puthz(460,195,"商务座数:",1,16,_WHITE); 
	}
	if(modify) 
	puthz(470,319,"更多",1,16,_WHITE);
	if(page<4)
	{
		puthz(470,359,"下一页",1,16,_WHITE);
	}
	puthz(470,397,"保存",1,16,_WHITE);
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
	puthz(30,92,"站名",1,16,_WHITE);
    puthz(86,92,"所在城市",1,16,_WHITE);
	puthz(152,92,"抵达时间",1,16,_WHITE);
	puthz(216,92,"发车时间",1,16,_WHITE);
	puthz(286,92,"一等座",1,16,_WHITE);
	puthz(335,92,"二等座",1,16,_WHITE);
	if(page==1&&!modify)
	{
		puthz(460,125,"一等座数:",1,16,_WHITE);
		puthz(460,160,"二等座数:",1,16,_WHITE);
	}
	if(modify) 
	puthz(470,319,"更多",1,16,_WHITE);
	if(page<4)
	{
		puthz(470,359,"下一页",1,16,_WHITE);
	}
	puthz(470,397,"保存",1,16,_WHITE);
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
	puthz(30,92,"站名",1,16,_WHITE);
	puthz(86,92,"所在城市",1,16,_WHITE);
	puthz(152,92,"时间",1,16,_WHITE);
	puthz(286,92,"硬座费",1,16,_WHITE);
	puthz(335,92,"硬卧费",1,16,_WHITE);
	puthz(384,92,"软卧费",1,16,_WHITE); 
	puthz(460,125,"硬座数:",1,16,_WHITE);
	puthz(460,160,"硬卧数:",1,16,_WHITE);
	puthz(460,195,"软卧数:",1,16,_WHITE); 
	puthz(470,397,"保存",1,16,_WHITE);
}

void ModifyData()
{
	cleardevice();
	input_frm(100,10,540,40);
	button2(290,50,350,80);
	_return(0,0);
	
	puthz(303,55,"修改",1,16,_WHITE);
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
	puthz(470,319,"更多",1,16,_WHITE);
	puthz(30,92,"站名",1,16,_WHITE);
	if(train=='K'||train=='T')
	{
		puthz(110,92,"硬座数",1,16,_WHITE);
		puthz(170,92,"硬卧数",1,16,_WHITE);
		puthz(230,92,"软卧数",1,16,_WHITE);
	}
	else if(train=='G')
	{
		puthz(110,92,"一等座数",1,16,_WHITE);
		puthz(170,92,"二等座数",1,16,_WHITE);
		puthz(230,92,"商务卧数",1,16,_WHITE);
	}
	else if(train=='D')
	{
		puthz(110,92,"一等座数",1,16,_WHITE);
		puthz(170,92,"二等座数",1,16,_WHITE);
		puthz(230,92,"软卧数",1,16,_WHITE);
	}
	if(page<4)
    puthz(470,359,"下一页",1,16,_WHITE);
	puthz(470,397,"保存",1,16,_WHITE);
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
	puthz(240,247,"火车(K)",1,16,_BLACK);
	puthz(240,277,"火车(T)",1,16,_BLACK);
	puthz(240,307,"动车(D)",1,16,_BLACK);
	puthz(240,337,"高铁(G)",1,16,_BLACK);
	puthz(240,367,"直达(Z)",1,16,_BLACK);
	puthz(234,397,"确定",1,16,_WHITE);
}

void start_book(int flag)
{
	if(flag==1)
	{
		op_window1(150,25,640,475);
	
		setcolor(BCTcolor(30));
		bar(151,240,639,270);
		bar(556,445,639,474);
		puthz(220,247,"请选择购票人:",1,16,_BLACK);
		setcolor(_WHITE);
		bar(151,445,560,474);
		puthz(210,452,"应付人民币:",1,16,_BROWN);
		puthz(332,452,"0元",1,16,_RED);
		puthz(568,452,"立即预定",1,16,_WHITE);
		
	}
	else 
	{
		op_window1(0,25,640,475);
	
		setcolor(BCTcolor(30));
		bar(201,240,639,270);
		bar(556,445,639,474);
		puthz(220,247,"请选择购票人:",1,16,_BLACK);
		setcolor(_WHITE);
		bar(1,445,560,474);
		puthz(10,452,"应付人民币:",1,16,_BROWN);
		puthz(132,452,"0元",1,16,_RED);
		puthz(568,452,"立即预定",1,16,_WHITE);
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
		puthz(364+200*(i%2),167+35*(i/2),"预定",1,16,_WHITE);
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
		puthz(154,87+i*35,"预定",1,16,_WHITE);
	}
	for(i=0;i<4;i++)
	{
		setcolor(_WHITE);
		bar(10,240+i*35,190,270+i*35);
		setcolor(BCTcolor(0));
		bar(151,240+i*35,190,270+i*35);
		puthz(154,247+i*35,"预定",1,16,_WHITE);
	}
	puthz(10,57,"第一程:",1,16,_BLACK);
	puthz(10,217,"第二程:",1,16,_BLACK); 
	
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
	puthz(305,227,"请选择支付方式",1,16,_BLACK);
	puthz(360,267,"支付宝",1,16,_BLACK);
	puthz(368,307,"微信",1,16,_BLACK);
	puthz(360,347,"银行卡",1,16,_BLACK);
}

void pay_method()
{
	op_window(500,250,610,340);
	shut(610,250);
	setcolor(BCTcolor(25));
	bar(501,271,609,300);
	bar(501,311,609,339);
	puthz(520,277,"扫描二维码",1,16,_BLACK);
	puthz(520,317,"输入密码",1,16,_BLACK);	
}

void paybypassword()
{
	op_window(500,250,610,340);
	shut(610,250);
	input_frm(520,270,575,300);
	button1(540,305,580,335);
	puthz(505,252,"支付密码",1,16,_WHITE);
	puthz(544,312,"支付",1,16,_WHITE);
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
	puthz(328,320,"支付成功",1,16,GTcolor(30));
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
	puthz(x+400,y+20,"改签",1,16,_WHITE);
	puthz(x+400,y+64,"退票",1,16,_WHITE);
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
	
	puthz(10,67,"输入初始密码:",1,16,_BLACK);
	puthz(26,127,"输入新密码:",1,16,_BLACK);
	puthz(26,187,"确认新密码:",1,16,_BLACK);
	puthz(192,297,"确认",1,16,_WHITE);
}

void success_hint()
{
	int i;
	char temp[2];
	setcolor(_WHITE);
	bar(1,1,279,329);
	CK_right(140,100);
	puthz(50,150,"修改密码成功,3秒后自",1,16,GTcolor(30));
	puthz(110,175,"动返回...",1,16,GTcolor(30));
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
	puthz(440,277,"蓝色经典",1,16,_WHITE);
	puthz(440,307,"粉红回忆",1,16,_WHITE);
	puthz(440,337,"秋意浓",1,16,_WHITE);
	puthz(440,367,"青葱岁月",1,16,_WHITE);
	puthz(440,397,"水墨风",1,16,_WHITE);
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
	puthz(42,57,"姓名:",1,16,_BLACK);
	puthz(42,117,"性别:",1,16,_BLACK);
	puthz(10,177,"身份证号",1,16,_BLACK);
	puthz(10,237,"手机号码:",1,16,_BLACK);
	puthz(10,297,"个性签名:",1,16,_BLACK);
	puthz(214,387,"保存",1,16,_WHITE);
}

void success_submit()
{
	cleardevice();
	setbkcolor(_WHITE);
	CK_right(320,100);
	puthz(50,7,"感谢您的宝贵意见！",1,16,GTcolor(20));
	delay(1500);
}

void clear_data()
{
	setcolor(_WHITE);
	bar(290,200,400,420);
	setcolor(GTcolor(25));
	rectangle(290,200,400,420);
	CK_right(345,270);
	puthz(313,340,"清理成功",1,16,GTcolor(30));
	delay(1000);
}
