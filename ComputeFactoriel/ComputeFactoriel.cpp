#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

int main()
{
    std::cout << "compute factoriel\n";

    // unsigned long long  a = 1;
    cpp_int a = 1;
    a = 1;
    for (int i = 1; i <= 100; i++) {
      a *= i;
      std::cout << "i= " << i << " a= " << a << std::endl;
    }

    std::cout << "Factoriel de 100 est " << a << std::endl;

    return EXIT_SUCCESS;
}
