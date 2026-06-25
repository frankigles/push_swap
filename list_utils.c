/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:57:43 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/25 22:33:47 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ft_lstnew(int value)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->val = value;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstadd_back(t_list **stack, char *c)
{
	t_list	*last_node;
	t_list	*new_node;
	long	num;

	num = ft_atoi(c);
	if (num < -2147483648 || num > 2147483647 || ft_lsthas(*stack, (int)num))
		return (0);
	new_node = ft_lstnew(num);
	if (!new_node)
		return (free_stack(stack), 0);
	if (!*stack)
	{
		*stack = new_node;
		return (1);
	}
	last_node = ft_lstlast(*stack);
	last_node->next = new_node;
	return (1);
}

int	ft_lstsize(t_list *head)
{
	size_t	size;
	t_list	*tmp;

	tmp = head;
	size = 0;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

int	ft_lsthas(t_list *head, int value)
{
	while (head)
	{
		if (head && head->val == value)
			return (1);
		head = head->next;
	}
	return (0);
}
