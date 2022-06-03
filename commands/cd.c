/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:26:29 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 19:55:37 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_dir(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (!dir)
	{
		printf("minishell: cd: ");
		printf ("%s: %s\n", str, strerror(errno));
		return (1);
	}
	else
	{
		closedir(dir);
		chdir(str);
	}
	return (0);
}

int	micro_cd(t_env *env, char *str)
{
	char	*path;

	path = get_env_content(env, str);
	if (!path)
	{
		printf ("minishell: cd: %s not set\n", str);
		return (1);
	}
	chdir(path);
	if (ft_strnstr("-", str, 1))
		print_pwd(NULL);
	return (0);
}

int	change_dir(t_shell *shell, char *cmd[])
{
	
	// сделать с $OLDPWD $PWD ‼️
	
	write (1, "my cd working...\n", 17);
	
	if (split_len(cmd) > 2)
		return (print_error("minishell: cd: too many arguments"));
	if (!cmd[1])
		return (micro_cd(shell->env, "HOME"));
	else if (ft_strnstr("-", cmd[1], 1))
		return (micro_cd(shell->env, "OLDPWD"));
	else
		return (open_dir(cmd[1]));
}
