/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/16 03:00:49 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	*name;
	char	*pwd;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	handle_signal();
	
	shell = shell_init(envp);
		
	printf ("*********************************\n");
	printf ("*\t\t\t\t*\n");
	printf ("*  Выход на Ctrl + D или exit   *\n");
	printf ("*\t\t\t\t*\n");
	printf ("*********************************\n");
	while (1)
	{
		name = get_name(shell, envp);
		str = readline(name);
		if (!str)
		{
			printf ("exit\n");
			break ;
		}
		str = parser(str, envp);
		free (name);
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			if (ft_strnstr(str, "cd", 2))
			{
				printf ("my cd working...\n");
				change_dir(shell, str, envp);
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
				ft_listprint(shell->env);
			}
			else if (ft_strnstr(str, "export", 6))
			{
				export_print(shell->env);
			}
			else if (ft_strnstr(str, "exit", 4))
				break;
			else
				action(str, make_env(shell));
		}
		free(str);
	}
	ft_clear_shell(shell);
	printf ("Завершён!\n");
	while (7)
	{
		int i = 1 + 1;
		i = i + i;
	}
	
	return (0);
}
