#pragma once

void InitOperateNum(struct shuju *StackNum);
void InitOperateSymbol(struct fuhao *StackSymbol);
void Inshuju(struct shuju *StackNum, double num);
void Infuhao(struct fuhao *StackSymbol, char ch);
double Randshuju(struct shuju *StackNum);
char Randfuhao(struct fuhao *StackSymbol);
double Putshuju(struct shuju *StackNum);
char Putfuhao(struct fuhao *StackSymbol);
int judge(char ch);
double Math(double v1, double v2, char c);
double pnc();
int fPg_func();
int sinf_func();
int fLg_func();




