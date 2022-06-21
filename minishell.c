/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/21 14:45:42 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	*name;
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
			break ;
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			parser(&str, shell->envp, shell);
			if (shell->list_commands && executor(shell))
			{
				
				ft_lstclear(&shell->list_commands, free_list_cmd);
				break;
			}
			ft_lstclear(&shell->list_commands, free_list_cmd);
		}
		free(str);
	}
	status = shell->status;
	ft_clear_shell(shell);
	printf ("exit\n");
	printf ("Завершён!\n");
	exit (status);
}
