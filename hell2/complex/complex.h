#ifndef COMPLEX_h
#define COMPLEX_h
#include<iostream>
class complex
{
private:
double re,im;
friend complex&_dopal(complex*,const complex&);
public:
complex(double r=0,double i=0):re(r),im(i){}
complex& operator +=(const complex&);
double real() const {return re;}
double imag() const {return im;}
};
inline complex&  _dopal(complex*ths,const complex& r)
{
    ths->re +=r.re;
    ths->im +=r.im;
    return *ths;
}
inline double real(const complex&a)
{
    return a.real();
}
inline double imag(const complex&a)
{
    return a.imag();
}
inline complex& complex::operator +=(const complex& r)
{
return _dopal(this,r);
}
inline complex operator +(const complex&m,const complex&r)
{
return complex(real(m)+real(r),imag(m)+imag(r));
}
inline complex operator +(double x,const complex&y)
{
    return complex(real(y)+x,real(y));
}
inline complex operator +(const complex&x,double y)
{
    return complex(real(x),imag(x)+y);
}
inline std::ostream& operator <<(std::ostream& cou,const complex&y)
{
return cou<<'('<<real(y)<<','<<imag(y)<<')';
}
#endif