#ifndef CALCULATE
#define CALCULATE
#include <iostream>
#include <string>
#include "fraction.h"
using namespace std;
struct Syntax_Error{};
struct Math_Error{};
struct Stack_Error{};
void read(int);
bool isChar(int);
bool isValue(int, bool &);
_Action::Frac limit();
_Action::Frac Plus(_Action::Frac);
_Action::Frac Minus(_Action::Frac);
_Action::Frac Multi(_Action::Frac);
_Action::Frac Div(_Action::Frac);
_Action::Frac Pow(_Action::Frac);
_Action::Frac XSqr(_Action::Frac);
_Action::Frac getVL();
double Rand();
double inte();
double RealInte(double,double);
double funclnte(string, double);
double vite();
double RealVite(double);
double Sqr();
double Sin();
double Cos();
double Tan();
double ArcSin();
double ArcCos();
double ArcTan();
double Arc();
double Log();
double In();
double Jc(double);

double r_d(double);
double d_r(double);

bool judge_m();
void get_timeformat(int &,int &,double &);
void Replace(string &,double);
#endif // CALCULATE

