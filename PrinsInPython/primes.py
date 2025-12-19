import math
import time


def get_primes_up_to(limit: int) -> list[int]:
    primes = []

    for num in range(2, limit + 1):
        is_prime = True
        square_root = int(math.sqrt(num))

        for i in range(2, square_root + 1):
            if num % i == 0:
                is_prime = False
                break

        if is_prime:
            primes.append(num)

    return primes


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
    limit = 10_000_000

    start = time.perf_counter()
    primes = get_primes_up_to(limit)
    end = time.perf_counter()

    elapsed = end - start

    print(f"Prime numbers up to {limit}:")
    # print(", ".join(map(str, primes)))  # affichage optionnel

    print(
        f"Time taken to compute primes up to {limit}: "
        f"{to_days_hours_minutes_seconds(elapsed)}"
    )

    input("Press Enter to exit...")


if __name__ == "__main__":
    main()
