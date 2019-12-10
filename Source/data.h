#ifndef __DATA_H__
#define __DATA_H__

#define TURE 1
#define FALSE 0
/*�쳵�ؿ�𳵼�¼*/
typedef struct
{
	char tra_num[6];//���� 
	char station[31][10];//30��վ������ 
	char city[31][10];//���ڳ��� 
	char arrive_time[30][6];//��վʱ�� 
	char start_time[31][6];//����ʱ��
	char hardseat_fee[30][4];//����һվӲ�����ã�Ԫ��
	char hardsleeper_fee[30][4];//����һվӲ�Է��ã�Ԫ��
	char softsleeper_fee[30][4]; //����һվ���Է��ã�Ԫ��
	char hard_seat[30][6];//����һվӲ����
	char hard_sleeper[30][6];//����һվӲ����
	char soft_sleeper[30][6];//����һվ������ 
}KT_train; 

/*ֱ���г���¼*/ 
typedef struct
{
	char tra_num[6];//���� 
	char station[2][10];//2��վ������
	char city[2][10];//���ڳ��� 
	char start_time[6];//ʼ��ʱ�� 
	char arrive_time[6];//�յ�ʱ�� 
	char hardseat_fee[4];//����һվӲ�����ã�Ԫ��
	char hardsleeper_fee[4];//����һվӲ�Է��ã�Ԫ��
	char softsleeper_fee[4]; //����һվ���Է��ã�Ԫ��
	char hard_seat[6];//����һվӲ����
	char hard_sleeper[6];//����һվӲ����
	char soft_sleeper[6];//����һվ������  
}Z_train;
 
/*������¼*/ 
typedef struct
{
	char tra_num[6];//���� 
	char station[31][10];//30��վ������ 
	char city[31][10];//���ڳ��� 
	char arrive_time[30][6];//��վʱ�� 
	char start_time[31][6];//����ʱ��
	char fclass_fee[30][4];//����һվһ�������ã�Ԫ��
	char sclass_fee[30][4];//����һվ���������ã�Ԫ�� 
	char f_seat[30][6];//����һվһ������
	char s_seat[30][6];//����һվ��������
}D_train;

/*������¼*/ 
typedef struct
{
	char tra_num[6];//���� 
	char station[31][10];//30��վ������ 
	char city[31][10];//���ڳ��� 
	char arrive_time[30][6];//��վʱ�� 
	char start_time[31][6];//����ʱ��
	char fclass_fee[30][4];//����һվһ�������ã�Ԫ��
	char sclass_fee[30][4];//����һվ���������ã�Ԫ��
	char business_fee[30][4];//����һվ���������ã�Ԫ�� 
	char f_seat[30][6];//����һվһ������
	char s_seat[30][6];//����һվ��������
	char b_seat[30][6];//����һվ�������� 
}G_train;


typedef struct
{
	int code;
	char city[10];
}CITYCODE;

int KT_save(char *T_num,KT_train *p,int page,int (*length)[9],int *lengthnum,int num,int k);
int Z_save(char *T_num,Z_train *p,int (*length)[2],int *lengthnum,int k);
int G_save(char *T_num,G_train *p,int page,int (*length)[9],int *lengthnum,int num,int k);
int D_save(char *T_num,D_train *p,int page,int (*length)[9],int *lengthnum,int num,int k);
int KT_read(char *T_num,KT_train *train,int num);
int Z_read(char *T_num,Z_train *train,int num);
int G_read(char *T_num,G_train *train,int num);
int D_read(char *T_num,D_train *train,int num);
int SearchTrain(char *T_num,int num);
int DeleteTrain(char *T_num,int num);

#endif

