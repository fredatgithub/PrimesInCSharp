using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace PrimesInCSharp
{
  internal class Program
  {
    static void Main()
    {
      Action<string> Display = Console.WriteLine;
      // time how long it takes to compute primes up to a certain number
      const int limit = 10_000_000;
      // 10_000 1ms
      // 100_000 15ms
      // 1_000_000 377ms
      // 10_000_000 9s 71ms on laptop and 6s 360ms on desktop
      // 100_000_000 04m:32s:126ms
      Stopwatch chrono = new Stopwatch();
      chrono.Start();
      List<int> primes = GetPrimesUpTo(limit);
      chrono.Stop();
      Display($"Prime numbers up to {limit}:");
      //Console.WriteLine(string.Join(", ", primes));
      Display($"Time taken to compute primes up to {limit}: {ToDaysHoursMinutesSeconds(chrono.Elapsed)}");

      Display("Press any key to exit...");
      Console.ReadKey();
    }

    private static List<int> GetPrimesUpTo(int limit)
    {
      List<int> primes = new List<int>();
      for (int num = 2; num <= limit; num++)
      {
        bool isPrime = true;
        int squareRoot = (int)Math.Sqrt(num);
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
          primes.Add(num);
        }
      }

      return primes;
    }

    private static string ToDaysHoursMinutesSeconds(TimeSpan timeSpan)
    {
      if (timeSpan.Days > 0)
      {
        return string.Format("{0}j {1:D2}h:{2:D2}m:{3:D2}s:{4:D3}ms",
            timeSpan.Days,
            timeSpan.Hours,
            timeSpan.Minutes,
            timeSpan.Seconds,
            timeSpan.Milliseconds);
      }

      return string.Format("{0:D2}h:{1:D2}m:{2:D2}s:{3:D3}ms",
          (int)timeSpan.TotalHours,
          timeSpan.Minutes,
          timeSpan.Seconds,
          timeSpan.Milliseconds);
    }
  }
}
