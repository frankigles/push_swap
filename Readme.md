RUN
	make test ARG="--simple --bench 2 1 3 6 5 8"

	or

	make test ARG="--simple --bench 2 1 3 6 5 8 9 0 10 20"


change flags as you wish



results for list: 2 1 3 6 5 8 9 0 10 20:

COMPLEX:
[bench] disorder: 20.00 %
[bench] strategy: Complex / O(n log n)
[bench] total_ops: 65
[bench] sa: 0 sb: 0 ss: 0 pa: 25 pb: 25
[bench] ra: 15 rb: 0 rr: 0 rra: 0 rrb: 0 rrr: 0

MEDIUM:
[bench] disorder: 20.00 %
[bench] strategy: Medium / O(n√n)
[bench] total_ops: 29
[bench] sa: 0 sb: 3 ss: 0 pa: 10 pb: 10
[bench] ra: 2 rb: 1 rr: 0 rra: 3 rrb: 0 rrr: 0

SIMPLE:
[bench] disorder: 20.00 %
[bench] strategy: Simple / O(n²)
[bench] total_ops: 24
[bench] sa: 0 sb: 0 ss: 0 pa: 10 pb: 10
[bench] ra: 0 rb: 3 rr: 0 rra: 1 rrb: 0 rrr: 0

ADAPTIVE:
[bench] disorder: 20.00 %
[bench] strategy: Adaptive / O(n√n)
[bench] total_ops: 29
[bench] sa: 0 sb: 3 ss: 0 pa: 10 pb: 10
[bench] ra: 2 rb: 1 rr: 0 rra: 3 rrb: 0 rrr: 0


Algorithm Selection Rationale

Low Disorder (< 0.2) & High Disorder (≥ 0.5) Regimes: The repository utilizes an optimized Turk Sort (Insertion Adaptation).

In low disorder states, it handles structural sorting immediately with an upper-bound time complexity of O(n^2).

In high disorder states, its greedy operational math minimizes the overall push_swap push/rotation counts, easily breaking past the "Excellent Performance" evaluation limits (<700 / <5500 moves).

Medium Disorder (0.2 ≤ d < 0.5) Regime: The program dynamically falls back to an O(n√n) Chunk Sort strategy, splitting elements into √n distinct range barriers before organizing them, strictly honoring the academic complexity boundaries set for this performance state.

Space Complexity: All native strategies perform processing in-place or over the existing dual-stack frame structures, guaranteeing a strict constant space layout of O(1).


The algorithm you’ve just shared is commonly known in the Push_swap community as the "Mechanical Turk" or "Turk Sort." It is a greedy algorithm that calculates the cost of moving each element and picks the "cheapest" one.

If you are filling out a report or selecting algorithms to fulfill these 4 specific requirements, you have already written two of them:
- Your Turk Sort code satisfies Requirement 1 (Algoritmo simple O(n^2) via Insertion).
- Your Chunk Sort code satisfies Requirement 2 (Algoritmo intermedio O(n√n) via Chunks).

/* ***SIMPLE - MIN/MAX SORT *** */

Step 1: Kickstart Stack B
Needs something in Stack B to compare numbers against. Your code instantly pushes the first two numbers:

Move 1 (pb): Pushes 2.
Move 2 (pb): Pushes 1.

Stack B looks like: [1, 2] (Top to Bottom)

Step 2: The "Cheapest Target" Math
Now Stack A contains: [3, 5, 4, 7, 9, 8, 6, 11]

Code enters the while (*stack_a) loop and calls push_cheapest. Here is exactly what happens under the hood for a number—let’s look at 3:

- Find Target: Code calls get_target to look at Stack B ([1, 2]) and find the smallest number in B that is still bigger than 3.

- The Safety Net: There is no number in B bigger than 3! So if (!target) safety net triggers and returns the absolute minimum of Stack B, which is 1.

- Calculate Cost: The code calculates how many moves it takes to bring 3 to the top of A, plus how many moves it takes to bring 1 to the top of B. It sums them up.

It calculates this cost for 3, 5, 4, 7, etc. It finds the absolute cheapest option, rotates both stacks, and pushes it. It repeats this until Stack A is completely empty.

Step 3: Push back and Clean up
Now Stack B holds all the elements, perfectly ordered relative to each other (descending).

The code loops through Stack B, finds where each element fits back into Stack A using get_target, pushes them back (pa), and finally does one last rotation to make sure the absolute minimum value is sitting right at the top of Stack A.

// COMPLEXITY
O(N^2) in the Worst Case

Here is why:
- Inside push_cheapest: Have a while (curr) loop that iterates through every remaining node in Stack A. If Stack A has $K$ elements, this loop runs K times.
- Inside that loop: Call get_cost, which calls get_target. get_target loops through every single element in Stack B to find the correct match.
- The Math: If Stack A has roughly N/2 elements and Stack B has roughly N/2 elements, the code is executing a nested loop of size approx N/2 x N/2, which equals N^2/4.In Big O notation, we drop constants, leaving us with O(N^2).

Space Complexity: $O(1)$

/* ***MEDIUM - CHUNK SORT *** */

Step 1: Divide into Chunks
The code calculates how many chunks to make using the square root of the stack size: √10 approx 3.

So, it creates 3 chunks of numbers:
Chunk 1: Numbers 1 to 3
Chunk 2: Numbers 4 to 6
Chunk 3: Numbers 7 to 10

Step 2: Throw Chunks into Stack B (The "Push to B" Phase)

The algorithm starts looking for any number that belongs to Chunk 1 (numbers 1, 2, or 3).
- It looks at Stack A from both the top and the bottom to find which number from Chunk 1 is closest to the exit.
- It rotates Stack A (ra or rra) to bring that number to the top and pushes it to Stack B (pb).
- The Optimization Hook: If the number pushed to B is smaller than the middle of the chunk, it rotates Stack B (rb). This keeps the absolutely smallest numbers near the bottom of Stack B and medium numbers near the top.
- It repeats this until all of Chunk 1 is in Stack B. Then it repeats for Chunk 2, and finally Chunk 3.

What Stack B looks like now: It's roughly sorted! Small numbers are at the bottom, and large numbers are near the top.

Step 3: Put them back beautifully (The "Push Back to A" Phase)

Now Stack A is completely empty, and Stack B holds all the numbers.
The algorithm finds the absolute maximum number remaining in Stack B, rotates Stack B to bring it to the top, and pushes it back to Stack A (pa).
Because Stack B was already roughly sorted, the largest numbers are already near the top. It takes very few moves to find and push them back. Once Stack B is empty, Stack A is perfectly sorted from smallest to largest!

// COMPLEXITY
The overall worst-case theoretical time complexity is O(n^2), but its average operation count behaves like (n√n).

Instead of rotating a maximum of $N$ times per element, dividing the stack into √n chunks means you are doing roughly √n work per element to position them. Doing √n work for N elements results in: N x √n = O(N√n)

The reason a strict evaluator calls this O(N^2) comes down to Phase 2 (push_back_to_a_nor) and worst-case scenarios. find_max_pos scans every single element left in Stack B to find the exact maximum.
