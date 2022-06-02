/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:41:34 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 18:58:08 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_f(char *s1, char *s2, int need_free)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(&str[ft_strlen(s1)], s2, ft_strlen(s2));
	if (need_free == 1)
		free (s1);
	else if (need_free == 2)
		free (s2);
	else if (need_free == 3)
	{
		free (s1);
		free (s2);
	}
	return (str);
}
