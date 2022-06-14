/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:07:36 by gopal             #+#    #+#             */
/*   Updated: 2022/06/14 18:35:01 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_open_q(char c, char *flag_open);

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

// идея функции: проверки на закрытые кавычки - если после прогона flag_open != 0 - Error!!!
// пайп в начале и в конце - ящик пандоры, редирект без пары - очень грустный - Error

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

int	cnt_len_word(char *str, int i)
{
	int j;

	j = i;
	while (!ft_isspace(str[j]) && str[j] != '\0')
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

void	check_open_q(char c, char *flag_open)
{
	if (!*flag_open && (c == '\'' || c ==  '"'))
		*flag_open = c;
	else if (*flag_open && c == *flag_open)
		*flag_open = 0;
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

// 3 типа редиректа и heredoc, а также пайп
// еще можно раздеть кавычки у строк, и склеить слипшие строки
// нужно поделить слова между < << > >> | 

// связные списки (или массивы?) для редиректов (с 3 типами) и команд между пайпами
// по сути нужен список команд для  pipex с бонусами

void	print_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		printf("%i - %s\n", i, list->content);
		list = list->next;
	}
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
	// нарезка между спец символами
	t_list	*list;
	char	*word;
	int		i;
	int		j;
	char	flag_open;

	list = *tokens;
	while (list)
	{
		word = list->content;
		i = 0;
		char *part1 = NULL;
		char *part2 =  NULL;
		char *part3 = NULL;
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

char	*parser(char *input, char **env)
{
	char *str;
	int i;
	// int j;
	t_list	*tokens = NULL;
	// char	*word;
	char	flag_open;

	str = ft_strtrim(input, " \t\v\f\r"); 
	free(input);
	// if (*str == '\0') // по идее здесь это обработается
	// 	return (str);
	flag_open = 0;
	i = 0;
	
	// цикл нарезает по пробелам, но за кавычками (не учитывает пайпы и редиректы ls|ls file1>file2)
	split_into_space(str, &tokens);
	puts("Tokens");
	print_list(tokens);
	
	t_list *list = tokens;
	list = tokens;

	insert_env_var(tokens, env);

	// < << > >> | - сами по себе токены, поэтому подлежать выпиливания из строки
	list = tokens;

	// нарезка между спец символами
	split_into_spec_sym(&tokens);
	

	strip_quotes(tokens);

	delete_empty_tokens(&tokens);
	//  вывод списка
	puts("Tokens 2");
	print_list(tokens);
	list = tokens;
	// проверка на пустую душу??????

	// определить что из токенов команды, редиректы и аргументы и кидать в спискок
	// <lo cmd arg1 arg2 arg3 | cmd 2 <redi1 <redir2 | cmd3 >redir4

	// list = tokens;
	// t_list *list_commands = NULL;
	// char *token;
	// t_list *node;
	// t_command	*cmd;
	// while (list)
	// {
	// 	token = list->content;
	// 	// для меня все логично
	// 	// if (ft_strcmp(token, "|")) { ладно пока оставлю, возможно буду переписывать
	// 		cmd = (t_command *) malloc(sizeof(t_command));

	// 		cmd->redirects_read = NULL;
	// 		cmd->redirects_write = NULL;
	// 		cmd->fd_read = -1;
	// 		cmd->fd_write = -1;
	// 		cmd->args = NULL;
	// 		cmd->cmd_name = NULL;

	// 		// нет я не выхожу из этого цикла ()
	// 		// цикл можно открыть здесь
	// 		while (ft_strncmp(token, "|", 1) && list)
	// 		{
	// 			token = list->content;
	// 			// давай просто опишем все случаи
	// 			// 1) Если токен == >> или > то вызвать f() которые заносить токены на запись в команде (next само собой)
	// 			// 2) Если токен == < или << то вызвать f() которые заносить токены на чтение в команде
	// 			// 3) если это не редир то аргументы
	// 			// ну ладно вроде все распланировали
				
	// 			list = list->next;
	// 		}
			
	// 		// тут внутри можно прыгать по листу до тех пор пока не встретим | или NULL
	// 		// ну сначала заполняем команду и зачем закидываем в лист
	// 		// не когда команда закончена тогда закидываю - так я задумал - 
	// 		node = ft_lstnew((void *) cmd);
	// 		ft_lstadd_back(&list_commands, node); //он закончить эту строку
	// 	// }
	// 	if (list)
	// 		list = list->next;
	// }


	ft_lstclear(&tokens, free);
	return(str);
}


