/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:07:36 by gopal             #+#    #+#             */
/*   Updated: 2022/06/01 13:16:52 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	cnt_len_word(char *str, int i)
{
	int j;

	j = i;
	while (!isspace(str[j]) && str[j])
	{
		if (str[j] == '\'')
		{
			j++;
			while (str[j] && str[j] != '\'')
				j++;
			if (str[j] == '\'')
				j++;
		}
		else if (str[j] == '\"')
		{
			j++;
			while (str[j] && str[j] != '\"')
				j++;
			if (str[j] == '\"')
				j++;
		}
		else
			j++;
	}
	return (j);
}

char	*parser(char *input, char **env)
{
	char *str = ft_strtrim(input, " \t\v\f\r");
	int i;
	int j;
	t_list	*tokens = NULL;
	char	*word;
	(void)env;

	i = 0;
	while (str[i] != '\0')
	{
		while (isspace(str[i]))
			i++;
		j = cnt_len_word(str, i);
		word = ft_substr(str, i, j - i);
		ft_lstadd_back(&tokens, ft_lstnew(word));
		i = j;
	}
	puts("Tokens");
	i = 0;
	while (tokens)
	{
		i++;
		printf("%i - %s\n", i, tokens->content);
		tokens = tokens->next;
	}
	
	ft_lstclear(&tokens, free);

	free(input);
	return(str);
}


