/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:54:06 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 19:34:41 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	signal_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	printf("  \n");
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
