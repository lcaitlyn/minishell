/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:23:08 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/04 15:47:01 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_n(char *str)
{
	int	i;

	i = 1;
	if (!str && str[0])
		return (0);
	if (str[0] != '-' && str[1] != 'n')
		return (0);
	while (str[i] - 'n' == 0)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	print_echo(char *str[], int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (i)
			write(fd, " ", 1);
		write(fd, str[i], ft_strlen(str[i]));
		i++;
	}
}

int	echo(char *args[], int fd)
{
	int	need_n;
	int	i;

	need_n = 1;
	i = 1;
	if (!args[1])
		need_n = 1;
	while (args && args[i] && is_n(args[i]))
	{
		if (is_n(args[i]))
		{
			if (need_n)
				need_n = 0;
			i++;
		}
		else
			break ;
	}
	print_echo(args + i, fd);
	if (need_n)
		write (fd, "\n", 1);
	if (fd != 1)
		close(fd);
	return (0);
}
