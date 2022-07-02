/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:40:36 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 04:12:32 by gopal            ###   ########.fr       */
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

int	is_sym_var_env(char c)
{
	return (ft_isalnum(c) || c == '_');
}
