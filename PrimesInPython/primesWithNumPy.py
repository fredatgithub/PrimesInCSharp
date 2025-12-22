import numpy as np
import time


def get_primes_up_to_numpy(limit: int) -> np.ndarray:
    # Tableau booléen : True = premier
    is_prime = np.ones(limit + 1, dtype=bool)
    is_prime[0:2] = False  # 0 et 1 ne sont pas premiers

    max_factor = int(limit ** 0.5) + 1

    for i in range(2, max_factor):
        if is_prime[i]:
            is_prime[i * i : limit + 1 : i] = False

    return np.nonzero(is_prime)[0]


def to_days_hours_minutes_seconds(elapsed_seconds: float) -> str:
    total_ms = int(elapsed_seconds * 1000)

    ms = total_ms % 1000
    total_seconds = total_ms // 1000
    seconds = total_seconds % 60
    total_minutes = total_seconds // 60
    minutes = total_minutes % 60
    total_hours = total_minutes // 60
    hours = total_hours % 24
    days = total_hours // 24

    if days > 0:
        return f"{days}j {hours:02}h:{minutes:02}m:{seconds:02}s:{ms:03}ms"
    else:
        return f"{total_hours:02}h:{minutes:02}m:{seconds:02}s:{ms:03}ms"


def main():
    limit = 10_000_000_000
    # 10_000_000 in 62ms in NumPy
    # Time taken to compute primes up to 10 000 000: 00h:00m:00s:062ms
    # Time taken to compute primes up to 100 000 000: 00h:00m:00s:663ms
    # Time taken to compute primes up to 1 000 000 000: 00h:00m:09s:638ms
    # error for 10_000_000_000
    # Ton code est correct pour ≤ 10⁹
    # Pour 10¹⁰, le crible segmenté est obligatoire
    # Même avec 64 GB, on ne peut pas allouer un tableau de taille N

    start = time.perf_counter()
    primes = get_primes_up_to_numpy(limit)
    end = time.perf_counter()

    elapsed = end - start

    print(f"Prime numbers up to {limit}: {len(primes)} primes found")
    # print(primes)  # affichage optionnel

    print(
        f"Time taken to compute primes up to {limit}: "
        f"{to_days_hours_minutes_seconds(elapsed)}"
    )

    input("Press Enter to exit...")


if __name__ == "__main__":
    main()
