/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 03:32:46 by gopal             #+#    #+#             */
/*   Updated: 2022/05/25 18:56:43 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ft_wc(char const *str, char c)
// {
// 	int	i;
// 	int	count_words;
// 	int	is_sep;

// 	count_words = 0;
// 	is_sep = 1;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == c)
// 			is_sep = 1;
// 		else
// 		{
// 			if (is_sep)
// 				count_words++;
// 			is_sep = 0;
// 		}
// 		i++;
// 	}
// 	return (count_words);
// }

// static int	word_len(char *word, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (word[i] != c && word[i])
// 		i++;
// 	return (i);
// }

// void	*free_mem(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (NULL);
// }	

// char	**fill_arr(char **arr, const char *str, char c)
// {
// 	int		j;
// 	int		w_len;
// 	char	*s;

// 	s = (char *) str;
// 	j = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			w_len = word_len(s, c);
// 			arr[j] = ft_substr(s, 0, w_len);
// 			if (!arr[j])
// 				return (free_mem(arr));
// 			s += (w_len - 1);
// 			j++;
// 		}
// 		s++;
// 	}
// 	return (arr);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr;
// 	int		l;

// 	if (!s)
// 		return (NULL);
// 	l = ft_wc(s, c);
// 	arr = (char **)ft_calloc(l + 1, sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	arr = fill_arr(arr, s, c);
// 	return (arr);
// }

char	**ft_free_split(char **arr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	ft_wrdlen(const char *s, int start, char c)
{
	int	i;

	i = 0;
	while (s[start] != c && s[start] != '\0')
	{
		start++;
		i++;
	}
	return (i);
}

int	ft_wrdcnt(char const *s, char c)
{
	int	i;
	int	total;
	int	j;

	i = 0;
	total = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			j = 0;
		if (s[i] != c && j == 0)
		{
			j++;
			total++;
		}
		i++;
	}
	return (total);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_wrdcnt(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i] != '\0' && j < ft_wrdcnt(s, c))
	{
		if (s[i] != c)
		{
			arr[j] = ft_substr(s, i, ft_wrdlen(s, i, c));
			if (!arr[j])
				return (ft_free_split(arr, j));
			i = i + ft_wrdlen(s, i, c) - 1;
			j++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}
