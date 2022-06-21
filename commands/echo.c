/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:23:08 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/21 14:26:10 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_echo(char *str[])
{
	int	i;

	i = 0;
	if (!str)
		return;
	write(1, str[i], ft_strlen(str[i]));
	i++;
	while (str[i])
	{
		write(1, " ", 1);
		write(1, str[i], ft_strlen(str[i]));
		i++;
	}
}

int	echo(char *cmd[])
{
	int	need_n;
	int	i;

	printf ("my echo working\n");
	need_n = 1;
	i = 1;
	if (!cmd[1])
		need_n = 1;
	while (cmd[i] && my_strnstr("-n", cmd[i], 2))
	{
		if (my_strnstr("-n", cmd[i], 2))
		{
			if (need_n)
				need_n = 0;
			i++;
		}
		else
			break;
	}
	print_echo(cmd + i);
	if (need_n)
		write (1, "\n", 1);
	return (0);
}
