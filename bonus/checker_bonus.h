/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:05:31 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/09 20:12:48 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int				val;
	struct s_list	*next;
}	t_list;

// ft_split_bonus.c
char	**ft_split(char const *s, char c);

// checker_utils_bonus.c
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isnum(char *num);
void	free_stack(t_list **stack);
void	free_string(char **str);

// lst_utils.c
int		ft_lstadd_back(t_list **stack, char *c);

// apply_move.c
void	apply_move(t_list **stack_a, t_list **stack_b, char *move);

#endif
