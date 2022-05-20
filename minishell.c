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
#include "color.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str = "";
	char	*name;
	char	*pwd;

	while (ft_strcmp(str, "exit"))
	{
		name = get_name(envp);
		str = readline(name);
		free (name);
		if (!str)
		{
			printf ("exit\n");
			break ;
		}
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			if (!ft_strcmp(str, "env"))
				system("env");
			else if (ft_strnstr(str, "cd", 2))
			{
				change_dir(str, envp);
			}
			else if (ft_strnstr(str, "pwd", 3))
			{
				pwd = get_pwd();
				printf ("%s\n", pwd);
				free(pwd);
			}
			else
			{
				if (execve(str, argv, envp) == -1)
					perror("minishell");
			}
				
		}
		free(str);
	}
//	printf("%s\n", name);
//	str = get_pwd(envp);
//	printf("%s\n", str);
//	free (str);
	return (0);
}
