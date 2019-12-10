#include "order.h"

int visual_order(int page,USER *user)
{
	int num=0,i;
	ORDER *order=user->order;
	for(i=0;i<page;i++)
	{
		order=order->next;
		order=order->next;
	}
	for(i=0;i<2&&order!=NULL;i++)
	{
		ticket(80,175+i*105);
		puthz(100,217+i*105,order->StartStation,1,16,_BLACK);
		puthz(337,217+i*105,order->FinalStation,1,16,_BLACK);
		puthz(100,195+i*105,order->StartTime,1,16,_BLACK);
		puthz(315,195+i*105,order->FinalTime,1,16,_BLACK);
		puthz(230,247+i*105,order->seat_kind,1,16,_BLACK);
		puthz(235,195+i*105,order->TrainNum,1,16,_BLACK);
		puthz(100,240+i*105,order->Identity,1,16,_BLACK);
		order=order->next;
	}
	if(order!=NULL)
	{
		puthz(550,360,"����",1,16,_WHITE);
		i++;
	}
	return i;
}

void refund(int ticket,USER *user)
{
	ORDER *temp=user->order,*temp1=NULL,*del;
	int i,mon,day,k;
	char _mon[3]={'\0','\0','\0'},_day[3]={'\0','\0','\0'};
	TIME _tm;
	StackNode *ptemp=NULL;
	StackHead *head=NULL,*htemp=NULL;
	
	for(i=0;i<ticket-1;i++)
	{
		temp=temp->next;
	}
	if(ticket) temp1=temp->next;
	else temp1=temp;
	/*��Ʊ����������*/
	_gettime(&_tm);
	for(i=0;i<2;i++)//ȡ����ʱ�� 
	{
		_mon[i]=temp1->StartTime[i];//�·� 
		_day[i]=temp1->StartTime[4+i];//��
	}
	mon=atoi(_mon);
	day=atoi(_day);
	k=daysDifference(_tm.month,_tm.day,mon,day)+1;//���������� 
	head=Deep_search(temp1->StartStation,temp1->FinalStation,0,0,k);//������� 
	for(htemp=head;htemp!=NULL;htemp=htemp->nextHead)//�ҵ���Ӧ�������������Ʊ���� 
	{
		if(!strcmp(htemp->buttom->trainnum,temp1->TrainNum))//���ζ�Ӧ��ȷ 
		{
			for(ptemp=htemp->buttom;ptemp->next!=NULL;ptemp=ptemp->next)
			{
				if(ptemp->last!=NULL&&strcmp(ptemp->last->trainnum,ptemp->trainnum))//��·������ת������ 
				{
					break;
				}
			}
			if(ptemp->next==NULL)//ֱ����ȷ���� 
			{
				/*��Ʊ����*/
				if(!strcmp(temp1->seat_kind,"Ӳ��")||!strcmp(temp1->seat_kind,"������"))
				{
					change_data(htemp->buttom,0,1,k,1);
				}
				else if(!strcmp(temp1->seat_kind,"Ӳ��")||!strcmp(temp1->seat_kind,"һ����"))
				{
					change_data(htemp->buttom,1,1,k,1);
				}
				else if(!strcmp(temp1->seat_kind,"����")||!strcmp(temp1->seat_kind,"������"))
				{
					change_data(htemp->buttom,2,1,k,1);
				}
				break; 
			}
		}
	}
	destroyStackHead(head);//ɾ������� 
	/*ɾ����Ʊ����*/
	if(ticket==0)
	{
		user->order=temp->next;
		free(temp);
	}
	else
	{
		del=temp->next;//��ɾ���ĳ�Ʊ��Ϣ 
		temp->next=del->next;
		free(del); 
	}
	setcolor(_WHITE);
	bar(200,150,440,370);
	setcolor(GTcolor(30));
	rectangle(200,150,440,370);
	CK_right(320,240);
	puthz(284,280,"��Ʊ�ɹ�",1,16,GTcolor(30));
	puthz(252,310,"Ӧ�˻��������",1,16,GTcolor(30));
	puthz(244,340,"�����հ�ԭ·���˻�",1,16,GTcolor(30));
	delay(2000); 
}

/*��ǩ����*/ 
void reschedul(int ticket,USER *user,int *xnow,int *ynow,int *mark)
{
	ORDER *order=user->order;
	char _mon[3]={'\0','\0','\0'},_day[3]={'\0','\0','\0'};
	int i,j=0,k=0;
	
	*mark=0;
	for(i=0;i<ticket;i++)
	{
		order=order->next;
	}
	for(i=0;i<6;i++)
	{
		if(order->StartTime[i]>=48&&order->StartTime[i]<=57&&i<2)
		{
			_mon[j]=order->StartTime[i];
			j++;
		}
		else if(order->StartTime[i]>=48&&order->StartTime[i]<=57&&i>1)
		{
			_day[k]=order->StartTime[i];
			k++;
		}	
	}
	f_look(user,order->StartStation,order->FinalStation,0,0,_mon,_day,xnow,ynow,mark);
	refund(ticket,user);
}
