/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:23:08 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/28 01:59:12 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (args && args[i] && my_strnstr("-n", args[i], 2))
	{
		if (my_strnstr("-n", args[i], 2))
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
