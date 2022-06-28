/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:18:49 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 08:48:44 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(key);
	if (*env)
	{
		value = *env + len;
		result = ft_substr(value, 0, ft_strlen(value));
	}
	return (result);
}

void	glue_parts(char **word, char *part1, char *part2, char *var)
{
	if (!var)
	{
		if (!part1 && !part2)
			*word = ft_strdup("");
		if (part1 && !part2)
			*word = part1;
		if (!part1 && part2)
			*word = part2;
		if (part1 && part2)
			*word = ft_strjoin_f(part1, part2, 3);
	}
	else
	{
		if (!part1 && !part2)
			*word = var;
		if (part1 && !part2)
			*word = ft_strjoin_f(part1, var, 3);
		if (!part1 && part2)
			*word = ft_strjoin_f(var, part2, 3);
		if (part1 && part2)
		{
			*word = ft_strjoin_f(part1, var, 3);
			*word = ft_strjoin_f(*word, part2, 3);
		}
	}
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
	glue_parts(word, part1, part2, var);
}

void	insert_env_var(char **ptr_word, char *word, char **env)
{
	char	flag_open;
	char	*value;
	int		i;
	int		j;

	flag_open = 0;
	i = -1;
	while (word[++i])
	{
		check_open_q(word[i], &flag_open);
		if (word[i] == '$' && flag_open != '\'' && word[i + 1])
		{
			j = ++i;
			value = NULL;
			if (ft_isdigit(word[j]) || word[j] == '$')
				j++;
			else if (is_sym_var_env(word[j]))
				value = find_var_env(get_key(word, &i, &j), env);
			replace_var_env(ptr_word, i - 1, j - 1, value);
			word = *ptr_word;
			i = -1;
		}
	}
}

void	insert_env_var_tokens(t_list *list, char **env)
{
	char	*word;
	char	**ptr_word;

	while (list)
	{
		word = list->content;
		ptr_word = (char **) &list->content;
		insert_env_var(ptr_word, word, env);
		list = list->next;
	}
}
