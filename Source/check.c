#include"check.h"
#include "svga.h"
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <mem.h>
#include "hmi .h"
#include "mouse.h"
#include "hz.h"


/*========================*/
/*鼠标位置判断函数集*/
/*作者：苏新明  施佳华*/ 
/*所有界面的鼠标位置与点击判断*/
/*========================*/

void check_login(int *judge,int x,int y,int state)
{
    if(x>200&&x<296&&y>296&&y<324&&state) 	*judge=1;	 
	else if(x>380&&x<476&&y>296&&y<324&&state)   *judge=2;
	else if(x>256&&x<384&&y>196&&y<224&&state)   *judge=14;
	else if(x>256&&x<384&&y>236&&y<264&&state)   *judge=15;
	else if(x>380&&x<476&&y>336&&y<364&&state)   *judge=20; 
	else if(x>600&&x<632&&y>438&&y<454&&state)   *judge=21;
	else if(x>600&&x<632&&y>454&&y<470&&state) 
	{
		closegraph(); 
		exit(0);
	}
	
}

void check_help(int *judge,int x,int y,int state)
{
	if(x>0&&x<20&&y>0&&y<20&&state) *judge=1;
}

int check_book(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;

	if(x>161&&x<308&&y>50&&y<90) C_position=3;
	else if(x>320&&x<467&&y>50&&y<90) C_position=4;
	else if(x>479&&x<626&&y>50&&y<90) C_position=5;
	else if(x>260&&x<376&&y>320&&y<340) C_position=6;
    else if(x>200&&x<280&&y>165&&y<195) C_position=97;
	else if(x>360&&x<440&&y>165&&y<195) C_position=98;
	else if((long)(x-300)*(x-300)+(long)(y-250)*(y-250)<225) *judge=99;
	else if(x>260&&x<270&&y>290&&y<300) C_position=100;
	else if(x>380&&x<390&&y>290&&y<300) C_position=101;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		puthz(204,62,"我的订单",1,16,_WHITE);
		puthz(363,62,"购票身份",1,16,_WHITE);
		puthz(522,62,"我的账户",1,16,_WHITE);
		puthz(298,322,"查询",1,16,_WHITE);
		setcolor(_BLACK);
		rectangle(260,290,270,300);
		rectangle(380,290,390,300);
		rectangle(200,165,280,195);
		rectangle(360,165,440,195);
		switch(C_position)
		{
			case 3:
				puthz(204,62,"我的订单",1,16,LIGHT_CYAN);
				break;
			case 4:
				puthz(363,62,"购票身份",1,16,LIGHT_CYAN);
				break;
			case 5:
				puthz(522,62,"我的账户",1,16,LIGHT_CYAN);
				break;
			case 6:
				puthz(298,322,"查询",1,16,LIGHT_CYAN);
				break;
			case 97:
				setcolor(LIGHT_CYAN);
				rectangle(200,165,280,195);
				break;
			case 98:
				setcolor(LIGHT_CYAN);
				rectangle(360,165,440,195);
				break;
			case 100:
				setcolor(LIGHT_CYAN);
				rectangle(260,290,270,300);
				break;
			case 101:
				setcolor(LIGHT_CYAN);
				rectangle(380,290,390,300);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
} 

int check_my_order(int *judge,int p,int x,int y,int state,int num)
{
	int C_position=-1;
    if(x>2&&x<149&&y>50&&y<90) C_position=2;
	else if(x>320&&x<467&&y>50&&y<90) C_position=4;
	else if(x>479&&x<626&&y>50&&y<90) C_position=5;
	else if(x>480&&x<512&&y>195&&y<211&&num>0) C_position=6;
	else if(x>480&&x<512&&y>239&&y<255&&num>0) C_position=7;
	else if(x>480&&x<512&&y>300&&y<316&&num>1) C_position=8;
	else if(x>480&&x<512&&y>344&&y<360&&num>1) C_position=9;
	else if(x>550&&x<582&&y>360&&y<376&&num>2) C_position=10;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		puthz(45,62,"车票预定",1,16,_WHITE);
		puthz(522,62,"我的账户",1,16,_WHITE);
		puthz(363,62,"购票身份",1,16,_WHITE);
		if(num>0)
		{
			puthz(480,195,"改签",1,16,_WHITE);
			puthz(480,239,"退票",1,16,_WHITE);
		}
		if(num>1)
		{
			puthz(480,300,"改签",1,16,_WHITE);
			puthz(480,344,"退票",1,16,_WHITE);
		}
		if(num==3)
		{
			puthz(550,360,"更多",1,16,_WHITE);
		}
		switch(C_position)
		{
			case 2:
				puthz(45,62,"车票预定",1,16,LIGHT_CYAN);
				break;
			case 4:
				puthz(363,62,"购票身份",1,16,LIGHT_CYAN);
				break;
			case 5:
				puthz(522,62,"我的账户",1,16,LIGHT_CYAN);
				break;
			case 6:
				puthz(480,195,"改签",1,16,LIGHT_CYAN);
				break;
			case 7:
				puthz(480,239,"退票",1,16,LIGHT_CYAN);
				break;
			case 8:
				puthz(480,300,"改签",1,16,LIGHT_CYAN);
				break;
			case 9:
				puthz(480,344,"退票",1,16,LIGHT_CYAN);
				break;
			case 10:
				puthz(550,360,"更多",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;

}

int check_identity(int *judge,int p,int x,int y,int state,int num)
{
	int C_position=-1,i,j;
    if(x>2&&x<149&&y>50&&y<90) C_position=2;
	else if(x>479&&x<626&&y>50&&y<90) C_position=5;
	else if(x>161&&x<308&&y>50&&y<90) C_position=3;
	else if(x>285&&x<345&&y>350&&y<380) C_position=7;
	for(i=0;i<num;i++)
	{
		if(x>270+240*(i%2)&&x<290+240*(i%2)&&y>175+35*(i/2)&&y<195+35*(i/2)) 
		{
			C_position=8+i;
		}
	}
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		puthz(45,62,"车票预定",1,16,_WHITE);
		puthz(204,62,"我的订单",1,16,_WHITE);
		puthz(522,62,"我的账户",1,16,_WHITE);
		puthz(300,358,"增加",1,16,_WHITE);
		setcolor(_WHITE);
		for(i=0;i<num;i++)
		{
			bar(275+240*(i%2),183+35*(i/2),285+240*(i%2),187+35*(i/2));
		}
		switch(C_position)
		{
			case 2:
				puthz(45,62,"车票预定",1,16,LIGHT_CYAN);
				break;
			case 3:
				puthz(204,62,"我的订单",1,16,LIGHT_CYAN);
				break;
			case 5:
				puthz(522,62,"我的账户",1,16,LIGHT_CYAN);
				break;
			case 7:
				puthz(300,358,"增加",1,16,LIGHT_CYAN);
				break;
		}
		for(i=0;i<num;i++)
		{
			if(C_position==i+8)
			{
				setcolor(LIGHT_CYAN);
				bar(275+240*(i%2),183+35*(i/2),285+240*(i%2),187+35*(i/2));
			}
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}
int check_my_account(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>2&&x<149&&y>50&&y<90) C_position=2;
	else if(x>161&&x<308&&y>50&&y<90) C_position=3;
	else if(x>320&&x<467&&y>50&&y<90) C_position=4;
	else if(x>67&&x<107&&y>250&&y<370) C_position=8;
	else if(x>181&&x<221&&y>250&&y<370) C_position=9;
	else if(x>295&&x<335&&y>250&&y<370) C_position=10;
	else if(x>409&&x<449&&y>250&&y<370) C_position=11;
	else if(x>523&&x<563&&y>250&&y<370) C_position=12;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		puthz(363,62,"购票身份",1,16,_WHITE);
		puthz(45,62,"车票预定",1,16,_WHITE);
		puthz(204,62,"我的订单",1,16,_WHITE);
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
		switch(C_position)
		{
			case 2:
				puthz(45,62,"车票预定",1,16,LIGHT_CYAN);
				break;
			case 3:
				puthz(204,62,"我的订单",1,16,LIGHT_CYAN);
				break;
			case 4:
				puthz(363,62,"购票身份",1,16,LIGHT_CYAN);
				break;
			case 8:
				puthz(79,284,"时",1,16,LIGHT_CYAN);
				puthz(79,303,"刻",1,16,LIGHT_CYAN);
				puthz(79,322,"表",1,16,LIGHT_CYAN);
				break;
			case 9:
				puthz(193,292,"消",1,16,LIGHT_CYAN);
				puthz(193,311,"息",1,16,LIGHT_CYAN);
				break;
			case 10:
				puthz(307,292,"设",1,16,LIGHT_CYAN);
				puthz(307,311,"置",1,16,LIGHT_CYAN);
				break;
			case 11:
				puthz(421,292,"反",1,16,LIGHT_CYAN);
				puthz(421,311,"馈",1,16,LIGHT_CYAN);
				break;
			case 12:
				puthz(535,292,"关",1,16,LIGHT_CYAN);
				puthz(535,311,"于",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
} 
void check_regist(int *judge,int x,int y,int state)
{
	if(x>320&&x<400&&y>330&&y<350&&state) *judge=19;
	else if(x>480&&x<500&&y>100&&y<120&&state) *judge=0;
	else if(x>300&&x<420&&y>150&&y<170&&state) *judge=16;
	else if(x>300&&x<420&&y>210&&y<230&&state) *judge=17;
	else if(x>300&&x<420&&y>270&&y<290&&state) *judge=18;
}

int check_add_identity(int *judge,int p,int x,int y,int state,int St)
{
	int C_position=-1,i,maxi=4;

	if(x>320&&x<400&&y>415&&y<445) C_position=6;
	else if(x>470&&x<490&&y>10&&y<30) C_position=4;
	else if(x>250&&x<420&&y>55&&y<85) C_position=7;
	else if(x>250&&x<420&&y>105&&y<135) C_position=8;
	else if(x>250&&x<420&&y>155&&y<185) C_position=9;
	else if(x>250&&x<420&&y>205&&y<235) C_position=10;
	if(St==2)
	{
		if(x>250&&x<420&&y>255&&y<285) C_position=11;
		else if(x>250&&x<420&&y>305&&y<335) C_position=12;
		else if(x>250&&x<420&&y>355&&y<385) C_position=13;
		maxi=7;
	}
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		setcolor(_BLACK);
		for(i=0;i<maxi;i++)
		{
			rectangle(250,55+i*50,420,85+i*50);
		}
		shut(490,10);
		puthz(344,422,"确认",1,16,_WHITE);
		setcolor(LIGHT_CYAN);
		switch(C_position)
		{
			case 4:
				Rshut(490,10);
				break;
			case 6:
				puthz(344,422,"确认",1,16,LIGHT_CYAN);
				break;
			case 7:
				rectangle(250,55,420,85);
				break;
			case 8:
				rectangle(250,105,420,135);
				break;
			case 9:
				rectangle(250,155,420,185);
				break;
			case 10:
				rectangle(250,205,420,235);
				break;
			case 11:
				rectangle(250,255,420,285);
				break;
			case 12:
				rectangle(250,305,420,335);
				break;
			case 13:
				rectangle(250,355,420,385);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y); 
	}
	return C_position;
}

int check_choose(int *judge,int p,int rx,int ry,int x,int y,int state)
{
	int C_position=-1;
	if(x>rx+60&&x<rx+80&&y>ry&&y<ry+20) C_position=0;
	else if(x>rx+15&&x<rx+25&&y>ry+30&&y<ry+40) C_position=1;
	else if(x>rx+15&&x<rx+25&&y>ry+60&&y<ry+70) C_position=2;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(rx+80,ry);
		setcolor(GTcolor(25));
		circle(rx+20,ry+35,5);
	    circle(rx+20,ry+65,5);
	    setcolor(BCTcolor(60));
		switch(C_position)
		{
			case 0:
				Rshut(rx+80,ry);
				break;
			case 1:
			    circle(rx+20,ry+35,5);
				break;
			case 2:
			    circle(rx+20,ry+65,5);
			    break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
} 


int check_settings(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;

	if(x>380&&x<400&&y>200&&y<220) C_position=5;
	else if(x>290&&x<400&&y>220&&y<260) C_position=6;
	else if(x>290&&x<400&&y>260&&y<300) C_position=7;
	else if(x>290&&x<400&&y>300&&y<340) C_position=8;
	else if(x>290&&x<400&&y>340&&y<380) C_position=9;
	else if(x>290&&x<400&&y>380&&y<420) C_position=0;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		puthz(310,232,"修改密码",1,16,_WHITE);
		puthz(310,272,"更换主题",1,16,_WHITE);
		puthz(310,312,"我的资料",1,16,_WHITE);
		puthz(310,352,"清除缓存",1,16,_WHITE);
		puthz(310,392,"退出",1,16,_WHITE);
		shut(400,200);
		switch(C_position)
		{
			case 5:
				Rshut(400,200);
				break;
			case 6:
				puthz(310,232,"修改密码",1,16,LIGHT_CYAN);
				break;
			case 7:
				puthz(310,272,"更换主题",1,16,LIGHT_CYAN);
				break;
			case 8:
				puthz(310,312,"我的资料",1,16,LIGHT_CYAN);
				break;
			case 9:
				puthz(310,352,"清除缓存",1,16,LIGHT_CYAN);
				break;
			case 0:
				puthz(310,392,"退出",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_time_table(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>0&&x<20&&y>0&&y<20) C_position=5;
	else if(x>100&&x<300&&y>50&&y<80) C_position=6;
	else if(x>340&&x<370&&y>50&&y<80) C_position=7; 
	else if(x>390&&x<420&&y>50&&y<80) C_position=8;
	else if(x>450&&x<530&&y>50&&y<80) C_position=9;
	if(state) *judge=C_position; 
	if(C_position!=p)
	{
		redraw(x,y);
		_return(0,0);
		setcolor(_BLACK);
		rectangle(100,50,300,80);
		rectangle(340,50,370,80);
		rectangle(390,50,420,80);
		puthz(474,57,"查询",1,16,_WHITE);
		switch(C_position)
		{
			case 5:
				_Breturn(0,0);
				break;
			case 6:
				setcolor(LIGHT_CYAN);
				rectangle(100,50,300,80);
				break;
			case 7:
				setcolor(LIGHT_CYAN);
				rectangle(340,50,370,80);;
				break;
			case 8:
				setcolor(LIGHT_CYAN);
				rectangle(390,50,420,80);
				break;
			case 9:
				puthz(474,57,"查询",1,16,LIGHT_CYAN);
		}
		getbk_mouse(x,y);
		draw_mouse(x,y); 
	}
	return C_position;
}

int check_Re_operate(int *judge,int p,int num,int x,int y,int state,int flag,int page)
{
	int C_position=-1,i,j;//光标位置 
	if(x>0&&x<20&&y>0&&y<20) C_position=2;
	else if(x>300&&x<332&&y>27&&y<43) C_position=3;
	else if(x>500&&x<532&&y>27&&y<43) C_position=4;
	else if(x>223&&x<287&&y>450&&y<466) C_position=5;
	else if(x>333&&x<397&&y>450&&y<466) C_position=6;
	else if(x>443&&x<507&&y>450&&y<466) C_position=7;
	else if(x>553&&x<617&&y>450&&y<466) C_position=8;
	else if(x>5&&x<73&&y>320&&y<336) C_position=9;
	else if(x>127&&x<195&&y>320&&y<336) C_position=10;
	else if(x>47&&x<79&&y>400&&y<416) C_position=11;
	else if(x>10&&x<80&&y>190&&y<220) C_position=12;
	else if(x>120&&x<190&&y>190&&y<220) C_position=13;
	else if(x>200&&x<640&&y>51&&y<141&&num>0) C_position=14;
	else if(x>200&&x<640&&y>141&&y<231&&num>1) C_position=15;
	else if(x>200&&x<640&&y>231&&y<321&&num>2) C_position=16;
	else if(x>200&&x<640&&y>321&&y<411&&num>3) C_position=17;
	else if(x>590&&x<640&&y>422&&y<438&&num>4) C_position=18;
	else if(x>110&&x<200&&y>130&&y<146) C_position=19;
	else if(x>200&&x<250&&y>422&&y<438&&page) C_position=20;
	if(state) *judge=C_position; 
	if(C_position!=p)
	{
		redraw(x,y);
		puthz(110,130,"重新搜索",1,16,_WHITE);
		puthz(300,27,"直达",1,16,GTcolor(20));
		puthz(500,27,"中转",1,16,GTcolor(20));
		puthz(223,450,"高级筛选",1,16,_WHITE);
		puthz(333,450,"出发时间",1,16,_WHITE);
		puthz(443,450,"旅行耗时",1,16,_WHITE);
		switch(flag)
		{
			case 0:
				puthz(553,450,"显示",1,16,_WHITE);
				break;
			case 1:
				puthz(553,450,"显示余票",1,16,_WHITE);
				break;
			case 2:
			    puthz(553,450,"显示价格",1,16,_WHITE);
				break; 
		}
		puthz(25,320,"前一天",1,16,_WHITE);
		puthz(127,320,"后一天",1,16,_WHITE);
		puthz(47,400,"这里",1,16,_WHITE);
		if(num>4)
		{
			puthz(590,422,"下一页",1,16,BCTcolor(0));
		}
		if(page) 
		{
			puthz(202,422,"上一页",1,16,BCTcolor(0));
		}
		setcolor(_WHITE);
		line(17,320,9,328);
		line(9,328,17,336);
		line(183,320,191,328);
		line(191,328,183,336);
		line(180,130,188,138);
 	    line(180,146,188,138);
		setcolor(_BLACK);
		rectangle(10,190,80,220);
		rectangle(120,190,190,220);
		for(i=0;i<num&&i<4;i++)
		{
			for(j=1;j<4;j++)
			{
				setcolor(BCTcolor(35+j));
				rectangle(200+j,51+i*90+j,640-j,141+i*90-j);
			}
		}
		_return(0,0);
		setcolor(LIGHT_CYAN);
		switch(C_position)
		{
			case 2:
				_Breturn(0,0);
				break;
			case 3:
				puthz(300,27,"直达",1,16,LIGHT_CYAN);  
				break;
			case 4:
				puthz(500,27,"中转",1,16,LIGHT_CYAN);
				break;
			case 5:
				puthz(223,450,"高级筛选",1,16,LIGHT_CYAN);
				break;
			case 6:
				puthz(333,450,"出发时间",1,16,LIGHT_CYAN);
				break;
			case 7:
				puthz(443,450,"旅行耗时",1,16,LIGHT_CYAN);
				break;
			case 8:
				switch(flag)
				{
					case 0:
						puthz(553,450,"显示",1,16,LIGHT_CYAN);
						break;
					case 1:
						puthz(553,450,"显示余票",1,16,LIGHT_CYAN);
						break;
					case 2:
					    puthz(553,450,"显示价格",1,16,LIGHT_CYAN);
						break; 
				}
				break;
			case 9:
				puthz(25,320,"前一天",1,16,LIGHT_CYAN);
				line(17,320,9,328);
				line(9,328,17,336);
				break;
			case 10:
				puthz(127,320,"后一天",1,16,LIGHT_CYAN);
				line(183,320,191,328);
				line(191,328,183,336);
				break;
			case 11:
				puthz(47,400,"这里",1,16,LIGHT_CYAN);
				break;
			case 12:
		        rectangle(10,190,80,220);
		        break;
			case 13:
				rectangle(120,190,190,220);
				break;
			case 14:
				for(j=1;j<4;j++)
				{
					setcolor(BCTcolor(j*10));
					rectangle(200+j,51+j,640-j,141-j);
				}
				break;
			case 15:
				for(j=1;j<4;j++)
				{
					setcolor(BCTcolor(j*10));
					rectangle(200+j,141+j,640-j,231-j);
				}
				break;
			case 16:
				for(j=1;j<4;j++)
				{
					setcolor(BCTcolor(j*10));
					rectangle(200+j,231+j,640-j,321-j);
				}
				break;
			case 17:
				for(j=1;j<4;j++)
				{
					setcolor(BCTcolor(j*10));
					rectangle(200+j,321+j,640-j,411-j);
				}
				break;
			case 18:
				puthz(590,422,"下一页",1,16,LIGHT_CYAN);
				break;
			case 19:
				puthz(110,130,"重新搜索",1,16,LIGHT_CYAN);
				line(180,130,188,138);
				line(180,146,188,138);
				break;
			case 20:
				puthz(202,422,"上一页",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}


int check_Adv_choose(int *judge,int p,int x,int y,int state)
{
	int C_position=0,i;
	if(x>280&&x<300&&y>200&&y<220) C_position=1;
	else if(x>220&&x<230&&y>250&&y<260) C_position=2;
	else if(x>220&&x<230&&y>280&&y<290) C_position=3;
	else if(x>220&&x<230&&y>310&&y<320) C_position=4;
	else if(x>220&&x<230&&y>340&&y<350) C_position=5;
	else if(x>220&&x<230&&y>370&&y<380) C_position=6;
	else if(x>230&&x<270&&y>390&&y<420) C_position=7;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(300,200);
		setcolor(BCTcolor(0));
		for(i=0;i<5;i++)
		{
			rectangle(220,250+i*30,230,260+i*30); 
		}
		puthz(240,247,"火车(K)",1,16,_BLACK);
		puthz(240,277,"火车(T)",1,16,_BLACK);
		puthz(240,307,"动车(D)",1,16,_BLACK);
		puthz(240,337,"高铁(G)",1,16,_BLACK);
		puthz(240,367,"直达(Z)",1,16,_BLACK);
		puthz(234,397,"确定",1,16,_WHITE);
		setcolor(BCTcolor(60));
		switch(C_position)
		{
			case 2:
				rectangle(220,250,230,260);
				break;
			case 3:
				rectangle(220,280,230,290);
				break;
			case 4:
			    rectangle(220,310,230,320);
				break;
			case 5:
				rectangle(220,340,230,350);
				break;
			case 6:
				rectangle(220,370,230,380);
				break;
			case 7:
				puthz(234,397,"确定",1,16,BCTcolor(60));
				break;
			case 1:
				Rshut(300,200);
				break;	
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	} 
	return C_position;
}


int check_message(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>0&&x<20&&y>0&&y<20) C_position=5;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		_return(0,0);
		if(C_position==5)
		{
			_Breturn(0,0);
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
} 

int check_about(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>0&&x<20&&y>0&&y<20) C_position=5;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		_return(0,0);
		if(C_position==5)
		{
			_Breturn(0,0);
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_feedback(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>0&&x<20&&y>0&&y<20) C_position=5;
	else if(x>100&&x<540&&y>30&&y<340) C_position=6;
	else if(x>100&&x<540&&y>350&&y<370) C_position=7;
	else if(x>100&&x<540&&y>380&&y<400) C_position=8;
	else if(x>480&&x<540&&y>420&&y<450) C_position=9;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		_return(0,0);
		setcolor(_BLACK);
		rectangle(100,30,540,340);
		rectangle(100,350,540,370);
		rectangle(100,380,540,400);
		puthz(494,427,"提交",1,16,_WHITE);
		switch(C_position)
		{
			case 5:
				_Breturn(0,0);
				break;
			case 6:
				setcolor(LIGHT_CYAN);
				rectangle(100,30,540,340);
				break;
			case 7:
				setcolor(LIGHT_CYAN);
				rectangle(100,350,540,370);
				break;
			case 8:
				setcolor(LIGHT_CYAN);
				rectangle(100,380,540,400);
				break;
			case 9:
				puthz(494,427,"提交",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

void check_manage(int *judge,int x,int y,int state)
{
	if(x>400&&x<536&&y>320&&y<340&&state) *judge=21;//管理员通行密码输入21
	else if(x>480&&x<530&&y>360&&y<380&&state) *judge=22;//数据系统界面 22
	else if(x>610&&x<630&&y>250&&y<270&&state) *judge=0;
} 

void check_data(int *judge,int x,int y,int state)
{
	if(x>0&&x<20&&y>0&&y<20&&state) *judge=0; 
	else if(x>20&&x<120&&y>50&&y<80&&state) *judge=23;
	else if(x>20&&x<120&&y>150&&y<180&&state) *judge=24;
	else if(x>20&&x<120&&y>100&&y<130&&state) *judge=25; 
}

void check_NewData(int *judge,int x,int y,int state)
{
	if(x>0&&x<20&&y>0&&y<20&&state) *judge=22;
	else if(x>100&&x<540&&y>10&&y<40&&state) *judge=93;
	else if(x>290&&x<350&&y>50&&y<80&&state) *judge=26;

}

void check_NewKT(int *judge,int x,int y,int state)
{
	int i;
	if(x>460&&x<550&&y>310&&y<340&&state) *judge=96; 
	else if(x>600&&x<620&&y>90&&y<110&&state) *judge=23;
	else if(x>460&&x<550&&y>350&&y<380&&state) *judge=94;
	else if(x>460&&x<550&&y>390&&y<420&&state) *judge=95; 
	for(i=0;i<9;i++)
	{
		if(x>30&&x<100&&y>120+i*35&&y<150+i*35&&state) *judge=27+i;
		else if(x>105&&x<175&&y>120+i*35&&y<150+i*35&&state) *judge=36+i;
		else if(x>180&&x<230&&y>125+i*35&&y<145+i*35&&state) *judge=45+i;
		else if(x>240&&x<290&&y>125+i*35&&y<145+i*35&&state) *judge=54+i;
		else if(x>310&&x<340&&y>125+i*35&&y<145+i*35&&state) *judge=63+i;
		else if(x>345&&x<385&&y>125+i*35&&y<145+i*35&&state) *judge=72+i;
		else if(x>400&&x<430&&y>125+i*35&&y<145+i*35&&state) *judge=81+i;
		else if(i<3&&x>550&&x<595&&y>125+i*35&&y<145+i*35&&state) *judge=90+i;
	}
}

void check_NewG(int *judge,int x,int y,int state)
{
	int i;
	if(x>460&&x<550&&y>310&&y<340&&state) *judge=96; 
	else if(x>600&&x<620&&y>90&&y<110&&state) *judge=23;
	else if(x>460&&x<550&&y>350&&y<380&&state) *judge=94;
	else if(x>460&&x<550&&y>390&&y<420&&state) *judge=95; 
	for(i=0;i<9;i++)
	{
		if(x>30&&x<100&&y>120+i*35&&y<150+i*35&&state) *judge=27+i;
		else if(x>105&&x<175&&y>120+i*35&&y<150+i*35&&state) *judge=36+i;
		else if(x>180&&x<230&&y>125+i*35&&y<145+i*35&&state) *judge=45+i;
		else if(x>240&&x<290&&y>125+i*35&&y<145+i*35&&state) *judge=54+i;
		else if(x>310&&x<340&&y>125+i*35&&y<145+i*35&&state) *judge=63+i;
		else if(x>345&&x<385&&y>125+i*35&&y<145+i*35&&state) *judge=72+i;
		else if(x>400&&x<430&&y>125+i*35&&y<145+i*35&&state) *judge=81+i;
		else if(i<3&&x>550&&x<595&&y>125+i*35&&y<145+i*35&&state) *judge=90+i;
	}
}

void check_NewD(int *judge,int x,int y,int state)
{
	int i;
	if(x>460&&x<550&&y>310&&y<340&&state) *judge=96; 
	else if(x>600&&x<620&&y>90&&y<110&&state) *judge=23;
	else if(x>460&&x<550&&y>350&&y<380&&state) *judge=94;
	else if(x>460&&x<550&&y>390&&y<420&&state) *judge=95; 
	for(i=0;i<9;i++)
	{
		if(x>30&&x<100&&y>120+i*35&&y<150+i*35&&state) *judge=27+i;
		else if(x>105&&x<175&&y>120+i*35&&y<150+i*35&&state) *judge=36+i;
		else if(x>180&&x<230&&y>125+i*35&&y<145+i*35&&state) *judge=45+i;
		else if(x>240&&x<290&&y>125+i*35&&y<145+i*35&&state) *judge=54+i;
		else if(x>310&&x<340&&y>125+i*35&&y<145+i*35&&state) *judge=63+i;
		else if(x>345&&x<385&&y>125+i*35&&y<145+i*35&&state) *judge=72+i;
		else if(i<2&&x>550&&x<595&&y>125+i*35&&y<145+i*35&&state) *judge=90+i;
	}
}

void check_NewZ(int *judge,int x,int y,int state)
{
	int i;
	if(x>600&&x<620&&y>90&&y<110&&state) *judge=23;
	else if(x>460&&x<550&&y>390&&y<420&&state) *judge=95; 
	for(i=0;i<3;i++)
	{
		if(i<2&&x>30&&x<100&&y>120+i*35&&y<150+i*35&&state) *judge=27+i;
		else if(x>105&&x<175&&y>125+i*35&&y<145+i*35&&state) *judge=36+i;
		else if(i<2&&x>180&&x<230&&y>125+i*35&&y<145+i*35&&state) *judge=45+i;
		else if(i==0&&x>310&&x<340&&y>125+i*35&&y<145+i*35&&state) *judge=63+i;
		else if(i==0&&x>355&&x<385&&y>125+i*35&&y<145+i*35&&state) *judge=72+i;
		else if(i==0&&x>400&&x<430&&y>125+i*35&&y<145+i*35&&state) *judge=81+i;
		else if(x>550&&x<595&&y>125+i*35&&y<145+i*35&&state) *judge=90+i;
	}
}

void check_DeleteData(int *judge,int x,int y,int state)
{
	if(x>0&&x<20&&y>0&&y<20&&state) *judge=22;
	else if(x>100&&x<540&&y>10&&y<40&&state) *judge=93;
	else if(x>290&&x<350&&y>50&&y<80&&state) *judge=26;
}
void check_more(int *judge,int x,int y,int state)
{
	int i;
	if(x>460&&x<550&&y>310&&y<340&&state) *judge=96; 
	else if(x>600&&x<620&&y>90&&y<110&&state) *judge=23;
	else if(x>460&&x<550&&y>350&&y<380&&state) *judge=94;
	else if(x>460&&x<550&&y>390&&y<420&&state) *judge=95;
	for(i=0;i<9;i++)
	{
		if(x>30&&x<100&&y>120+i*35&&y<150+i*35&&state) *judge=27+i;
		else if(x>110&&x<155&&y>125+i*35&&y<145+i*35&&state) *judge=36+i;
		else if(x>170&&x<215&&y>125+i*35&&y<145+i*35&&state) *judge=45+i;
		else if(x>230&&x<275&&y>125+i*35&&y<145+i*35&&state) *judge=54+i;
	}
}

int check_DEstbook(int *judge,int p,int x,int y,int state,int idnum)
{
	int C_position=-1,i;
	if(x>620&&x<640&&y>30&&y<50) C_position=1;
	else if(x>556&&x<639&&y>445&&y<474) C_position=2;
	for(i=0;i<4;i++)
	{
		if(x>360+200*(i%2)&&x<400+200*(i%2)&&y>160+35*(i/2)&&y<190+35*(i/2))
		{
			C_position=3+i;
		}
	}
	for(i=0;i<idnum;i++)
	{
		if(x>260+(i%2)*220&&y>275+(i/2)*35&&x<360+(i%2)*220&&y<305+(i/2)*35)
		{
			C_position=7+i;
		}
	}
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(640,25);
		puthz(568,452,"立即预定",1,16,_WHITE);
		setcolor(_BLACK);
		for(i=0;i<4;i++)
		{
			puthz(364+200*(i%2),167+35*(i/2),"预定",1,16,_WHITE);
		}
		for(i=0;i<idnum;i++)
		{
			rectangle(260+(i%2)*220,275+(i/2)*35,360+(i%2)*220,305+(i/2)*35);
		}
		switch(C_position)
		{
			case 1:
				Rshut(640,25);
				break;
			case 2:
				puthz(568,452,"立即预定",1,16,LIGHT_CYAN);
				break;
		}
		for(i=0;i<4;i++)
		{
			if(C_position==3+i)
			{
				puthz(364+200*(i%2),167+35*(i/2),"预定",1,16,LIGHT_CYAN);
			}
		}
		for(i=0;i<idnum;i++)
		{
			if(C_position==7+i)
			{
				setcolor(LIGHT_CYAN);
				rectangle(260+(i%2)*220,275+(i/2)*35,360+(i%2)*220,305+(i/2)*35);
			}
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_REstbook(int *judge,int p,int x,int y,int state,int idnum)
{
	int C_position=-1,i;
	if(x>620&&x<640&&y>30&&y<50) C_position=1;
	else if(x>556&&x<639&&y>445&&y<474) C_position=2;
	for(i=0;i<4;i++)
	{
		if(x>151&&x<190&&y>80+i*35&&y<110+i*35)
		{
			C_position=3+i;
		}
	}
	for(i=0;i<4;i++)
	{
		if(x>151&&x<190&&y>240+i*35&&y<270+i*35)
		{
			C_position=7+i;
		}
	}
	for(i=0;i<idnum;i++)
	{
		if(x>260+(i%2)*220&&y>275+(i/2)*35&&x<360+(i%2)*220&&y<305+(i/2)*35)
		{
			C_position=11+i;
		}
	}
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(640,25);
		puthz(568,452,"立即预定",1,16,_WHITE);
		for(i=0;i<4;i++)
		{
			puthz(154,87+i*35,"预定",1,16,_WHITE);
		}
		for(i=0;i<4;i++)
		{
			puthz(154,247+i*35,"预定",1,16,_WHITE);
		}
		for(i=0;i<idnum;i++)
		{
			setcolor(_BLACK);
			rectangle(260+(i%2)*220,275+(i/2)*35,360+(i%2)*220,305+(i/2)*35);
		}
		switch(C_position)
		{
			case 1:
				Rshut(640,25);
				break;
			case 2:
				puthz(568,452,"立即预定",1,16,LIGHT_CYAN);
				break;
		}
		for(i=0;i<4;i++)
		{
			if(C_position==3+i)
			{
				puthz(154,87+i*35,"预定",1,16,LIGHT_CYAN);
			}
		}
		for(i=0;i<4;i++)
		{
			if(C_position==7+i)
			{
				puthz(154,247+i*35,"预定",1,16,LIGHT_CYAN);
			}	
		}
		for(i=0;i<idnum;i++)
		{
			if(C_position==11+i)
			{
				setcolor(LIGHT_CYAN);
				rectangle(260+(i%2)*220,275+(i/2)*35,360+(i%2)*220,305+(i/2)*35);
			}
		}
		getbk_mouse(x,y);
		draw_mouse(x,y); 
	}
	return C_position;
}

int check_TTB(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>610&&x<630&&y>100&&y<120) C_position=1;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(630,100);
		if(C_position==1)
		{
			Rshut(630,100);
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_password(int *judge,int p,int x,int y,int state)
{
	int C_position=-1,i;
	if(x>260&&x<280&&y>0&&y<20) C_position=1;
	else if(x>130&&x<265&&y>60&&y<90) C_position=2;
	else if(x>130&&x<265&&y>120&&y<150) C_position=3;
	else if(x>130&&x<265&&y>180&&y<210) C_position=4;
	else if(x>180&&y>290&&x<240&&y<320) C_position=6;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(280,0);
		setcolor(_BLACK);
		for(i=0;i<3;i++)
		{
			rectangle(130,60+i*60,265,90+i*60);
		}
		puthz(192,297,"确认",1,16,_WHITE);
		switch(C_position)
		{
			case 1:
				Rshut(280,0);
				break;
			case 2:
				setcolor(LIGHT_CYAN);
				rectangle(130,60,265,90);
				break;
			case 3:
				setcolor(LIGHT_CYAN);
				rectangle(130,120,265,150);
				break;
			case 4:
				setcolor(LIGHT_CYAN);
				rectangle(130,180,265,210);
				break;
			case 6:
				puthz(192,297,"确认",1,16,LIGHT_CYAN);
				break; 
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_theme(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>504&&x<524&&y>250&&y<270) C_position=1;
	else if(x>420&&x<524&&y>270&&y<300) C_position=2;
	else if(x>420&&x<524&&y>300&&y<330) C_position=3;
	else if(x>420&&x<524&&y>330&&y<360) C_position=4;
	else if(x>420&&x<524&&y>360&&y<390) C_position=5;
	else if(x>420&&x<524&&y>390&&y<420) C_position=6;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(524,250);
		puthz(440,277,"蓝色经典",1,16,_WHITE);
		puthz(440,307,"粉红回忆",1,16,_WHITE);
		puthz(440,337,"秋意浓",1,16,_WHITE);
		puthz(440,367,"青葱岁月",1,16,_WHITE);
		puthz(440,397,"水墨风",1,16,_WHITE);
		switch(C_position)
		{
			case 1:
				Rshut(524,250);
				break;
			case 2:
				puthz(440,277,"蓝色经典",1,16,LIGHT_CYAN);
				break;
			case 3:
				puthz(440,307,"粉红回忆",1,16,LIGHT_CYAN);
				break;
			case 4:
				puthz(440,337,"秋意浓",1,16,LIGHT_CYAN);
				break;
			case 5:
				puthz(440,367,"青葱岁月",1,16,LIGHT_CYAN);
				break;
			case 6:
				puthz(440,397,"水墨风",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_profile(int *judge,int p,int x,int y,int state)
{
	int C_position=-1,i;
	if(x>280&&x<300&&y>0&&y<20) C_position=1;
	else if(x>90&&x<255&&y>50&&y<80) C_position=2;
	else if(x>90&&x<255&&y>110&&y<140) C_position=3;
	else if(x>90&&x<255&&y>170&&y<200) C_position=4;
	else if(x>90&&x<255&&y>230&&y<260) C_position=5;
	else if(x>90&&x<255&&y>290&&y<350) C_position=6;
	else if(x>214&&x<250&&y>380&&y<410) C_position=7;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(300,0);
		setcolor(_BLACK);
		for(i=0;i<4;i++)
		{
			rectangle(90,50+i*60,255,80+i*60);
		}
		rectangle(90,290,255,350);
		puthz(214,387,"保存",1,16,_WHITE);
		switch(C_position)
		{
			case 1:
				Rshut(300,0);
				break;
			case 6:
				setcolor(LIGHT_CYAN);
				rectangle(90,290,255,350);
				break;
			case 7:
				puthz(214,387,"保存",1,16,LIGHT_CYAN);
				break;
		}
		for(i=0;i<4;i++)
		{
			if(C_position==i+2)
			{
				setcolor(LIGHT_CYAN);
				rectangle(90,50+i*60,255,80+i*60);
			}
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_pay(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>400&&x<420&&y>200&&y<220) C_position=1;
	else if(x>301&&x<419&&y>260&&y<290) C_position=2;
	else if(x>301&&x<419&&y>300&&y<330) C_position=3;
	else if(x>301&&x<419&&y>340&&y<370) C_position=4;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		puthz(360,267,"支付宝",1,16,_BLACK);
		puthz(368,307,"微信",1,16,_BLACK);
		puthz(360,347,"银行卡",1,16,_BLACK);
		shut(420,200);
		switch(C_position)
		{
			case 1:
				Rshut(420,200);
				break;
			case 2:
				puthz(360,267,"支付宝",1,16,LIGHT_CYAN);
				break;
			case 3:
				puthz(368,307,"微信",1,16,LIGHT_CYAN);
				break;
			case 4:
				puthz(360,347,"银行卡",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position; 
}

int check_paymethod(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>590&&x<610&&y>250&&y<270) C_position=1;
	else if(x>501&&x<609&&y>271&&y<300) C_position=2;
	else if(x>501&&x<609&&y>311&&y<339) C_position=3;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(610,250);
		puthz(520,277,"扫描二维码",1,16,_BLACK);
		puthz(520,317,"输入密码",1,16,_BLACK);
		switch(C_position)
		{
			case 1:
				Rshut(610,250);
				break;
			case 2:
				puthz(520,277,"扫描二维码",1,16,LIGHT_CYAN);
				break;
			case 3:
				puthz(520,317,"输入密码",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}

int check_pwEnter(int *judge,int p,int x,int y,int state)
{
	int C_position=-1;
	if(x>590&&x<610&&y>250&&y<270) C_position=1;
	else if(x>520&&x<575&&y>270&&y<300) C_position=2;
	else if(x>540&&x<580&&y>305&&y<325) C_position=3;
	if(state) *judge=C_position;
	if(C_position!=p)
	{
		redraw(x,y);
		shut(610,250);
		setcolor(_BLACK);
		rectangle(520,270,575,300);
		puthz(544,312,"支付",1,16,_WHITE);
		switch(C_position)
		{
			case 1:
				Rshut(610,250);
				break;
			case 2:
				setcolor(LIGHT_CYAN);
				rectangle(520,270,575,300);
				break;
			case 3:
				puthz(544,312,"支付",1,16,LIGHT_CYAN);
				break;
		}
		getbk_mouse(x,y);
		draw_mouse(x,y);
	}
	return C_position;
}
