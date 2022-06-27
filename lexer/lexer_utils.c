/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:40:36 by gopal             #+#    #+#             */
/*   Updated: 2022/06/27 18:40:33 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	check_open_q(char c, char *flag_open)
{
	if (!*flag_open && is_quote(c))
		*flag_open = c;
	else if (*flag_open && c == *flag_open)
		*flag_open = 0;
}

int	is_spec_sym(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_single_token(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (!is_spec_sym(word[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_sym_var_env(char c)
{
	return (ft_isalnum(c) || c == '_');
}
