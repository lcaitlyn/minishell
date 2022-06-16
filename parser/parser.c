/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:07:36 by gopal             #+#    #+#             */
/*   Updated: 2022/06/16 03:29:59 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_open_q(char c, char *flag_open);
void	free_list_cmd(void *cmd);

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

// идея функции: проверки на закрытые кавычки - если после прогона flag_open != 0 - Error!!!
// 				 и она также сообщает что не закрыта нужная кавычка (хранится в flag_open)
// Пример: ls "text - не валидно 👺 ls text" - 

// Идея другой функции - проверяет, что пайпы не стоят в начале и в конце
// 						 и проверяет сами токены редиректов
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
	if (!*flag_open && is_quote(c))
		*flag_open = c;
	else if (*flag_open && c == *flag_open)
		*flag_open = 0;
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

// нарезка между спец символами
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

int	is_redirects(char *str)
{
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
			|| !ft_strcmp(str, "<") || !ft_strcmp(str, "<<"));
}

int	is_pipe(char *str)
{
	return (!ft_strcmp(str, "|"));
}

int	is_valid_end_start_tokens(t_list *tokens)
{
	char	*first_token;
	char	*last_token;

	first_token = tokens->content;
	last_token = (ft_lstlast(tokens))->content;
	if (!ft_strcmp(first_token, "|"))
	{
		ft_putstr_fd("Syntax error: '|' cannot stand at the beginning\n", 2 );
		return (0);
	}
	if (!ft_strcmp(last_token, "|"))
	{
		ft_putstr_fd("Syntax error: '|' can't stand at the end\n", 2);
		return (0);
	}
	if (is_redirects(last_token))
	{
		ft_putstr_fd("Syntax error: parse error near '\\n'\n", 2);
		return (0);
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
		if (is_single_token(token))
		{
			if (is_redirects(token) || is_pipe(token))
			{
				tokens = tokens->next;
				continue;
			}
			ft_putstr_fd("Syntax error: invalid token '", 2);
			ft_putstr_fd(token, 2);
			ft_putstr_fd("'\n", 2);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

char	*parser(char *input, char **env)
{
	char *str;
	t_list	*tokens = NULL;
	

	str = ft_strtrim(input, " \t\v\f\r"); 
	free(input);
	wait(0);
	// if (*str == '\0') // по идее здесь это обработается
	// 	return (str);

	// цикл нарезает по пробелам, но за кавычками (не учитывает пайпы и редиректы ls|ls file1>file2)
	split_into_space(str, &tokens);
	insert_env_var(tokens, env);
	split_into_spec_sym(&tokens); // < << > >> | - сами по себе токены, поэтому подлежать выпиливания из строки
	strip_quotes(tokens);
	delete_empty_tokens(&tokens);

	puts("Tokens 2");
	print_list(tokens);

	// проверка на пустую душу??????
	t_list *list_commands = NULL;
	if (is_valid_tokens(tokens))
	{
		// определить что из токенов команды, редиректы и аргументы и кидать в спискок
		// <lo cmd arg1 arg2 arg3 | cmd 2 <redi1 <redir2 | cmd3 >redir4
		t_list	*list;
		char	*token;
		char	*next_token;

		list = tokens;
		// t_list *node;
		t_command	*cmd;
		while (list)
		{
				
			token = list->content;
			if (is_pipe(token))
				continue;
			cmd = (t_command *) malloc(sizeof(t_command));

			cmd->redirects_read = NULL;
			cmd->redirects_write = NULL;
			cmd->fd_read = -1;
			cmd->fd_write = -1;
			cmd->args = NULL;
			cmd->list_args = NULL;
			cmd->cmd_name = NULL;


			while (!is_pipe(token) && list)
			{
				token = list->content; // повторояет строку 526
				if (is_redirects(token))
				{
					if (list->next)
					{
						next_token = list->next->content;
						if (!is_redirects(next_token))
						{
							t_redirect *redir = (t_redirect *) malloc(sizeof(t_redirect));
							// redir->type_redir = token;
							redir->type_redir = ft_strdup(token);
							redir->file_name = ft_strdup(next_token);
							if (!ft_strcmp(token, "<") || !ft_strcmp(token, "<<"))
								ft_lstadd_back(&cmd->redirects_read, ft_lstnew(redir));
							if (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>"))
								ft_lstadd_back(&cmd->redirects_write, ft_lstnew(redir));
							list = list->next->next;
							continue ;
						}
						else
						{
							ft_putstr_fd("Oh! два спец токена не могут быть рядом", 2);
						}
					}
					else
					{
						// "так получилось, что редирект оказался в конце,
						// хотя такого не может случиться,  ибо есть проверка is_valid_tokens"
						puts("Oh!");
					}
					
				}
				
				if (!cmd->cmd_name)
					cmd->cmd_name = ft_strdup(token);
				ft_lstadd_back(&cmd->list_args, ft_lstnew(ft_strdup(token)));
				
				list = list->next;
			}
			
			// тут внутри можно прыгать по листу до тех пор пока не встретим | или NULL
			// ну сначала заполняем команду и зачем закидываем в лист
			// стоит отметить, что если у команды нет команды но oдни редиректы, то bash ничего не делает
			ft_lstadd_back(&list_commands, ft_lstnew(cmd));
			if (list)
				list = list->next;
		}
	}

	ft_lstclear(&tokens, free);

	// int i = 0;
	
	t_list **list_cmds = &list_commands;

	
	// while(list_commands)
	// {
	// 	// puts("Кря!");
	// 	t_command *command = (t_command *)(list_commands)->content;
	// 	// char *redir = (t_redirect *) command->redirects_write 
	// 	// 	? ((t_redirect *) command->redirects_write->content)
	// 	// 	: NULL;
	// 	printf("%i - cmd - %s\n", ++i, (command->cmd_name));
	// 	printf("args (1st)  - %s, redir to write - %s %s \n",
	// 		command->list_args->content,
	// 		((t_redirect *) command->redirects_write->content)->type_redir,
	// 		((t_redirect *) command->redirects_write->content)->file_name);
	// 	printf("redir to read - %s %s \n",
	// 		((t_redirect *) command->redirects_read->content)->type_redir,
	// 		((t_redirect *) command->redirects_read->content)->file_name);

	// 	list_commands = list_commands->next;
	// 	command = NULL;
	// }
	// puts("Кря!");
	
	ft_lstclear(list_cmds, free_list_cmd); // тут не все так просто с функцией очистки
	list_commands = NULL;
	return(str);
}

void	free_redirect(void *redir)
{
	t_redirect *rdr;

	rdr = (t_redirect *) redir;
	free(rdr->file_name);
	free(rdr->type_redir);
	free(rdr);
}

void	free_list_cmd(void *command)
{
	t_command	*cmd;

	cmd = (t_command *) command;
	puts("Cry");
	free(cmd->cmd_name);
	ft_lstclear(&cmd->redirects_read, free_redirect);
	ft_lstclear(&cmd->redirects_write, free_redirect);
	ft_lstclear(&cmd->list_args, free);
	free(cmd);
}
