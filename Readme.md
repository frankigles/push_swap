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





you do:

estimate insertion cost
estimate chunk cost
estimate radix cost
choose minimum
🔧 Step 1 — define a cost struct
typedef struct s_cost
{
	int	insertion;
	int	chunk;
	int	radix;
}	t_cost;
🔧 Step 2 — estimate each algorithm
1. Radix (easy)

Radix cost is predictable:

int	estimate_radix(int size)
{
	int	bits;
	int	cost;

	bits = 0;
	while ((1 << bits) < size)
		bits++;

	cost = bits * (size * 2);
	return (cost);
}

Reason:

each bit = full scan of stack
~push + rotate per element
2. Insertion (approximation)

You don’t simulate fully, just estimate inversions:

int	estimate_insertion(int size, float disorder)
{
	return ((int)(size * size * disorder));
}

Better version (if you want accuracy later):

count inversions directly
3. Chunk (heuristic model)

Chunk depends on size + number of chunks:

int	estimate_chunk(int size)
{
	int	chunks;

	if (size <= 100)
		chunks = 5;
	else
		chunks = 11;

	return (size * 3 + chunks * size / 2);
}

This is approximate but works well in practice.

🔧 Step 3 — dispatcher picks minimum
void	sort_dispatcher(t_list **a, t_list **b, t_flags *flags)
{
	int	size;
	float	desord;
	t_cost	c;

	size = ft_lstsize(*a);
	desord = compute_disorder(*a);

	if (size <= 5)
	{
		small_sort(a, b, flags);
		return ;
	}

	c.insertion = estimate_insertion(size, desord);
	c.chunk = estimate_chunk(size);
	c.radix = estimate_radix(size);

	if (c.insertion <= c.chunk && c.insertion <= c.radix)
		insertion_sort(a, b, flags);
	else if (c.chunk <= c.radix)
		chunk_sort(a, b, flags);
	else
		radix_sort(a, b, flags);
}
1. Radix Sort Adaptation (The Winner)Radix sort works by processing individual bits of the numbers. Since you have two stacks, you can use Stack B as a temporary bucket for "0" bits and keep "1" bits in Stack A.How it works:Look at the least significant bit (LSB) of each number.If the bit is 0, execute pb (push to B).If the bit is 1, execute ra (rotate A).After one pass, push everything from B back to A (pa).Repeat for the next bit.Why it hits the target: For 500 elements, you need 9 bits ($2^9 = 512$). Each bit takes roughly $N$ operations to sort and $N$ (or fewer) to push back.Max Ops: $500 \times 9 \text{ bits} \times 2 \approx 9,000$ ops.The Optimization: By using a coordinate compression (pre-sorting the numbers and replacing them with their rank 0 to 499), you ensure you only ever deal with 9 bits. With smart bit-checking, you can consistently stay under the 5,500 limit.


The algorithm you’ve just shared is commonly known in the Push_swap community as the "Mechanical Turk" or "Turk Sort." It is a greedy algorithm that calculates the cost of moving each element and picks the "cheapest" one.
