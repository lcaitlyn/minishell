/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:54:52 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 10:21:04 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// нужно добавить обработку ошибок на функцию pipe() (boring т_т)
void	set_pipes_cmds(t_list *list_commands, t_shell *shell)
{
	t_command	*cmd;
	int			size;
	int			pipe_fd[2];

	size = ft_lstsize(list_commands);
	while (list_commands)
	{
		cmd = list_commands->content;
		if (size > 1 && list_commands->next)
			pipe(pipe_fd);
		if (shell->list_commands == list_commands)
			cmd->fd_read = STDIN_FILENO;
		if (list_commands->next)
			((t_command *) list_commands->next->content)->fd_read = pipe_fd[0];
		if (!list_commands->next)
			cmd->fd_write = STDOUT_FILENO;
		else
			cmd->fd_write = pipe_fd[1];
		list_commands = list_commands->next;
	}
}

void	execute_list_cmds(t_shell *shell)
{
	t_command	*cmd;
	t_list		*list_commands;

	list_commands = shell->list_commands;
	set_pipes_cmds(list_commands, shell);
	while (list_commands)
	{
		cmd = (t_command *) list_commands->content;
		execute_cmd(cmd, shell);
		list_commands = list_commands->next;
	}
}

int	executor(t_shell *shell)
{
	t_command	*cmd;

	if (ft_lstsize(shell->list_commands) == 1)
	{
		cmd = (t_command *)shell->list_commands->content;
		if (cmd->cmd_name
			&& !ft_strcmp(cmd->cmd_name, "exit")
			&& !my_exit(shell, cmd->args))
			return (1);
	}
	execute_list_cmds(shell);
	return (0);
}
