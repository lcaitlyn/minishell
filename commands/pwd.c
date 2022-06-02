/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:17:31 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 19:49:58 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_pwd_for_name(t_shell *shell)
{
	char	*home;
	char	*pwd;
	char	*fr;

	home = get_my_env(shell->env, "HOME");
	pwd = getcwd(0, 256);
	fr = pwd;
	if (home && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		pwd = ft_strjoin("~", pwd + ft_strlen(home));
		free(fr);
	}
	// pwd = ft_strjoin_f(TERM_BLUE, pwd, 2);
	// pwd = ft_strjoin_f(pwd, RESET, 1);
	return (pwd);
}

int	print_pwd(char	**cmd)
{
	char	*pwd;

	if (cmd)
		if (cmd[1])
			return (print_error("pwd: too many arguments"));
	pwd = getcwd(0, 256);
	printf ("%s\n", pwd);
	free(pwd);
	return (0);
}

//char	*get_home(void)
//{
//	
//}
