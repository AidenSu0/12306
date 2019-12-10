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
/*车站网的深度优先搜索*/ 
/*作者：苏新明*/
/*调用Deep_search（）返回结果头指针*/ 
/*========================*/

/*遍历入栈函数*/
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

/*遍历出栈函数*/ 
void popStack(StackNode **top)
{
	StackNode *temp=*top;
	*top=(*top)->next;
	(*top)->last=NULL;
	free(temp);
}

/*将栈2复制到栈1,栈1只需传入NULL指针,栈1实质为双向链表 不设栈顶指针*/
/*后一数据为->next*/ 
void copyStack(StackNode **buttom1,StackNode *buttom2) 
{
	StackNode *pNew=NULL,*pEnd=*buttom1,*position=buttom2;	
	while(position->last!=NULL) 
	{
		if((pNew=(StackNode *)malloc(sizeof(StackNode)))==NULL)//结果指针域 
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

/*搜索预处理*/ 
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
	StackNode *p=NULL,*buttom=NULL;//遍历指针 
	
	memset(tempSt,'\0',100);
	memset(tempFi,'\0',100);
	/*获取两城市车站*/ 
	fp=fopen("C:\\PRJ\\File\\CIST\\citycode","rb");
	while(!feof(fp))//匹配城市 
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
	      //取车站信息 
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
	/*改签模式下的搜索*/
	if(code[0]==-1||code[1]==-1)
	{
		strcpy(tempSt[0],Stcity);
		strcpy(tempFi[0],Ficity);
		tempSt[1][0]='\0';
		tempFi[1][0]='\0';
	}

	creatGraph(&graph,&Arc,GD,ST,num);//创建图 
	net.gr=graph;
	net.ar=Arc;
	/*设置栈底*/
	if((p=(StackNode *)malloc(sizeof(StackNode)))==NULL)
	{
		printf("error!");
		getch();
		exit(1); 
	}
	p->next=NULL;
	buttom=p;
	for(i=0;tempSt[i][0]!='\0'&&i<10;i++)//组合搜索 
	{
		strcpy(Ststation,tempSt[i]);
		for(j=0;tempFi[j][0]!='\0'&&j<10;j++)
		{
			strcpy(Fistation,tempFi[j]);
  		    Gtemp=graph;
  		    STnum=0;//重置车站代号 
			FInum=0;
			while(Gtemp!=NULL)//Gtemp指向当前车站节点 
			{	
				if(!strcmp(Gtemp->station,Ststation)&&!STnum)//确定起始站序号 
				{
					STnum=Gtemp->SNnum;
				}
				if(!strcmp(Gtemp->station,Fistation)&&!FInum)//确定终点站序号 
				{	
					FInum=Gtemp->SNnum;
				}
				if(STnum&&FInum)
				{
					break;
				}
				Gtemp=Gtemp->Nextstation;
			}
			if(Gtemp==NULL)//改换车站 
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
			while(p!=buttom)//清除遍历栈 
			{
				popStack(&p);
			}
		}
	}
	free(buttom);//清空遍历栈底 
	destroyGraph(graph,Arc);//释放图 
	return head;
}

/*路线的深度优先搜索算法*/
/*p为遍历指针，q为结果尾指针，传入buttom和q用栈空间换取搜索时间*/
int DFS(RESULT **head,NET *pnet,NUMBER STnum,NUMBER FInum,StackNode **p,StackNode *buttom,StackHead **q,int reverse)//返回0表示找不到该城市 
{
	GraphNode *m=pnet->gr;
	ArcNode *n=pnet->ar;
	
	while(m->SNnum!=STnum)//m指向当前车站节点 
	{
		m=m->Nextstation;
		if(m==NULL)
		{
			return 0;//表示找不到该车站 
		}
	}
	if(STnum==FInum)//搜索到终点站
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
		popStack(p);//向下还原 遍历指针 
		return 1;
	}
	while(1)//搜索该车站所有弧上的信息 
	{
		while(STnum-(n->STSnum))
		{
			n=n->NextArc;
			if(n==NULL)
			{
				return 1;//该节点弧已全遍历 
			} 
		}
		if(strcmp((((*p)->next)->trainnum),n->trainnum)&&(*p)->next!=NULL)//上一次的车次和当前车次不一样 
		{
			if(reverse)//不允许二次转车 (改变该判断值可设定允许转车次数，但可能造成循环搜索，这对于乘客来说是不必要的)
			{
				return 1;
			}
			reverse++;//转车次数增加 
		}
		pushStack(p,m->station,n->trainnum);//经站信息入栈
		DFS(head,pnet,n->FISnum,FInum,p,buttom,q,reverse);//递归搜索 
		popStack(p);//经站信息出栈 	
		if(strcmp((((*p)->next)->trainnum),n->trainnum)&&(*p)->next!=NULL)//上一次的车次和下一次的车次不一样 
		{
			reverse--;//转车次数减少 
		}
		
		n=n->NextArc;    //换弧  
		if(n==NULL)
		{
			return 1;
		} 
	}	
}

/*销毁搜索网络*/ 
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

/*销毁结果*/ 
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

/*创建图*/ 
void creatGraph(GRAPH **graph,ARC **Arc,int GD,int ST,int num)
{
	char TName[301][6];//设定上限三百条车次记录
	int number=0,i;
	NUMBER Sr_num=0;//车站序列号 
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


/*四种车次组建搜索网络*/ 
void dealZtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,Z_train *Ztrain,NUMBER *Sr_num) 
{
	int exist1=0,exist2=0;
	GraphNode *p=*graph,*pNew=NULL;
	ArcNode *arcNew=NULL;
	NUMBER num1=0,num2=0;
	
	while(p!=NULL)//判断车站节点是否已在图中 
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
	if(!exist1)//新建车站节点 
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
	
	if(!exist2)//新建车站节点 
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
	if((arcNew=malloc(sizeof(ArcNode)))==NULL)//新建连接两车站的弧 
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
	
	for(i=0;strcmp(KTtrain->start_time[(i==0)?0:(i-1)],"###");i++)//保证所有车站遍历入图 
	{
		exist=0;//改变车站后 存在标志清零
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
			if((arcNew=(ArcNode *)malloc(sizeof(ArcNode)))==NULL)//新建连接两车站的弧 
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
		exist=0;//改变车站后 存在标志清零
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
			if((arcNew=malloc(sizeof(ArcNode)))==NULL)//新建连接两车站的弧 
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
		exist=0;//改变车站后 存在标志清零 
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
			if((arcNew=malloc(sizeof(ArcNode)))==NULL)//新建连接两车站的弧 
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

/*获取车次信息,返回记录条数*/
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
		if(tempName[0]!='K'&&tempName[0]!='T'&&tempName[0]!='Z'&&tempName[0]!='G'&&tempName[0]!='D')//避免错误车次写入 
		{
			fclose(fp);
			return i;
		}
		len=strlen(tempName);
		tempName[len-1]='\0';//消除空格
		if(GD)//只搜索高铁动车 
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
	return (i-1);//文件尾会多读一次 
}
