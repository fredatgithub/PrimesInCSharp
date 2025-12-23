import time
from datetime import datetime
from pathlib import Path

# =========================
# PARAMÈTRES (équivalent Settings.Default.IncrementNumber)
# =========================
INCREMENT_NUMBER = 5000  # à adapter


# =========================
# UTILITAIRES
# =========================
def read_file(filename: str, default="2") -> str:
    try:
        return Path(filename).read_text().strip()
    except Exception:
        return default


def write_to_file(filename: str, content, append=False):
    mode = "a" if append else "w"
    with open(filename, mode, encoding="utf-8") as f:
        if isinstance(content, list):
            for line in content:
                f.write(str(line) + "\n")
        else:
            f.write(str(content) + "\n")


def add_time_to_filename(filename: str) -> str:
    now = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    return f"{filename}-{now}.txt"


def plural(n: int) -> str:
    return "s" if n > 1 else ""


def format_elapsed_time(seconds: float) -> str:
    minutes, sec = divmod(int(seconds), 60)
    hours, minutes = divmod(minutes, 60)

    result = []
    if hours:
        result.append(f"{hours} heure{plural(hours)}")
    if minutes:
        result.append(f"{minutes} minute{plural(minutes)}")
    result.append(f"{sec} seconde{plural(sec)}")

    return " ".join(result)


def format_number(n: int) -> str:
    return f"{n:,}".replace(",", " ")


# =========================
# TEST DE PRIMALITÉ (Miller-Rabin)
# =========================
def is_prime(n: int) -> bool:
    if n < 2:
        return False
    if n in (2, 3):
        return True
    if n % 2 == 0:
        return False

    # Décomposition n-1 = d * 2^s
    s = 0
    d = n - 1
    while d % 2 == 0:
        s += 1
        d //= 2

    # Bases suffisantes pour entiers < 2^64
    bases = [2, 325, 9375, 28178, 450775, 9780504, 1795265022]
    for a in bases:
        if a >= n:
            continue
        x = pow(a, d, n)
        if x in (1, n - 1):
            continue
        for _ in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True


# =========================
# PROGRAMME PRINCIPAL
# =========================
def main():
    while True:
        print("Searching for big integer prime numbers")

        now = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        print(f"Search started on {now}\n")

        # Continuer depuis le dernier nombre
        last_number = int(read_file("lastNumber.txt"))
        if last_number % 2 == 0:
            last_number += 1

        start_number = last_number
        end_number = start_number + INCREMENT_NUMBER

        print(f"Starting searching from: {format_number(start_number)}\n")
        print(f"Searching for {INCREMENT_NUMBER} numbers after {format_number(start_number)}")
        print(f"Processing numbers until {format_number(end_number)}\n")

        primes = []
        counter = 0

        start_time = time.perf_counter()

        for i in range(0, INCREMENT_NUMBER, 2):
            current = start_number + i
            if is_prime(current):
                print(f"{format_number(current)} is prime")
                primes.append(current)
                counter += 1

        elapsed = time.perf_counter() - start_time

        if counter == 0:
            result_msg = (
                f"No prime found between: "
                f"{format_number(start_number)} and {format_number(end_number)}"
            )
        else:
            result_msg = (
                f"{counter} prime{plural(counter)} found between: "
                f"{format_number(start_number)} and {format_number(end_number)}"
            )

        print(result_msg)
        write_to_file("PrimeCounter.txt", result_msg, append=True)

        time_msg = (
            f"To search for prime numbers within {INCREMENT_NUMBER} numbers, "
            f"it took : {format_elapsed_time(elapsed)}"
        )
        print(time_msg)

        write_to_file(
            "TimeTaken.txt",
            f"{time_msg} starting at {start_number} and ending at {end_number}",
            append=True
        )

        if primes:
            filename = add_time_to_filename("BigIntegerPrimes")
            with open(filename, "w", encoding="utf-8") as f:
                f.write(
                    f"Prime numbers between {primes[0]} and {primes[-1]}\n"
                )
                for p in primes:
                    f.write(f"{p}\n")

        write_to_file("lastNumber.txt", str(end_number))
        print("The result were written to a file on a disk")
        print(f"End of processing on {datetime.now()}\n")


if __name__ == "__main__":
    main()
