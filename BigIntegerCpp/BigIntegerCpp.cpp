#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

bool static IsPrime(const cpp_int& number)
{
  if (number <= 1) return false;
  if (number == 2 || number == 3 || number == 5) return true;
  if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0) return false;
  
  cpp_int squareRoot = sqrt(number);
  for (cpp_int divisor = 7; divisor <= squareRoot; divisor += 2)
  {
    if (number % divisor == 0)
    {
      return false;
    }
  }
  return true;
}

int main()
{
    std::cout << "Computing big integer primes\n";

    cpp_int number = 8446744073714979933;
    if (IsPrime(number))
    {
      cout << number << " est premier" << std::endl;
    }
    else
    {
      cout << number << " n'est pas premier" << std::endl;
    }

    return EXIT_SUCCESS;
}
