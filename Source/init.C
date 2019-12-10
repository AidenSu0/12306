#include<dos.h>
#include<stdio.h>
#include "init.h" 
#include"svga.h"
/*========================*/
/*初始化函数*/
/*作者：苏新明*/
/*========================*/ 
void initGR()
{
	
	SetSVGAmode();//设置256色模式 


    SetPalette();//自定义写入调色板 
  //  int driver=DETECT,mode;
  //  union REGS regs;
  //  initgraph(&driver,&mode,"C:\\BORLANDC\\BGI");
  //  initgraph(&driver,&mode,"D:\\BC31\\DISK_C\\BORLANDC\\BGI");
   // SVGA_Init();
   // Set_Pal_File("win.act");
  	
/*	
	regs.x.ax=0x4f02;
	regs.x.bx=0x103;//设置成640x480分辨率256色模式
	int86(0x10,&regs,&regs);
	if(regs.x.ax != 0x004f) 
	{
		printf("Failed to set SVGA mode!");
		 
		exit(1);
	}
*/	
}
void initMU()
{
	int code;
	union REGS regs;
    regs.x.ax=0;
    int86(51,&regs,&regs);
    code=regs.x.ax;
	if(code==0) printf("mouse failed!");
	regs.x.ax=7;
	regs.x.cx=1;
	regs.x.dx=639;
	int86(51,&regs,&regs);
	regs.x.ax=8;
	regs.x.cx=1;
	regs.x.dx=479;
	int86(51,&regs,&regs);
}

