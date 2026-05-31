#include <iostream>
#include "complex.h"
int main()
{
    complex a(2,1);
    complex b(3,2);
    a+=b;
    std::cout<<a.real()<<'\n';
    std::cout<<a.imag()<<'\n';
    std::cout<<a+3<<'\n';
    std::cout<<3+a<<'\n';
    system("pause");
    return 0;
}