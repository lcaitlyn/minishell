/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:18:22 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/02 11:59:34 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_paths(char *paths[])
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
}

char	*ft_find_cmd(char *cmd, char *paths[])
{
	char	*path;
	int		i;

	i = 0;
	if (!paths)
		return (0);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_f(path, cmd, 1);
		if (access(path, F_OK) == 0)
		{
			ft_clear_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	**ft_find_paths(char *envp[])
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (0);
}

void	ft_exec(char *path, char *argv, char *envp[])
{
	char	**cmd;

	if (ft_strlen(argv) == 0)
		ft_perror("");
	cmd = ft_split(argv, ' ');
	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	if (!path || access(path, X_OK) == -1)
		path = ft_find_cmd(cmd[0], ft_find_paths(envp));
	if (!path)
		ft_perror ("execve");
	if (execve(path, cmd, envp) == -1)
		ft_perror("");
}
