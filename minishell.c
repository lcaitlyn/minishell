/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/02 04:11:30 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_shell	*g_shell;

void	print_welcome(void)
{
	printf (":::::::::::::::::::::::::::::::::\n");
	printf (":\t\t\t\t:\n");
	printf("%s", READLINE_GREEN);
	printf (":       M I N I S H E L L       :\n");
	printf("%s", RESET);
	printf (":\t\t\t\t:\n");
	printf (":  Выход на Ctrl + D или exit   :\n");
	printf (":\t\t\t\t:\n");
	printf (":::::::::::::::::::::::::::::::::\n");
}

void	loop_dormammu(t_shell *g_shell, char **envp)
{
	char	*name;
	char	*str;

	while (777)
	{
		name = get_name(g_shell, envp);
		str = readline(name);
		free (name);
		if (!str)
			break ;
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			lexer(&str, g_shell);
			parser(g_shell);
			if (g_shell->list_commands && executor(g_shell))
			{
				ft_lstclear(&g_shell->list_commands, free_list_cmd);
				break ;
			}
			ft_lstclear(&g_shell->list_commands, free_list_cmd);
		}
		free(str);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	status;

	(void)argc;
	(void)argv;
	handle_signal();
	g_shell = shell_init(envp);
	print_welcome();
	loop_dormammu(g_shell, envp);
	status = g_shell->status;
	ft_clear_shell(g_shell);
	printf ("exit\n");
	exit (status);
}
