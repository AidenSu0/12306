#include<stdio.h>
#include<stdlib.h>
#include<alloc.h>
#include<string.h>
#include "svga.h"
#include "function.h"
#include "data.h"
#include <conio.h>
#include <mem.h>
#include <errno.h>
    /*��¼���溯��*/
int KT_save(char *T_num,KT_train *p,int page,int (*length)[9],int *lengthnum,int num,int k)
{
	char path1[35]={"C:\\PRJ\\File\\data"},date[3];
	char path2[35]={"C:\\PRJ\\File\\data"};
	char path3[35];
	char code[6],station[10];//�洢���г�վ��Ϣ
	CITYCODE citycode;
	FILE *fp,*fp1;
	int i,j,m=0,z=0;
	
	memset(station,'\0',10);
	memset(&citycode,'\0',sizeof(CITYCODE));
	itoa(k,date,10);
	strcat(path1,date);
	strcat(path2,date);
	strcat(path1,"\\");
	strcat(path2,"\\TNAME.DAT");
	//��ֹ������Ϣ��������  �������� 
			for(i=0;i<=num;i++) 
			for(j=0;j<7;j++)
			{
				if(page==1&&i==0&&(j==1||j==2)) continue;
				if(i==num&&j!=0&&j!=1&&j!=2) continue;
				if(length[j][i]==0) m=1;
			}
			if((lengthnum[0]==0||lengthnum[1]==0||lengthnum[2]==0)&&page==1) m=1;
			if(m) return FALSE;
			
	
	if(lengthnum[3]!=-1)//���޸�ģʽ
	{
		//д��������Ϣ
		fp=fopen(path2,"a");
		fputs(p->tra_num,fp);
		fputc('\n',fp);
		fclose(fp);
	
	//��λ������		
		for(i=1;i<num+(page-1)*9;i++)
		{
			strcpy(p->hard_seat[i],p->hard_seat[0]);
			strcpy(p->hard_sleeper[i],p->hard_sleeper[0]);
			strcpy(p->soft_sleeper[i],p->soft_sleeper[0]);
		}
	}	
	
	strcpy(p->start_time[num+(page-1)*9],"###");//��վ������־ 
	
	strcat(path1,T_num);
	fp=fopen(path1,"w");
	if(fwrite(p,sizeof(KT_train),1,fp)!=1)
	{
		printf("Write error!");
		getch();
		exit(0);
	}
	fclose(fp);
	/*���³����복վ��ƥ����Ϣ*/
	for(i=0;i<=num+(page-1)*9;i++)//���³��г�վ��Ϣ 
	{
		fp=fopen("C:\\PRJ\\File\\CIST\\citycode","rb");
		while(!feof(fp))//������������ Ѱ�Ҵ��ڱ�� 
		{
			if(fread(&citycode,sizeof(CITYCODE),1,fp)==1)
			{
				z++;
			}
			if(!strcmp(citycode.city,p->city[i]))//ƥ�䵽���� 
			{
				itoa(citycode.code,code,10);
				strcpy(path3,"C:\\PRJ\\File\\CIST\\");
				strcat(path3,code);
				fp1=fopen(path3,"r+");
				while(!feof(fp1))//ƥ�䳵վ��Ϣ 
				{
					fread(station,10,1,fp1);
					if(!strcmp(station,p->station[i]))//ƥ�䵽��վ 
					{
						break;
					}
				}
				if(strcmp(station,p->station[i])&&feof(fp1))//δƥ�䵽��վ 
				{
					fwrite(p->station[i],10,1,fp1);
				}
				fclose(fp1);
				break; 
			}
		}
		if(strcmp(citycode.city,p->city[i])&&feof(fp))//δƥ�䵽���� 
		{
			fclose(fp);//�����ԣ�ֱ�����ļ�βд��������⣬��������׷�ӷ�ʽ�� 
			fp=fopen("C:\\PRJ\\File\\CIST\\citycode","ab");
			citycode.code=z;
			strcpy(citycode.city,p->city[i]);
			fwrite(&citycode,sizeof(CITYCODE),1,fp); 
			itoa(citycode.code,code,10);
			strcpy(path3,"C:\\PRJ\\File\\CIST\\");
			strcat(path3,code);
			fp1=fopen(path3,"w");
			fwrite(p->station[i],10,1,fp1);
			fclose(fp1);
		}
		z=0; 
		fclose(fp);
	}
	return TURE;
} 

