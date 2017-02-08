
#include <cstdio>
#include <iostream>

#include "flint_mpz_class.hh"

//
// You can compile with
//   g++ -g -Wall -lflint -lgmp test.cpp -o test
//

bool t1(flint_mpz_class & a, int b, bool expected)
{
    if (a == b) {
        std::cout << ""
    }
}

int main()
{
    std::cout << "FLINTpp test program!" << std::endl;

    flint_mpz_class a1(0);
    flint_mpz_class a2(1);
    flint_mpz_class a3(2245.234);
    flint_mpz_class a4("8762872163817451541823217361");

    std::cout << "Setting number 0: got " << a1.get_str() << std::endl;
    std::cout << "Setting number 1: got " << a2.get_str() << std::endl;
    std::cout << "Setting number 2245.234: got " << a3.get_str() << std::endl;
    std::cout << "Setting number 8762872163817451541823217361: got " << a4.get_str() << std::endl;



    getchar();
    return 0;
}
