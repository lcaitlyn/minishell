/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:52:08 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 10:52:10 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strindex(char *str, char a)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != a)
		i++;
	if (i < ft_strlen(str))
		return (i);
	else
		return (-1);
}
