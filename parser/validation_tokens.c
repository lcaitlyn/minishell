/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:49:37 by gopal             #+#    #+#             */
/*   Updated: 2022/07/03 03:55:34 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_end_start_tokens(t_list *tokens)
{
	char	*first_token;
	char	*last_token;

	first_token = tokens->content;
	last_token = (ft_lstlast(tokens))->content;
	if (!ft_strcmp(first_token, "|"))
	{
		ft_putendl_fd("Syntax error: '|' cannot stand at the beginning", 2);
		return (0);
	}
	if (!ft_strcmp(last_token, "|"))
	{
		ft_putendl_fd("Syntax error: '|' can't stand at the end", 2);
		return (0);
	}
	if (is_redirects(last_token))
	{
		ft_putendl_fd("Syntax error: parse error near '\\n'", 2);
		return (0);
	}
	return (1);
}
// если есть пайп в конце, то мы должны дополнить ввод и добавить эту комманду в историю
// 

int	check_redirect_tokens(char *token, t_list *next_node_token)
{
	char	*next_token;

	if (next_node_token)
	{
		next_token = next_node_token->content;
		if (is_redirects(token) && (is_redirects(next_token) || is_pipe(next_token)))
		{
			printf("Syntax error: Invalid token '%s' after redirect '%s'\n", \
				next_token, token);
			return (0);
		}
	}
	return (1);
}

int	check_neighboring_tokens(char *token, t_list *next_node_token)
{
	char	*next_token;

	if (next_node_token)
	{
		next_token = next_node_token->content;
		if (is_spec_token(token) && is_spec_token(next_token))
		{
			printf("Syntax error: '%s' can't stand next to '%s'\n", \
				token, next_token);
			return (0);
		}
	}
	return (1);
}

int	is_valid_tokens(t_list *tokens)
{
	char	*token;

	if (!is_valid_end_start_tokens(tokens))
		return (0);
	while (tokens)
	{
		token = tokens->content;
		if (is_token_only_spec_sym(token) && !is_spec_token(token))
		{
			printf("Syntax error: invalid token '%s'\n", token);
			return (0);
		}
		if (!check_redirect_tokens(token, tokens->next)
			|| !check_neighboring_tokens(token, tokens->next))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
