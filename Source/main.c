#include "check.h"
#include "function.h"
#include "init.h"
#include "svga.h"
#include"hmi.h"
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<bios.h>
#include<conio.h>
#include<string.h>
#include<alloc.h>
#include "mouse.h"
#include "gettime.h" 


void main()
{
	FILE *fp;
	int judge=0,mark=1,state=0;
	char account[20];
	char timetoday[10],oldtime[10],temp[5];
	TIME _tm;
	union REGS regs;
	
	/*鼠标初状态*/
    int xnow,ynow,btnow=0;
    
    initGR();
    initMU();
    /*数据更新判断及操作（若当前日期更新 则数据更新）*/
    _gettime(&_tm);
    itoa(_tm.year,temp,10);
    strcpy(timetoday,temp);
    itoa(_tm.month,temp,10);
    strcat(timetoday,temp);
    itoa(_tm.day,temp,10);
    strcat(timetoday,temp);
    strcat(timetoday,"\n");
    if((fp=fopen("C:\\PRJ\\File\\data0\\TIME.DAT","r"))==NULL)
    {
    	printf("Can't open file");
    	getch();
    	exit(1);
	}
	fgets(oldtime,10,fp);
	fclose(fp);
	if(strcmp(oldtime,timetoday))
	{
		refresh();
		fp=fopen("C:\\PRJ\\File\\data0\\TIME.DAT","w");
		fseek(fp,0,SEEK_SET);
		fputs(timetoday,fp);
		fclose(fp);
	}
    while(1)
    {
    	switch(judge)
    	{
    		case 0:
    			judge=f_login(account,&xnow,&ynow,&btnow,&mark);
				mark=0;
				break;
			case 1:
				judge=f_register(&xnow,&ynow,&btnow,&mark);
				mark=0;
				break;
			case 2:
				judge=f_UserControl(account,&xnow,&ynow,&mark);
				mark=0;
				break;
			case 20:
				judge=f_manage(&xnow,&ynow,&btnow,&mark);
				mark=0;
				break;
			default:
				judge=0;
				break;
		}
		
	}
}


/*修正时间调试用 
void main()
{
	TIME _tm;
	_gettime(&_tm);
	printf("%dy",_tm.year);
	printf("%dm",_tm.month);
	printf("%dd",_tm.day);
	printf("%dh",_tm.hour);
	printf("%dmin",_tm.min);
	getch();
}*/
