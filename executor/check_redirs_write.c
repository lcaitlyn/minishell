/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 08:37:52 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 12:23:21 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd_write(t_redirect *redirect, int old_fd_write)
{
	int	new_fd_write;

	new_fd_write = -1;
	if (!ft_strcmp(redirect->type_redir, ">")
		|| !ft_strcmp(redirect->type_redir, ">>"))
	{
		if (old_fd_write != 1 && old_fd_write != -1)
			close(old_fd_write);
		if (access(redirect->file_name, F_OK) == 0
			&& access(redirect->file_name, W_OK) != 0)
		{
			perror("MiniShell: ");
			return (-1);
		}
		if (!ft_strcmp(redirect->type_redir, ">"))
			new_fd_write = open(redirect->file_name,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (!ft_strcmp(redirect->type_redir, ">>"))
			new_fd_write = open(redirect->file_name,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		return (new_fd_write);
	}
	return (new_fd_write);
}

void	check_redirs_write(t_command *cmd)
{
	t_list		*list_fd;
	t_redirect	*redirect;

	list_fd = cmd->redirects_write;
	while (list_fd)
	{
		redirect = list_fd->content;
		cmd->fd_write = get_fd_write(redirect, cmd->fd_write);
		list_fd = list_fd->next;
	}
}
