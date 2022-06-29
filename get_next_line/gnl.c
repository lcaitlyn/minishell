/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:37:37 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/29 15:16:48 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_line_remainder(char *buf, char **line)
{
	char	*new_line;

	new_line = ft_strchr(buf, '\n');
	*new_line = '\0';
	*line = ft_strjoin_f(*line, buf, 1);
	*line = ft_strjoin_f(*line, "\n", 1);
	ft_strlcpy(buf, new_line + 1, ft_strlen(new_line + 1) + 1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	bytes_read = 1;
	while (!ft_strchr(buf, '\n') && bytes_read)
	{
		line = ft_strjoin_f(line, buf, 1);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
	}
	if (line && !ft_strlen(line))
	{
		free(line);
		line = NULL;
	}
	if (ft_strchr(buf, '\n'))
		set_line_remainder(buf, &line);
	return (line);
}
