/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:15 by gopal             #+#    #+#             */
/*   Updated: 2022/07/03 14:41:07 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*make_tokens(char **input, char **env)
{
	char			*str;
	static t_list	*tokens;

	tokens = NULL;
	str = ft_strtrim(*input, " \t\n\v\f\r");
	if (*str)
	{
		split_into_tokens(str, &tokens);
		insert_env_var_tokens(tokens, env);
		strip_quotes(tokens);
	}
	free(str);
	return (tokens);
}

void	lexer(char **input, t_shell *shell)
{
	char	**env;

	env = make_env(shell);
	shell->list_tokens = make_tokens(input, env);
}
