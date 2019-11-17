#include "fraction.h"
#include <cmath>
#include <iostream>

using namespace std;
namespace _Action
{
	__int64 get_maxY(__int64 a, __int64 b)
	{
        a=abs(a);
        b=abs(b);
		if (a && b)
		{
			if (a<b) swap(a, b);
			while (a%b)
			{
				a = a%b;
				swap(a, b);
			}
			return b;
		}
		return 0;
	}

	std::ostream & operator <<(std::ostream & out, Frac & f)
	{
        f.YF();
        __int64 num=f.num,deno=f.deno;
        if (num%deno==0)
        {
            out<<num/deno;
        }
        else if (num/deno==0)
        {
            out<<num<<" : "<<deno;
        }
        else
        {
            if (f.out_statue)
            {
                if (num<0)
                {
                    out<<"-";
                    num=-num;
                }
                out<<num/deno<<" & "<<num%deno<<":"<<deno;
            }
            else
            {
                out<<num<<" : "<<deno;
            }
        }
        return out;
	}

    std::istream & operator >>(std::istream & in, Frac & f)
    {
        f.deno=1;
        in>>f.num;
        return in;
    }

	void Frac::YF()
	{
        double tp_Num=num,tp_Deno=deno;
		if (!tp_Num)
        {
            return;
        }
        while (tp_Num<1e9 && tp_Deno<1e9)
        {
            tp_Num*=10;
            tp_Deno*=10;
        }
        tp_Num=round(tp_Num);
        tp_Deno=round(tp_Deno);
        __int64 temp = get_maxY(tp_Num, tp_Deno);
		if (temp)
		{
			deno = tp_Deno / temp;
			num = tp_Num / temp;
		}
        if (deno<0)
        {
            num=-num;
            deno=-deno;
        }
	}

    Frac pow(Frac a, Frac b)
    {
        return Frac(::pow(a.num,(double)b),::pow(a.deno,(double)b));
    }
    Frac inv(const Frac & a)
    {
        if (a.num==0) throw FracDenoZero();
        return Frac(a.deno,a.num);
    }

    void Frac::set_out_statue(bool t)
    {
        out_statue=t;
    }

    Frac::Frac(double a, double b, bool t):out_statue(t)
	{
        if (!b) throw FracDenoZero();
        if (num)
        {
            num=a;
            deno=b;
        }
        else
        {
            num=0;
            deno=1;
        }        
	}

    void Frac::setvalue(double a, double b)
	{
        if (!b) throw FracDenoZero();
		if (a)
		{
            num=a;
            deno=b;
		}
	}

	Frac Frac::operator-() const
	{
        return Frac(-num, deno);
	}

	bool Frac::operator==(const Frac & read) const
	{
		if (num == read.num && deno == read.deno) return true;
		return false;
	}

	bool Frac::operator>(const Frac & read) const
	{
        if ((double)(*this)>(double)read) return true;
		return false;
	}

	bool Frac::operator<(const Frac & read) const
	{
        if ((double)(*this)<(double)read) return true;
		return false;
	}

	bool Frac::operator>=(const Frac & read) const
	{
		if ((*this)<read) return false;
		return true;
	}

	bool Frac::operator<=(const Frac & read) const
	{
		if ((*this)>read) return false;
		return true;
	}

	Frac Frac::operator +(const Frac & read) const
	{
		return Frac(read.deno*num + deno*read.num, read.deno*deno);
	}

	Frac Frac::operator -(const Frac & read) const
	{
		return *this + Frac(-read.num, read.deno);
	}

	Frac Frac::operator *(const Frac & read) const
	{
		return Frac(num*read.num, deno*read.deno);
	}

	Frac Frac::operator /(const Frac & read) const
	{
		return Frac(num*read.deno, deno*read.num);
	}

    Frac Frac::operator +=(const Frac & read)
    {
        (*this)=(*this)+read;
        YF();
        return *this;
    }

    Frac Frac::operator -=(const Frac & read)
    {
        (*this)=(*this)-read;
        return *this;
    }

	Frac Frac::operator ++()
	{
		num += deno;
		return *this;
	}

	Frac Frac::operator ++(int)
	{
		num += deno;
		return Frac(num - deno, deno);
	}

	Frac Frac::operator --()
	{
		num -= deno;
        YF();
		return *this;
	}

	Frac Frac::operator --(int)
	{
		num -= deno;
		return Frac(num + deno, deno);
	}

	const Frac &Frac::operator =(const Frac & read)
	{
		this->num = read.num;
		this->deno = read.deno;
		return *this;
	}

    Frac::operator double() const
	{
        return ((double)num) / ((double)deno);
	}

}
