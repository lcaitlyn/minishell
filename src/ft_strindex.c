/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:52:08 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 20:28:56 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strindex(char *str, char a)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != a)
		i++;
	if (i < ft_strlen(str))
		return (i);
	else
		return (-1);
}
