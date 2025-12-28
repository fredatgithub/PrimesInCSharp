#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <limits>

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

string ToDaysHoursMinutesSeconds(chrono::milliseconds duration)
{
  long long totalMs = duration.count();

  long long ms = totalMs % 1000;
  long long totalSeconds = totalMs / 1000;
  long long seconds = totalSeconds % 60;
  long long totalMinutes = totalSeconds / 60;
  long long minutes = totalMinutes % 60;
  long long totalHours = totalMinutes / 60;
  long long hours = totalHours % 24;
  long long days = totalHours / 24;

  stringstream ss;

  if (days > 0)
  {
    ss << days << "j "
      << setw(2) << setfill('0') << hours << "h:"
      << setw(2) << minutes << "m:"
      << setw(2) << seconds << "s:"
      << setw(3) << ms << "ms";
  }
  else
  {
    ss << setw(2) << setfill('0') << totalHours << "h:"
      << setw(2) << minutes << "m:"
      << setw(2) << seconds << "s:"
      << setw(3) << ms << "ms";
  }

  return ss.str();
}

static string formatWithThousands(cpp_int number) 
{
  std::string numberAsString = number.convert_to<std::string>();
  int insertPosition = numberAsString.length() - 3;
  while (insertPosition > 0)
  {
    numberAsString.insert(insertPosition, "'");
    insertPosition -= 3;
  }

  return numberAsString;
}

string static VersionCpp(long version)
{
  if (version >= 202002L) return "C++20 or later";
  if (version >= 201703L) return "C++17";
  if (version >= 201402L) return "C++14";
  if (version >= 201103L) return "C++11";
  if (version >= 199711L) return "C++98";
  return "pre-standard C++";
}

int main()
{
    cout << "Computing big integer primes compiled with ";
    cout << "C++ version: " << VersionCpp(__cplusplus) << std::endl;
    cout << "please wait..." << std::endl;

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_s(&tm, &t);
    const char* jours[] = { "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi" };
    std::ostringstream oss;
    oss << jours[tm.tm_wday] << " "
      << std::setfill('0')
      << std::setw(2) << tm.tm_mday << "/"
      << std::setw(2) << (tm.tm_mon + 1) << "/"
      << (tm.tm_year + 1900) << " "
      << std::setw(2) << tm.tm_hour << ":"
      << std::setw(2) << tm.tm_min << ":"
      << std::setw(2) << tm.tm_sec;
    std::string today = oss.str();
    
    cpp_int number = cpp_int("18446744073714979933");
    cout << formatWithThousands(number) << " started on ";
    cout << today << endl;
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
