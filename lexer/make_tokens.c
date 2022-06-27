/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:15 by gopal             #+#    #+#             */
/*   Updated: 2022/06/27 18:41:05 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**make_tokens(char **input, char **env)
{
	char	*str;
	t_list	**tokens;

	tokens = NULL;
	str = ft_strtrim(*input, " \t\v\f\r");
	if (*str)
	{
		tokens = ft_calloc(1, sizeof(t_list **));
		split_into_space(str, tokens);
		insert_env_var_tokens(*tokens, env);
		split_into_spec_sym(tokens);
		strip_quotes(*tokens);
		// delete_empty_tokens(tokens);
	}
	free(str);
	return (tokens);
}

// echo "" hello   --- печатает ' hello' то есть пустая строка это тоже аргумент
// под вопросом эта функция delete_empty_tokens(tokens);
