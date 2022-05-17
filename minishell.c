/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/17 12:00:37 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_username(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "USER=", 5) != 0)
			return (envp[i] + 5);
		i++;
	}
	return NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str = "";
	char	*name;

	
//	while (*envp)
//	{
//		printf ("%s\n", *envp++);
//	}
	name = ft_strjoin("minishell@", get_username(envp));
	name = ft_strjoin(name, ": ");
	while (ft_strcmp(str, "exit"))
	{
		str = readline(name);
		if (ft_strcmp(str, ""))
		{
			printf ("%s\n", str);
			add_history(str);
		}
		free(str);
	}
	free (name);
	return (0);
}
