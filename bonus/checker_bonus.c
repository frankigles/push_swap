/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraigles <fraigles@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:56:39 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/23 22:04:39 by fraigles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include "gnl/get_next_line.h"

void	free_stack_bonus(t_list **stack)
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

int	is_sorted(t_list **stack)
{
	t_list	*current;

	if (!*stack)
		return (1);
	current = *stack;
	while (current->next)
	{
		if (current->val > current->next->val)
			return (0);
		current = current->next;
	}
	return (1);
}

int	init(t_list **stack, char **argv)
{
	int		i;
	int		allocated;

	if (!*argv)
		return (0);
	if (argv[1] == NULL)
	{
		argv = ft_split(*argv, ' ');
		if (!argv)
			return (0);
		allocated = 1;
	}
	i = 0;
	while (argv[i])
	{
		if (!ft_isnum(argv[i]) || !ft_lstadd_back(stack, argv[i]))
		{
			if(allocated)
				free_string(argv);
			free_stack(stack);
			return (0);
		}
		i++;
	}
	if (allocated)
		free_string(argv);
	return (1);
}

void	checker(t_list **stack_a, t_list **stack_b)
{
	char	*line;
	int		i;

	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
		line[i] = '\0';
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		apply_move(stack_a, stack_b, line);
		free(line);
	}
	if (is_sorted(stack_a) && !(*stack_b))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	stack_a = NULL;
	stack_b = NULL;
	argv++;
	if (!init(&stack_a, argv))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	checker(&stack_a, &stack_b);
	free_stack_bonus(&stack_a);
	free_stack_bonus(&stack_b);
	return (0);
}
