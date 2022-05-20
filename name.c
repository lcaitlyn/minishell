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
	char	**name;
	int		len;

	str = get_next_line(fd[0]);
	len = ft_wrdcnt(str, '.');
	name = ft_split(str, '.');
	replace = ft_strchr(name[0], '\n');
	if (replace)
		*replace = '\0';
	free(str);
	str = ft_strjoin("", name[0]);
	ft_free_split(name, len);
	return (str);
}

void	reader(int *fd, char *envp[])
{
	char *str;

	if (dup2(fd[1], 1) == -1)
		ft_perror("dup");
	ft_exec("uname -n", envp);
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
	name = ft_strjoin(get_username(envp), "@");
	name = ft_strjoin(name, uname);
	free (uname);
	name = ft_strjoin(name, ":~$ " RESET);
	name = ft_strjoin(READLINE_GREEN, name);
	name = ft_strjoin(name, RESET);
	return (name);
}
