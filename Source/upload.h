#ifndef __UPLOAD_H__
#define __UPLOAD_H__

#include "data.h"
int KT_visual(KT_train *p,int (*length)[9],int page,int more);
int G_visual(G_train *p,int (*length)[9],int page,int more);
int D_visual(D_train *p,int (*length)[9],int page,int more);
void Z_visual(Z_train *p,int (*length)[2],int *lengthnum);
int f_NewKT(int *xnow,int *ynow,int *btnow,int *mark,int page,KT_train* p);
int f_NewZ(int *xnow,int *ynow,int *btnow,int *mark,Z_train *p);
int f_NewG(int *xnow,int *ynow,int *btnow,int *mark,int page,G_train *p);
int f_NewD(int *xnow,int *ynow,int *btnow,int *mark,int page,D_train *p);
int f_KTmore(int *xnow,int *ynow,int *btnow,int *mark,int page,KT_train *p,int num);
int f_ModifyKT(int *xnow,int *ynow,int *btnow,int *mark,int page,KT_train *p);
int f_ModifyZ(int *xnow,int *ynow,int *btnow,int *mark,Z_train *p);
int f_Gmore(int *xnow,int *ynow,int *btnow,int *mark,int page,G_train *p,int num);
int f_ModifyG(int *xnow,int *ynow,int *btnow,int *mark,int page,G_train *p);
int f_Dmore(int *xnow,int *ynow,int *btnow,int *mark,int page,D_train *p,int num);
int f_ModifyD(int *xnow,int *ynow,int *btnow,int *mark,int page,D_train *p);

#endif
