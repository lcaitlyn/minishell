/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 08:29:55 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 08:44:05 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
