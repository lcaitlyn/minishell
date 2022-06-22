/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:57:05 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/03 10:57:07 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_is_num(char *str)
{
	while (*str)
	{
		if (!((*str <= '9' && *str >= '0') || (*str == ' ')
				|| (*str == '-') || (*str == '+')))
			return (0);
		else
			str++;
	}
	return (1);
}

char	*shlvl(char *content)
{
	char	**split;
	char	*newcontent;

	if (!content)
		return (ft_itoa(1));
	newcontent = NULL;
	split = ft_split(content, ' ');
	if (split_len(split) > 1)
		newcontent = ft_itoa(1);
	else if (ft_is_num(split[0]))
	{
		if (ft_atoi(split[0]) == 999)
			newcontent = ft_strdup("");
		else if (ft_atoi(split[0]) < 0)
			newcontent = ft_itoa(0);
		else
			newcontent = ft_itoa(ft_atoi(split[0]) + 1);
	}
	else
		newcontent = ft_itoa(1);
	ft_free_split(split);
	return (newcontent);
}
