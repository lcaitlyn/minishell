/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:18:22 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/18 17:18:36 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_clear_paths(char *paths[])
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
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
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/", 0);
		path = ft_strjoin(path, cmd, 0);
		if (access(path, F_OK) == 0)
		{
			ft_clear_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_clear_paths(paths);
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
	if (envp[i] == NULL)
		ft_perror("");
	exit (0);
}

void	ft_exec(char *argv, char *envp[])
{
	char	*path;
	char	**cmd;

	if (ft_strlen(argv) == 0)
		ft_perror("");
	cmd = ft_split(argv, ' ');
	path = ft_find_cmd(cmd[0], ft_find_paths(envp));
	if (!path)
		ft_perror ("");
	if (execve(path, cmd, envp) == -1)
		ft_perror("");
}
