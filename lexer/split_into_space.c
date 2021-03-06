/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:34:35 by gopal             #+#    #+#             */
/*   Updated: 2022/07/04 15:56:20 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the idea of the function: checking for closed quotes -
// if after running flag_open != 0 - Error!!!
// and it also reports that the necessary quotation 
// mark is not closed (stored in flag_open)
// Example: ls "text - not valid 👺 ls text" -

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

// split_into_space and split_into_spec_sim can be combined and simplified
// the second function has an overly complicated implementation
// by inserting into the middle of the list

void	split_into_tokens(char *str, t_list **tokens)
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
