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
	char	*str;
	char	*name;
	char	*pwd;
	t_shell	*shell;

	handle_signal();
	
	shell = shell_init(envp);
		
	printf ("*********************************\n");
	printf ("*\t\t\t\t*\n");
	printf ("*  Выход на Ctrl + D или exit   *\n");
	printf ("*\t\t\t\t*\n");
	printf ("*********************************\n");
	while (1)
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
				pwd = getcwd(0, 256);
				printf ("%s\n", pwd);
				free(pwd);
			}
			else if (ft_strnstr(str, "env", 3))
			{
				ft_lstprint(shell->env);
			}
			else if (ft_strnstr(str, "export", 6))
			{
				export_print(shell->env);
			}
			else if (ft_strnstr(str, "exit", 4))
				break;
			else
				action(str, envp);
		}
		free(str);
	}
	ft_clear_shell(shell);
	printf ("Завершён!\n");
	return (0);
}
