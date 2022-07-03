/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 08:29:55 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 14:59:41 by lcaitlyn         ###   ########.fr       */
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
		shell->status = change_dir(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "pwd"))
		shell->status = print_pwd(cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "env"))
		shell->status = ft_listprint(shell->env);
	else if (!ft_strcmp(cmd->cmd_name, "echo"))
		shell->status = echo(cmd->args, cmd->fd_write);
	else if (!ft_strcmp(cmd->cmd_name, "export"))
		shell->status = export(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "unset"))
		shell->status = unset(shell, cmd->args);
	else if (!ft_strcmp(cmd->cmd_name, "exit"))
		shell->status = my_exit(shell, cmd->args);
}
