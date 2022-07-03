/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/03 16:02:58 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// Disables output of such characters to the terminal ^C, ^D...
void	set_param_tty(t_shell *shell)
{
	t_termios	setting_tty;

	tcgetattr(0, &shell->setting_out_tty);
	tcgetattr(0, &setting_tty);
	setting_tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &setting_tty);
}

void	unset_param_tty(t_shell *shell)
{
	tcsetattr(0, TCSANOW, &shell->setting_out_tty);
}

void	loop_shell(t_shell *shell, char **envp)
{
	char	*name;

	while (777)
	{
		name = get_name(shell, envp);
		shell->last_cmd_line = readline(name);
		free (name);
		if (!shell->last_cmd_line)
			break ;
		if (ft_strlen(shell->last_cmd_line) != 0)
		{
			lexer(&shell->last_cmd_line, shell);
			parser(shell);
			add_history(shell->last_cmd_line);
			if (shell->list_commands && executor(shell))
			{
				ft_lstclear(&shell->list_commands, free_list_cmd);
				break ;
			}
			ft_lstclear(&shell->list_commands, free_list_cmd);
		}
		free(shell->last_cmd_line);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	status;

	(void)argc;
	(void)argv;
	print_welcome();
	handle_signal();
	g_shell = shell_init(envp);
	set_param_tty(g_shell);
	loop_shell(g_shell, envp);
	status = g_shell->status;
	unset_param_tty(g_shell);
	ft_clear_shell(g_shell);
	printf ("exit\n");
	exit (status);
}
