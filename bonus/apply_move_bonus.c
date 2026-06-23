/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraigles <fraigles@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 20:30:33 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/23 21:46:54 by fraigles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	swap_top(t_list **stack)
{
	int	tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = (*stack)->val;
	(*stack)->val = (*stack)->next->val;
	(*stack)->next->val = tmp;
}

static void	push(t_list **dst, t_list **src)
{
	t_list	*tmp;

	if (!*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dst;
	*dst = tmp;
}

static void	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	*stack = first->next;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
}

static void	rev_rotate(t_list **stack)
{
	t_list	*prev;
	t_list	*last;

	if (!*stack || !(*stack)->next)
		return ;
	prev = NULL;
	last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	apply_move(t_list **stack_a, t_list **stack_b, char *move)
{
	if (!ft_strcmp(move, "sa"))
		swap_top(stack_a);
	else if (!ft_strcmp(move, "sb"))
		swap_top(stack_b);
	else if (!ft_strcmp(move, "ss"))
		return (swap_top(stack_a), swap_top(stack_b));
	else if (!ft_strcmp(move, "pa"))
		push(stack_a, stack_b);
	else if (!ft_strcmp(move, "pb"))
		push(stack_b, stack_a);
	else if (!ft_strcmp(move, "ra"))
		rotate(stack_a);
	else if (!ft_strcmp(move, "rb"))
		rotate(stack_b);
	else if (!ft_strcmp(move, "rr"))
		return (rotate(stack_a), rotate(stack_b));
	else if (!ft_strcmp(move, "rra"))
		rev_rotate(stack_a);
	else if (!ft_strcmp(move, "rrb"))
		rev_rotate(stack_b);
	else if (!ft_strcmp(move, "rrr"))
	{
		rev_rotate(stack_a);
		rev_rotate(stack_b);
	}
	else
	{
		write(2, "Error\n", 6);
		free_stack(stack_a);
		free_stack(stack_b);
		exit(1);
	}
}
