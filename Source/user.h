#ifndef __USER_H__
#define __USER_H__

typedef struct OR//订单的数据结构 
{
	char TrainNum[6];
	char seat_kind[8];
	char StartStation[10];
	char FinalStation[10];
	char StartTime[18];
	char FinalTime[18];
	char Identity[10];
	struct OR *next;
}ORDER;

typedef struct
{
	char identity_num[22];
	char name[22];
	char sex[4];
	char identity[6];
	char university[22];
	char stu_num[22];
	char entry_time[22];
}ID;


typedef struct US//账户的数据结构 
{
	char account_name[18];
	char password[17];
	char AllIdentity[10][10];
	char name[22];
	char sex[3];
	char idnum[22];
	char phone_num[22];
	char signature[42];//个性签名（最大20个汉字）
	char message[10][6]; //发车提醒 
	struct OR *order;
}USER;


void f_login_loading(char *account,USER *user);
void login_loading();
int f_UserControl(char *account,int *xnow,int *ynow,int *mark);
int f_my_order(USER *user,int *xnow,int *ynow,int *mark);
int f_identity(USER *user,int *xnow,int *ynow,int *mark);
int f_add_identity(USER *user,int *xnow,int *ynow,int *mark);
int f_my_account(USER *user,int *xnow,int *ynow,int *mark);
int f_time_table(int *xnow,int *ynow,int *mark);
int f_message(USER *user,int *xnow,int *ynow,int *mark);
int f_settings(USER *user,int *xnow,int *ynow,int *mark);
int f_feedback(int *xnow,int *ynow,int *mark);
int f_about(int *xnow,int *ynow,int *mark);
int f_about(int *xnow,int *ynow,int *mark);
void save_user(USER *user);
int save_identity(USER *user,ID *id,int *len,int St);
int choose_sex(int *x,int *y,int x1,int y1,int *mark);
int choose_id(int *x,int *y,int *mark); 
int id_visual(USER *user);
void delete_id(int i,USER *user);
void visual_TTB(char *trainnum,char *mon,char *day,int *xnow,int *ynow);
int TTB(char *trainnum,int num);
int change_password(USER *user,int *xnow,int *ynow);
void change_theme(int *xnow,int *ynow);
void profile(USER *user,int *xnow,int *ynow);
#endif
