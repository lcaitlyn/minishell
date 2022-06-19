/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:07:36 by gopal             #+#    #+#             */
/*   Updated: 2022/06/17 18:07:14 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_open_q(char c, char *flag_open);
void	free_list_cmd(void *cmd);



// идея функции: проверки на закрытые кавычки - если после прогона flag_open != 0 - Error!!!
// 				 и она также сообщает что не закрыта нужная кавычка (хранится в flag_open)
// Пример: ls "text - не валидно 👺 ls text" - 

// Идея другой функции - проверяет, что пайпы не стоят в начале и в конце
// 						 и проверяет сами токены редиректов
// пайп в начале и в конце - ящик пандоры, редирект без пары - очень грустный - Error





// int	cnt_len_word(char *str, int i)
// {
// 	int j;

// 	j = i;
// 	while (!ft_isspace(str[j]) && str[j] != '\0')
// 	{
// 		if (str[j] == '\'')
// 		{
// 			j++;
// 			while (str[j] && str[j] != '\'')
// 				j++;
// 			if (str[j] == '\'')
// 				j++;
// 		}
// 		else if (str[j] == '\"')
// 		{
// 			j++;
// 			while (str[j] && str[j] != '\"')
// 				j++;
// 			if (str[j] == '\"')
// 				j++;
// 		}
// 		else
// 			j++;
// 	}
// 	return (j);
// }


// 3 типа редиректа и heredoc, а также пайп
// еще можно раздеть кавычки у строк, и склеить слипшие строки
// нужно поделить слова между < << > >> | 

// связные списки (или массивы?) для редиректов (с 3 типами) и команд между пайпами
// по сути нужен список команд для  pipex с бонусами

void	print_list(t_list *list)
{
	int	i;

	i = 0;
	puts("");
	while (list)
	{
		i++;
		printf("\t%i - %s\n", i, (char *) list->content);
		list = list->next;
	}
}

void	print_redir_list(t_list *list)
{
	int	i;

	i = 0;
	puts("");
	while (list)
	{
		i++;
		printf("\t %i - %s %s\n",  i, 
			((t_redirect *) list->content)->type_redir,
			((t_redirect *) list->content)->file_name);
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

void	print_list_cmds(t_list *list_commands)
{
	t_command	*command;
	char		*name;
	t_list		*redir_read;
	t_list		*redir_write;
	t_list		*args;
	int			i = 0;

	while (list_commands)
	{
		command = (t_command *)(list_commands)->content;
		name = command->cmd_name;
		redir_read = command->redirects_read;
		redir_write = command->redirects_write;
		args = command->list_args;
		printf("--> %i command = - %s <-- \n", ++i, name);

		printf("  rediretcs to read **");
		if (redir_read)
			print_redir_list(redir_read);
		else
			printf(": Empty\n");
		printf("  rediretcs to write **");
		if (redir_write)
			print_redir_list(redir_write);
		else
			printf(": Empty\n");
		printf("  arguments list**");
		if (args)
			print_list(args);
		else
			printf(": Empty\n");
		puts("");
		
		list_commands = list_commands->next;
	}
}

char	*parser(char *input, char **env)
{
	// char	*str;
	t_list	**tokens = NULL;

	tokens = make_tokens(input, env);

	// puts("Tokens:");
	// print_list(tokens);

	// проверка на пустую душу??????
	t_list *list_commands = NULL;
	if (is_valid_tokens(*tokens))
	{
		// определить что из токенов команды, редиректы и аргументы и кидать в спискок
		// <lo cmd arg1 arg2 arg3 | cmd 2 <redi1 <redir2 | cmd3 >redir4
		t_list	*list;
		char	*token;
		char	*next_token;

		list = *tokens;
		// t_list *node;
		t_command	*cmd;
		while (list)
		{
				
			token = list->content;
			if (is_pipe(token))
				continue;
			cmd = (t_command *) malloc(sizeof(t_command));

			cmd->cmd_name = NULL;
			cmd->list_args = NULL;
			cmd->redirects_read = NULL;
			cmd->redirects_write = NULL;
			cmd->args = NULL;
			cmd->fd_read = -1;
			cmd->fd_write = -1;

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

	ft_lstclear(tokens, free);
	print_list_cmds(list_commands);
	ft_lstclear(&list_commands, free_list_cmd); // тут не все так просто с функцией очистки
	list_commands = NULL;
	return(ft_strdup("Zaglushka"));
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
	free(cmd->cmd_name);
	ft_lstclear(&cmd->redirects_read, free_redirect);
	ft_lstclear(&cmd->redirects_write, free_redirect);
	ft_lstclear(&cmd->list_args, free);
	free(cmd);
}
