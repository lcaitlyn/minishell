/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/29 08:18:26 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	print_welcome()
{
	printf (":::::::::::::::::::::::::::::::::\n");
	printf (":\t\t\t\t:\n");
	printf (":       M I N I S H E L L       :\n");
	printf (":\t\t\t\t:\n");
	printf (":  Выход на Ctrl + D или exit   :\n");
	printf (":\t\t\t\t:\n");
	printf (":::::::::::::::::::::::::::::::::\n");
}

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
	print_welcome();
	while (7)
	{
		name = get_name(shell, envp);
		str = readline(name);
		free (name);
		if (!str)
			break ;
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			lexer(&str, shell);
			parser(shell);
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
