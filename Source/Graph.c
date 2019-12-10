#include <stdio.h>
#include "data.h"
#include "graph.h"
#include <alloc.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "svga.h"
#include "gettime.h"
#include <mem.h>
/*========================*/
/*��վ���������������*/ 
/*���ߣ�������*/
/*����Deep_search�������ؽ��ͷָ��*/ 
/*========================*/

/*������ջ����*/
void pushStack(StackNode **top,char *station,char *trainnum)
{
	StackNode *pNew=NULL;
	if((pNew=(StackNode *)malloc(sizeof(StackNode)))==NULL)
	{
		printf("Error!");
		getch();
		exit(1);
	}
	strcpy((*top)->station,station);
	strcpy((*top)->trainnum,trainnum);
	(*top)->last=pNew;
	pNew->next=*top;
	pNew->last=NULL;
	*top=pNew;
}

/*������ջ����*/ 
void popStack(StackNode **top)
{
	StackNode *temp=*top;
	*top=(*top)->next;
	(*top)->last=NULL;
	free(temp);
}

/*��ջ2���Ƶ�ջ1,ջ1ֻ�贫��NULLָ��,ջ1ʵ��Ϊ˫������ ����ջ��ָ��*/
/*��һ����Ϊ->next*/ 
void copyStack(StackNode **buttom1,StackNode *buttom2) 
{
	StackNode *pNew=NULL,*pEnd=*buttom1,*position=buttom2;	
	while(position->last!=NULL) 
	{
		if((pNew=(StackNode *)malloc(sizeof(StackNode)))==NULL)//���ָ���� 
		{
			printf("Error!");
			getch();
			exit(1); 
		}
		strcpy(pNew->station,position->station);
		strcpy(pNew->trainnum,position->trainnum);
		if(pEnd==NULL)
		{
			pNew->last=NULL;
			*buttom1=pNew;
		}
		else
		{
			pNew->last=pEnd;
			pEnd->next=pNew;
		}
		pNew->next=NULL;
		pEnd=pNew;
		position=position->last;
	}
} 

