/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraigles <fraigles@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:09:55 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/24 22:40:23 by fraigles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_flags
{
	int	simple;
	int	medium;
	int	complex;
	int	adaptive;
	int	bench;
	int	total_ops;
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
	int	chunks;
	int	num_chunks;
	int	total_size;
}	t_flags;

typedef struct s_list
{
	int				val;
	int				idx;
	struct s_list	*next;
}	t_list;

typedef struct s_range
{
	int	min;
	int	max;
}	t_range;

// ft_split.c
char	**ft_split(char const *s, char c);

// list_utils.c
t_list	*ft_lstnew(int value);
t_list	*ft_lstlast(t_list *head);
int		ft_lstsize(t_list *head);
int		ft_lstadd_back(t_list **stack, char *c);
int		ft_lsthas(t_list *head, int value);

// utils.c
long	ft_atoi(const char *str);
int		ft_isnum(char *num);
int		is_sorted(t_list **stack);
int		ft_strcmp(const char *s1, const char *s2);
void	free_string(char **str);

// main.c
void	free_stack(t_list **stack);
void	handle_error(char *msg);

// ACTIONS
int		swap(t_list **stack);
int		rotate(t_list **stack);
int		rev_rotate(t_list **stack);
int		push(t_list **stack_to, t_list **stack_from);
int		pa(t_list **stack_a, t_list **stack_b, t_flags *flags);
int		pb(t_list **stack_a, t_list **stack_b, t_flags *flags);
int		ra(t_list **stack_a, t_flags *flags);
int		rb(t_list **stack_b, t_flags *flags);
int		rr(t_list **stack_a, t_list **stack_b, t_flags *flags); // NOT USED yet
int		rra(t_list **stack_a, t_flags *flags);
int		rrb(t_list **stack_b, t_flags *flags);
int		rrr(t_list **stack_a, t_list **stack_b, t_flags *flags);
int		sa(t_list **stack_a, t_flags *flags);
int		sb(t_list **stack_b, t_flags *flags);
int		ss(t_list **stack_a, t_list **stack_b, t_flags *flags);

// flags_util.c
char	**parse_flags(char **arg, t_flags *flags);

// print_utils.c
void	ft_print_stack(t_list *stack_a, char *name);
void	print_flags(t_flags *flags);

// compute_disorder.c
float	compute_disorder(t_list **stack_a);

// bench.c
void	print_bench(float disorder, t_flags *flags);

/* ALGORITHMs */

// simple.c
void	ft_simple(t_list **stack_a, t_list **stack_b, t_flags *flags);

// algo_utils.c
int		find_min_val(t_list *stack);
int		find_max_val(t_list *stack);
int		find_max_pos(t_list *stack);
int		ft_sqrt(int number);

// insert_sort.c
void	insert_sort(t_list **a, t_list **b, t_flags *f);

// insert_sort_utils.c
t_list	*find_min(t_list *stack);
t_list	*find_max(t_list *stack);
t_list	*get_target(t_list *stack, int val, char mode);
int		get_moves(t_list *stack, t_list *target);
int		get_cost(t_list *a, t_list *b, t_list *node);

// radix_sort.c
void	ft_radix_sort(t_list **a, t_list **b, t_flags *flags);
// medium.c
void	chunk_sort(t_list **stack_a, t_list **stack_b, t_flags *flags);

// chunk_quick_sort.c
// void	index_stack(t_list *stack);
// void	run_pure_quick_sort(t_list **stack_a, t_list **b, t_flags *flags);
// void	chunk_quick_sort(t_list **a, t_list **b, t_flags *flags);
// void	push_back_to_a(t_list **stack_a, t_list **stack_b, t_flags *flags);

// qs.c
// void	quick_sort_a(t_list **a, t_list **b, int size, t_flags *flags);

/* FT_PRINTF */
int		ft_printf_fd(int fd, char const *format, ...);
int		ft_putstr_fd(char *str, int fd);
int		ft_putnbr_fd(long nbr, int fd);
int		ft_puthex_fd(unsigned long long nb, int is_uppercase, int fd);
int		ft_putptr_fd(void *ptr, int fd);
int		ft_putfloat_fd(double num, int precision, int fd);

#endif
