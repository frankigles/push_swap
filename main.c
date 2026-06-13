/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:11:23 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/11 19:47:42 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	handle_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		write(1, &msg[i++], 1);
	write(1, "\n", 1);
	exit(0);
}

void	free_stack(t_list **stack)
{
	t_list	*current;
	t_list	*next;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}

int	init(t_list **stack, char **argv, t_flags *flags)
{
	int		i;

	argv = parse_flags(argv, flags);
	if (!*argv)
		return (0);
	if (argv[1] == NULL)
		argv = ft_split(*argv, ' ');
	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
	{
		if (!ft_isnum(argv[i]) || !ft_lstadd_back(stack, argv[i]))
			return (0);
		i++;
	}
	if (argv[1] == NULL)
		free_string(argv);
	return (1);
}

void	alg_sele(t_list **stack_a, t_list **stack_b, float dis, t_flags *flags)
{
	if (!*stack_a || !(*stack_a)->next)
		return ;
	if (flags->simple)
		insert_sort(stack_a, stack_b, flags);
	if (flags->medium)
		chunk_sort(stack_a, stack_b, flags);
	if (flags->complex)
		ft_radix_sort(stack_a, stack_b, flags);
		// quick_sort_a(stack_a, stack_b, ft_lstsize(*stack_a), flags);
		// chunk_quick_sort(stack_a, stack_b, flags);
	if (flags->adaptive && dis < 0.2)
		return (insert_sort(stack_a, stack_b, flags));
	if (flags->adaptive && dis < 0.5)
		return (chunk_sort(stack_a, stack_b, flags));
	if (flags->adaptive)
		ft_radix_sort(stack_a, stack_b, flags);
		// insert_sort(stack_a, stack_b, flags); // should go O(n log n) with dis > 0.5
		// quick_sort_a(stack_a, stack_b, ft_lstsize(*stack_a), flags);
		// chunk_quick_sort(stack_a, stack_b, flags);
		// ft_radix_sort(stack_a, stack_b, flags);
		// quick_sort_a(stack_a, stack_b, ft_lstsize(*stack_a), flags);
		// chunk_quick_sort(stack_a, stack_b, flags);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	float	disorder;
	t_flags	flags;

	if (argc < 2)
		return (-1);
	argv++;
	stack_a = NULL;
	stack_b = NULL;
	if (!init(&stack_a, argv, &flags))
		return (handle_error("Error"), -1);
	// print_flags(&flags);
	disorder = compute_disorder(&stack_a);
	if (!is_sorted(&stack_a))
		alg_sele(&stack_a, &stack_b, disorder, &flags);
	if (flags.bench)
		print_bench(disorder, &flags);
	// ft_print_stack(stack_a, "final A");
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
