import time
import random
import math
import statsmodule

SIZE = 1_000_000
data = [random.random() * 1000 for _ in range(SIZE)]

# ---- Pure Python ----
def compute_stats_python(data):
    n = len(data)
    mean = sum(data) / n
    variance = sum((x - mean) ** 2 for x in data) / n
    std_dev = math.sqrt(variance)
    return mean, variance, std_dev, min(data), max(data)

start = time.perf_counter()
r_py = compute_stats_python(data)
t_py = time.perf_counter() - start

# ---- C Extension ----
start = time.perf_counter()
r_c = statsmodule.compute_stats(data)
t_c = time.perf_counter() - start

# ---- Results ----
print("=" * 55)
print(f"{'Benchmark':^55}")
print("=" * 55)
print(f"{'Metric':<15} {'Python':>15} {'C Extension':>15}")
print("-" * 55)
labels = ["Mean", "Variance", "Std Dev", "Min", "Max"]
for label, py_v, c_v in zip(labels, r_py, r_c):
    print(f"{label:<15} {py_v:>15.4f} {c_v:>15.4f}")
print("-" * 55)
print(f"{'Time (s)':<15} {t_py:>15.4f} {t_c:>15.4f}")
speedup = t_py / t_c if t_c > 0 else float('inf')
print(f"\n  Speedup: C extension is {speedup:.1f}x faster than pure Python")
print("=" * 55)
