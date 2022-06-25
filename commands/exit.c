/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:22 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/22 17:08:06 by gopal            ###   ########.fr       */
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

int	my_exit(t_shell *shell, char **cmd)
{
	int	i;

	if (!cmd)
		return (1);
	if (size_len(cmd) == 1)
		return (0);
	if (size_len(cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	i = 0;
	while (cmd[1][i])
		if (!ft_isdigit(cmd[1][i]))
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			return (1);
		}
		else
			i++;
	i = ft_atoi(cmd[1]);
	if (i >= 0 && i <= 255)
		shell->status = i;
	else
		shell->status = i % 256;
	return (0);
}
