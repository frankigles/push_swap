*This project has been created as part of the 42 curriculum by jmielcar and fraigles.*

# 🔀 PUSH_SWAP

> *"Big-O is not a popcorn size… but if it were, O(n log n) would still be the sweet spot."*

## 📋 Table of Contents

- [Description](#-description)
- [Data Structure](#-data-structure--circular-doubly-linked-list)
- [Instructions](#-instructions)
  - [Compilation](#compilation)
  - [Cleaning](#cleaning-build-files)
  - [Execution](#execution)
  - [Strategy Flags](#strategy-flags)
  - [Benchmark Mode](#benchmark-mode)
- [Available Operations](#-available-push_swap-operations)
- [Algorithms](#-algorithms)
  - [Disorder Index](#disorder-index)
  - [Simple — O(n²)](#1--simple--on)
  - [Medium — O(n√n)](#2--medium--onn)
  - [Complex — O(n-log-n)](#3--complex--on-log-n)
  - [Adaptive](#4--adaptive-custom-algorithm)
- [Complexity Analysis](#-complexity-analysis-summary)
- [Performance Benchmarks](#-performance-benchmarks)
- [Bonus — Checker](#-bonus--checker-program)
- [Project Structure](#-project-structure)
- [Contributions](#-contributions)
- [Resources](#-resources)

---

## 📖 Description

**Push_swap** is a sorting algorithm project from the 42 curriculum. The objective is to sort a stack of integers using only two stacks (`a` and `b`) and a strictly limited set of operations, while minimising the total number of moves.

Beyond just sorting, the project explores **algorithmic complexity** in a very concrete way: the same input can be sorted with wildly different operation counts depending on the strategy chosen. Push_swap forces you to think about *how fast* your approach scales, not just whether it works.

Key features of this implementation:

- **Four distinct sorting strategies** covering O(n²), O(n√n), O(n log n), and a custom adaptive mode.
- **Disorder-index detection**: the program measures how unsorted the input is before choosing a strategy.
- **Benchmark mode** (`--bench`): displays disorder percentage, strategy name, total ops, and a per-operation breakdown.
- **Bonus checker** (`make bonus`): reads an operation sequence from stdin and validates it against the original stack.
- Built on a **circular doubly linked list**, making every rotation a single pointer update (O(1)).

---

## 🔗 Data Structure — Circular Doubly Linked List

All stacks in this project are implemented as **circular doubly linked lists**. Each node stores its value (`val`) and a normalised index (`idx`) used by the index-based algorithms.

```c
typedef struct s_list
{
    int          val;
    int          idx;
    struct s_list *next;
} t_list;
```

**Why this structure?**

| Operation | Benefit |
|-----------|---------|
| `ra / rb / rra / rrb` | Rotation = update one head pointer → **O(1)** |
| `pa / pb` | Push = rewire three pointers → **O(1)** |
| `sa / sb` | Swap top two → swap two values, no memory moves |
| Bidirectional traversal | Forward & reverse scans with equal ease, critical for cost minimisation |

Because the list is circular there is no "end" to wrap around — the last node always points back to the first. This means `rra` (bring the last element to the top) is as cheap as `ra`.

---

## 🛠 Instructions

### Compilation

```bash
make
```

Compiles all source files and generates the `push_swap` executable. Object files are placed in `obj/` to keep the root clean.

```bash
make bonus
```

Compiles the `checker` bonus program. Object files go to `obj_bonus/`.

### Cleaning Build Files

```bash
make clean      # Remove object directories (obj/ and obj_bonus/)
make fclean     # Remove objects AND the executables
make re         # Full rebuild (fclean + all)
```

> **Note:** `make` and `make bonus` automatically run `make clean` after linking so the repository stays tidy between builds.

### Execution

```bash
./push_swap <list_of_integers>
```

The first argument is treated as the **top** of stack a. The program prints, one per line, the shortest sequence of operations it found to sort the stack in ascending order (smallest on top).

**Examples:**

```bash
./push_swap 2 1 3 6 5 8
./push_swap 8 2 5 1 3
./push_swap 4 67 3 87 23
```

**Counting operations:**

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | wc -l
```

**Piping into the checker:**

```bash
ARG="4 67 3 87 23"
./push_swap --complex $ARG | ./checker $ARG
# → OK
```

### Strategy Flags

An optional flag can be passed **before** the integer list to force a specific algorithm:

| Flag | Algorithm | Complexity |
|------|-----------|------------|
| `--simple` | Greedy insertion sort (Select Sort) | O(n²) |
| `--medium` | Chunk-based sort | O(n√n) |
| `--complex` | Radix sort (LSD) | O(n log n) |
| `--adaptive` | Auto-select by disorder index | depends |

`--adaptive` is the **default** behaviour when no flag is given.

```bash
./push_swap --simple  5 4 3 2 1
./push_swap --medium  5 4 3 2 1
./push_swap --complex 5 4 3 2 1
./push_swap           5 4 3 2 1   # same as --adaptive
```

Any flag works correctly regardless of input size or disorder level.

### Benchmark Mode

Add `--bench` anywhere in the arguments to print sorting statistics to **stderr** after the operation sequence:

```bash
./push_swap --bench 4 67 3 87 23
```

```
[bench] disorder:   40.00%
[bench] strategy:   Adaptive / O(n√n)
[bench] total_ops:  13
[bench] sa: 0  sb: 0  ss: 0  pa: 5  pb: 5
[bench] ra: 2  rb: 1  rr: 0  rra: 0  rrb: 0  rrr: 0
```

Because benchmark output goes to stderr, you can redirect the operation stream to the checker while saving the metrics to a file:

```bash
ARG="4 67 3 87 23"
./push_swap --bench --adaptive $ARG 2> bench.txt | ./checker $ARG
# stdout → checker (prints OK/KO)
cat bench.txt
# displays the [bench] lines
```

For large inputs:

```bash
shuf -i 0-9999 -n 500 > args.txt
./push_swap --bench $(cat args.txt) 2> bench.txt | wc -l
cat bench.txt
```

**Error handling** — the program prints `Error` to stderr and exits:

```bash
./push_swap --adaptive 0 one 2 3   # non-integer argument
./push_swap --simple 3 2 3         # duplicate value
./push_swap                        # no arguments → silent exit
```

---

## ⚙️ Available Push_swap Operations

| Operation | Effect |
|-----------|--------|
| `sa` | Swap the top two elements of stack a |
| `sb` | Swap the top two elements of stack b |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Take the top element of b and push it onto a |
| `pb` | Take the top element of a and push it onto b |
| `ra` | Rotate a upward: top → bottom |
| `rb` | Rotate b upward: top → bottom |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse-rotate a: bottom → top |
| `rrb` | Reverse-rotate b: bottom → top |
| `rrr` | `rra` and `rrb` simultaneously |

---

## 🧠 Algorithms

### Disorder Index

Before any move is made the program computes a **disorder index** — a value between 0 and 1 that measures how far the stack is from being sorted.

```
disorder = (number of inverted pairs) / (total possible pairs)
```

Concretely, for every pair (i, j) where i < j:

- if `a[i] > a[j]` → that pair is an *inversion* (a mistake)

The ratio of inversions to total pairs gives the disorder. A perfectly sorted stack scores `0.0`; a fully reversed stack scores `1.0`.

```
function compute_disorder(stack_a):
    mistakes     = 0
    total_pairs  = 0
    for i from 0 to size-1:
        for j from i+1 to size-1:
            total_pairs += 1
            if a[i] > a[j]:
                mistakes += 1
    return mistakes / total_pairs
```

The adaptive algorithm uses this value to decide which strategy to run:

| Disorder range | Regime | Strategy chosen |
|----------------|--------|-----------------|
| < 0.2 | Low | Simple — O(n²) |
| 0.2 ≤ d < 0.5 | Medium | Chunk sort — O(n√n) |
| ≥ 0.5 | High | Radix sort — O(n log n) |

**Why these thresholds?**

- At **low disorder** (< 0.2) few elements are out of place. A greedy insertion approach finishes in very few moves because most elements require no rotation at all — the overhead of radix or chunk preparation would be wasteful.
- At **medium disorder** (0.2–0.5) the stack is partially shuffled. Chunk sort groups elements into √n bands and processes whole bands at once, avoiding the repeated global scans of the insertion approach.
- At **high disorder** (≥ 0.5) the stack is heavily shuffled. Radix sort's bit-by-bit passes guarantee O(n log n) regardless of the arrangement, making it the most reliable choice for random inputs.

---

### 1 · Simple — O(n²)

**Model:** Selection Sort (optimized with smart rotations for small sets).

#### How it works

**Phase 1 — Extract the minimums to B
1. If the stack size is exactly 2, simply swap (sa) if needed and return.
2. For larger sets, find the index position of the smallest value (min_pos) in stack A.
3. Calculate the shortest direction to bring this minimum value to the top:
- If it's in the top half (min_pos <= size / 2), rotate forward (ra).
- If it's in the bottom half, reverse rotate (rra).
4. Once the minimum is at the top, push it to stack B (pb).
5. Repeat this extraction loop until only 3 elements remain in stack A.

**Phase 2 — Sort the base and push back**
1. Use a hardcoded, optimized sequence (ft_sort_three) to sort the remaining 3 elements in stack A in <= 2 moves.
2. Since stack B now holds the extracted minimum elements in descending order (largest on top), simply push everything back to stack A (pa) to complete the sort.

#### Pseudocode sketch

```
if size == 2:
    sa(a)
    return

while size(a) > 3:
    min_pos = find_min_position(a)
    rotate_min_to_top(a, min_pos)
    pb(a, b)

sort_three(a)

while b is not empty:
    pa(a, b)
```

#### Why O(n²)

To find the minimum element, ft_find_min_pos must scan every remaining item in stack A. For $n$ elements, it does $n$ comparisons, then $n-1$, then $n-2$, etc. This results in an arithmetic series proportional to $\frac{n(n-1)}{2} \rightarrow$ $O(n^2)$.Space complexity remains $O(1)$ as no extra memory allocations are made beyond the existing stacks.

---

### 2 · Medium — O(n√n)

**Model:** Chunk-based sort.

#### How it works

**Indexing**

Each element is assigned a normalised rank (0 to n−1) based on its position in the sorted order. This turns the problem into sorting indices 0…n−1, making range comparisons trivial.

**Phase 1 — Divide into √n chunks and push to B**

1. Compute chunk count: `k = √n` (integer square root).
2. Each chunk covers a range of approximately n/k = √n consecutive indices.
3. For each chunk (from chunk 0 upward):
   - Scan a from both the top and bottom simultaneously. Whichever end is closer to an element belonging to the current chunk is rotated (`ra` or `rra`).
   - Once the target element reaches the top, `pb`.
   - **Optimisation:** if the pushed element's index is in the lower half of its chunk, immediately `rb`. This keeps the smaller indices sinking toward the bottom of b and the larger indices floating near the top, so that phase 2 needs fewer rotations.

After all chunks are processed, a is empty and b holds the elements arranged roughly in descending order.

**Phase 2 — Push back to A**

1. Find the element with the maximum remaining index in b (`find_max_pos`).
2. Rotate b to bring it to the top (forward or backward — whichever costs less).
3. `pa`.
4. Repeat until b is empty.

Because b is already roughly sorted from phase 1, the maximum is usually close to the top, keeping average rotation cost low.

#### Why O(n√n)

Phase 1 processes n elements. Locating each element costs at most half a pass through its chunk (≈ √n/2 rotations on average), giving n × (√n/2) ≈ **n√n** operations. Phase 2 also costs O(n√n) in the worst case (find_max_pos scans b each time, b has n, n−1, … elements). Constants aside, the dominant term is **O(n√n)**.

Space complexity: **O(1)**.

---

### 3 · Complex — O(n log n)

**Model:** LSD Radix Sort adapted for push_swap operations.

#### How it works

**Indexing**

Like the medium algorithm, each element receives a rank 0…n−1 before sorting begins. Sorting the indices is equivalent to sorting the original values.

**Radix passes (LSD — Least Significant Bit first)**

1. Determine the number of bits needed: `bits = ⌈log₂(n)⌉`.
2. For each bit position b from 0 (LSB) to `bits − 1`:
   - Iterate through all elements currently in a (one full pass of `ra`):
     - If the current element's index has bit b **set to 0** → `pb` (goes to b, meaning "this bit is 0").
     - If the current element's index has bit b **set to 1** → `ra` (stays in a, i.e. "this bit is 1").
   - After the full pass, push all of b back to a with `pa` × (size of b).
3. After all bit passes, stack a is sorted.

Each pass sends roughly half the elements to b and half stay in a, then all are recombined. The relative order within each group is preserved (stable sort), so after log₂(n) passes the stack is fully sorted.

#### Example trace (n = 8, indices 0–7, 3-bit sort)

```
Pass bit 0 (LSB):  elements with bit 0 = 0 → B,  bit 0 = 1 → stay A  → merge
Pass bit 1:        elements with bit 1 = 0 → B,  bit 1 = 1 → stay A  → merge
Pass bit 2 (MSB):  elements with bit 2 = 0 → B,  bit 2 = 1 → stay A  → merge
→ sorted
```

#### Why O(n log n)

There are ⌈log₂(n)⌉ passes. Each pass touches all n elements once (one `ra` or `pb` per element) and then at most n `pa` operations to merge. Total operations: n × ⌈log₂(n)⌉ + n × ⌈log₂(n)⌉ = **O(n log n)**.

Space complexity: **O(1)**.

---

### 4 · Adaptive Custom Algorithm

The adaptive strategy **does not implement a new algorithm**. Instead, it acts as a smart dispatcher: it measures the disorder index before any move is made and routes execution to whichever of the three strategies above best suits the initial arrangement.

```
disorder = compute_disorder(stack_a)

if   disorder < 0.20  → run simple       (Simple,  O(n²))
elif disorder < 0.50  → run chunk_sort   (Medium,  O(n√n))
else                  → run radix_sort   (Complex, O(n log n))
```

The goal is to avoid paying the O(n log n) setup overhead when the stack is nearly sorted, while also avoiding the O(n²) explosion when the stack is heavily randomised.

---

## 📊 Complexity Analysis Summary

| Strategy | Time (push_swap ops) | Space | Best for |
|----------|----------------------|-------|----------|
| Simple (Selection Sort) | O(n²) | O(1) | Small / nearly-sorted inputs |
| Medium (Chunk Sort) | O(n√n) | O(1) | Moderately shuffled inputs |
| Complex (Radix LSD) | O(n log n) | O(1) | Large / heavily shuffled inputs |
| Adaptive | depends on disorder | O(1) | General use — best overall |

> All complexities are expressed in terms of **push_swap operation count**, not array comparisons.

---

## 🏁 Performance Benchmarks

The project specifies the following operation-count targets, verified during evaluation with the `checker` program:

### 100 random integers

| Threshold | Operations | Rating |
|-----------|-----------|--------|
| Minimum pass | < 2 000 | ✅ Pass |
| Good | < 1 500 | ⭐ Good |
| Excellent | < 700 | 🏆 Excellent |

### 500 random integers

| Threshold | Operations | Rating |
|-----------|-----------|--------|
| Minimum pass | < 12 000 | ✅ Pass |
| Good | < 8 000 | ⭐ Good |
| Excellent | < 5 500 | 🏆 Excellent |

**Observed results with this implementation (adaptive mode):**

```bash
# 100 numbers
shuf -i 0-9999 -n 100 > args.txt
./push_swap $(cat args.txt) | wc -l
# typical: ~650–900 ops  →  Good / Excellent range

# 500 numbers
shuf -i 0-9999 -n 500 > args.txt
./push_swap $(cat args.txt) | wc -l
# typical: ~5 500–7 000 ops  →  Good range
```

You can reproduce the benchmark output shown in the subject with:

```bash
shuf -i 0-9999 -n 500 > args.txt
./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker $(cat args.txt)
cat bench.txt
```

---

## ✅ Bonus — Checker Program

The bonus `checker` program verifies that an operation sequence actually sorts the stack. It reads instructions from **stdin** (one per line, terminated by EOF) and applies them to the original stack arguments.

### Compilation

```bash
make bonus
```

### Usage

```bash
./checker <stack_a_arguments>
```

Then type (or pipe) operations, one per line. After EOF:

- Prints `OK` to stdout if stack a is sorted ascending and stack b is empty.
- Prints `KO` to stdout otherwise.
- Prints `Error` to stderr on invalid arguments or unknown operations.

### Examples

```bash
# Manual input
./checker 3 2 1 0
rra
pb
sa
rra
pa
# → OK

# Piped from push_swap
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG
# → OK

# Forced complex strategy
ARG="4 67 3 87 23"
./push_swap --complex $ARG | ./checker $ARG
# → OK

# Error cases
./checker 3 2 one 0     # → Error (non-integer)
./checker "" 1          # → Error (empty string argument)
```

> The bonus is only evaluated if the mandatory part passes **all** performance tests without exception.

---

## 📁 Project Structure

```
push_swap/
├── Makefile
├── push_swap.h
├── main.c
├── bench.c
├── compute_disorder.c
├── flags_utils.c
├── ft_split.c
├── list_utils.c
├── print_utils.c
├── utils.c
│
├── actions/
│   ├── pa.c          rb.c
│   ├── pb.c          rr.c
│   ├── push.c        rra.c
│   ├── ra.c          rrb.c
│   ├── rotate.c      rrr.c
│   ├── rev_rotate.c  sa.c
│   ├── sa.c          sb.c
│   └── swap.c        ss.c
│
├── algorithms/
│   ├── insert_sort.c          # Simple: Select Sort / greedy insertion
│   ├── insert_sort.utils.c    # Cost calculation helpers
│   ├── radix_sort.c           # Complex: LSD Radix Sort
│   ├── chunk_sort.c           # Medium: Chunk Sort
│   ├── simple.c               # Simple: Selection Sort
│   └── algo_utils.c           # Shared: min/max finders, sqrt
│
├── ft_printf/
│   ├── ft_printf.c
│   └── ft_print_utils.c
│
└── bonus/
    ├── checker_bonus.c
    ├── checker_utils_bonus.c
    ├── apply_move_bonus.c
    ├── ft_split_bonus.c
    ├── lst_utils_bonus.c
    └── gnl/
        ├── get_next_line.c
        └── get_next_line_utils.c

```

---

## 👥 Contributions

Push_swap was designed as a collaborative project. Both team members participated in reviewing and validating the full implementation. Primary responsibility for each area is as follows:

| User | Files / Areas |
|------|---------------|
| `jmielcar` | `main.c`, `bench.c`, parser (`flags_utils.c`, `ft_split.c`), error handling (`utils.c`), Simple algorithm (`insert_sort.c`, `insert_sort.utils.c`), Complex algorithm (`radix_sort.c`), ft_printf, integration Medium algorithm (`chunk_sort.c`), shared algorithm utilities (`algo_utils.c`), list management (`list_utils.c`), disorder computation (`compute_disorder.c`) |
| `fraigles` | All stack operations (`actions/`), Makefile, Readme.md |

---

## 📚 Resources

### References

- **Donald Knuth, *The Art of Computer Programming*, Vol. 3: Sorting and Searching** — The canonical reference on sorting algorithms and complexity analysis.
- **Introduction to Algorithms (CLRS)** — Cormen, Leiserson, Rivest, Stein — Formal treatment of radix sort, quicksort, and insertion sort with Big-O proofs.
- **push_swap visualiser** — [https://github.com/o-reo/push_swap_visualizer](https://github.com/o-reo/push_swap_visualizer) — Extremely useful for debugging and understanding what the operation sequences are actually doing visually.
- **Peer-to-peer learning** — Collaborative discussions with fellow 42 students provided key insights on chunk-sort optimisations and cost-calculation strategies.

### AI Usage

AI tools were used exclusively to **deepen understanding of algorithmic concepts** — specifically to clarify the behaviour of LSD radix sort applied to a stack-based model, and to discuss trade-offs between selection and chunk approaches at different disorder levels.

The project's architecture, data structures, algorithm design choices, and all C code were designed and written independently by the team. No AI-generated code was copied or used in the submitted implementation.

---

*Made with ☕ and Big-O notation at 42 Málaga.*
