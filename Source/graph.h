#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <stdio.h>
#include "data.h"



/**********************采用改良的图的邻接矩阵比邻接列
表实现能一定程度节省堆内存(由于为了方便在邻接矩阵下搜
索车站，势必要建立所有车站的地址索引，链式索引最小要八个
字节)，但搜索速度相对较慢，且越孤立的车站排列速度差尤为
明显，但在堆内存很小的情况下，这是值得的**********/ 


/*当车次信息较多时（上万车站），受机器默认堆内存限制，可能出现内存溢出的现象
该搜索上限处理65535条车站信息，若超出范围或堆限制 将不采取该搜索方式*/

//编号采用你NUMBER意在节省系统堆内存 
typedef struct A
{
	unsigned short int STSnum;//起始车站好 
	unsigned short int FISnum;//到达车站号 
	char trainnum[6];//该车站间对应车次 
	struct A *NextArc;
}ArcNode;

typedef struct B
{
	unsigned short int SNnum;//车站编号 
	char station[10];//车站名 
	struct B *Nextstation;
}GraphNode;

/*为了能如数组一样从前往后访问，将栈向双向链表改进 */
typedef struct C
{
	char station[10];
	char trainnum[6];
	struct C *next;
	struct C *last;
}StackNode;


/*用来存放所有结果的栈底*/
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

/*入栈函数*/
void pushStack(StackNode **top,char *station,char *trainnum);
/*出栈函数*/ 
void popStack(StackNode **top);

void copyStack(StackNode **buttom1,StackNode *buttom2);

RESULT *Deep_search(char *StStaion,char *Fistation,int GD,int ST,int num);

int DFS(RESULT **head,NET *pnet,NUMBER STnum,NUMBER FInum,StackNode **p,StackNode *buttom,StackHead **q,int reverse);//返回0表示找不到该城市

void destroyGraph(GRAPH *graph,ARC *Arc);//释放图 

void destroyStackHead(StackHead *head);//释放搜索结果 

void creatGraph(GRAPH **graph,ARC **Arc,int GD,int ST,int num);//创建图 

void dealZtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,Z_train *Ztrain,NUMBER *Sr_num);

void dealKTtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,KT_train *KTtrain,NUMBER *Sr_num);

void dealDtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,D_train *Dtrain,NUMBER *Sr_num);

void dealGtrain(GRAPH **graph,ARC **Arc,GraphNode **station,ArcNode **arc,G_train *Gtrain,NUMBER *Sr_num);

/*获取车次信息,返回记录条数*/
int infoTname(char (*name)[6],int GD,int ST,int num);

#endif

