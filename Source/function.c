
/*所有界面功能控制函数*/
#include "check.h"
#include "function.h"
#include "hz.h"
#include "init.h"
#include "upload.h"
#include "hmi.h"
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<bios.h>
#include<conio.h>
#include<string.h>
#include<alloc.h>
#include "mouse.h"
#include "svga.h"
#include "input.h"
#include "data.h"
#include "user.h"
#include "mem.h"
#include "gettime.h"
#include "graph.h"

int f_login(char *s,int *xnow,int *ynow,int *btnow,int *mark)
{
	FILE *fp,*pfp;
	int judge=0;//登录界面状态 
	int m=0;
	int state=0;
	int tab=0,i,all;
	int c_length=0,p_length=0;
    char snow[100][20];//账户输入字符串与原有账户字符串 
    char sp[20],spnow[500][20];//密码输入字符串与原有密码字符串 
	log_in();
	fp=fopen("c:\\PRJ\\File\\account.dat","r");
	pfp=fopen("c:\\PRJ\\File\\key.dat","r");
	//检测文件结束
	for(i=0;!feof(fp);i++)
	fgets(snow[i],18,fp);
	all=i-1;//消除结束符影响 
	for(i=0;!feof(pfp);i++)
	fgets(spnow[i],18,pfp);	
		
	while(1)
	{
		if(judge==14)
		{
			//账户输入
			c_length=nhz_input(xnow,ynow,256,196,392,224,s,&tab,0,c_length);
			*(s+c_length)='\n';
			*(s+c_length+1)='\0';
			judge=0;
			if(tab==1) judge=15;
		} 
		else if(judge==15)
		{
			//密码输入
			p_length=nhz_input(xnow,ynow,256,236,392,264,sp,&tab,1,p_length);
			*(sp+p_length)='\n';
			*(sp+p_length+1)='\0';
			judge=0;
		}
		
		//登陆检测
		check_login(&judge,*xnow,*ynow,state);
		state=mouse_control(xnow,ynow,btnow,mark);
		if(judge==21)
		{
			f_help(xnow,ynow,btnow,mark);
			*mark=0;
			log_in();
			judge=0;
		}
		if(judge==2)
		{
			for(i=0;i<all;i++)
			{
				if((strcmp(s,snow[i])==0)&&(strcmp(sp,spnow[i])==0)&&s[0]!='\n')
					{
			  	    m=1;//账号和密码均正确 
			  	    *(s+c_length)='\0';//消除换行符  方便账户文件打开  
				    break;						
				}
			}
			if(m==0)//账号或密码错误 
			{
				outtextxy(400,254,"error!");
				judge=0;//不登录 
			}
		}
		if(judge!=0&&judge!=14&&judge!=15) 
		{
			fclose(fp);
			fclose(pfp);
			return (judge);
		}
	}
} 
//注册
int f_register(int *xnow,int *ynow,int *btnow,int *mark)
{
	FILE *fp,*pfp;
	USER account;
	int i,all=0,m=0,r=0;
	int judge=1;
	int tab=0;
	int state=0;
	char accountpath[50]={"c:\\PRJ\\File\\account\\"};
	int c_length=0,p_length=0,rp_length=0;
	char s[20];
	char sp[20];
	char rsp[20];
	char now[100][18];//含有少于500个用户信息，用户名不长于16位 
	regist();
	
	fp=fopen("c:\\PRJ\\File\\account.dat","r+");
	pfp=fopen("c:\\PRJ\\File\\key.dat","r+");
	for(i=0;!feof(fp);i++)
	fgets(now[i],18,fp);//获取已有账户 
	fseek(pfp,0,SEEK_END);//保证密码位在文件尾 
	all=i-1;

	while(1)
	{
		if(judge==16)//输入账号 
		{
			c_length=nhz_input(xnow,ynow,300,150,436,170,s,&tab,0,c_length);
			*(s+c_length)='\n';
			*(s+c_length+1)='\0';
			if(tab==1) judge++;
		} 
		else if(judge==17)//输入密码 
		{
			p_length=nhz_input(xnow,ynow,300,210,436,230,sp,&tab,1,p_length);
			*(sp+p_length)='\n';
			*(sp+p_length+1)='\0';
			if(tab==1) judge++;
		} 
		else if(judge==18)//确认密码 
		{
			rp_length=nhz_input(xnow,ynow,300,270,436,290,rsp,&tab,1,rp_length);
			*(rsp+rp_length)='\n';
			*(rsp+rp_length+1)='\0';
			r=1;
		} 
		judge=1;
		check_regist(&judge,*xnow,*ynow,state);
		state=mouse_control(xnow,ynow,btnow,mark);//state为鼠标状态，确定点击并松开返回true
			
			
		if(judge==19&&m==0&&(!strcmp(sp,rsp)))//输入格式规整   保存当前创建 
		{
			memset(&account,0,sizeof(USER));//把account后USER长度的替换为0
			account.order=NULL; 
			fputs(s,fp);//将s写入fp
			fclose(fp);
			fputs(sp,pfp);
			fclose(pfp);
			//creat()函数找不到宏定义参数 改用写文件方式创建文件
			*(s+c_length)='\0'; //消除换行符
			*(sp+p_length)='\0';
			strcpy(account.account_name,s);
			strcpy(account.password,sp);
			strcat(accountpath,s);
			fp=fopen(accountpath,"w");
			fwrite(&account,sizeof(USER),1,fp);
			fclose(fp);
			return(0); 
		} 
		else if(judge==0)
		{
			fclose(fp);
			fclose(pfp);
			return (0);
		}
			
			
		if(bioskey(1)) exit(0);
		tab=0;
			
			 
		if(m==0)
		for(i=0;i<all;i++)
		{
			if(strcmp(s,now[i])==0)
			{
				outtextxy(440,164,"exist!");
				m=1;//账户已存在标志
				break;
			}	
		}
		i=0;//防止遮盖exist重画 
		if(m==1)
		for(i=0;i<all;i++)
		{
			if(strcmp(s,now[i])==0)
			break; 
		}
		if(i==all)
		{
			setcolor(_CYAN);
			bar(440,150,495,170);
			m=0;//新账户状态 
		}
		if(r==1)//重输密码已进行 
		{
			if(strcmp(sp,rsp)!=0)//两次密码不一样
			outtextxy(440,284,"error!"); 
			else 
		    {
			    setcolor(_CYAN);
			    bar(440,270,495,290);
		    }			
		}
				
	}
}
//管理员登陆
int f_manage(int *xnow,int *ynow,int *btnow,int *mark) 
{
	char s[20];
	char *sd="19990519";
	//char *sd="1";调试状态 
	int judge=16;
	int length=0;
	int state=0;
	int tab=0;
	manage();
	
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_manage(&judge,*xnow,*ynow,state);
		//管理员密码登陆
		if(judge==21)
		{
			length=nhz_input(xnow,ynow,400,320,536,340,s,&tab,1,length);
			judge=20;
		}
		else if(judge==22&&(strcmp(s,sd)==0))//judge为22且密钥输入正确
		{
			*mark=0;
			judge=f_data(xnow,ynow,btnow,mark);
		}
		if(judge==0) return(0);
	}
} 

