#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

// Déclaration des fonctions
vector<unsigned long long> GetPrimesUpTo(unsigned long long limit);
string ToDaysHoursMinutesSeconds(chrono::milliseconds duration);
string formatWithThousands(unsigned long long number);
string VersionCpp(long number);

int main()
{
  const unsigned long long limit = 10'000'000'000;
  // 10_000 0ms too fast to measure
  // 100_000 15ms in C# and 7ms in C++
  // 1_000_000 377ms in C# and 165ms in C++
  // 10_000_000 9s 71ms on laptop and 6s 360ms on desktop in C# and 4s 153ms on Desktop in C++
  // 100_000_000 04m:32s:126ms in C# and 01m:45s:528ms in C++
  // 1_000_000_000 47m:19s:642ms in C++ on desktop
  // 1'410'065'408: 01h : 17m : 29s : 825ms on Desktop in C++ (all primes stored in memory)
  // 1_000_000_000 23m:54s:108ms in C++ on desktop with optimized code
  // 1_410_065_408: 38m:14s:773ms on desktop in C++ with optimized code
  // 10'000'000'000 XXXXXXX environ 11 jours, 8 heures et 10 minutes in C++ on desktop

  std::cout << "Compilation of this program has been done with " << VersionCpp(__cplusplus) << std::endl;
  cout << "Calculating prime numbers up to " << formatWithThousands(limit) << " please wait ..." << endl;
  const char* jours[] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
  
  auto now = std::chrono::system_clock::now();
  std::time_t t = std::chrono::system_clock::to_time_t(now);

  std::tm tm{};
  localtime_s(&tm, &t);

  std::cout << "starting on: ";
  std::cout << jours[tm.tm_wday] << " "
    << std::setfill('0')
    << std::setw(2) << tm.tm_mday << "/"
    << std::setw(2) << (tm.tm_mon + 1) << "/"
    << (tm.tm_year + 1900) << " "
    << std::setw(2) << tm.tm_hour << ":"
    << std::setw(2) << tm.tm_min << ":"
    << std::setw(2) << tm.tm_sec
    << std::endl;

  // Démarrage du chronomètre
  auto start = chrono::high_resolution_clock::now();

  vector<unsigned long long> primes = GetPrimesUpTo(limit);

  auto end = chrono::high_resolution_clock::now();
  auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

  cout << "Prime numbers up to " << formatWithThousands(limit) << ":" << endl;
  cout << "Time taken to compute primes up to " << formatWithThousands(limit) << ": "
    << ToDaysHoursMinutesSeconds(elapsed) << endl;

  cout << "Press Enter to exit...";
  cin.get();

  return 0;
}

static string formatWithThousands(unsigned long long number) {
  string numberAsString = std::to_string(number);
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

bool static IsPrime(int number)
{
  if (number <= 1) return false;
  if (number == 2 || number == 3 || number == 5) return true;
  if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0) return false;
  int squareRoot = static_cast<int>(sqrt(number));
  for (int divisor = 7; divisor <= squareRoot; divisor += 2)
  {
    if (number % divisor == 0)
    {
      return false;
    }
  }

  return true;
}

bool static IsPrime(unsigned long long number)
{
  if (number <= 1) return false;
  if (number == 2 || number == 3 || number == 5) return true;
  if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0) return false;
  int squareRoot = static_cast<unsigned long long>(sqrt(number));
  for (unsigned long long divisor = 7; divisor <= squareRoot; divisor += 2)
  {
    if (number % divisor == 0)
    {
      return false;
    }
  }

  return true;
}

static vector<unsigned long long> GetPrimesUpTo(unsigned long long limit)
{
  vector<unsigned long long> primes;
  primes.push_back(2);
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

  std::ostringstream formattedNumber;
  formattedNumber << formatWithThousands(limit);
  std::string limitNumber = formattedNumber.str();
  
  for (unsigned long long number = 3; number <= limit; number += 2)
  {
    cout << formatWithThousands(number) << " out of " << limitNumber << " started on ";
    std::cout << today << endl;

    if (IsPrime(number))
    {
      primes.push_back(number);
    }
  }

  return primes;
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
