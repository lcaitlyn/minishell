/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:37:37 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/29 04:47:32 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_next_line(int fd)
{
	char	c;
	char	*line;
	char	*word;

	if ((read(fd, &c, 1)) == 0)
		return (NULL);
	line = malloc(100);
	word = line;
	*line++ = c;
	while ((read(fd, &c, 1)) > 0 && c != '\n')
		*line++ = c;
	if (c == '\n')
		*line++ = '\n';
	*line = '\0';
	return (word);
}
