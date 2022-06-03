/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:07:36 by gopal             #+#    #+#             */
/*   Updated: 2022/06/03 10:19:47 by gopal            ###   ########.fr       */
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
// $
// промотка цифр
// нахождение длины старта и конца переменной
// замена переменной на значение из окружения
// $

void	check_open_q(char c, char *flag_open)
{
	if (!*flag_open && (c == '\'' || c ==  '"'))
	{
		*flag_open = c;
	}
	else if (*flag_open && c == *flag_open)
	{
		*flag_open = 0;
	}
}

// 012345678
// ***ret
// ***ret***
// ret***

int	is_sym_var_env(char c)
{
	return (ft_isalnum(c) || c =='_');
}

char	*find_var_env(char *key, char **env)
{
	char	*value;
	char	*result;
	int		len;

	key = ft_strjoin_f(key, "=", 1);
	len = ft_strlen(key);
	while (*env && ft_strncmp(*env, key, len))
		env++;
	result = NULL;
	if (*env)
	{
		value = *env + len;
		result = ft_substr(value, 0, ft_strlen(value));
	}
	return (result);
}

void	replace_var_env(char **word, int start, int end, char *var)
{
	char	*part1;
	char	*part2;
	int		len;

	part1 = NULL;
	part2 = NULL;
	len = ft_strlen(*word);
	if (start)
		part1 = ft_substr(*word, 0, start);
	if (len - end - 1)
		part2 = ft_substr(*word, end + 1, len - end - 1);
	if (!var)
	{
		if (!part1 && !part2)
			*word = ft_strdup("");
		else if (part1 && !part2)
			*word = part1;
		else if (!part1 && part2)
			*word = part2;
		else if (part1 && part2)
			*word = ft_strjoin_f(part1, part2, 3);
	}
	else
	{
		if (!part1 && !part2)
			*word = var;
		else if (part1 && !part2)
			*word = ft_strjoin_f(part1, var, 1);
		else if (!part1 && part2)
			*word = ft_strjoin_f(var, part2, 2);
		else if (part1 && part2)
		{
			*word = ft_strjoin_f(part1, var, 3);
			*word = ft_strjoin_f(*word, part2, 3);
		}
	}
}

char	*parser(char *input, char **env)
{
	char *str = ft_strtrim(input, " \t\v\f\r");
	int i;
	int j;
	t_list	*tokens = NULL;
	char	*word;

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
	t_list *list = tokens;
	while (list)
	{
		i++;
		printf("%i - %s\n", i, list->content);
		list = list->next;
	}
	
	list = tokens;

	while (list)
	{
		word = list->content;
		i = 0;
		char flag_open = 0;
		while (word[i])
		{
			check_open_q(word[i], &flag_open);
			if (word[i] == '$' && !flag_open)
			{
				i++;
				j = i;
				if (ft_isdigit(word[j]))
				{
					while (ft_isdigit(word[j]))
						j++;
					replace_var_env((char **)&list->content, i - 1, j - 1, NULL);
					word = list->content;
					i = 0;
					continue;
				}
				if (is_sym_var_env(word[j]))
				{
					while (is_sym_var_env(word[j]))
						j++;
					char *word2 = ft_substr(word, i, j - i);
					char *value = find_var_env(word2, env);
					replace_var_env((char **)&list->content, i - 1, j - 1, value);
					word = list->content;
					i = 0;
					continue;
				}
			}
			i++;
		}
		list = list->next;
	}

	list = tokens;
	puts("Tokens 2");
	i = 0;
	while (list)
	{
		i++;
		printf("%i - %s\n", i, list->content);
		list = list->next;
	}

	ft_lstclear(&tokens, free);

	free(input);
	return(str);
}


