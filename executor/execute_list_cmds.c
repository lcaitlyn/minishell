/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:54:52 by gopal             #+#    #+#             */
/*   Updated: 2022/06/20 14:13:30 by gopal            ###   ########.fr       */
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

void	execute_cmd(t_command *cmd, char **env)
{
	
	cmd->fd_read = check_redirs_read(cmd->redirects_read);
	cmd->fd_write = check_redirs_write(cmd->redirects_read);
	// тут типа долгая настройка fd
	// нужно придумать организацию пайпов (типа у первого нет входного потока от пайпа,
	// у последнего нет выходного пайпа, а еще редиректы переопределяют пайтп)

	// Нужно разобрать как работает Pipex с бонусами

	// action(cmd->cmd_name, env);
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return ;
	}
	else if (pid == 0)
	{
		char	*path;
		// char	**cmd;
		// если команда нет, но есть редирект, то Баш ничего не делает
		// if (ft_strlen(argv) == 0)
		// 	ft_perror("");
		// cmd = ft_split(argv, ' ');
		path = ft_find_cmd(cmd->cmd_name, ft_find_paths(env));
		if (!path)
			ft_perror (""); // cmd not found
		if (execve(path, cmd->args, env) == -1)
			ft_perror("Command execution error");
	}
		// ft_exec(str, envp);
	waitpid(pid, 0, 0);
}

void	execute_list_cmds(t_shell *shell)
{
	t_command	*cmd;
	t_list		*list_commands;

	list_commands = shell->list_commands;
	
	while (list_commands)
	{
		cmd = (t_command *) list_commands->content;

		if (!ft_strcmp(cmd->cmd_name, "cd"))
		{
			printf ("my cd working...\n");
			change_dir(shell, shell->last_cmd_input, shell->envp);
		}
		else if (!ft_strcmp(cmd->cmd_name, "pwd"))
		{
			printf ("my pwd working...\n");
			char *pwd = getcwd(0, 256);
			printf ("%s\n", pwd);
			free(pwd);
		}
		else if (!ft_strcmp(cmd->cmd_name, "env"))
		{
			ft_listprint(shell->env);
		}
		else if (!ft_strcmp(cmd->cmd_name, "export"))
		{
			export_print(shell->env);
		}
		else if (!ft_strcmp(cmd->cmd_name, "exit"))
		{
			break;
		}
		else
			execute_cmd(cmd, shell->envp);
		list_commands = list_commands->next;
	}
}