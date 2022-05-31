/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:17:31 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/20 13:17:51 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_pwd_for_name(t_shell *shell, char *envp[])
{
	char	*home;
	char	*pwd;
	char	**split;
	char	*fr;

	home = get_my_env(shell->env, "HOME");
	printf ("home = %s\n", home);
	pwd = getcwd(0, 256);
	fr = pwd;
	if (ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		pwd = ft_strjoin("~", pwd + ft_strlen(home), 0);
		free(fr);
		fr = pwd;
	}
	pwd = ft_strjoin(TERM_BLUE, pwd, 0);
	free(fr);
	pwd = ft_strjoin(pwd, RESET, 1);
	printf ("pwd = %s\n", pwd);
	return (pwd);
}
