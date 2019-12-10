#ifndef __FUNCTION_H__
#define __FUNCTION_H__


void f_help(int *xnow,int *ynow,int *btnow,int *mark);
int f_login(char *,int *,int *,int *,int *);
int f_register(int *,int *,int *,int *);
int f_manage(int *,int *,int *,int *);
int f_data(int *,int *,int *,int*);
int f_NewData(int *xnow,int *ynow,int *btnow,int *mark);
int f_DeleteData(int *xnow,int *ynow,int *btnow,int *mark);
int f_ModifyData(int *xnow,int *ynow,int *btnow,int *mark);
void refresh();
void copyfiles(char *path1,char *path2,int k);

#endif
