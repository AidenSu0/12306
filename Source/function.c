
/*���н��湦�ܿ��ƺ���*/
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
	int judge=0;//��¼����״̬ 
	int m=0;
	int state=0;
	int tab=0,i,all;
	int c_length=0,p_length=0;
    char snow[100][20];//�˻������ַ�����ԭ���˻��ַ��� 
    char sp[20],spnow[500][20];//���������ַ�����ԭ�������ַ��� 
	log_in();
	fp=fopen("c:\\PRJ\\File\\account.dat","r");
	pfp=fopen("c:\\PRJ\\File\\key.dat","r");
	//����ļ�����
	for(i=0;!feof(fp);i++)
	fgets(snow[i],18,fp);
	all=i-1;//����������Ӱ�� 
	for(i=0;!feof(pfp);i++)
	fgets(spnow[i],18,pfp);	
		
	while(1)
	{
		if(judge==14)
		{
			//�˻�����
			c_length=nhz_input(xnow,ynow,256,196,392,224,s,&tab,0,c_length);
			*(s+c_length)='\n';
			*(s+c_length+1)='\0';
			judge=0;
			if(tab==1) judge=15;
		} 
		else if(judge==15)
		{
			//��������
			p_length=nhz_input(xnow,ynow,256,236,392,264,sp,&tab,1,p_length);
			*(sp+p_length)='\n';
			*(sp+p_length+1)='\0';
			judge=0;
		}
		
		//��½���
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
			  	    m=1;//�˺ź��������ȷ 
			  	    *(s+c_length)='\0';//�������з�  �����˻��ļ���  
				    break;						
				}
			}
			if(m==0)//�˺Ż�������� 
			{
				outtextxy(400,254,"error!");
				judge=0;//����¼ 
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
//ע��
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
	char now[100][18];//��������500���û���Ϣ���û���������16λ 
	regist();
	
	fp=fopen("c:\\PRJ\\File\\account.dat","r+");
	pfp=fopen("c:\\PRJ\\File\\key.dat","r+");
	for(i=0;!feof(fp);i++)
	fgets(now[i],18,fp);//��ȡ�����˻� 
	fseek(pfp,0,SEEK_END);//��֤����λ���ļ�β 
	all=i-1;

	while(1)
	{
		if(judge==16)//�����˺� 
		{
			c_length=nhz_input(xnow,ynow,300,150,436,170,s,&tab,0,c_length);
			*(s+c_length)='\n';
			*(s+c_length+1)='\0';
			if(tab==1) judge++;
		} 
		else if(judge==17)//�������� 
		{
			p_length=nhz_input(xnow,ynow,300,210,436,230,sp,&tab,1,p_length);
			*(sp+p_length)='\n';
			*(sp+p_length+1)='\0';
			if(tab==1) judge++;
		} 
		else if(judge==18)//ȷ������ 
		{
			rp_length=nhz_input(xnow,ynow,300,270,436,290,rsp,&tab,1,rp_length);
			*(rsp+rp_length)='\n';
			*(rsp+rp_length+1)='\0';
			r=1;
		} 
		judge=1;
		check_regist(&judge,*xnow,*ynow,state);
		state=mouse_control(xnow,ynow,btnow,mark);//stateΪ���״̬��ȷ��������ɿ�����true
			
			
		if(judge==19&&m==0&&(!strcmp(sp,rsp)))//�����ʽ����   ���浱ǰ���� 
		{
			memset(&account,0,sizeof(USER));//��account��USER���ȵ��滻Ϊ0
			account.order=NULL; 
			fputs(s,fp);//��sд��fp
			fclose(fp);
			fputs(sp,pfp);
			fclose(pfp);
			//creat()�����Ҳ����궨����� ����д�ļ���ʽ�����ļ�
			*(s+c_length)='\0'; //�������з�
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
				m=1;//�˻��Ѵ��ڱ�־
				break;
			}	
		}
		i=0;//��ֹ�ڸ�exist�ػ� 
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
			m=0;//���˻�״̬ 
		}
		if(r==1)//���������ѽ��� 
		{
			if(strcmp(sp,rsp)!=0)//�������벻һ��
			outtextxy(440,284,"error!"); 
			else 
		    {
			    setcolor(_CYAN);
			    bar(440,270,495,290);
		    }			
		}
				
	}
}
//����Ա��½
int f_manage(int *xnow,int *ynow,int *btnow,int *mark) 
{
	char s[20];
	char *sd="19990519";
	//char *sd="1";����״̬ 
	int judge=16;
	int length=0;
	int state=0;
	int tab=0;
	manage();
	
	while(1)
	{
		state=mouse_control(xnow,ynow,btnow,mark);
		check_manage(&judge,*xnow,*ynow,state);
		//����Ա�����½
		if(judge==21)
		{
			length=nhz_input(xnow,ynow,400,320,536,340,s,&tab,1,length);
			judge=20;
		}
		else if(judge==22&&(strcmp(s,sd)==0))//judgeΪ22����Կ������ȷ
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
			//��������
			*mark=0;
			judge=f_NewData(xnow,ynow,btnow,mark);
			if(judge==22)
			{
				//����ϵͳ����
				data();
				*mark=0;
			}		
		}
		else if(judge==24)
		{
			//ɾ������
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
			//�޸ĳ���
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
	char num[55];//���泵����Ϣ �����㹻�ռ� ��ֹ���� 
	
	KT_train KTtrain;
	G_train Gtrain;
	Z_train Ztrain;
	D_train Dtrain;
	/*��ʼ���ṹ�� ����ֹ�����ļ�������*/
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
			k=1;//����Ϣ��־ 
		}
		

		if(length>5&&(!m))
		{
			setcolor(_WHITE);
			puthz(274,134,"���θ�ʽ����",1,16,_WHITE);
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
				k=0;//�Ѵ��ڱ�־ 
				continue;
			}
			//���������Ƿ����
			//�ж���ʲô�г�
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
			
			/*����½��������*/
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
	int length=0,m=0;//m�����ж����������Ƿ����
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
//�޸ĳ�����Ϣ
int f_ModifyData(int *xnow,int *ynow,int *btnow,int *mark)
{
	int judge=25;
	int state=0;
	int length=0,m=0;
	int tab=0,k=0;
	char num[55];//���泵����Ϣ �����㹻�ռ� ��ֹ���� 
	
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
			k=1;//�����־ 
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
				k=0;//�����ڱ�־ 
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
			
			//����½��������
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

/*���ݸ��º���*/
void refresh()
{
	TIME _tm;
	int alldays=0,i;
	char daynum[2][3];
	char path1[35]={"C:\\PRJ\\File\\data"};
	char path2[35]={"C:\\PRJ\\File\\data"};
	_gettime(&_tm);
	cleardevice();//�����Ļ		
	setbkcolor(LIGHT_BLUE);
	puthz(1,1,"���ݸ�����,��ȴ�...",1,16,_PINK);
	//��������
	Pro_bar(0,100,540,200,7);
	//��õ�ǰ�·�����
	alldays=days(_tm.month,_tm.year);

	for(i=1;i<alldays;i++)
	{
		strcpy(path1,"C:\\PRJ\\File\\data");
		strcpy(path2,"C:\\PRJ\\File\\data");
		itoa(i,daynum[0],10);//��������������ת��Ϊ�ַ���
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
	num=infoTname(Name,0,0,k+1);//��ȡ��Դ�ļ���������
	for(i=0;i<num;i++)//��������
	{
		fputs(Name[i],fp1);
		fputc('\n',fp1);
	}
	fclose(fp1);
	for(i=0;i<num;i++)//����ļ����� 
	{
		strcpy(aim_path,path1);//��ʼ��·�� 
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
		while(!feof(fp2))//����ļ�����
		{
			ch=fgetc(fp2);//��ȡһ���ֽڴ���ch
			fputc(ch,fp1);//��chд��һ����fp1��
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