int Z_save(char *T_num,Z_train *p,int (*length)[2],int *lengthnum,int k)
{
	char path1[35]={"C:\\PRJ\\File\\data"},date[3];
	char path2[35]={"C:\\PRJ\\File\\data"};
	char path3[35];
	char code[6],station[10];//�洢���г�վ��Ϣ
	CITYCODE citycode;
	FILE *fp,*fp1;
	int i,j,m=0,z=0;
	
	memset(station,'\0',10);
	memset(&citycode,'\0',sizeof(CITYCODE));
	itoa(k,date,10);
	strcat(path1,date);
	strcat(path2,date);
	strcat(path1,"\\");
	strcat(path2,"\\TNAME.DAT");
	//��ֹ������Ϣ��������  �������� 
			for(i=0;i<2;i++) 
			for(j=0;j<7;j++)
			{
				if(j==3||(i==1&&(j==4||j==5||j==6))) continue;
				if(length[j][i]==0) m=1;
			}
			if(lengthnum[0]==0||lengthnum[1]==0||lengthnum[2]==0) m=1;
			if(m)	return FALSE;	
	//ע��ֱ�ﳵ�������жϳ�վ�Ƿ���� 
			
	if(lengthnum[3]!=-1)
	{
		fp=fopen(path2,"a");
		fputs(p->tra_num,fp);
		fputc('\n',fp);
		fclose(fp);
	}		
	
	
	strcat(path1,T_num);
	fp=fopen(path1,"w");
	if(fwrite(p,sizeof(Z_train),1,fp)!=1)
	{
		printf("Write error!");
		getch();
		exit(0);
	}
	fclose(fp);
	/*���³����복վ��ƥ����Ϣ*/ 
	for(i=0;i<2;i++)//���³��г�վ��Ϣ 
	{
		fp=fopen("C:\\PRJ\\File\\CIST\\citycode","rb");
		while(!feof(fp))//������������ Ѱ�Ҵ��ڱ�� 
		{
			if(fread(&citycode,sizeof(CITYCODE),1,fp)==1)
			{
				z++;
			}
			if(!strcmp(citycode.city,p->city[i]))//ƥ�䵽���� 
			{
				itoa(citycode.code,code,10);
				strcpy(path3,"C:\\PRJ\\File\\CIST\\");
				strcat(path3,code);
				fp1=fopen(path3,"r+");
				while(!feof(fp1))//ƥ�䳵վ��Ϣ 
				{
					fread(station,10,1,fp1);
					if(!strcmp(station,p->station[i]))//ƥ�䵽��վ 
					{
						break;
					}
				}
				if(strcmp(station,p->station[i])&&feof(fp1))//δƥ�䵽��վ 
				{
					fwrite(p->station[i],10,1,fp1);
				}
				fclose(fp1);
				break; 
			}
		}
		if(strcmp(citycode.city,p->city[i])&&feof(fp))//δƥ�䵽���� 
		{
			fclose(fp);
			fp=fopen("C:\\PRJ\\File\\CIST\\citycode","ab");
			citycode.code=z;
			strcpy(citycode.city,p->city[i]);
			fwrite(&citycode,sizeof(CITYCODE),1,fp);
			itoa(citycode.code,code,10);
			strcpy(path3,"C:\\PRJ\\File\\CIST\\");
			strcat(path3,code);
			fp1=fopen(path3,"w");
			fwrite(p->station[i],10,1,fp1);
			fclose(fp1);
		}
		z=0;
		fclose(fp);
	}
	return TURE;
} 

