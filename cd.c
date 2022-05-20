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
		printf("%s: command not found\n", str);
		return ;
	}
	else if (ft_strlen(str) == 2)
	{
		chdir(get_envp("HOME=", envp));
	}
	else
	{
		printf ("Go go go\n");
		split = ft_split(str, ' ');
		printf ("%s\n", split[0]);
		if (split[1])
			printf ("%s\n", split[1]);
		if (split[0] == "cd ")
			printf ("Yes\n");
		//dir = get_envp("cd ", split);
		//ft_free_split(split, ft_wrdcnt(str, ' '));
		//printf ("%s\n", dir);
		//if (chdir(dir) == -1)
		//	return (perror("minishell"));
	}
}
