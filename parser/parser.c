/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:07:36 by gopal             #+#    #+#             */
/*   Updated: 2022/06/09 14:27:47 by gopal            ###   ########.fr       */
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

int	is_spec_sym(char c)
{
	return (c == '>' || c == '<' || c == '|') ;
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

// 3 типа редиректа и heredoc, а также пайп
// еще можно раздеть кавычки у строк, и склеить слипшие строки
// нужно поделить слова между < << > >> | 

// связные списки (или массивы?) для редиректов (с 3 типами) и команд между пайпами
// по сути нужен список команд для  pipex с бонусами

char	*parser(char *input, char **env)
{
	char *str = ft_strtrim(input, " \t\v\f\r");
	int i;
	int j;
	t_list	*tokens = NULL;
	char	*word;
	char	flag_open;

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
		flag_open = 0;
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

	// < << > >> | - сами по себе токены, поэтому подлежать распилу
	list = tokens;

	while (list)
	{
		word = list->content;
		i = 0;
		// если это строка, то "fr|as" просто строка
		char *part1 = NULL;
		char *part3 = NULL;
		flag_open = 0;
		if (is_single_token(word))
		{
			list = list->next;
			continue;
		}
		while (word[i])
		{
			// пример: cat|ls преобразуется в  <cat> <|> <ls>
			// пример: cat<<ls преобразуется в  cat << ls
			// пример: cat| преобразуется в  <cat> <|>
			// пример: |ls преобразуется в <|> <ls>
			
			check_open_q(word[i], &flag_open);
			if (!flag_open)
			{
				j = i;
				while (!is_spec_sym(word[j]) && !is_quote(word[j]) && word[j] != '\0')
					j++;
				if (!word[j])
				{
					i = j;
					break;
				}
				if (j > i)
					part1 = ft_substr(word, i, j - i);
				i = j;
				while (is_spec_sym(word[j]))
					j++;
				char *part2 = ft_substr(word, i, j - i);
				// есть два исхода: ls| или ls|ls 
				part3 = NULL;
				if (word[j]) {
					i = j;
					while (word[j])
						j++;
					part3 = ft_substr(word, i, j - i);
				}
				// есть некое слово word, который мы разделили на 2-3 части
				// нужно в середину связного списка засунуть еще 3 слова
				t_list *tail = list->next;
				free(word);
				if (part1)
				{
					list->content = part1;
					list->next = ft_lstnew(part2);
					if (part3)
					{
						list->next->next = ft_lstnew(part3);
						list->next->next->next = tail;
						// list = list->next->next;
						list = list->next;
						word = part3;
						i = 0;
						break;
					}
					else {
						list->next->next = tail;
						list = list->next;
					}
				}
				else {
					list->content = part2;
					if (part3)
					{
						list->next = ft_lstnew(part3);
						list->next->next = tail;
						word = part3;
						i = 0;
						break;
					}
					else {
						// тут случай когда нет и part1 и part3 но есть part2
						// тогда резать никого не надо, но по идее этого не случиться
						// из-за проверку сверху функцией is_single_token
						puts("Но это случилось!");
					}
				}
			}
			i++;
		}
		list = list->next;
	}

	//  вывод списка
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