int f_data(int *xnow,int *ynow,int *btnow,int *mark) 
{
	int judge=22;
	int state=0;

	data();
	
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_data(&judge,*xnow,*ynow,state);
//		outtextxy(200,300,Otrain->tra_num);
		if(judge==23)
		{
			//建立车次
			*mark=0;
			judge=f_NewData(xnow,ynow,btnow,mark);
			if(judge==22)
			{
				//数据系统界面
				data();
				*mark=0;
			}		
		}
		else if(judge==24)
		{
			//删除车次
			*mark=0;
			judge=f_DeleteData(xnow,ynow,btnow,mark);
			if(judge==22)
			{
				data();
				*mark=0;
			}
		}
		if(judge==25)
		{
			//修改车次
			*mark=0;
			judge=f_ModifyData(xnow,ynow,btnow,mark);
			if(judge==22)
			{
				data();
				*mark=0;
			}
		}
		else if(judge==0) 
		{
			return (0);
		}
	}
}

int f_NewData(int *xnow,int *ynow,int *btnow,int *mark)
{
	int judge=23;
	int state=0;
	int length=0,m=0;
	int tab=0,k=0;
	char num[55];//储存车次信息 定义足够空间 防止过载 
	
	KT_train KTtrain;
	G_train Gtrain;
	Z_train Ztrain;
	D_train Dtrain;
	/*初始化结构体 ，防止存入文件结束符*/
	memset(&KTtrain,0,sizeof(KT_train));
	memset(&Gtrain,0,sizeof(G_train));
	memset(&Ztrain,0,sizeof(Z_train));
	memset(&Dtrain,0,sizeof(D_train));
	
	NewData();
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewData(&judge,*xnow,*ynow,state);
		if(judge==93)
		{
			length=nhz_input(xnow,ynow,100,10,540,40,num,&tab,0,length);
			k=1;//新信息标志 
		}
		

		if(length>5&&(!m))
		{
			setcolor(_WHITE);
			puthz(274,134,"车次格式错误",1,16,_WHITE);
			//outtextxy(500,64,"error!");
			m=1;
		}
		else if(m&&length<6)
		{
			setcolor(LIGHT_BLUE);
			bar(500,45,600,75);
			m=0;
		}
		
		
		if(judge==26&&length<6&&k)
		{
			if(SearchTrain(num,1))
			{
				outtextxy(200,300,"Exist!");
				k=0;//已存在标志 
				continue;
			}
			//搜索车次是否存在
			//判断是什么列车
			if(num[0]=='K'||num[0]=='T')
			{
				strcpy(KTtrain.tra_num,num);
				judge=f_NewKT(xnow,ynow,btnow,mark,1,&KTtrain);
			}
			
			else if(num[0]=='Z') 
			{
				strcpy(Ztrain.tra_num,num);
				judge=f_NewZ(xnow,ynow,btnow,mark,&Ztrain);
			}
			
			else if(num[0]=='G')
			{
				strcpy(Gtrain.tra_num,num);
				judge=f_NewG(xnow,ynow,btnow,mark,1,&Gtrain);
			}
			
			else if(num[0]=='D')
			{
				strcpy(Dtrain.tra_num,num);
				judge=f_NewD(xnow,ynow,btnow,mark,1,&Dtrain);
			}
			
			/*清除新建数据面板*/
			if(judge==23)
			{
				*mark=0;
				NewData();
				length=0;
				k=0;
			}
		}
		else if(judge==22) return(22);
		judge=23;
	}
}

