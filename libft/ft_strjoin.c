/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:41:34 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/03/09 14:41:47 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2, int need_free)
{
	char	*dest;
	char	*p;
	void	*tmp;

	tmp = (void *)s1;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	p = dest;
	while (*s1 != '\0')
		*dest++ = *s1++;
	while (*s2 != '\0')
		*dest++ = *s2++;
	*dest++ = '\0';
	if (need_free)
		free(tmp);
	return (p);
}
