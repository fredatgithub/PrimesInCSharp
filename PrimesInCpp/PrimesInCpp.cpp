#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

// Déclaration des fonctions
vector<int> GetPrimesUpTo(int limit);
string ToDaysHoursMinutesSeconds(chrono::milliseconds duration);

int main()
{
  const int limit = 100'000'000;
  // 10_000 0ms too fast to measure
  // 100_000 15ms in C# and 7ms in C++
  // 1_000_000 377ms in C# and 165ms in C++
  // 10_000_000 9s 71ms on laptop and 6s 360ms on desktop in C# and 4s 153ms on Desktop in C++
  // 100_000_000 04m:32s:126ms
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

vector<int> GetPrimesUpTo(int limit)
{
  vector<int> primes;

  for (int num = 2; num <= limit; num++)
  {
    bool isPrime = true;
    int squareRoot = static_cast<int>(sqrt(num));

    for (int i = 2; i <= squareRoot; i++)
    {
      if (num % i == 0)
      {
        isPrime = false;
        break;
      }
    }

    if (isPrime)
    {
      primes.push_back(num);
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

