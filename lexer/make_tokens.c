/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:45:15 by gopal             #+#    #+#             */
/*   Updated: 2022/06/17 18:13:22 by gopal            ###   ########.fr       */
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

int	skiper_spaces(char *str, int *i, char *flag_open)
{
	int j;

	while (ft_isspace(str[*i]))
		(*i)++;
	j = *i;
	check_open_q(str[j], flag_open);
	while (str[j] && (!ft_isspace(str[j]) || (ft_isspace(str[j]) && *flag_open)))
	{
		j++;
		check_open_q(str[j], flag_open);
	}
	return (j);
}

int	is_sym_var_env(char c)
{
	return (ft_isalnum(c) || c =='_');
}

int	is_spec_sym(char c)
{
	return (c == '>' || c == '<' || c == '|');
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
	free(key);
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
			*word = ft_strjoin_f(part1, var, 3);
		else if (!part1 && part2)
			*word = ft_strjoin_f(var, part2, 3);
		else if (part1 && part2)
		{
			*word = ft_strjoin_f(part1, var, 3);
			*word = ft_strjoin_f(*word, part2, 3);
		}
	}
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

void	split_into_space(char *str, t_list **tokens)
{
	int		i;
	int		j;
	char	*word;
	char	flag_open;

	i = 0;
	flag_open = 0;
	while (str[i] != '\0')
	{
		j = skiper_spaces(str, &i, &flag_open);
		word = ft_substr(str, i, j - i);
		ft_lstadd_back(tokens, ft_lstnew(word));
		i = j;
	}
}

void	split_into_spec_sym(t_list **tokens)
{
	t_list	*list;
	char	*word;
	int		i;
	int		j;
	char	flag_open;
	char	*part1;
	char	*part2;
	char	*part3;

	list = *tokens;
	while (list)
	{
		word = list->content;
		i = 0;
		part1 = NULL;
		part2 =  NULL;
		part3 = NULL;
		flag_open = 0;
		if (is_single_token(word))
		{
			list = list->next;
			continue;
		}
		while (word[i])
		{			
			check_open_q(word[i], &flag_open);
			j = i;
			// это скип для первого слова
			while ((!is_spec_sym(word[j]) && word[j] != '\0')
				|| (is_spec_sym(word[j]) && flag_open))
			{
				j++;
				check_open_q(word[j], &flag_open);
			}
			//
			if (!word[j]) // если 1е слово идет до конца строки, то резать нечего
			{
				i = j;
				break;
			}
			if (j > i)
				part1 = ft_substr(word, i, j - i);
			i = j;
			while (is_spec_sym(word[j]))
				j++;
			part2 = ft_substr(word, i, j - i);
			part3 = NULL;
			if (word[j]) {
				i = j;
				while (word[j])
					j++;
				part3 = ft_substr(word, i, j - i);
			}

			t_list *tail;
			tail = list->next;
			free(word); 
			if (part1)
			{
				list->content = part1;
				list->next = ft_lstnew(part2);
				if (part3)
				{
					list->next->next = ft_lstnew(part3);
					list->next->next->next = tail;
					word = part3;
					i = 0;
					break;
				}
				else
				{	
					list->next->next = tail;
					list = list->next;
					break;
				}
			}
			else
			{
				list->content = part2;
				if (part3)
				{
					list->next = ft_lstnew(part3);
					list->next->next = tail;
					break;
				}
			}
			i++;
		}
		list = list->next;
	}
}

void	strip_quotes(t_list *tokens)
{
	char	*word;
	char	*result;
	char	flag_open;
	int		i;
	int		j;

	while (tokens)
	{
		word = tokens->content;
		flag_open = 0;
		i = 0; // можно покумекать как сократить код потом (типа инверсия условии)
		j = 0;
		while (word[i] != '\0')
		{
			if (!flag_open && is_quote(word[i]))
				flag_open = word[i];
			else if (flag_open && word[i] == flag_open)
				flag_open = 0;
			else
				j++;
			i++;
		}
		result = (char *) ft_calloc(j + 1, 1);
		i = 0;
		j = 0;
		while (word[i] != '\0')
		{
			if (!flag_open && is_quote(word[i]))
				flag_open = word[i];
			else if (flag_open && word[i] == flag_open)
				flag_open = 0;
			else
				result[j++] = word[i];
			i++;
		}
		tokens->content = result;
		free(word);
		tokens = tokens->next;
	}
}

void	delete_empty_tokens(t_list **tokens) // а если нужно удалить первое значение? и больше ничего нет
{
	t_list	*tail;
	t_list	*list;
	char	*word;

	list = *tokens;
	while (list)
	{
		word = list->content;
		tail = list->next;
		if (*word == '\0')
		{
			ft_lstdelone(list, free);
			*tokens = tail;
			list = *tokens;
			continue ;
		}
		else if (tail) // здесь убеждаемся в том, что это не конец списка
		{
			word = tail->content;
			if (!ft_strncmp(word, "", 1)) // надо проверить что он не последний
			{
				ft_lstdelone(tail, free);
				if (tail->next)
					list->next = tail->next;
				else
					list->next = NULL;
			}
		}
		list = list->next; 
	}
}

void	insert_env_var(t_list *list, char **env)
{
	char	*word;
	char	flag_open;
	int		i;
	int		j;

	while (list)
	{
		word = list->content;
		i = 0;
		flag_open = 0;
		while (word[i])
		{
			check_open_q(word[i], &flag_open);
			if (word[i] == '$' && flag_open != '\'')
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
}

t_list	**make_tokens(char **input, char**env)
{
	char	*str;
	t_list	**tokens = NULL;

	str = ft_strtrim(*input, " \t\v\f\r");
	if (!*str)
	{
		free(*input);
		*input = str;
		return (tokens);
	}

	tokens = ft_calloc(1, sizeof(t_list **));
	split_into_space(str, tokens);
	insert_env_var(*tokens, env);
	split_into_spec_sym(tokens); 
	strip_quotes(*tokens);
	delete_empty_tokens(tokens);
	free(str);
	return (tokens);
}
