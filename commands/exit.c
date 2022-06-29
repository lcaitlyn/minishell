/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:22 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/29 03:38:36 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_len(char *arr[])
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	is_args_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("minishell: exit: %s: numeric argument required\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

// если аргумент не адекватен, то он повторяется
// (вызывается в 'executor' и 'execute_builtin_cmd')
int	my_exit(t_shell *shell, char **cmd_args)
{
	int	i;

	if (!cmd_args)
		return (1);
	if (size_len(cmd_args) == 1)
		return (0);
	if (size_len(cmd_args) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	i = 0;
	if (!is_args_digit(cmd_args[1]))
		return (1);
	i = ft_atoi(cmd_args[1]);
	if (i >= 0 && i <= 255)
		shell->status = i;
	else
		shell->status = i % 256;
	return (0);
}