/*����Ԥ����*/ 
RESULT *Deep_search(char *Stcity,char *Ficity,int GD,int ST,int num)
{
	int i,j,code[2]={-1,-1};
	GRAPH *graph=NULL;
	ARC *Arc=NULL;
	GraphNode *Gtemp=NULL;
	CITYCODE citycode;
	NET net;
	FILE *fp=NULL;
	char tempSt[10][10],tempFi[10][10],_code[2][6];
	char Ststation[10],Fistation[10],path[35];
	NUMBER STnum=0,FInum=0;
	RESULT *head=NULL,*q=head,*connect=head;
	StackNode *p=NULL,*buttom=NULL;//����ָ�� 
	
	memset(tempSt,'\0',100);
	memset(tempFi,'\0',100);
	/*��ȡ�����г�վ*/ 
	fp=fopen("C:\\PRJ\\File\\CIST\\citycode","rb");
	while(!feof(fp))//ƥ����� 
	{
		fread(&citycode,sizeof(CITYCODE),1,fp);
		if(!strcmp(citycode.city,Stcity))
		{
			code[0]=citycode.code;
		}
		if(!strcmp(citycode.city,Ficity))
		{
			code[1]=citycode.code;
		}
		if(code[0]!=-1&&code[1]!=-1)
		{
			break;
		}
	}
	fclose(fp);
	      //ȡ��վ��Ϣ 
	for(i=0;i<2;i++)
	{
		itoa(code[i],_code[i],10);
	}
	strcpy(path,"C:\\PRJ\\File\\CIST\\");
	strcat(path,_code[0]);
	fp=fopen(path,"r");
	for(i=0;!feof(fp)&&i<10;i++)
	{
		if(fread(tempSt[i],10,1,fp)!=1)
		{
			tempSt[i][0]='\0';
		}
	}
	fclose(fp);
	strcpy(path,"C:\\PRJ\\File\\CIST\\");
	strcat(path,_code[1]);
	fp=fopen(path,"r");
	for(i=0;!feof(fp)&&i<10;i++)
	{
		if(fread(tempFi[i],10,1,fp)!=1)
		{
			tempFi[i][0]='\0';
		}
	}
	fclose(fp);
	/*��ǩģʽ�µ�����*/
	if(code[0]==-1||code[1]==-1)
	{
		strcpy(tempSt[0],Stcity);
		strcpy(tempFi[0],Ficity);
		tempSt[1][0]='\0';
		tempFi[1][0]='\0';
	}

	creatGraph(&graph,&Arc,GD,ST,num);//����ͼ 
	net.gr=graph;
	net.ar=Arc;
	/*����ջ��*/
	if((p=(StackNode *)malloc(sizeof(StackNode)))==NULL)
	{
		printf("error!");
		getch();
		exit(1); 
	}
	p->next=NULL;
	buttom=p;
	for(i=0;tempSt[i][0]!='\0'&&i<10;i++)//������� 
	{
		strcpy(Ststation,tempSt[i]);
		for(j=0;tempFi[j][0]!='\0'&&j<10;j++)
		{
			strcpy(Fistation,tempFi[j]);
  		    Gtemp=graph;
  		    STnum=0;//���ó�վ���� 
			FInum=0;
			while(Gtemp!=NULL)//Gtempָ��ǰ��վ�ڵ� 
			{	
				if(!strcmp(Gtemp->station,Ststation)&&!STnum)//ȷ����ʼվ��� 
				{
					STnum=Gtemp->SNnum;
				}
				if(!strcmp(Gtemp->station,Fistation)&&!FInum)//ȷ���յ�վ��� 
				{	
					FInum=Gtemp->SNnum;
				}
				if(STnum&&FInum)
				{
					break;
				}
				Gtemp=Gtemp->Nextstation;
			}
			if(Gtemp==NULL)//�Ļ���վ 
			{
				continue;	
			}
			
			if(head==NULL)
			{
				DFS(&head,&net,STnum,FInum,&p,buttom,&q,0);
				connect=head;
			}
			else
			{
				DFS(&(connect->nextHead),&net,STnum,FInum,&p,buttom,&q,0);
			}
			while(connect->nextHead!=NULL)
			{
				connect=connect->nextHead;
			}
			while(p!=buttom)//�������ջ 
			{
				popStack(&p);
			}
		}
	}
	free(buttom);//��ձ���ջ�� 
	destroyGraph(graph,Arc);//�ͷ�ͼ 
	return head;
}

/*·�ߵ�������������㷨*/
/*pΪ����ָ�룬qΪ���βָ�룬����buttom��q��ջ�ռ任ȡ����ʱ��*/
int DFS(RESULT **head,NET *pnet,NUMBER STnum,NUMBER FInum,StackNode **p,StackNode *buttom,StackHead **q,int reverse)//����0��ʾ�Ҳ����ó��� 
{
	GraphNode *m=pnet->gr;
	ArcNode *n=pnet->ar;
	
	while(m->SNnum!=STnum)//mָ��ǰ��վ�ڵ� 
	{
		m=m->Nextstation;
		if(m==NULL)
		{
			return 0;//��ʾ�Ҳ����ó�վ 
		}
	}
	if(STnum==FInum)//�������յ�վ
	{
		pushStack(p,m->station,"###");
		if(*head==NULL)
		{
			if((*q=(StackHead *)malloc(sizeof(StackHead)))==NULL)
			{
				printf("error!");
				getch();
				exit(1); 
			} 
			(*q)->buttom=NULL;
			(*q)->nextHead=NULL;
			*head=*q;
		}
		else 
		{
			if(((*q)->nextHead=(StackHead *)malloc(sizeof(StackHead)))==NULL)
			{
				printf("error!");
				getch(); 
				exit(1); 
			} 
			(*q)=(*q)->nextHead;
			(*q)->buttom=NULL;
			(*q)->nextHead=NULL;
		}
		copyStack(&((*q)->buttom),buttom);
		popStack(p);//���»�ԭ ����ָ�� 
		return 1;
	}
	while(1)//�����ó�վ���л��ϵ���Ϣ 
	{
		while(STnum-(n->STSnum))
		{
			n=n->NextArc;
			if(n==NULL)
			{
				return 1;//�ýڵ㻡��ȫ���� 
			} 
		}
		if(strcmp((((*p)->next)->trainnum),n->trainnum)&&(*p)->next!=NULL)//��һ�εĳ��κ͵�ǰ���β�һ�� 
		{
			if(reverse)//���������ת�� (�ı���ж�ֵ���趨����ת�����������������ѭ������������ڳ˿���˵�ǲ���Ҫ��)
			{
				return 1;
			}
			reverse++;//ת���������� 
		}
		pushStack(p,m->station,n->trainnum);//��վ��Ϣ��ջ
		DFS(head,pnet,n->FISnum,FInum,p,buttom,q,reverse);//�ݹ����� 
		popStack(p);//��վ��Ϣ��ջ 	
		if(strcmp((((*p)->next)->trainnum),n->trainnum)&&(*p)->next!=NULL)//��һ�εĳ��κ���һ�εĳ��β�һ�� 
		{
			reverse--;//ת���������� 
		}
		
		n=n->NextArc;    //����  
		if(n==NULL)
		{
			return 1;
		} 
	}	
}

