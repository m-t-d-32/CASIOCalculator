#include "baseconv.h"
bool judgeifnum(char t)
{
    if ((t>='0' && t<='9') || (t>='A' && t<='Z'))
    {
        return true;
    }
    return false;
}

string convertwhole(string t,int base)
{
    string result="";
    int size=t.size();
    for (int i=0;i<size;)
    {
        string temp="";
        int j,k;
        for (j=i;j<size;j++)
        {
            if (judgeifnum(t[j])==true)
                temp+=t[j];
            else
                break;
        }
        result+=convertto10(temp,base);
        for (k=j;k<size;k++)
        {
            if (judgeifnum(t[k])==false)
                result+=t[k];
            else
                break;
        }
        i=k;
    }
    return result;
}

string convertto10(string t,int base)
{
    int result=0;
    int size=t.size();
    for (int i=0;i<size;i++)
    {
        result*=base;
        if (t[i]>='0'&& t[i]<='9')
            result+=(t[i]-'0');
        else
            result+=(t[i]-'A'+10);
    }
    stringstream temp;
    temp<<result;
    string final=temp.str();
    return final;
}

string tobs(int num,int nowbase)
{
    if (num==0)
        return "0";
    else
    {
        string t;
        if (num<0)
        {
            t="-";
            num=-num;
        }
        else
        {
            t="";
        }
        int max=log10(num)/log10(nowbase)+1;
        for (int i=max-1;i>=0;i--)
        {
            t+=reflect[num/((int)(pow(nowbase,i)))];
            num-=num/((int)(pow(nowbase,i)))*((int)(pow(nowbase,i)));
        }
        return t;
    }
}

