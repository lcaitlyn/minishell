/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:26:29 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/20 14:26:32 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	change_dir(char *str, char *envp[])
{
	int		i;
	char	*dir;
	char	**split;

	i = 0;
	if (str[2] && str[2] != ' ')
	{
		//execve(str, 0, 0);
		return (perror("minishell"));
	}
	else if (ft_strlen(str) == 2)
	{
		chdir(get_envp("HOME=", envp));
	}
	else
	{
		split = ft_split(str, ' ');
		dir = get_envp("cd ", split);
		ft_free_split(split, ft_wrdcnt(str, ' '));
		printf ("%s\n", dir);
		if (chdir(dir) == -1)
			return (perror("minishell"));
	}
}
