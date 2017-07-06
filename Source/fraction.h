#include <iostream>
#include <cmath>
#ifndef __Action14__Frac
#define __Action14__Frac

namespace _Action
{
#define mecro 1e9
	void Error(int);
	class Frac
	{
		private:
			int num;
			int deno;
            bool out_statue;
			void YF();
		public:
			Frac(double a=0,double b=1);
			void setvalue(double,double b=1);
            void set_out_statue(bool);
			Frac operator+ (const Frac &) const;
			Frac operator- (const Frac &) const;
			Frac operator* (const Frac &) const;
			Frac operator/ (const Frac &) const;
			Frac operator- () const;
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
			operator double() const;
			friend std::ostream & operator <<(std::ostream &,Frac &);
	};
	int get_maxY(int,int);
	void swap(int &,int &);
	std::ostream & operator <<(std::ostream &,Frac &);
	
	struct FracDenoZero{};
}
#endif