/*������������*/ 
void destroyGraph(GRAPH *graph,ARC *Arc)
{
	GRAPH *Gtemp=graph;
	ARC *Atemp=Arc;
	while(graph!=NULL)
	{
		Gtemp=graph;
		graph=graph->Nextstation;
		free(Gtemp);
	}
	while(Arc!=NULL)
	{
		Atemp=Arc;
		Arc=Arc->NextArc;
		free(Atemp);
	}
}

/*���ٽ��*/ 
void destroyStackHead(StackHead *head)
{
	StackHead *temp=head;
	StackNode *ptemp=NULL;
	while(temp!=NULL)
	{
		ptemp=temp->buttom;
		while(ptemp!=NULL)
		{
			temp->buttom=ptemp->next;
			free(ptemp);
			ptemp=temp->buttom;
		}
		head=temp->nextHead;
		free(temp);
		temp=head;
	} 
}

/*����ͼ*/ 
void creatGraph(GRAPH **graph,ARC **Arc,int GD,int ST,int num)
{
	char TName[301][6];//�趨�������������μ�¼
	int number=0,i;
	NUMBER Sr_num=0;//��վ���к� 
	GraphNode *station=NULL;
	ArcNode *arc=NULL;
	KT_train KTtrain;
	G_train Gtrain;
	Z_train Ztrain;
	D_train Dtrain;
	
	number=infoTname(TName,GD,ST,num);
	for(i=0;i<number;i++)
	{
		switch(TName[i][0])
		{
		case 'Z':
			Z_read(TName[i],&Ztrain,num);
			dealZtrain(graph,Arc,&station,&arc,&Ztrain,&Sr_num);
			break;
		case 'G':
			G_read(TName[i],&Gtrain,num);
			dealGtrain(graph,Arc,&station,&arc,&Gtrain,&Sr_num);
			break;
		case 'D':
			D_read(TName[i],&Dtrain,num);
			dealDtrain(graph,Arc,&station,&arc,&Dtrain,&Sr_num);
			break;
		default:
			KT_read(TName[i],&KTtrain,num);
			dealKTtrain(graph,Arc,&station,&arc,&KTtrain,&Sr_num);
			break;
		}
	}	
}


