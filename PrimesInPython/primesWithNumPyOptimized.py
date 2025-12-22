import numpy as np
import time
import math


def simple_sieve(limit: int) -> np.ndarray:
    """Crible classique jusqu'à sqrt(N)"""
    is_prime = np.ones(limit + 1, dtype=bool)
    is_prime[:2] = False

    for i in range(2, int(limit ** 0.5) + 1):
        if is_prime[i]:
            is_prime[i * i :: i] = False

    return np.nonzero(is_prime)[0]


def segmented_sieve(limit: int, segment_size: int = 100_000_000) -> int:
    """Crible segmenté – retourne seulement le nombre de nombres premiers"""
    sqrt_limit = int(math.isqrt(limit))
    base_primes = simple_sieve(sqrt_limit)

    count = 0

    for low in range(2, limit + 1, segment_size):
        high = min(low + segment_size, limit + 1)
        segment = np.ones(high - low, dtype=bool)

        for p in base_primes:
            start = max(p * p, ((low + p - 1) // p) * p)
            if start >= high:
                continue
            segment[start - low :: p] = False

        count += np.count_nonzero(segment)

    return count


def main():
    limit = 10_000_000_000
    # Crible segmenté pour 10 milliards
    # 10_000_000_000 in ~2 minutes on a typical machine
    # Number of primes up to 10000000000: 455052511 # Time: 77.61 seconds
    # Number of primes up to 10000000000: 455052511 # Time: 76.94 seconds
    start = time.perf_counter()
    prime_count = segmented_sieve(limit)
    end = time.perf_counter()

    print(f"Number of primes up to {limit}: {prime_count}")
    print(f"Time: {end - start:.2f} seconds")


if __name__ == "__main__":
    main()
