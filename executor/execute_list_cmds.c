/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:54:52 by gopal             #+#    #+#             */
/*   Updated: 2022/06/25 12:27:04 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirs_read(t_list *redirects_read)
{
	(void)redirects_read;
	// проверим что файлы существуют и доступны для чтения
	// и вернем fd последнего редиректа
	// а, еще heredoc (интерактивный ввод до стоп слова) - тоже редирект
	// и стоит в такой же очереди
	// а пайп (ввод из терминала 0 fd) будет доступен при отсутсвии редиректов

	// вывод ошибки если что-то пошло не так (или это свалить на заботы команды с execve?)

	return (0); // по умолчанию возращаем fd ввода стандартного терминала
}

int	check_redirs_write(t_list *redirects_write)
{
	(void)redirects_write;
	// проверим что файлы существуют и доступны для записи
	// если их нет, то создать, если есть - перезаписать на ноль
	// за исключением редиректа '>>' - открыть файл для добавления контента
	// и вернем fd последнего редиректа
	// Так, результат выполнения команды мы пишем в последний файл редиректа 
	// (несмотря на то, что мы создали или обнулили до этого другие файлы)
	// а пайп (вывод из терминала 1 fd) будет доступен при отсутсвии редиректов

	// вывод ошибки если что-то пошло не так (или это свалить на заботы команды с execve?)

	return (1); // по умолчанию возращаем fd вывода стандартного терминала
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
		echo(cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "export"))
		export(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "unset"))
		unset(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "exit"))
		my_exit(shell, cmd->args);
}

void	execute_cmd(t_command *cmd, /*char **env */ t_shell *shell)
{
	
	// cmd->fd_read = check_redirs_read(cmd->redirects_read);
	// cmd->fd_write = check_redirs_write(cmd->redirects_read);

	// тут типа долгая настройка fd
	// нужно придумать организацию пайпов (типа у первого нет входного потока от пайпа,
	// у последнего нет выходного пайпа, а еще редиректы переопределяют пайтп)

	// Нужно разобрать как работает Pipex с бонусами
	pid_t	pid;

	make_env(shell);
	if (cmd->cmd_name && is_builtin_cmd(cmd->cmd_name))
	{
		execute_builtin_cmd(cmd, shell);
	}
	else if (cmd->cmd_name)
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
	// i = 0;
	while (list_commands)
	{
		cmd = (t_command *) list_commands->content;
		list_commands = list_commands->next;
		execute_cmd(cmd, shell);
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
