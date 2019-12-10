#ifndef __CHECK_H__
#define __CHECK_H__

void check_help(int *judge,int x,int y,int state);
void check_login(int *,int x,int y,int state);
int check_book(int *judge,int p,int x,int y,int state);
int check_my_order(int *judge,int p,int x,int y,int state,int num);
int check_identity(int *judge,int p,int x,int y,int state,int num);
int check_my_account(int *judge,int p,int x,int y,int state); 
void check_regist(int *,int x,int y,int state);
int check_add_identity(int *,int p,int x,int y,int state,int St);
int check_choose(int *judge,int p,int rx,int ry,int x,int y,int state);
int check_settings(int *judge,int p,int x,int y,int state);
int check_time_table(int *judge,int p,int x,int y,int state);
int check_Re_operate(int *,int p,int num,int x,int y,int state,int flag,int page);
int check_message(int *judge,int p,int x,int y,int state);
int check_about(int *judge,int p,int x,int y,int state);
int check_feedback(int *judge,int p,int x,int y,int state);
void check_manage(int *,int x,int y,int state);
void check_data(int *,int x,int y,int state);
void check_NewData(int *,int x,int y,int state);
void check_NewKT(int *,int x,int y,int state);
void check_NewG(int *judge,int x,int y,int state);
void check_NewD(int *judge,int x,int y,int state);
void check_NewZ(int *judge,int x,int y,int state);
void check_DeleteData(int *judge,int x,int y,int state);
void check_more(int *judge,int x,int y,int state);
int check_DEstbook(int *judge,int p,int x,int y,int state,int idnum);
int check_REstbook(int *judge,int p,int x,int y,int state,int idnum);
int check_TTB(int *judge,int p,int x,int y,int state);
int check_password(int *judge,int p,int x,int y,int state);
int check_theme(int *judge,int p,int x,int y,int state);
int check_profile(int *judge,int p,int x,int y,int state);
int check_pay(int *judge,int p,int x,int y,int state);
int check_paymethod(int *judge,int p,int x,int y,int state);
int check_pwEnter(int *judge,int p,int x,int y,int state);
#endif
