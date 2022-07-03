/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 08:39:29 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 15:43:33 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

char	*get_path_cmd(char *cmd_name, char **env)
{
	char	*path;

	if (access(cmd_name, F_OK) == 0 && access(cmd_name, X_OK) == 0)
		path = cmd_name;
	else
		path = ft_find_cmd(cmd_name, ft_find_paths(env));
	if (!path || access(path, X_OK) == -1)
	{
		printf ("minishell: %s: command not found\n", cmd_name);
		free(path);
		exit (1);
	}
	return (path);
}

void	fork_execve_cmd(t_command *cmd, t_shell *shell)
{
	int		pid;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell's error fork cmd");
		shell->status = 1;
	}
	else if (pid == 0)
	{
		dup2(cmd->fd_read, 0);
		dup2(cmd->fd_write, 1);
		path = get_path_cmd(cmd->cmd_name, shell->my_envp);
		if (execve(path, cmd->args, shell->my_envp) < 0)
			ft_perror("Command execution error");
	}
	else
	{
		waitpid(pid, &shell->status, 0);
		shell->status = shell->status / 256;
	}
		
		
}

void	execute_cmd(t_command *cmd, t_shell *shell)
{
	check_redirs_read(cmd);
	check_redirs_write(cmd);
	make_env(shell);
	if (cmd->cmd_name && is_builtin_cmd(cmd->cmd_name))
		execute_builtin_cmd(cmd, shell);
	else if (cmd->cmd_name && cmd->fd_read >= 0 && cmd->fd_write > 0)
	{
		fork_execve_cmd(cmd, shell);
		if (!isatty(cmd->fd_read))
			close(cmd->fd_read);
		if (!isatty(cmd->fd_write))
			close(cmd->fd_write);
	}
	if (!cmd->cmd_name && cmd->fd_read > 0)
		close(cmd->fd_read);
	if (!cmd->cmd_name && cmd->fd_write > 1)
		close(cmd->fd_write);
}