int f_DeleteData(int *xnow,int *ynow,int *btnow,int *mark)
{
	int judge=24;
	int tab=0;
	int state=0;
	int check1=0,check2=1;
	int length=0,m=0;//m用来判断名称输入是否合理
	char num[55];
	char filename[30]={"C:\\PRJ\\File\\data1\\"};
	
	DeleteData();
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_DeleteData(&judge,*xnow,*ynow,state);
		if(judge==93)
		{
			setcolor(LIGHT_BLUE);
			bar(200,300,440,330);
			length=nhz_input(xnow,ynow,100,10,540,40,num,&tab,0,length);
		}
		
		
		if(length>5&&(m==0))
		{
			setcolor(_WHITE);
			outtextxy(500,64,"error!");
			m=1;
		}
		else if(m&&length<6)
		{
			setcolor(BCTcolor(0));
			bar(500,45,600,75);
			m=0;
		}
	
		if(judge==26&&length>0&&length<6)
		{
			strcat(filename,num);
			check1=unlink(filename);
			check2=DeleteTrain(num,1);
			if(!check1&&check2)
			{
				setcolor(_WHITE);
				outtextxy(250,319,"Succeed!");
				strcpy(filename,"C:\\PRJ\\File\\data\\");  
			}
			else
			{
				setcolor(_WHITE); 
				strcpy(filename,"C:\\PRJ\\File\\data\\");
				outtextxy(250,319,"Failed!");
			}
		}
		if(judge==22) return 22;
		judge=24;
	}
}
//修改车次信息
int f_ModifyData(int *xnow,int *ynow,int *btnow,int *mark)
{
	int judge=25;
	int state=0;
	int length=0,m=0;
	int tab=0,k=0;
	char num[55];//储存车次信息 定义足够空间 防止过载 
	
	KT_train KTtrain;
	G_train Gtrain;
	Z_train Ztrain;
	D_train Dtrain;
	
	ModifyData();
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_NewData(&judge,*xnow,*ynow,state);
		if(judge==93)
		{
			length=nhz_input(xnow,ynow,100,10,540,40,num,&tab,0,length);
			k=1;//重输标志 
		}
		

		if(length>5&&(!m))
		{
			setcolor(_WHITE);
			outtextxy(500,64,"error!");
			m=1;
		}
		else if(m&&length<6)
		{
			setcolor(LIGHT_BLUE);
			bar(500,45,600,75);
			m=0;
		}
		
		
		if(judge==26&&length<6&&k)
		{
			if(!SearchTrain(num,1))
			{
				outtextxy(200,300,"Not exist!");
				k=0;//不存在标志 
				continue;
			}
			if(num[0]=='K'||num[0]=='T')
			{
				KT_read(num,&KTtrain,1);
				judge=f_ModifyKT(xnow,ynow,btnow,mark,1,&KTtrain);
			}
			
			else if(num[0]=='Z') 
			{
				Z_read(num,&Ztrain,1);
				judge=f_ModifyZ(xnow,ynow,btnow,mark,&Ztrain);
			}
			
			else if(num[0]=='G')
			{
				G_read(num,&Gtrain,1);
				judge=f_ModifyG(xnow,ynow,btnow,mark,1,&Gtrain);
			}
						
			else if(num[0]=='D')
			{
				D_read(num,&Dtrain,1);
				judge=f_ModifyD(xnow,ynow,btnow,mark,1,&Dtrain);
			}
			
			//清除新建数据面板
			if(judge==23)
			{
				*mark=0;
				ModifyData();
				length=0;
				k=0;
			}
		}
		else if(judge==22) return(22);
		judge=25;
	}
}

