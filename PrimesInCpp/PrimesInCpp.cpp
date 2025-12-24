#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

// Déclaration des fonctions
vector<int> GetPrimesUpTo(int limit);
string ToDaysHoursMinutesSeconds(chrono::milliseconds duration);

int main()
{
  const int limit = 10'000'000'000;
  // 10_000 0ms too fast to measure
  // 100_000 15ms in C# and 7ms in C++
  // 1_000_000 377ms in C# and 165ms in C++
  // 10_000_000 9s 71ms on laptop and 6s 360ms on desktop in C# and 4s 153ms on Desktop in C++
  // 100_000_000 04m:32s:126ms in C# and 01m:45s:528ms in C++
  // 1_000_000_000 47m:19s:642ms in C++ on desktop
  // 1'410'065'408: 01h : 17m : 29s : 825ms on Desktop in C++ (all primes stored in memory)
  // 1_000_000_000 23m:54s:108ms in C++ on desktop with optimized code
  // 10'000'000'000 XXXXXXXXXXXXXXXXXX in C++ on desktop

  cout << "Calculating prime numbers up to " << limit << " please wait ..." << endl;
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

  vector<int> primes = GetPrimesUpTo(limit);

  auto end = chrono::high_resolution_clock::now();
  auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

  cout << "Prime numbers up to " << limit << ":" << endl;
  // Affichage optionnel des nombres premiers
  // for (int p : primes) cout << p << " ";
  // cout << endl;

  cout << "Time taken to compute primes up to "
    << limit << ": "
    << ToDaysHoursMinutesSeconds(elapsed) << endl;

  cout << "Press Enter to exit...";
  cin.get();

  return 0;
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

vector<int> GetPrimesUpTo(int limit)
{
  vector<int> primes;

  for (int number = 2; number <= limit; number++)
  {
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

