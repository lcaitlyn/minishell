/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:23:08 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/25 12:04:30 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char *str[])
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (i)
			write(1, " ", 1);
		write(1, str[i], ft_strlen(str[i]));
		i++;
	}
}

// Нужно переписать echo так, чтобы он писал по заданному fd
int	echo(char *args[])
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
	print_echo(args + i);
	if (need_n)
		write (1, "\n", 1);
	return (0);
}
