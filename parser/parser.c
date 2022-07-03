/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:07:36 by gopal             #+#    #+#             */
/*   Updated: 2022/07/03 15:46:04 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_cmd(void)
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	cmd->cmd_name = NULL;
	cmd->list_args = NULL;
	cmd->redirects_read = NULL;
	cmd->redirects_write = NULL;
	cmd->args = NULL;
	cmd->args_count = 0;
	cmd->fd_read = -1;
	cmd->fd_write = -1;
	return (cmd);
}

void	fill_redirect(t_command *cmd, char *token, char *next_token)
{
	t_redirect	*redir;

	redir = (t_redirect *) malloc(sizeof(t_redirect));
	redir->type_redir = ft_strdup(token);
	redir->file_name = ft_strdup(next_token);
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, "<<"))
		ft_lstadd_back(&cmd->redirects_read, ft_lstnew(redir));
	if (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>"))
		ft_lstadd_back(&cmd->redirects_write, ft_lstnew(redir));
}

void	fill_cmd_name_args(t_command *cmd, char *token)
{
	t_list	*node;

	if (!cmd->cmd_name)
		cmd->cmd_name = ft_strdup(token);
	node = ft_lstnew(ft_strdup(token));
	ft_lstadd_back(&cmd->list_args, node);
	cmd->args_count += 1;
}

void	make_cmd(t_list **list_tokens, t_shell *shell)
{
	t_command	*cmd;
	t_list		*list;
	char		*token;
	char		*next_token;

	list = *list_tokens;
	cmd = init_cmd();
	while (list && !is_pipe(list->content))
	{
		token = list->content;
		if (is_redirects(token))
		{
			next_token = list->next->content;
			fill_redirect(cmd, token, next_token);
			list = list->next;
		}
		else
			fill_cmd_name_args(cmd, token);
		list = list->next;
	}
	cmd->args = get_arr_args(cmd->list_args);
	ft_lstadd_back(&shell->list_commands, ft_lstnew(cmd));
	*list_tokens = list;
}

// *** Debug print's functions ***
// puts("Tokens:");
// print_list(*tokens);
// print_list_cmds(list_commands);

void	parser(t_shell *shell)
{
	t_list		*list;

	if (shell->list_tokens && is_valid_tokens(shell->list_tokens))
	{
		list = shell->list_tokens;
		if (check_pipe_end(list, shell) && is_valid_tokens(list))
		{
			while (list)
			{
				if (!is_pipe(list->content))
					make_cmd(&list, shell);
				if (list)
					list = list->next;
			}
		}
	}
	ft_lstclear(&shell->list_tokens, free);
	shell->list_tokens = NULL;
}
