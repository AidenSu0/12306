#ifndef __BOOK_H__
#define __BOOK_H__

#include "user.h"
#include "gettime.h"
#include "graph.h" 
#include "visual.h"
#include "booking.h"
int f_book(USER *user,int *xnow,int *ynow,int *mark);
int timechoose(char *choosemon,char *chooseday,int x,int y,int *xnow,int *ynow,int *mark);
int f_look(USER *user,char *ss,char *fs,int GD,int ST,char *mon,char *day,int *xnow,int *ynow,int *mark);
int Re_operate(USER *user,char *ss,char *fs,StackNode **ResDer,StackNode **ResRev,char *mon,char *day,int *xnow,int *ynow,int *mark,int k);
void now_visual(StackNode **Der,StackNode **Rev,int flag,int mode,int *num,int k,int page);
void visualtime(int x1,int y1,int *departline,char (*mon)[3],char (*_mark)[6],char (*nowday)[6][3]); 
void select(int *xnow,int *ynow,int x,int y,int *Select);
int frm(int x1,int y1,int x2,int y2);//½á¹û¿òÏÔÊ¾
int f_Adv_choose(int *xnow,int *ynow,int *Se);


void ChangeVersion(int *xnow,int *ynow,StackNode **R,int *num,int *mode,int flag,int k);
void ChangeShowMode(int *flag,int *xnow,int *ynow);
void re_visual(StackNode **Der,StackNode **Rev,int *Se,int flag,int mode,int *num,int k);
void T_sort(StackNode **p,int k);
void TT_sort(StackNode **p,int k);
int get_min(StackNode *rp,int k);
int ShowLastDay(char *mon,char *day,int k);
int ShowNextDay(char *mon,char *day,int k);

 
#endif
