/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:56:57 by lcaitlyn          #+#    #+#             */
/*   Updated: 2021/10/27 15:56:58 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *str, int a)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (void *)0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)a)
		{
			p = (void *)&str[i];
			return (p);
		}
		i++;
	}
	if ((char)a == '\0')
		p = ((void *)&str[i]);
	return (p);
}
