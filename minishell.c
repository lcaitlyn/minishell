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

#include "include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str = "";
	char	*name;
	char	*pwd;

	// handle_signal();
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
			if (ft_strnstr(str, "cd", 2))
			{
				printf ("my cd working...\n");
				change_dir(str, envp);
			}
			else if (ft_strnstr(str, "pwd", 3))
			{
				printf ("my pwd working...\n");
				pwd = get_pwd();
				printf ("%s\n", pwd);
				free(pwd);
			}
			// else if (ft_strnstr(str, "ls", 2))
			// {
			// 	printf ("my ls working...\n");
			// 	ls(str, envp);
			// }
			else
			{
				action(str, envp);
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
