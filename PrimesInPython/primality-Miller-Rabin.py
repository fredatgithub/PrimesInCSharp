import random


def miller_rabin(n, k=10):
    """
    Test de primalité de Miller-Rabin
    n : nombre à tester
    k : nombre de tests (plus k est grand, plus le test est fiable)
    """
    if n < 2:
        return False
    if n in (2, 3):
        return True
    if n % 2 == 0:
        return False

    # écrire n-1 sous la forme d * 2^s
    s = 0
    d = n - 1
    while d % 2 == 0:
        d //= 2
        s += 1

    for _ in range(k):
        a = random.randrange(2, n - 2)
        x = pow(a, d, n)

        if x == 1 or x == n - 1:
            continue

        for _ in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True


def generate_large_prime(bits=512):
    while True:
        n = random.getrandbits(bits)
        n |= 1  # rendre le nombre impair
        if miller_rabin(n):
            return n


# Exemple d'utilisation
if __name__ == "__main__":
    test_numbers = [17, 18, 19, 20, 561, 1105, 1729, 1000000007]
    for number in test_numbers:
        result = miller_rabin(number)
        print(f"{number} is {'prime' if result else 'not prime'}")
    n = 10**100 + 39  # nombre très grand

    if miller_rabin(n):
        print(f"Le nombre {n} est probablement premier")
    else:
        print(f"Le nombre {n} n'est pas premier")
    prime = generate_large_prime(512)
    print("Le nombre suivant est premier généré au hasard de 512 bits")
    print(prime)
