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
	t_shell	*shell;

	handle_signal();
	shell = shell_init(envp);
	printf ("\nВыход на Ctrl + D или exit\n\n");
	while (ft_strcmp(str, "exit"))
	{
		name = get_name(envp);
		if (!name)
			name = ft_strjoin("", "minishell> ", 0);
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
			else if (ft_strnstr(str, "exit", 4))
				break;
			else
				action(str, envp);
		}
		free(str);
	}
//	printf("%s\n", name);
//	str = get_pwd(envp);
//	printf("%s\n", str);
//	free (str);
	printf ("Завершён!\n");
	return (0);
}