int G_save(char *T_num,G_train *p,int page,int (*length)[9],int *lengthnum,int num,int k)
{
	char path1[35]={"C:\\PRJ\\File\\data"},date[3];
	char path2[35]={"C:\\PRJ\\File\\data"};
	char path3[35];
	char code[6],station[10];//�洢���г�վ��Ϣ
	CITYCODE citycode;
	FILE *fp,*fp1;
	int i,j,m=0,z=0;
	
	memset(station,'\0',10);
	memset(&citycode,'\0',sizeof(CITYCODE));
	itoa(k,date,10);
	strcat(path1,date);
	strcat(path2,date);
	strcat(path1,"\\");
	strcat(path2,"\\TNAME.DAT");
	//��ֹ������Ϣ��������  �������� 
			for(i=0;i<=num;i++) 
			for(j=0;j<7;j++)
			{
				if(page==1&&i==0&&j==2) continue;
				if(i==num&&j!=0&&j!=2) continue;
				if(length[j][i]==0) m=1;
			}
			if((lengthnum[0]==0||lengthnum[1]==0||lengthnum[2]==0)&&page==0) m=1;
			if(m) return FALSE;
	if(lengthnum[3]!=-1)
	{
		fp=fopen(path2,"a");
		fputs(p->tra_num,fp);
		fputc('\n',fp);
		fclose(fp);
		 
		for(i=0;i<num+(page-1)*9;i++)
		{
			strcpy(p->b_seat[i],p->b_seat[0]);
			strcpy(p->f_seat[i],p->f_seat[0]);
			strcpy(p->s_seat[i],p->s_seat[0]);
		}
	}		
	
	strcpy(p->start_time[num+(page-1)*9],"###");//��վ������־
	
	strcat(path1,T_num);
	fp=fopen(path1,"w");
	if(fwrite(p,sizeof(G_train),1,fp)!=1)
	{
		printf("Write error!");
		getch();
		exit(0);
	}
	fclose(fp);
	/*���³����복վ��ƥ����Ϣ*/
	for(i=0;i<=num+(page-1)*9;i++)//���³��г�վ��Ϣ 
	{
		fp=fopen("C:\\PRJ\\File\\CIST\\citycode","rb");
		while(!feof(fp))//������������ Ѱ�Ҵ��ڱ�� 
		{
			if(fread(&citycode,sizeof(CITYCODE),1,fp)==1)
			{
				z++;
			}
			if(!strcmp(citycode.city,p->city[i]))//ƥ�䵽���� 
			{
				itoa(citycode.code,code,10);
				strcpy(path3,"C:\\PRJ\\File\\CIST\\");
				strcat(path3,code);
				fp1=fopen(path3,"r+");
				while(!feof(fp1))//ƥ�䳵վ��Ϣ 
				{
					fread(station,10,1,fp1);
					if(!strcmp(station,p->station[i]))//ƥ�䵽��վ 
					{
						break;
					}
				}
				if(strcmp(station,p->station[i])&&feof(fp1))//δƥ�䵽��վ 
				{
					fwrite(p->station[i],10,1,fp1);
				}
				fclose(fp1);
				break; 
			}
		}
		if(strcmp(citycode.city,p->city[i])&&feof(fp))//δƥ�䵽���� 
		{
			fclose(fp);
			fp=fopen("C:\\PRJ\\File\\CIST\\citycode","ab");
			citycode.code=z;
			strcpy(citycode.city,p->city[i]);
			fwrite(&citycode,sizeof(CITYCODE),1,fp);
			itoa(citycode.code,code,10);
			strcpy(path3,"C:\\PRJ\\File\\CIST\\");
			strcat(path3,code);
			fp1=fopen(path3,"w");
			fwrite(p->station[i],10,1,fp1);
			fclose(fp1);
		}
		z=0;
		fclose(fp);
	}
	return TURE;
} 


