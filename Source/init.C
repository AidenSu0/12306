#include<dos.h>
#include<stdio.h>
#include "init.h" 
#include"svga.h"
/*========================*/
/*��ʼ������*/
/*���ߣ�������*/
/*========================*/ 
void initGR()
{
	
	SetSVGAmode();//����256ɫģʽ 


    SetPalette();//�Զ���д���ɫ�� 
  //  int driver=DETECT,mode;
  //  union REGS regs;
  //  initgraph(&driver,&mode,"C:\\BORLANDC\\BGI");
  //  initgraph(&driver,&mode,"D:\\BC31\\DISK_C\\BORLANDC\\BGI");
   // SVGA_Init();
   // Set_Pal_File("win.act");
  	
/*	
	regs.x.ax=0x4f02;
	regs.x.bx=0x103;//���ó�640x480�ֱ���256ɫģʽ
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
