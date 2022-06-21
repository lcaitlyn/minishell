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

void	print_echo(char *str, int len)
{
	int		i;
	char	*tmp;

	tmp = str;
	i = 0;
	while (i < len)
	{
		tmp = strstr(tmp, "-n");
		if (tmp)
			i++;
	tmp = tmp + 2;
	}
	while (*tmp == ' ')
		tmp++;
	write (1, tmp, ft_strlen(tmp));
}

int	echo(char *str, char *cmd[])
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
	print_echo(str, i - 1);
	if (need_n)
		write (1, "\n", 1);
	return (0);
}
