#include <sstream>
#include <iostream>
#include <cmath>
#include <QDebug>
#include <QMessageBox>
#include "calculate.h"
#include "fraction.h"
using namespace std;
using namespace _Action;

#define const_pi 3.14159265358979
#define const_e 2.718281828459045
#define eps 1e-6
extern bool CanbeConvert;
extern stringstream *buffer;
extern Frac ans;
extern Frac memory;
char temp[100];
enum exp_value{Rad,Deg};
extern int express;


void read(int times)
{
    for (int i=0;i<times;i++)
    {
        buffer->get();
    }
}
bool isChar(int read)
{
    if (read>=65 && read<=90 || read>=97 && read<=122)
        return true;
    return false;
}
bool isValue(int read,bool &neg)
{
    neg=false;
    if (read>=48 && read<58 || read=='.') return true;
    else if(read=='-' || read=='+')
    {
        while (read=='-' || read=='+')
        {
            if (read=='-') neg=!neg;
            buffer->get();
            read=buffer->peek();
        }
        bool temp;
        return isValue(read,temp);
    }
    return false;
}
Frac getVL()
{
    Frac value1;
    bool neg;
    if (isValue(buffer->peek(),neg))
    {
        (*buffer)>>value1;
    }
    else if (buffer->peek()=='(')
    {
        read(1);
        value1=limit();
        if (buffer->peek()==')' || buffer->peek()==EOF)
            read(1);
        else
            throw Syntax_Error();
    }
    else if (buffer->peek()=='S')
    {
        value1=inte();
    }
    else if (buffer->peek()=='d')
    {
        value1=vite();
    }
    else if (buffer->peek()=='R')
    {
        value1=Rand();
    }
    else if (buffer->peek()=='s')
    {
        value1=Sin();
    }
    else if (buffer->peek()=='c')
    {
        value1=Cos();
    }
    else if (buffer->peek()=='t')
    {
        value1=Tan();
    }
    else if (buffer->peek()=='a')
    {
        value1=Arc();
    }
    else if (buffer->peek()=='l')
    {
        value1=Log();
    }
    else if (buffer->peek()=='I')
    {
        value1=In();
    }
    else if (buffer->peek()=='A')
    {
        value1=ans;
        read(3);
    }
    else if (buffer->peek()=='M')
    {
        value1=memory;
        read(1);
    }
    else if (buffer->peek()=='e')
    {
        value1=const_e;
        read(1);
    }
    else if (buffer->peek()=='p')
    {
        value1=const_pi;
        read(2);
    }
    else
    {
        throw(Syntax_Error());
    }
    if (neg)
    {
        value1=-value1;
    }
    if (buffer->peek()=='!')
    {
        value1=Jc((double)value1);
        read(1);
    }
    if (fabs((double)value1)>1e100)
    {
        throw(Math_Error());
    }
    return value1;
}
Frac limit()
{
    Frac value1=getVL();
    while (true)
    {
        char m=buffer->peek();
        if (m==EOF || m==')' || m==',')
        {
            return value1;
            break;
        }
        switch(m)
        {
            case '+':
                {
                    value1=Plus(value1);
                    break;
                }
            case '-':
                {
                    value1=Minus(value1);
                    break;
                }
            case 'x':
                {
                    value1=Multi(value1);
                    break;
                }
            case '/':
                {
                    value1=Div(value1);
                    break;
                }
            case '^':
                {
                    value1=Pow(value1);
                    break;
                }
            case 'X':
                {
                    value1=XSqr(value1);
                    break;
                }
            default:
                {
                    throw(Syntax_Error());
                    break;
                }
        }
        if (fabs((double)value1)>1e100)
        {
            throw(Math_Error());
        }
    }
}
Frac Plus(Frac value)
{
    read(1);
    Frac value1=getVL();
    char m=buffer->peek();
    switch(m)
    {
        case '+':
            {
                return Plus(value+value1);
                break;
            }
        case '-':
            {
                return Minus(value+value1);
                break;
            }
        case 'x':
            {
                return value+Multi(value1);
                break;
            }
        case '/':
            {
                return value+Div(value1);
                break;
            }
        case '^':
            {
                return value+Pow(value1);
                break;
            }
        case 'X':
            {
                return value+XSqr(value1);
                break;
            }
        default:
            {
                return value+value1;
                break;
            }
    }
}
Frac Minus(Frac value)
{
    read(1);
    Frac value1=getVL();
    char m=buffer->peek();
    switch(m)
    {
        case '+':
            {
                return Plus(value-value1);
                break;
            }
        case '-':
            {
                return Minus(value-value1);
                break;
            }
        case 'x':
            {
                return value-Multi(value1);
                break;
            }
        case '/':
            {
                return value-Div(value1);
                break;
            }
        case '^':
            {
                return value-Pow(value1);
                break;
            }
        case 'X':
            {
                return value-XSqr(value1);
                break;
            }
        default:
            {
                return value-value1;
                break;
            }
    }
}
Frac Multi(Frac value)
{
    read(1);
    Frac value1=getVL();
    char m=buffer->peek();
    switch(m)
    {
        case 'x':
            {
                return Multi(value*value1);
                break;
            }
        case '/':
            {
                return Div(value*value1);
                break;
            }
        case '^':
            {
                return value*Pow(value1);
                break;
            }
        case 'X':
            {
                return value*XSqr(value1);
                break;
            }
        default:
            {
                return value*value1;
                break;
            }
    }
}
Frac Div(Frac value)
{
    read(1);
    Frac value1=getVL();
    char m=buffer->peek();
    switch(m)
    {
        case 'x':
            {
                if (fabs((double)value1)<eps) throw Math_Error();
                return Multi(value/value1);
                break;
            }
        case '/':
            {
                if (fabs((double)value1)<eps) throw Math_Error();
                return Div(value/value1);
                break;
            }
        case '^':
            {
                value1=Pow(value1);
                if (fabs((double)value1)<eps) throw Math_Error();
                return value/value1;
                break;
            }
        case 'X':
            {
                value1=XSqr(value1);
                if (fabs((double)value1)<eps) throw Math_Error();
                return value/value1;
                break;
            }
        default:
            {
                if (fabs((double)value1)<eps) throw Math_Error();
                return value/value1;
                break;
            }
    }
}
Frac Pow(Frac value)
{
    read(1);
    Frac value1=getVL();
    char m=buffer->peek();
    switch(m)
    {
        case '^':
            {
                value1=Multi(value1);
                if (fabs((double)value1)<eps && fabs(double(value))<eps) throw Math_Error();
                return pow(value,value1);
                break;
            }
        case 'X':
            {
                value1=XSqr(value1);
                if (fabs((double)value1)<eps && fabs(double(value))<eps) throw Math_Error();
                return pow(value,value1);
                break;
            }
        default:
            {
                if (fabs((double)value1)<eps && fabs(double(value))<eps) throw Math_Error();
                return pow(value,value1);
                break;
            }
    }
}
Frac XSqr(Frac value)
{
    read(4);
    Frac value1=getVL();
    char m=buffer->peek();
    switch (m)
    {
        case 'X':
            {
                if (fabs((double)value)<eps) throw Math_Error();
                value1=XSqr(value1);
                return pow(value1,inv(value));
                break;
            }
        default:
            {
                return pow(value1,inv(value));
                break;
            }
    }
}
double inte()
{
    double min,max;
    read(2);

    string backup;
    getline(*buffer,backup);
    buffer->clear();
    buffer->str(backup);
    while (buffer->peek()!=',')
    {
        buffer->get();
        if (buffer->peek()==EOF)
        {
            throw Syntax_Error();
        }
    }
    buffer->get();
    min=(double)limit();
    if (buffer->peek()==',')
    {
        buffer->get();
        max=(double)limit();
    }
    else
    {
        throw Syntax_Error();
    }
    string lasttime;
    getline(*buffer,lasttime);
    buffer->clear();
    buffer->str(backup);
    double result=RealInte(min,max);
    buffer->str(lasttime);
    buffer->get();
    return result;
}
double RealInte(double min,double max)
{
    bool minus=false;
    if (min>max)
    {
        double temp=min;min=max;max=temp;
        minus=true;
    }
    double sum=0;
    string rap;
    getline(*buffer,rap,',');
    buffer->clear();
    buffer->str(rap);
    for (double it=min;it<max;it+=eps)
    {
        sum+=funclnte(rap,it)*eps;
    }
    if (minus) sum=-sum;
    return sum;
}
double funclnte(string rap,double it)
{
    Replace(rap,it);
    string backup;
    backup=buffer->str();
    buffer->clear();
    buffer->str(rap);
    double result=(double)limit();
    buffer->clear();
    buffer->str(backup);
    return result;
}
void Replace(string &p,double t)
{
    string sum;
    char temp[100];
    sprintf(temp,"%lf",t);
    for (int i=0;i<p.size();i++)
    {
        if (p[i]!='U')
        {
            sum+=p[i];
        }
        else
        {
            sum+=temp;
        }
    }
    p=sum;
}
double vite()
{
    double s;
    read(5);
    string backup;
    getline(*buffer,backup);
    buffer->clear();
    buffer->str(backup);
    while (buffer->peek()!=',')
    {
        buffer->get();
        if (buffer->peek()==EOF)
        {
            throw Syntax_Error();
        }
    }
    buffer->get();
    s=(double)limit();
    string lasttime;
    getline(*buffer,lasttime);
    buffer->clear();
    buffer->str(backup);
    double result=RealVite(s);
    buffer->clear();
    buffer->str(lasttime);
    buffer->get();
    return result;
}
double RealVite(double s)
{
    string rap;
    getline(*buffer,rap,',');
    buffer->clear();
    buffer->str(rap);
    double t1=funclnte(rap,s+eps),t2=funclnte(rap,s);
    return ((t1-t2)/eps);
}
double Sin()
{
    read(4);
    double temp=(double)limit();
    read(1);
    if (express==Deg)
    {
        return sin(d_r(temp));
    }
    else
    {
        return sin(temp);
    }
}
double Cos()
{
    read(4);
    double temp=(double)limit();
    read(1);
    if (express==Deg)
    {
        return cos(d_r(temp));
    }
    else
    {
        return cos(temp);
    }
}
double Tan()
{
    read(4);
    double temp=(double)limit();
    if (fabs((temp-const_pi/2)/const_pi-(int)((temp-const_pi/2)/const_pi))<eps)
        throw Math_Error();
    read(1);
    if (express==Deg)
    {
        return tan(d_r(temp));
    }
    else
    {
        return tan(temp);
    }
}
double Arc()
{
    read(3);

    char m=buffer->peek();
    switch(m)
    {
    case 's':{
                return ArcSin();
                break;
             }
    case 'c':{
                return ArcCos();
                break;
             }
    case 't':{
                return ArcTan();
                break;
             }
    }
}
double ArcSin()
{
    read(4);
    double temp=(double)limit();
    if (temp>1 || temp<-1)
        throw Math_Error();
    read(1);
    if (express==Deg)
    {
        return r_d(asin(temp));
    }
    else
    {
        return asin(temp);
    }
}
double ArcCos()
{
    read(4);

    double temp=(double)limit();
    if (temp>1 || temp<-1)
        throw Math_Error();
    read(1);
    if (express==Deg)
    {
        return r_d(acos(temp));
    }
    else
    {
        return acos(temp);
    }
}
double ArcTan()
{
    read(4);
    double temp=(double)limit();
    read(1);
    if (express==Deg)
    {
        return r_d(atan(temp));
    }
    else
    {
        return atan(temp);
    }
}
double Log()
{
    read(4);
    double temp=(double)limit();
    if (temp<=0)
        throw Math_Error();
    read(1);
    return log10(temp);
}
double In()
{
    read(3);

    double temp=(double)limit();
    if (temp<=0)
        throw Math_Error();
    read(1);
    return log(temp);
}
double Rand()
{
    read(3);
    char m=buffer->peek();
    if (m=='(')
    {
        buffer->get();
        double min=(double)limit();
        if (buffer->peek()!=',')
            throw Syntax_Error();
        buffer->get();
        double max=(double)limit();
        double result=min+rand()%32767*(max-min)/32767.0;
        read(1);
        return result;
    }
    else
    {
        buffer->get();
        return rand()%32767/32767.0;
    }
}

double Jc(double c)
{
    if (fabs(c-(int)c)>eps || c<0)
    {
        throw Math_Error();
    }
    else
    {
        double sum=1;
        for (double i=1;i<=c;i++)
        {
            sum*=i;
        }
        return sum;
    }
}
void get_timeformat(int & h,int & m,double & s)
{
    double bk=fabs((double)ans);
    h=(int)bk;
    bk-=h;
    bk*=60;
    if (fabs(bk-(int)bk)*60<0.01) bk=(int)bk;
    m=(int)bk;
    bk-=m;
    bk*=60;
    bk=(int)(bk*100)/100.0;
    s=bk;
}

bool judge_m()
{
    if (abs((double)memory)>eps)
    {
        return true;
    }
    return false;
}

double d_r(double t)
{
    return t/180*const_pi;
}

double r_d(double t)
{
    return t*180/const_pi;
}
