/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:57:06 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 20:26:58 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*ft_substr(char const *s, unsigned int start, int len)
// {
// 	char	*str;
// 	char	*p;
// 	int		lensub;

// 	if (!s)
// 		return (NULL);
// 	lensub = ft_strlen((char *)s) - start;
// 	if (lensub > len)
// 		lensub = len;
// 	if (start >= (unsigned int)ft_strlen((char *)s) || len < 1)
// 	{
// 		str = malloc(sizeof(char));
// 		return (str);
// 	}
// 	str = malloc((lensub + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	p = str;
// 	str[lensub] = '\0';
// 	while (lensub > 0)
// 	{
// 		lensub--;
// 		str[lensub] = (char)s[start + lensub];
// 	}
// 	return (p);
// }