/*���ֳ����齨��������*/ 
void dealZtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,Z_train *Ztrain,NUMBER *Sr_num) 
{
	int exist1=0,exist2=0;
	GraphNode *p=*graph,*pNew=NULL;
	ArcNode *arcNew=NULL;
	NUMBER num1=0,num2=0;
	
	while(p!=NULL)//�жϳ�վ�ڵ��Ƿ�����ͼ�� 
	{
		if(!strcmp(p->station,Ztrain->station[0])&&!exist1)
		{
			num1=p->SNnum;
			exist1=1;
			p=*graph;
		}
		if(!strcmp(p->station,Ztrain->station[1])&&!exist2)
		{
			num2=p->SNnum;
			exist2=1;
			p=*graph;
		}
		if(exist1&&exist2)
		{
			break;
		}
		p=p->Nextstation;
	}
	if(!exist1)//�½���վ�ڵ� 
	{
		if((pNew=malloc(sizeof(GraphNode)))==NULL)
		{
			printf("Rrror!");
			getch();
			exit(1);
		}
		(*Sr_num)++;
		pNew->SNnum=*Sr_num;
		pNew->Nextstation=NULL;
		num1=pNew->SNnum;
		strcpy(pNew->station,Ztrain->station[0]);
		if(*station!=NULL)
		{
			(*station)->Nextstation=pNew;
		} 
		*station=pNew;
		if(*graph==NULL)
	    {
		    *graph=pNew;
	    }
	}
	
	if(!exist2)//�½���վ�ڵ� 
	{
		if((pNew=malloc(sizeof(GraphNode)))==NULL)
		{
			printf("Rrror!");
			getch();
			exit(1);
		}
		(*Sr_num)++;
		pNew->SNnum=*Sr_num;
		pNew->Nextstation=NULL;
		num2=pNew->SNnum;
		strcpy(pNew->station,Ztrain->station[1]);
		if(*station!=NULL)
		{
			(*station)->Nextstation=pNew;
		} 
		*station=pNew;
	}
	if((arcNew=malloc(sizeof(ArcNode)))==NULL)//�½���������վ�Ļ� 
	{
		printf("Error!");
		getch();
		exit(1);
	}
	arcNew->STSnum=num1;
	arcNew->FISnum=num2;
	arcNew->NextArc=NULL;
	strcpy(arcNew->trainnum,Ztrain->tra_num);
	if(*arc!=NULL)
	{
		(*arc)->NextArc=arcNew;
	}
	if(*Arc==NULL)
	{
		*Arc=arcNew;
	}
	*arc=arcNew;
}

void dealKTtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,KT_train *KTtrain,NUMBER *Sr_num)
{
	int exist=0,i;
	GraphNode *p=*graph,*pNew=NULL;
	ArcNode *arcNew=NULL;
	NUMBER num1=0,num2=0; 
	
	for(i=0;strcmp(KTtrain->start_time[(i==0)?0:(i-1)],"###");i++)//��֤���г�վ������ͼ 
	{
		exist=0;//�ı䳵վ�� ���ڱ�־����
		while(p!=NULL)
		{
			if(!strcmp(p->station,KTtrain->station[i])&&!exist)
			{
				num2=p->SNnum;
				exist=1;
				break;
			}
			p=p->Nextstation;
		}
		p=*graph;
		if(!exist)
		{
			if((pNew=(GraphNode *)malloc(sizeof(GraphNode)))==NULL)
	  	    {   
			    printf("Rrror!");
			    getch();
			    exit(1);
		    }
		    (*Sr_num)++;
			pNew->SNnum=*Sr_num;
			pNew->Nextstation=NULL;
			num2=pNew->SNnum;
			strcpy(pNew->station,KTtrain->station[i]);
			if((*station)!=NULL)
			{
				(*station)->Nextstation=pNew;
			} 
			*station=pNew;
			if(*graph==NULL)
	        {
		        *graph=pNew;
	        }
		}
		if(i)
		{
			if((arcNew=(ArcNode *)malloc(sizeof(ArcNode)))==NULL)//�½���������վ�Ļ� 
			{
				printf("Error!");
				getch();
				exit(1);
			}
			arcNew->STSnum=num1;
			arcNew->FISnum=num2;
			arcNew->NextArc=NULL;
			strcpy(arcNew->trainnum,KTtrain->tra_num);
			if(*arc!=NULL)
			{
				(*arc)->NextArc=arcNew;
			}
			*arc=arcNew;
			if(*Arc==NULL)
			{
				*Arc=arcNew;
			}
		}
		num1=num2;
	}
}

void dealDtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,D_train *Dtrain,NUMBER *Sr_num)
{
	int exist=0,i;
	GraphNode *p=*graph,*pNew=NULL;
	ArcNode *arcNew=NULL;
	NUMBER num1=0,num2=0; 
	
	for(i=0;strcmp(Dtrain->start_time[(i==0)?0:(i-1)],"###");i++)
	{
		exist=0;//�ı䳵վ�� ���ڱ�־����
		while(p!=NULL)
		{
			if(!strcmp(p->station,Dtrain->station[i])&&!exist)
			{
				num2=p->SNnum;
				exist=1;
				break;
			}
			p=p->Nextstation;
		}
		p=*graph;
		if(!exist)
		{
			if((pNew=malloc(sizeof(GraphNode)))==NULL)
	  	    {   
			    printf("Rrror!");
			    getch();
			    exit(1);
		    }
		    (*Sr_num)++;
			pNew->SNnum=*Sr_num;
			pNew->Nextstation=NULL;
			num2=pNew->SNnum;
			strcpy(pNew->station,Dtrain->station[i]);
			if(*station!=NULL)
			{
				(*station)->Nextstation=pNew;
			} 
			*station=pNew;
			if(*graph==NULL)
	        {
		        *graph=pNew;
	        }
		}
		if(i)
		{
			if((arcNew=malloc(sizeof(ArcNode)))==NULL)//�½���������վ�Ļ� 
			{
				printf("Error!");
				getch();
				exit(1);
			}
			arcNew->STSnum=num1;
			arcNew->FISnum=num2;
			arcNew->NextArc=NULL;
			strcpy(arcNew->trainnum,Dtrain->tra_num);
			if(*arc!=NULL)
			{
				(*arc)->NextArc=arcNew;
			}
			*arc=arcNew;
			if(*Arc==NULL)
			{
				*Arc=arcNew;
			}
		}
		num1=num2;
	}
}

void dealGtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,G_train *Gtrain,NUMBER *Sr_num)
{
	int exist,i;
	GraphNode *p=*graph,*pNew=NULL;
	ArcNode *arcNew=NULL;
	NUMBER num1=0,num2=0; 
	
	for(i=0;strcmp(Gtrain->start_time[(i==0)?0:(i-1)],"###");i++)
	{
		exist=0;//�ı䳵վ�� ���ڱ�־���� 
		while(p!=NULL)
		{
			if(!strcmp(p->station,Gtrain->station[i])&&!exist)
			{
				num2=p->SNnum;
				exist=1;
				break;
			}
			p=p->Nextstation;
		}
		p=*graph;
		if(!exist)
		{
			if((pNew=malloc(sizeof(GraphNode)))==NULL)
	  	    {   
			    printf("Error!");
			    getch();
			    exit(1);
		    }
		    (*Sr_num)++;
			pNew->SNnum=*Sr_num;
			pNew->Nextstation=NULL;
			num2=pNew->SNnum;
			strcpy(pNew->station,Gtrain->station[i]);
			if(*station!=NULL)
			{
				(*station)->Nextstation=pNew;
			} 
			*station=pNew;
			if(*graph==NULL)
	        {
		        *graph=pNew;
	        }
		}
		if(i)
		{
			if((arcNew=malloc(sizeof(ArcNode)))==NULL)//�½���������վ�Ļ� 
			{
				printf("Error!");
				getch();
				exit(1);
			}
			arcNew->STSnum=num1;
			arcNew->FISnum=num2;
			arcNew->NextArc=NULL;
			strcpy(arcNew->trainnum,Gtrain->tra_num);
			if(*arc!=NULL)
			{
				(*arc)->NextArc=arcNew;
			}
			*arc=arcNew;
			if(*Arc==NULL)
			{
				*Arc=arcNew;
			}
		}
		num1=num2;
	}
}

/*��ȡ������Ϣ,���ؼ�¼����*/
int infoTname(char (*name)[6],int GD,int ST,int num)
{
	FILE *fp;
	char path[35]={"C:\\PRJ\\File\\data"},date[3];
	int i,j,len;
	char tempName[7];
	
	itoa(num,date,10);
	strcat(path,date);
	strcat(path,"\\TNAME.DAT");
	fp=fopen(path,"r");
	for(i=0;i<300&&!feof(fp);i++)
	{
		fgets(tempName,7,fp);
		if(tempName[0]!='K'&&tempName[0]!='T'&&tempName[0]!='Z'&&tempName[0]!='G'&&tempName[0]!='D')//������󳵴�д�� 
		{
			fclose(fp);
			return i;
		}
		len=strlen(tempName);
		tempName[len-1]='\0';//�����ո�
		if(GD)//ֻ������������ 
		{
			if(tempName[0]=='G'||tempName[0]=='D')
			{
				strcpy(name[i],tempName); 
				i++;
			}
			i--;
		}
		else 
		{
			strcpy(name[i],tempName); 
		} 
	}
	if(i==300)
	{
		printf("Too many Train!");
	}
	fclose(fp);
	return (i-1);//�ļ�β����һ�� 
}
