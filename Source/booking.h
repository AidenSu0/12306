#ifndef __BOOKING_H__
#define __BOOKING_H__


#include "user.h"
#include "gettime.h"
#include "graph.h" 
#include "visual.h"


void DEstart_book(StackNode *p,USER *user,int *xnow,int *ynow,int k);
void REstart_book(StackNode *p,USER *user,int *xnow,int *ynow,int k);
void change_plan_1(int buyer_num,int *price,int kind_click,int x,int y);
int change_plan_2(int buyer_num,int price,int *consumer,int buyer_click,int x,int y,int mode);
void change_plan_3(int buyer_num,int (*price)[4],int kind_click,int *kind,int x,int y); 
void instant_bookDE(StackNode *p,int kind,USER *user,int *consumer,int *xnow,int *ynow,int k);
void change_data(StackNode *p,int kind,int buyer_num,int k,int mode);
void change_order(StackNode *p,int *consumer,int kind,USER *user,int k);
void deal_ordertime(StackNode *p,ORDER *order,int k);
int dayDifference(StackNode *p,int k);
void copy_detailTime(StackNode *p,char *st_time,char *fi_time,int k);
void instant_book(StackNode *p,int kind,USER *user,int *consumer,int k);
int f_pay_method(int *xnow,int *ynow);
int enter_password(int *xnow,int *ynow);
void instant_bookRE(StackNode *p,StackNode *q,int *kind,USER *user,int *consumer,int *xnow,int *ynow,int k);

#endif
