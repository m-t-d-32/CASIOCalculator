#include "fraction.h"

namespace _Action
{
	void swap(int &a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

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
        if (f.out_statue)
        {
            int zf=0;
            bool z=(f.num>0);
            f.deno=fabs(f.deno);
            while (f.num>=f.deno)
            {
                f.num-=f.deno;
                zf++;
            }
            if (!z) out<<"-";
            if (zf) out<<zf<<" & ";
        }
		if (f.num)
            out << f.num << "/" << f.deno;
		else
			out << 0;
		return out;
	}

	void Frac::YF()
	{
		int temp = get_maxY(num, deno);
		if (temp)
		{
			deno /= temp;
			num /= temp;
		}
	}
    void Frac::set_out_statue(bool t)
    {
        out_statue=t;
    }

    Frac::Frac(double a, double b):out_statue(true)
	{
        if (!b) throw FracDenoZero();
		if (a)
		{
			int max = a > b ? a : b;
			int temp = mecro / max;
			num = a*temp;
			deno = b*temp;
			YF();
		}
		else
		{
			num = 0;
			deno = 1;
		}
	}

	void Frac::setvalue(double a, double b)
	{
        if (!b) throw FracDenoZero();
		if (a)
		{
			int max = a > b ? a : b;
			int temp = mecro / max;
			num = a*temp;
			deno = b*temp;
			YF();
		}
		else
		{
			num = 0;
			deno = 1;
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
