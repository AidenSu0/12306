#ifndef __DETAIL_H__
#define __DETAIL_H__

#include "stdio.h"
#include "input.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "check.h"
#include "hmi.h"
#include "user.h"
#include "svga.h"
#include <alloc.h>
#include "mouse.h"
#include "hz.h"
#include <conio.h>
#include "gettime.h"
#include <mem.h>
#include "book.h"
#include "graph.h"
#include "bios.h"
#include "visual.h"
void DEdetail_get(StackNode *p,int *price,int *seatnum,int k);
void DEdetail_visual(StackNode *p,int *price,int *seatnum,int k);
void REdetail_visual(StackNode *p,StackNode *q,int (*price)[4],int (*seatnum)[3],int k);
void REdetail1_visual(StackNode *p,int *price,int *seatnum);
void REdetail2_visual(StackNode *p,int *price,int *seatnum);


#endif