int D_save(char *T_num,D_train *p,int page,int (*length)[9],int *lengthnum,int num,int k)
{
	char path1[35]={"C:\\PRJ\\File\\data"},date[3];
	char path2[35]={"C:\\PRJ\\File\\data"};
	char path3[35];
	char code[6],station[10];//�洢���г�վ��Ϣ
	CITYCODE citycode;
	FILE *fp,*fp1;
	int i,j,m=0,z=0;
	
	memset(station,'\0',10);
	memset(&citycode,'\0',sizeof(CITYCODE));
	itoa(k,date,10);
	strcat(path1,date);
	strcat(path2,date);
	strcat(path1,"\\");
	strcat(path2,"\\TNAME.DAT");
	//��ֹ������Ϣ��������  �������� 
			for(i=0;i<=num;i++) 
			for(j=0;j<7;j++)
			{
				if((page==1&&i==0&&j==2)||j==6) continue;
				if(i==num&&j!=0&&j!=2) continue;
				if(length[j][i]==0) m=1;
			}
			if((lengthnum[0]==0||lengthnum[1]==0)&&page==0) m=1;
			if(m) 
			{
				printf("false");
				printf("%d",num); 
				return FALSE;
			}
	
	if(lengthnum[3]!=-1)
	{
		fp=fopen(path2,"a");
		fputs(p->tra_num,fp);//д��������Ϣ 
		fputc('\n',fp);
		fclose(fp);
	 
		for(i=0;i<num+(page-1)*9;i++)
		{
			strcpy(p->f_seat[i],p->f_seat[0]);
			strcpy(p->s_seat[i],p->s_seat[0]);
		}
	}		
	strcpy(p->start_time[num+(page-1)*9],"###");//��վ������־
	
	strcat(path1,T_num);
	fp=fopen(path1,"w");
	if(fwrite(p,sizeof(D_train),1,fp)!=1)
	{
		printf("Write error!");
		getch(); 
		exit(0);
	}
	fclose(fp);
	/*���³����복վ��ƥ����Ϣ*/
	for(i=0;i<=num+(page-1)*9;i++)//���³��г�վ��Ϣ 
	{
		fp=fopen("C:\\PRJ\\File\\CIST\\citycode","rb");
		while(!feof(fp))//������������ Ѱ�Ҵ��ڱ�� 
		{
			if(fread(&citycode,sizeof(CITYCODE),1,fp)==1)
			{
				z++;
			}
			if(!strcmp(citycode.city,p->city[i]))//ƥ�䵽���� 
			{
				itoa(citycode.code,code,10);
				strcpy(path3,"C:\\PRJ\\File\\CIST\\");
				strcat(path3,code);
				fp1=fopen(path3,"r+");
				while(!feof(fp1))//ƥ�䳵վ��Ϣ 
				{
					fread(station,10,1,fp1);
					if(!strcmp(station,p->station[i]))//ƥ�䵽��վ 
					{
						break;
					}
				}
				if(strcmp(station,p->station[i])&&feof(fp1))//δƥ�䵽��վ 
				{
					fwrite(p->station[i],10,1,fp1);
				}
				fclose(fp1);
				break; 
			}
		}
		if(strcmp(citycode.city,p->city[i])&&feof(fp))//δƥ�䵽���� 
		{
			fclose(fp);
			fp=fopen("C:\\PRJ\\File\\CIST\\citycode","ab");
			citycode.code=z;
			strcpy(citycode.city,p->city[i]);
			fwrite(&citycode,sizeof(CITYCODE),1,fp);
			itoa(citycode.code,code,10);
			strcpy(path3,"C:\\PRJ\\File\\CIST\\");
			strcat(path3,code);
			fp1=fopen(path3,"w");
			fwrite(p->station[i],10,1,fp1);
			fclose(fp1);
		}
		z=0;
		fclose(fp);
	}
	return TURE;
} 

    /*��¼��ȡ����*/ 
