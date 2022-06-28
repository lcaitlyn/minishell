/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:15 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 14:09:33 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_tokens(char **input, char **env, t_shell *shell)
{
	char	*str;
	t_list	**tokens;

	str = ft_strtrim(*input, " \t\v\f\r");
	if (*str)
	{
		tokens = ft_calloc(1, sizeof(t_list **));
		split_into_tokens(str, tokens);
		insert_env_var_tokens(*tokens, env);
		strip_quotes(*tokens);
		shell->list_tokens = tokens;
	}
	free(str);
}

void	lexer(char **input, t_shell *shell)
{
	char	**env;

	env = make_env(shell);
	make_tokens(input, env, shell);
}
