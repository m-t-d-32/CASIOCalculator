#include <iostream>
#include <math.h>
#ifndef __Action14__Frac
#define __Action14__Frac

namespace _Action
{
#define mecro 1e9
	void Error(int);
	class Frac
	{
		private:
            double num;
            double deno;
            bool out_statue;
		public:
            void YF();
            Frac(double a=0,double b=1);
			void setvalue(double,double b=1);
            void set_out_statue(bool);
			Frac operator+ (const Frac &) const;
			Frac operator- (const Frac &) const;
			Frac operator* (const Frac &) const;
			Frac operator/ (const Frac &) const;
			Frac operator- () const;
            Frac operator-=(const Frac &);
            Frac operator+=(const Frac &);
			bool operator== (const Frac &) const;
			bool operator> (const Frac &) const;
			bool operator< (const Frac &) const;
			bool operator>= (const Frac &) const;
			bool operator<= (const Frac &) const;
			bool operator!= (const Frac &) const;
			Frac operator++ (int);
			Frac operator++ ();
			Frac operator-- (int);
			Frac operator-- ();
            Frac convert(int) const;
			const Frac &operator= (const Frac &);
            explicit operator double() const;
            friend Frac inv(const Frac &);
			friend std::ostream & operator <<(std::ostream &,Frac &);
            friend std::istream & operator >>(std::istream &,Frac &);
            friend Frac pow(Frac ,Frac );
	};
	int get_maxY(int,int);

    template<class T>
    void swap(T &a,T &b)
    {
        T temp=a;
        a=b;
        b=temp;
    }
    Frac pow(Frac ,Frac );
    Frac inv(const Frac &);
    std::istream & operator >>(std::istream &,Frac &);
	std::ostream & operator <<(std::ostream &,Frac &);
	
	struct FracDenoZero{};
}
#endif
