/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 08:35:15 by gopal             #+#    #+#             */
/*   Updated: 2022/07/03 13:12:11 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	heredoc(int fd_write, char *stop_word)
{
	int		pid;
	int		status;

	signal(SIGINT, (void *) SIG_IGN);
	pid = fork();
	if (pid < 0)
		ft_perror("fork's error");
	if (pid == 0)
	{
		signal(SIGINT, (void *) &handler_readline_heredoc);
		g_shell->buffer = readline("heredoc> ");
		rl_on_new_line();
		while (g_shell->buffer && ft_strcmp(g_shell->buffer, stop_word) != 0)
		{
			ft_putstr_fd(g_shell->buffer, fd_write);
			ft_putstr_fd("\n", fd_write);
			free(g_shell->buffer);
			g_shell->buffer = readline("heredoc> ");
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(fd_write);
	signal(SIGINT, (void *) &signal_sigint);
	return (status / 256);
}

int	get_fd_read(t_redirect *redirect, int old_fd_read)
{
	int	new_fd_read;

	if (old_fd_read != 0 && old_fd_read != -1)
		close(old_fd_read);
	if (access(redirect->file_name, F_OK) != 0
		|| access(redirect->file_name, R_OK) != 0)
	{
		perror("MiniShell");
		g_shell->status = 1;
		return (-1);
	}
	new_fd_read = open(redirect->file_name, O_RDONLY);
	return (new_fd_read);
}

void	check_redirs_read(t_command *cmd)
{
	t_redirect	*redirect;
	t_list		*list_fd;
	int			pipe_heredoc[2];

	list_fd = cmd->redirects_read;
	while (list_fd)
	{
		redirect = list_fd->content;
		if (!ft_strcmp(redirect->type_redir, "<"))
			cmd->fd_read = get_fd_read(redirect, cmd->fd_read);
		if (!ft_strcmp(redirect->type_redir, "<<"))
		{
			if (cmd->fd_read != 0 && cmd->fd_read != -1)
				close(cmd->fd_read);
			pipe(pipe_heredoc);
			cmd->fd_read = pipe_heredoc[0];
			if (heredoc(pipe_heredoc[1], redirect->file_name))
			{
				close(pipe_heredoc[0]);
				g_shell->status = 1;
				cmd->fd_read = -1;
			}
		}
		list_fd = list_fd->next;
	}
}
