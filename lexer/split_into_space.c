/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:34:35 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 09:34:55 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_string(char c)
{
	return (!ft_isspace(c) && !is_spec_sym(c));
}

int	is_str_word(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_string(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_length_token(char *str, int *i, char *flag_open)
{
	int	j;

	while (ft_isspace(str[*i]))
		(*i)++;
	j = *i;
	check_open_q(str[j], flag_open);
	if (is_string(str[j]))
	{
		while (str[j]
			&& (is_string(str[j]) || (!is_string(str[j]) && *flag_open)))
		{
			j++;
			check_open_q(str[j], flag_open);
		}
	}
	else if (is_spec_sym(str[j]))
	{
		while (str[j] && is_spec_sym(str[j]))
			j++;
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
		j = get_length_token(str, &i, &flag_open);
		word = ft_substr(str, i, j - i);
		ft_lstadd_back(tokens, ft_lstnew(word));
		i = j;
	}
}
