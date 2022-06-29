/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:54:52 by gopal             #+#    #+#             */
/*   Updated: 2022/06/29 15:10:47 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirs_read(t_command *cmd)
{
	t_list		*list_fd;
	int			fd;
	t_redirect	*redirect;

	list_fd = cmd->redirects_read;
	while (list_fd)
	{
		redirect = list_fd->content;
		
		if (!ft_strcmp(redirect->type_redir, "<"))
		{
			if (cmd->fd_read != 0 && cmd->fd_read != -1)
				close(cmd->fd_read);
			if (access(redirect->file_name, F_OK) != 0
				|| access(redirect->file_name, R_OK) != 0)
			{
				perror("miniSH");
				cmd->fd_read = -1;
			}
			fd = open(redirect->file_name, O_RDONLY);
			cmd->fd_read = fd;
		}
		if (!ft_strcmp(redirect->type_redir, "<<"))
		{
			if (cmd->fd_read != 0 && cmd->fd_read != -1)
				close(cmd->fd_read);
			int	pipe_heredoc[2];
			pipe(pipe_heredoc);
			cmd->fd_read = pipe_heredoc[0];
			signal(SIGINT, (void *) SIGTERM);
			char	*line_read = readline("heredoc> ");
			while (ft_strcmp(line_read, redirect->file_name) != 0 )
			{
				ft_putstr_fd(line_read, pipe_heredoc[1]);
				ft_putstr_fd("\n", pipe_heredoc[1]);
				free(line_read);
				signal(SIGINT, (void *) SIG_IGN);
				// signal(SIGINT, (void *)&signal_sigint);
				line_read = readline("heredoc> ");
				signal(SIGINT, (void *) SIGTERM);
			}
			close(pipe_heredoc[1]);
			signal(SIGINT, (void *)&signal_sigint);
		} 
		list_fd = list_fd->next;
	}
}

void	check_redirs_write(t_command *cmd)
{
	t_list		*list_fd;
	int			fd;
	t_redirect	*redirect;

	list_fd = cmd->redirects_write;
	while (list_fd)
	{
		redirect = list_fd->content;
		
		if (!ft_strcmp(redirect->type_redir, ">")
			|| !ft_strcmp(redirect->type_redir, ">>"))
		{
			if (cmd->fd_write != 1 && cmd->fd_write != -1)
				close(cmd->fd_write);
			if (access(redirect->file_name, F_OK) == 0
				&& access(redirect->file_name, W_OK) != 0)
			{
				perror("miniSH");
				cmd->fd_read = -1;
			}
			if (!ft_strcmp(redirect->type_redir, ">"))
				fd = open(redirect->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (!ft_strcmp(redirect->type_redir, ">>"))
				fd = open(redirect->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
			cmd->fd_write = fd;
		}
		list_fd = list_fd->next;
	}
}

int	is_builtin_cmd(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "cd")
		|| !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "env")
		|| !ft_strcmp(cmd_name, "echo")
		|| !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset")
		|| !ft_strcmp(cmd_name, "exit"))
	{
		return (1);
	}
	return (0);
}

void	execute_builtin_cmd(t_command *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->cmd_name, "cd"))
		change_dir(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "pwd"))
		print_pwd(cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "env"))
		ft_listprint(shell->env);
	else if (!ft_strcmp(cmd->cmd_name, "echo"))
		echo(cmd->args, cmd->fd_write);
	else if (!ft_strcmp(cmd->cmd_name, "export"))
		export(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "unset"))
		unset(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "exit"))
		my_exit(shell, cmd->args);
}

void	execute_cmd(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	check_redirs_read(cmd);
	check_redirs_write(cmd);
	make_env(shell);
	if (cmd->cmd_name && is_builtin_cmd(cmd->cmd_name))
	{
		execute_builtin_cmd(cmd, shell);
	}
	else if (cmd->cmd_name && cmd->fd_read >= 0 && cmd->fd_write > 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("minishell's error fork cmd");
			return ;
		}
		else if (pid == 0)
		{
			char	*path;
			// если команда нет, но есть редирект, то Баш ничего не делает
			dup2(cmd->fd_read, 0);
			dup2(cmd->fd_write, 1);
			if (access(cmd->args[0], X_OK) == 0)
				path = cmd->args[0];
			else
				path = ft_find_cmd(cmd->cmd_name, ft_find_paths(shell->my_envp));
			if (!path || access(path, X_OK) == -1)
				exit (printf ("minishell: %s: command not found\n", cmd->cmd_name) % 1);
			if (execve(path, cmd->args, shell->my_envp) == -1)
			{
				ft_perror("Command execution error");
				exit(1);
			}
		}
		else
		{
			int	status;
			waitpid(pid, &status, 0);
			if (cmd->fd_read != 0)
				close(cmd->fd_read);
			if (cmd->fd_write != 1)
				close(cmd->fd_write);
		}
	}
}

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
		{
			pipe(pipe_fd);
		}
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
		if (cmd->cmd_name && !ft_strcmp(cmd->cmd_name, "exit")
			&& !my_exit(shell, cmd->args))
			return (1);
	}
	execute_list_cmds(shell);
	return (0);
}
