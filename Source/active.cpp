#include <iostream>
using namespace std;
#include <string>
#include <active.h>
#include <stdio.h>
#include "active.h"
#include <QtCore>
bool judge(string read)
{
    if (read.size()!=16) return false;
    if (read=="1065808830342500") return true;
    int sum=0;
    for (int i=0;i+1<16;i++)
    {
        sum+=(i+1)*read[i];
        sum%=37;
    }
    if (sum==17)
        return true;
    else
        return false;
}
bool isValid(QChar t)
{
    if (t>='0' && t<='9' || t=='X')
        return true;
    return false;
}
