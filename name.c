/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uname.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:45:33 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/20 09:45:37 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

char	*writer(int *fd, char *envp[])
{
	char	*str;
	char	*replace;

	str = get_next_line(fd[0]);
	replace = ft_strchr(str, '\n');
	if (replace)
		*replace = '\0';
	return (str);
}

void	reader(int *fd, char *envp[])
{
	char *str;

	if (dup2(fd[1], 1) == -1)
		ft_perror("dup");
	ft_exec("hostname -s", envp);
}

char	*get_uname(char *envp[])
{
	int		fd[2];
	pid_t	id;
	char	*name;

	if (pipe(fd) == -1)
		ft_perror("pipe");
	id = fork();
	if (id == -1)
		ft_perror("fork");
	else if (id == 0)
		reader(fd, envp);
	waitpid(id, 0, 0);
	if (id > 0)
		name = writer(fd, envp);
	return (name);
}

char	*get_username(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "USER=", 5) != 0)
			return (envp[i] + 5);
		i++;
	}
	return NULL;
}

char	*get_name(char *envp[])
{
	char	*name;
	char	*uname;

	uname = get_uname(envp);
	name = ft_strjoin(get_username(envp), "@", 0);
	name = ft_strjoin(name, uname, 1);
	free (uname);
	name = ft_strjoin(name, ":~$ ", 1);
	uname = name;
	name = ft_strjoin(OK, name, 0);
	free(uname);
	name = ft_strjoin(name, RESET, 1);
	return (name);
}
