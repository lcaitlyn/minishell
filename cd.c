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

void	open_dir(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (!dir)
	{
		printf("minishell: cd :");
		perror(str);
		return ;
	}
	else
	{
		chdir(str);
		free(dir);
	}
}

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
		chdir(get_envp("HOME=", envp));
	else
	{
		
		split = ft_split(str, ' ');
		open_dir(split[1]);
		ft_free_split(split, ft_wrdcnt(str, ' '));
	}
}
