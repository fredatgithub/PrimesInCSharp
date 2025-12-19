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
      // time how long it takes to compute primes up to 1 million
      int limit = 100;
      Stopwatch chrono = new Stopwatch();
      chrono.Start();
      List<int> primes = GetPrimesUpTo(limit);
      chrono.Stop();
      Console.WriteLine($"Prime numbers up to {limit}:");
      Console.WriteLine(string.Join(", ", primes));
      Display($"Time taken to compute primes up to {limit}: {ToHourMinutesSeconds(chrono.Elapsed)}");

      
    }

    private static List<int> GetPrimesUpTo(int limit)
    {
      List<int> primes = new List<int>();
      for (int num = 2; num <= limit; num++)
      {
        bool isPrime = true;
        for (int i = 2; i <= Math.Sqrt(num); i++)
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

    private static string ToHourMinutesSeconds(TimeSpan timeSpan)
    {
      return string.Format("{0:D2}h:{1:D2}m:{2:D2}s:{3:D2}",
          timeSpan.Hours,
          timeSpan.Minutes,
          timeSpan.Seconds,
          timeSpan.Milliseconds);
    }
  }
}
