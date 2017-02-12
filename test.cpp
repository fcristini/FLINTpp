
#include <cstdio>
#include <iostream>

#include "flint_mpz_class.hh"

//
// You can compile with
//   g++ -g -Wall -lflint -lgmp test.cpp -o test
//

int main()
{
    std::cout << "FLINTpp test program!" << std::endl;

    flint_mpz_class a1(0);
    flint_mpz_class a2(1);
    flint_mpz_class a3(2245.234);
    flint_mpz_class a4("8762872163817451541823217361");

    std::cout << "Setting a1 to 0: got " << a1.get_str() << std::endl;
    std::cout << "Setting a2 to 1: got " << a2.get_str() << std::endl;
    std::cout << "Setting a3 to 2245.234: got " << a3.get_str() << std::endl;
    std::cout << "Setting a4 to 8762872163817451541823217361: got " << a4.get_str() << std::endl;

    std::cout << "a1 < a2 returns " << (a1 < a2) << std::endl;
    std::cout << "a3 < 2234 returns " << (a3 < 2234) << std::endl;
    std::cout << "a3 >= 2235 returns " << (a3 >= 2235) << std::endl;

    std::cout << "a1 + a2 returns " << (a1 + a2).get_str() << std::endl;
    std::cout << "a3 - a2 returns " << (a3 - a2).get_str() << std::endl;
    std::cout << "a3 * a2 returns " << (a3 * a2).get_str() << std::endl;
    std::cout << "a4 / a3 returns " << (a4 / a3).get_str() << std::endl;

    std::cout << "a3 + 35 returns " << (a3 + 35).get_str() << std::endl;
    std::cout << "a3 - 35 returns " << (a3 - 35).get_str() << std::endl;
    std::cout << "a3 * 35 returns " << (a3 * 35).get_str() << std::endl;
    std::cout << "a3 / 35 returns " << (a3 / 35).get_str() << std::endl;

    std::cout << "a3 += 10000 returns " << (a3 += 10000).get_str() << std::endl;
    std::cout << "a3 -= 10000 returns " << (a3 -= 10000).get_str() << std::endl;
    std::cout << "a3 *= 10000 returns " << (a3 *= 10000).get_str() << std::endl;
    std::cout << "a3 /= 10000 returns " << (a3 /= 10000).get_str() << std::endl;

    getchar();
    return 0;
}
