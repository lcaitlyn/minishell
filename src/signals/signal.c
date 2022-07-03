/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:54:06 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/03 15:48:48 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

int	handler_readline_heredoc(int sig)
{
	(void)sig;
	if (!g_shell->buffer)
		free(g_shell->buffer);
	g_shell->buffer = NULL;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	exit(1);
	return (0);
}

int	handler_readline_pipe(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	if (!g_shell->buffer)
		free(g_shell->buffer);
	g_shell->buffer = NULL;
	exit(1);
	return (0);
}

int	signal_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (0);
}

int	handle_signal(void)
{
	signal(SIGINT, (void *)&signal_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
