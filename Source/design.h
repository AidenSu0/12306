#ifndef __TRAIN_H__
#define __TRAIN_H__

#include "check.h"
#include "function.h"
#include "init.h"
#include "svga.h"
#include"hmi.h"
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<bios.h>
#include<conio.h>
#include<string.h>
#include<alloc.h>
#include "mouse.h"
#include "gettime.h" 

void _train(int x,int y);
void falling_star(int x1,int y1,int x2,int y2);
void starry_sky(int x1,int y1,int x2,int y2);
void texture(int x1,int y1,int x2,int y2);
void alipay(int x,int y);
void WeChat_pay(int x,int y);
void BankCard(int x,int y);
void QRCode(int x,int y);
void CK_right(int x,int y);
#endif
