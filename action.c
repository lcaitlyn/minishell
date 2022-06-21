/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:54:24 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/20 13:25:13 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	action(char *str, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		return ;
	}
	else if (pid == 0)
		ft_exec(str, envp);
	waitpid(pid, 0, 0);
}
