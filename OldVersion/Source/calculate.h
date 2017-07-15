#ifndef CALCULATE
#define CALCULATE
#include <iostream>
#include <string>
using namespace std;
struct Syntax_Error{};
struct Math_Error{};
void read(int);
bool isChar(int);
bool isValue(int, bool &);
double limit();
double Plus(double);
double Minus(double);
double Multi(double);
double Div(double);
double Pow(double);
double XSqr(double);
double getVL();
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
bool judge_m();
void get_timeformat(int &,int &,double &);
void Replace(string &,double);
#endif // CALCULATE

