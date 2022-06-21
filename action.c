/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:54:24 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/21 13:14:22 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	split_len(char *arr[])
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

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
	ft_exec(0, str, envp);
	waitpid(pid, 0, 0);
}
