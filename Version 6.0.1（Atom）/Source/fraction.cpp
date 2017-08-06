#include "fraction.h"
#include <cmath>
#include <iostream>
using namespace std;
namespace _Action
{
	int get_maxY(int a, int b)
	{
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
        Frac temp=f;
        if (temp.out_statue)
        {
            int zf=0;
            bool z=(temp.num>0);
            temp.deno=fabs(temp.deno);
            while (temp.num>=temp.deno)
            {
                temp.num-=temp.deno;
                zf++;
            }
            if (!z) out<<"-";
            if (zf) out<<zf<<"   ";
        }
        if (temp.num)
            out << temp.num << ":" << temp.deno;
		else
			out << 0;
		return out;
	}

    std::istream & operator >>(std::istream & in, Frac & f)
    {
        f.deno=1;
        in>>f.num;
        //cout<<f<<endl;
        return in;
    }

	void Frac::YF()
	{
        if (num)
        {
            int max = num > deno ? num : deno;
            int temp = mecro / max;
            num *=temp;
            deno *=temp;
        }
        else
        {
            return;
        }
		int temp = get_maxY(num, deno);
		if (temp)
		{
			deno /= temp;
			num /= temp;
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

    Frac::Frac(double a, double b):out_statue(true)
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
		return *this;
	}

	Frac Frac::operator --(int)
	{
		num -= deno;
		return Frac(num + deno, deno);
	}

	Frac Frac::convert(int read) const
	{
		int temp = get_maxY(deno, read);
		Frac tpf;
		tpf.deno = deno*read / temp;
		tpf.num = num*read / temp;
		return tpf;
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
