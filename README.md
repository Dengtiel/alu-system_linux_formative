# Week 3 Formative Assignment 1 — Linux Systems Programming

**Student:** Deng Mayen Deng Akol  

---

## Repository Structure

```
week3_formative/
├── project1/               # Investigating a Suspicious Binary
│   ├── data_sync.c         # Simulated file sync tool
│   ├── analysis_output.txt # objdump + nm command outputs
│   └── forensic_report.md  # 1-page forensic analysis
│
├── project2/               # System Call Monitoring Tool
│   ├── backup_tool.c       # File backup C program
│   ├── strace_output.txt   # Full strace capture
│   └── syscall_summary.md  # Syscall table + analysis
│
├── project3/               # Python Performance Extension
│   ├── stats_python.py     # Pure Python statistics
│   ├── statsmodule.c       # CPython C extension
│   ├── setup.py            # Build configuration
│   └── benchmark.py        # Head-to-head benchmark
│
├── project4/               # Signal-Based Server Controller
│   ├── monitor_service.c   # Background monitor service
│   └── signal_explanation.md # How signals are handled
│
└── README.md               # This file
```

---

## Project Summaries

### Project 1 — Investigating a Suspicious Binary

A C program (`data_sync.c`) simulates a file synchronization tool. It was compiled and analyzed using `objdump` and `nm` without executing it.

**Key findings:**
- Entry point: `0x11a0` (`_start`)
- 27 ELF sections including `.text`, `.rodata`, `.plt`, `.bss`
- Imports: `fopen`, `fclose`, `fread`, `fwrite`, `stat`, `mkdir`, `fprintf`
- Only dynamic dependency: `libc.so.6`
- Conclusion: benign local file sync tool; no network or crypto indicators

**Compile command:**
```bash
gcc -o data_sync data_sync.c
```

**Analysis commands:**
```bash
objdump -f data_sync              # Entry point
objdump -h data_sync              # Sections
objdump -d -j .plt data_sync      # Imported function stubs
nm data_sync                      # Symbol table
objdump -p data_sync | grep NEEDED  # Dynamic dependencies
```

---

### Project 2 — System Call Monitoring Tool

A C program (`backup_tool.c`) performs file creation, log writing, and file reading. It was traced with `strace` to identify all system calls.

**Key syscalls identified:**
- File: `openat`, `read`, `write`, `close`, `fstat`, `lseek`
- Process: `execve`, `getpid`, `brk`, `mmap`, `mprotect`, `getrandom`

**Compile & run commands:**
```bash
gcc -o backup_tool backup_tool.c
strace -o strace_output.txt ./backup_tool
```

---

### Project 3 — Python C Extension

A CPython C extension (`statsmodule.c`) accelerates statistics computation using Welford's single-pass online algorithm.

**Benchmark result (1,000,000 elements):**

| Implementation | Time (s) |
|---------------|----------|
| Pure Python   | ~0.12    |
| C Extension   | ~0.011   |
| **Speedup**   | **~10×** |

**Build & run commands:**
```bash
python3 setup.py build_ext --inplace
python3 benchmark.py
```

---

### Project 4 — Signal-Based Server Controller

`monitor_service.c` is a background service that prints a status message every 5 seconds and responds to OS signals using `sigaction()`.

| Signal   | Behavior |
|----------|----------|
| `SIGINT` | "Monitor Service shutting down safely." → `exit(0)` |
| `SIGUSR1`| "System status requested by administrator." → continues |
| `SIGTERM`| "Emergency shutdown signal received." → `exit(1)` |

**Compile & run commands:**
```bash
gcc -o monitor_service monitor_service.c
./monitor_service &
kill -SIGUSR1 <pid>
kill -SIGTERM <pid>
```

---

## How to Run All Projects

```bash
# Project 1
cd project1 && gcc -o data_sync data_sync.c && objdump -h data_sync && nm data_sync

# Project 2
cd project2 && gcc -o backup_tool backup_tool.c && strace -o strace_output.txt ./backup_tool

# Project 3
cd project3 && python3 setup.py build_ext --inplace && python3 benchmark.py

# Project 4
cd project4 && gcc -o monitor_service monitor_service.c && ./monitor_service
# In another terminal: kill -SIGUSR1 <pid>
```