/*数据更新函数*/
void refresh()
{
	TIME _tm;
	int alldays=0,i;
	char daynum[2][3];
	char path1[35]={"C:\\PRJ\\File\\data"};
	char path2[35]={"C:\\PRJ\\File\\data"};
	_gettime(&_tm);
	cleardevice();//清除屏幕		
	setbkcolor(LIGHT_BLUE);
	puthz(1,1,"数据更新中,请等待...",1,16,_PINK);
	//画进度条
	Pro_bar(0,100,540,200,7);
	//获得当前月份天数
	alldays=days(_tm.month,_tm.year);

	for(i=1;i<alldays;i++)
	{
		strcpy(path1,"C:\\PRJ\\File\\data");
		strcpy(path2,"C:\\PRJ\\File\\data");
		itoa(i,daynum[0],10);//将任意类型数字转化为字符串
		itoa(i+1,daynum[1],10);
		strcat(path1,daynum[0]);
		strcat(path1,"\\");
		strcat(path2,daynum[1]);
		strcat(path2,"\\");
		copyfiles(path1,path2,i);
		Pro_bar(0,100,540,200,7+i*3);//
	}
	copyfiles(path2,"C:\\PRJ\\File\\data0\\",-1);
} 

void copyfiles(char *path1,char *path2,int k)
{
	FILE *fp1,*fp2;
	int num,i=0;
	char aim_path[35],source_path[35],Name[301][6],ch;
	strcpy(aim_path,path1);
	strcpy(source_path,path2);
	strcat(aim_path,"TNAME.DAT");
	if((fp1=fopen(aim_path,"w"))==NULL)
	{
		printf("Can't open file");
		getch();
		exit(0);
	}
	num=infoTname(Name,0,0,k+1);//获取来源文件车次索引
	for(i=0;i<num;i++)//复制索引
	{
		fputs(Name[i],fp1);
		fputc('\n',fp1);
	}
	fclose(fp1);
	for(i=0;i<num;i++)//逐个文件复制 
	{
		strcpy(aim_path,path1);//初始化路径 
		strcpy(source_path,path2);
		strcat(aim_path,Name[i]);
		strcat(source_path,Name[i]);
		if((fp1=fopen(aim_path,"w"))==NULL)
		{
			printf("Can't open file");
			getch();
			exit(1);
		}
		if((fp2=fopen(source_path,"r"))==NULL)
		{
			printf("Can't open file");
			getch();
			exit(1);
		}
		while(!feof(fp2))//检测文件结束
		{
			ch=fgetc(fp2);//读取一个字节存入ch
			fputc(ch,fp1);//将ch写入一个流fp1中
		}
		fclose(fp1);
		fclose(fp2);
	}
}

void f_help(int *xnow,int *ynow,int *btnow,int *mark)
{
	int state=0,judge=0;
	*mark=0;
	_help();
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_help(&judge,*xnow,*ynow,state);
		if(judge==1)
		{
			return;
		}
	}
}
