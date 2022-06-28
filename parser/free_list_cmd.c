/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:46:42 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 10:53:31 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(void *redir)
{
	t_redirect	*rdr;

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
	ft_free_split(cmd->args);
	free(cmd);
}
