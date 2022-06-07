/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:23:08 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/06 16:23:11 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo(char *cmd[])
{
	int	need_n;
	int	i;

	printf ("my echo working\n");
	need_n = 1;
	i = 1;
	if (!cmd[1])
		need_n = 1;
	while (cmd[i] && ft_strnstr("-n", cmd[i], 2))
	{
		if (ft_strnstr("-n", cmd[i], 2)
			&& ft_strlen("-n") == ft_strlen(cmd[i]))
		{
			if (need_n)
				need_n = 0;
			i++;
		}
		else
			break;
	}
	while (cmd[i])
	{
		write (1, cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	if (need_n)
		write (1, "\n", 1);
	return (0);
}
