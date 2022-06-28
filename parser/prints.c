/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:02:31 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 13:08:06 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_list_cmds(t_list *list_commands)
// {
// 	t_command	*command;
// 	char		*name;
// 	t_list		*redir_read;
// 	t_list		*redir_write;
// 	t_list		*args;
// 	char		**arr_args;
// 	int			i = 0;

// 	while (list_commands)
// 	{
// 		command = (t_command *)(list_commands)->content;
// 		name = command->cmd_name;
// 		redir_read = command->redirects_read;
// 		redir_write = command->redirects_write;
// 		args = command->list_args;
// 		arr_args = command->args;
// 		printf("--> %i command = - %s <-- \n", ++i, name);

// 		printf("  rediretcs to read **");
// 		if (redir_read)
// 			print_redir_list(redir_read);
// 		else
// 			printf(": Empty\n");
// 		printf("  rediretcs to write **");
// 		if (redir_write)
// 			print_redir_list(redir_write);
// 		else
// 			printf(": Empty\n");
// 		printf("  arguments list**");
// 		if (args)
// 			print_list(args);
// 		else
// 			printf(": Empty\n");
// 		printf("  arguments array**");
// 		if (arr_args)
// 			print_arr_str(arr_args);
// 		else
// 			printf(": Empty\n");
// 		puts("");
// 		list_commands = list_commands->next;
// 	}
// }

// void	print_list(t_list *list)
// {
// 	int	i;

// 	i = 0;
// 	puts("");
// 	while (list)
// 	{
// 		printf("\t%i - %s\n", ++i, (char *) list->content);
// 		list = list->next;
// 	}
// }

// void	print_arr_str(char **arr)
// {
// 	int	i;

// 	i = -1;
// 	puts("");
// 	while (arr && arr[++i])
// 	{
// 		printf("\t%i - %s\n", i, arr[i]);
// 	}
// }

// void	print_redir_list(t_list *list)
// {
// 	int	i;

// 	i = 0;
// 	puts("");
// 	while (list)
// 	{
// 		i++;
// 		printf("\t %i - %s %s\n",  i, 
// 			((t_redirect *) list->content)->type_redir,
// 			((t_redirect *) list->content)->file_name);
// 		list = list->next;
// 	}
// }
