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

char	*get_pwd_for_name(char *envp[])
{
	char	*home;
	char	*pwd;
	char	**split;
	char	*fr;

	home = getenv("HOME");
	pwd = malloc(100);
	fr = pwd;
	pwd = getcwd(pwd, 256);
	pwd = ft_strnstr(pwd, home, ft_strlen(pwd));
	if (!pwd)
		pwd = getcwd(pwd, 1000);
	else
		pwd = ft_strjoin("~", pwd + ft_strlen(home), 0);
	free(fr);
	fr = pwd;
	pwd = ft_strjoin(TERM_BLUE, pwd, 0);
	free(fr);
	pwd = ft_strjoin(pwd, RESET, 1);
	return (pwd);
}

char	*get_pwd(void)
{
	char	*str;

	str = malloc(100);
	str = getcwd(str, 1000);
	return (str);
}
