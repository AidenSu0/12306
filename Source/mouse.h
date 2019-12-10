#ifndef __MOUSE_H__
#define __MOUSE_H__

void draw_mouse(int ,int);
void getbk_mouse(int ,int);
void redraw(int ,int);
void readxy(int *,int *,int *);
int mouse_control(int *xnow,int *ynow,int *btnow,int *mark);
void Add_frame(int *xnow,int *ynow,int x1,int y1,int x2,int y2);

#endif
