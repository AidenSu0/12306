#ifndef __ORDER_H__
#define __ORDER_H__

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
#include "detail.h"
int visual_order(int page,USER *user);
void refund(int ticket,USER *user);
void reschedul(int ticket,USER *user,int *xnow,int *ynow,int *mark);
#endif
