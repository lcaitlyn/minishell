/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:12:17 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/29 15:21:03 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;

	str = ft_strnstr(haystack, needle, len);
	if (!str)
		return (NULL);
	if (str && ft_strlen(haystack) == ft_strlen(needle))
		return (str);
	return (NULL);
}
