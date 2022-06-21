/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/21 14:15:44 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**my_parser(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	return (cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	*name;
	char	**cmd;
	t_shell	*shell;
	int		status;

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
		free (name);
		if (!str)
		{
			printf ("exit\n");
			break ;
		}
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			parser(&str, shell->envp, shell);
			if (!(shell->list_commands))
				execute_list_cmds(shell);
			ft_lstclear(&shell->list_commands, free_list_cmd);
		}
		free(str);
		shell->last_cmd_input = NULL;
	}
	status = shell->status;
	ft_clear_shell(shell);
	printf ("Завершён!\n");
	exit (status);
}
