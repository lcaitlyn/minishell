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

#include "../include/minishell.h"

void	open_dir(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (!dir)
	{
		printf("minishell: cd: ");
		printf ("%s: %s\n", str, strerror(errno));
		return ;
	}
	else
	{
		closedir(dir);
		chdir(str);
	}
}

void	change_dir(t_shell *shell, char *str, char *envp[])
{
	int		i;
	char	*dir;
	char	**split;
	char	*home;

	i = 0;
	if (str[2] && str[2] != ' ')
	{
		printf("%s: command not found\n", str);
		return ;
	}
	else if (ft_strlen(str) == 2)
	{
		home = get_my_env(shell->env, "HOME");
		if (!home)
		{
			// возможно создать нормальную функцию
			
			printf ("minishell: cd: HOME not set\n");
			return ;
		}
		if (chdir(home) == -1)
			printf ("minishell: cd: %s: No such file or directory\n", home);
	}
	else
	{
		split = ft_split(str, ' ');
		open_dir(split[1]);
		ft_free_split(split, ft_wrdcnt(str, ' '));
	}
}
