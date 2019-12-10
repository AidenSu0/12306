#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <stdio.h>
#include "data.h"



/**********************���ø�����ͼ���ڽӾ�����ڽ���
��ʵ����һ���̶Ƚ�ʡ���ڴ�(����Ϊ�˷������ڽӾ�������
����վ���Ʊ�Ҫ�������г�վ�ĵ�ַ��������ʽ������СҪ�˸�
�ֽ�)���������ٶ���Խ�������Խ�����ĳ�վ�����ٶȲ���Ϊ
���ԣ����ڶ��ڴ��С������£�����ֵ�õ�**********/ 


/*��������Ϣ�϶�ʱ������վ�����ܻ���Ĭ�϶��ڴ����ƣ����ܳ����ڴ����������
���������޴���65535����վ��Ϣ����������Χ������� ������ȡ��������ʽ*/

//��Ų�����NUMBER���ڽ�ʡϵͳ���ڴ� 
typedef struct A
{
	unsigned short int STSnum;//��ʼ��վ�� 
	unsigned short int FISnum;//���ﳵվ�� 
	char trainnum[6];//�ó�վ���Ӧ���� 
	struct A *NextArc;
}ArcNode;

typedef struct B
{
	unsigned short int SNnum;//��վ��� 
	char station[10];//��վ�� 
	struct B *Nextstation;
}GraphNode;

/*Ϊ����������һ����ǰ������ʣ���ջ��˫������Ľ� */
typedef struct C
{
	char station[10];
	char trainnum[6];
	struct C *next;
	struct C *last;
}StackNode;


/*����������н����ջ��*/
typedef struct D
{
	StackNode *buttom;
	struct D *nextHead;
}StackHead;

typedef struct
{
	GraphNode *gr;
	ArcNode *ar;
}NET;

typedef StackHead RESULT;
typedef GraphNode GRAPH;
typedef ArcNode ARC; 
typedef unsigned short int NUMBER;

/*��ջ����*/
void pushStack(StackNode **top,char *station,char *trainnum);
/*��ջ����*/ 
void popStack(StackNode **top);

void copyStack(StackNode **buttom1,StackNode *buttom2);

RESULT *Deep_search(char *StStaion,char *Fistation,int GD,int ST,int num);

int DFS(RESULT **head,NET *pnet,NUMBER STnum,NUMBER FInum,StackNode **p,StackNode *buttom,StackHead **q,int reverse);//����0��ʾ�Ҳ����ó���

void destroyGraph(GRAPH *graph,ARC *Arc);//�ͷ�ͼ 

void destroyStackHead(StackHead *head);//�ͷ�������� 

void creatGraph(GRAPH **graph,ARC **Arc,int GD,int ST,int num);//����ͼ 

void dealZtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,Z_train *Ztrain,NUMBER *Sr_num);

void dealKTtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,KT_train *KTtrain,NUMBER *Sr_num);

void dealDtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,D_train *Dtrain,NUMBER *Sr_num);

void dealGtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,G_train *Gtrain,NUMBER *Sr_num);

/*��ȡ������Ϣ,���ؼ�¼����*/
int infoTname(char (*name)[6],int GD,int ST,int num);

#endif

