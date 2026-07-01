import time
import random
import math

def compute_stats_python(data):
    """Pure Python: mean, variance, std dev, min, max."""
    n = len(data)
    mean = sum(data) / n
    variance = sum((x - mean) ** 2 for x in data) / n
    std_dev = math.sqrt(variance)
    minimum = min(data)
    maximum = max(data)
    return mean, variance, std_dev, minimum, maximum

if __name__ == "__main__":
    SIZE = 1_000_000
    data = [random.random() * 1000 for _ in range(SIZE)]

    start = time.perf_counter()
    mean, var, std, mn, mx = compute_stats_python(data)
    elapsed = time.perf_counter() - start

    print(f"[Python] Results on {SIZE:,} elements:")
    print(f"  Mean     : {mean:.4f}")
    print(f"  Variance : {var:.4f}")
    print(f"  Std Dev  : {std:.4f}")
    print(f"  Min      : {mn:.4f}")
    print(f"  Max      : {mx:.4f}")
    print(f"  Time     : {elapsed:.4f} seconds")
