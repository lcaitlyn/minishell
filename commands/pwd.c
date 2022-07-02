/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:17:31 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/01 22:14:25 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd_for_name(t_shell *shell)
{
	char	*home;
	char	*pwd;
	char	*fr;

	home = get_env_content(shell->env, "HOME");
	pwd = getcwd(0, 256);
	if (!home)
		return (pwd);
	fr = pwd;
	if (ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		pwd = ft_strjoin("~", pwd + ft_strlen(home));
		free(fr);
	}
	return (pwd);
}
// pwd = ft_strjoin_f(TERM_BLUE, pwd, 2);
// pwd = ft_strjoin_f(pwd, RESET, 1);

int	print_pwd(char	**cmd)
{
	char	*pwd;

	if (split_len(cmd) > 1)
		return (print_error("minishell: pwd: too many arguments"));
	pwd = getcwd(0, 256);
	printf ("%s\n", pwd);
	free(pwd);
	return (0);
}
