/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:54:43 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 20:12:41 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Продублировал код в сплите в папке libft, там закомментил старый libft

// char	**ft_free_split(char **arr, int j)
// {
// 	int	i;

// 	i = 0;
// 	while (i < j)
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (NULL);
// }

// int	ft_wrdlen(const char *s, int start, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[start] != c && s[start] != '\0')
// 	{
// 		start++;
// 		i++;
// 	}
// 	return (i);
// }

// int	ft_wrdcnt(char const *s, char c)
// {
// 	int	i;
// 	int	total;
// 	int	j;

// 	i = 0;
// 	total = 0;
// 	j = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == c)
// 			j = 0;
// 		if (s[i] != c && j == 0)
// 		{
// 			j++;
// 			total++;
// 		}
// 		i++;
// 	}
// 	return (total);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	arr = (char **)malloc((ft_wrdcnt(s, c) + 1) * sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	while (s[i] != '\0' && j < ft_wrdcnt(s, c))
// 	{
// 		if (s[i] != c)
// 		{
// 			arr[j] = ft_substr(s, i, ft_wrdlen(s, i, c));
// 			if (!arr[j])
// 				return (ft_free_split(arr, j));
// 			i = i + ft_wrdlen(s, i, c) - 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	arr[j] = NULL;
// 	return (arr);
// }
