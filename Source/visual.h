#ifndef __VISUAL_H__
#define __VISUAL_H__

void De_visual(StackNode *result,int s_num,int flag,int k);

/*四种直达情况*/ 
void DeKT_visual(StackNode *result,StackNode *temp,int x1,int y1,int flag,int k);
void DeG_visual(StackNode *result,StackNode *temp,int x1,int y1,int flag,int k);
void DeD_visual(StackNode *result,StackNode *temp,int x1,int y1,int flag,int k);
void DeZ_visual(StackNode *result,int x1,int y1,int flag,int k); 


void Re_visual(StackNode *result,int s_num,int flag,int k);
/*16种转车组合*/
void KTReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void KTReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void KTReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void KTReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void GReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void GReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void GReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void GReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void DReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void DReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void DReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void DReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void ZReKT_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void ZReG_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void ZReD_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);
void ZReZ_visual(StackNode *result,StackNode *center,StackNode *temp,int x1,int y1,int flag,int k);

#endif
