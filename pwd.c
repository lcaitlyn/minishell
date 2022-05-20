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

#include "minishell.h"

char	*get_envp(char *str, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], str, ft_strlen(str)) != 0)
			return (envp[i] + ft_strlen(str));
		i++;
	}
	return NULL;
}

char	*get_pwd_for_name(char *envp[])
{
	char	*home;
	char	*pwd;
	char	**split;
	char	*fr;

	home = get_envp("HOME=", envp);
	pwd = malloc(100);
	fr = pwd;
	pwd = getcwd(pwd, 1000);
	split = ft_split(pwd, ' ');
	pwd = get_envp(home, &pwd);
	free (fr);
	fr = NULL;
	if (!pwd)
	{
		pwd = getcwd(pwd, 1000);
		fr = pwd;
	}
	pwd = ft_strjoin(TERM_BLUE "~", pwd, 0);
	if (fr)
		free(fr);
	pwd = ft_strjoin(pwd, RESET, 1);
	ft_free_split(split, 1);
	return (pwd);
}

char	*get_pwd(void)
{
	char	*str;

	str = malloc(100);
	str = getcwd(str, 1000);
	return (str);
}
