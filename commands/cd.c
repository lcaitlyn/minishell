/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:26:29 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/02 03:17:07 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_dir(t_shell *shell, char *str)
{
	DIR		*dir;
	char	*oldpwd;
	char	*pwd;

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
		oldpwd = getcwd(0, 256);
		chdir(str);
		change_env(shell, "OLDPWD", oldpwd);
		pwd = getcwd(0, 256);
		change_env(shell, "PWD", pwd);
		change_env(shell, "_", ft_strdup("cd"));
	}
	return (0);
}

int	micro_cd(t_shell *shell, char *str)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = get_env_content(shell->env, str);
	if (!path)
	{
		printf ("minishell: cd: %s not set\n", str);
		return (1);
	}
	oldpwd = getcwd(0, 256);
	chdir(path);
	change_env(shell, "OLDPWD", oldpwd);
	pwd = getcwd(0, 256);
	change_env(shell, "PWD", pwd);
	change_env(shell, "_", ft_strdup("cd"));
	if (my_strnstr("OLDPWD", str, 6))
		print_pwd(NULL);
	return (0);
}

	// write (1, "my cd working...\n", 17);
int	change_dir(t_shell *shell, char *cmd[])
{
	if (split_len(cmd) > 2)
		return (print_error("minishell: cd: too many arguments"));
	if (!cmd[1])
		return (micro_cd(shell, "HOME"));
	else if (my_strnstr("-", cmd[1], 1))
		return (micro_cd(shell, "OLDPWD"));
	else
		return (open_dir(shell, cmd[1]));
}
