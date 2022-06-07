/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/01 11:54:26 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**my_parser(char *str)
{
	void	*tmp;
	char	**cmd;

	tmp = (void *)str;
	cmd = ft_split(str, ' ');
	return (cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	*name;
	char	**cmd;
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
//	printf ("HOME = %s\n", shell->home);
	while (1)
	{
		name = get_name(shell, envp);
		str = readline(name);
		free (name);
		if (!str)
		{
			printf ("exit\n");
			break ;
		}
		cmd = NULL;
		cmd = my_parser(str);
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			if (my_strnstr("cd", cmd[0], 2))
			{
				exit_stat = change_dir(shell, cmd);
			}
			else if (my_strnstr("pwd", cmd[0], 3))
			{
				exit_stat = print_pwd(cmd);
			}
			else if (my_strnstr("env", cmd[0], 3))
			{
				exit_stat = ft_listprint(shell->env);
			}
			else if (my_strnstr("echo", cmd[0], 4))
			{
				exit_stat = echo(cmd);
			}
			else if (my_strnstr(str, "export", 6))
			{
				export_print(shell->env);
			}
			else if (my_strnstr(str, "exit", 4))
				break;
			else
				action(str, make_env(shell));
		}
		ft_free_split(cmd);
		free(str);
	}
	ft_clear_shell(shell);
	printf ("Завершён!\n");
	exit_stat = 0;
	return (exit_stat);
}
