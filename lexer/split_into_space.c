/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:34:35 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 03:52:03 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skiper_spaces(char *str, int *i, char *flag_open)
{
	int	j;

	while (ft_isspace(str[*i]))
		(*i)++;
	j = *i;
	check_open_q(str[j], flag_open);
	while (str[j]
		&& (!ft_isspace(str[j]) || (ft_isspace(str[j]) && *flag_open)))
	{
		j++;
		check_open_q(str[j], flag_open);
	}
	return (j);
}

// split_into_space и split_into_spec_sym можно объединить и упростить
// у второй функции слишком усложненная реализация 
// через вставку в середину списка

void	split_into_space(char *str, t_list **tokens)
{
	int		i;
	int		j;
	char	*word;
	char	flag_open;

	i = 0;
	flag_open = 0;
	while (str[i] != '\0')
	{
		j = skiper_spaces(str, &i, &flag_open);
		word = ft_substr(str, i, j - i);
		ft_lstadd_back(tokens, ft_lstnew(word));
		i = j;
	}
}