int KT_read(char *T_num,KT_train *train,int num)
{
	char path[35]={"C:\\PRJ\\File\\data"},date[3];
	FILE *fp;
	int a=0;

	itoa(num,date,10);
	strcat(path,date);
	strcat(path,"\\");
	strcat(path,T_num);
	if((fp=fopen(path,"r"))==NULL)
	{
		printf("KT_read:%s",strerror(errno));
		getch();
		return 0;
	}
	if(fread(train,sizeof(KT_train),1,fp)!=1)
	{
		printf("Read error��");
		getch();
		exit(0);
	}
	fclose(fp);
	return 1;
}

int Z_read(char *T_num,Z_train *train,int num)
{
	char path[35]={"C:\\PRJ\\File\\data"},date[3];
	FILE *fp;
	
	itoa(num,date,10);
	strcat(path,date);
	strcat(path,"\\");
	strcat(path,T_num);
	if((fp=fopen(path,"r"))==NULL)
	{
		return 0;
	}
	if(fread(train,sizeof(Z_train),1,fp)!=1)
	{
		printf("Read error!");
		getch();
		exit(0);
	}
	fclose(fp);
	return 1;
} 

int G_read(char *T_num,G_train *train,int num)
{
	char path[35]={"C:\\PRJ\\File\\data"},date[3];
	FILE *fp;
	
	itoa(num,date,10);
	strcat(path,date);
	strcat(path,"\\");
	strcat(path,T_num);
	if((fp=fopen(path,"r"))==NULL)
	{
		return 0;
	}
	if(fread(train,sizeof(G_train),1,fp)!=1)
	{
		printf("Read error!");
		getch();
		exit(0);
	}
	fclose(fp);
	return 1;
} 

int D_read(char *T_num,D_train *train,int num)
{
	char path[35]={"C:\\PRJ\\File\\data"},date[3];
	FILE *fp;
	
	itoa(num,date,10);
	strcat(path,date);
	strcat(path,"\\");
	strcat(path,T_num);
	if((fp=fopen(path,"r"))==NULL)
	{
		return 0;
	}
	if(fread(train,sizeof(D_train),1,fp)!=1)
	{
		printf("Read error!");
		getch();
		exit(0);
	}
	fclose(fp);
	return 1;
} 


int SearchTrain(char *T_num,int num)
{
	char TName[301][7];//�趨�������������μ�¼
	char path[35]={"C:\\PRJ\\File\\data"},date[3];
	char temp[7]; 
	FILE *fp;
	int i,j;
	
	itoa(num,date,10);
	strcat(path,date);
	strcat(path,"\\TNAME.DAT");
	fp=fopen(path,"r");
	for(i=0;i<300&&!feof(fp);i++)
	fgets(TName[i],7,fp);
	fclose(fp);
	if(i==300) printf("Too many Train!");
	strcpy(temp,T_num);
	strcat(temp,"\n");
	for(j=0;j<i;j++)
	{
		if(!strcmp(TName[j],temp)) return TURE;
	}
	return FALSE;
} 

//�������ļ���ɾ������ 
int DeleteTrain(char *T_num,int num)
{
	char TName[301][7]; 
	char path[35]={"C:\\PRJ\\File\\data"},date[3];
	char temp[7]; 
	FILE *fp;
	int i,j,k;
	
	itoa(num,date,10);
	strcat(path,date);
	strcat(path,"\\TNAME.DAT");
	fp=fopen(path,"r");
	for(i=0;i<300&&!feof(fp);i++)
	{
		fgets(TName[i],7,fp);
	}
	fclose(fp);
	if(i==300)
	{
		 printf("Too many Train!");
		 return 1;
	}
	strcpy(temp,T_num);
	strcat(temp,"\n");
	for(j=0;j<i;j++)
	{
		if(!strcmp(TName[j],temp))
		{
			if(!strcmp(strcpy(TName[j],TName[i-2]),TName[i-2]))
			{
				fp=fopen(path,"w");
				for(k=0;k<i-2;k++)
				fputs(TName[k],fp);
				fclose(fp);
				return TURE;
			}	
		}
	}
	return FALSE;
} 
