/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:56:39 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 20:05:33 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*ft_strnstr(const char *s1, const char *s2, int n)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	j = 0;
// 	if (s2[0] == '\0')
// 		return ((char *)&s1[0]);
// 	len = ft_strlen((char *)s2);
// 	while (s1[i] != '\0' && i < n)
// 	{
// 		if (s1[i] == s2[j])
// 			while ((s1[i + j] == s2[j]) && (i + j < n) && (j < len))
// 				j++;
// 		if (j == len)
// 			return ((char *)&s1[i]);
// 		else
// 			j = 0;
// 		i++;
// 	}
// 	return (NULL);
// }
