/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:57:25 by gopal             #+#    #+#             */
/*   Updated: 2022/07/03 15:44:53 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_shell;

void	child_process_end_pipe(int fd_write)
{
	signal(SIGINT, (void *) &handler_readline_pipe);
	g_shell->buffer = readline("pipe> ");
	if (!g_shell->buffer)
	{
		ft_putendl_fd("bash: syntax error: unexpected end of file", 2);
		exit(1);
	}
	ft_putstr_fd(g_shell->buffer, fd_write);
	free(g_shell->buffer);
	exit(0);
}

char	*fork_end_pipe(void)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	g_shell->buffer = NULL;
	signal(SIGINT, (void *) SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		printf("Fork's error!");
		return (NULL);
	}
	if (pid == 0)
		child_process_end_pipe(fd[1]);
	waitpid(pid, &g_shell->status, 0);
	g_shell->status /= 256;
	close(fd[1]);
	g_shell->buffer = get_next_line(fd[0]);
	signal(SIGINT, (void *) &signal_sigint);
	return (g_shell->buffer);
}

int	check_pipe_end(t_list	*list, t_shell *shell)
{
	t_list	*tail_list;
	t_list	*last_elem;
	char	*line;

	last_elem = ft_lstlast(list);
	while (is_pipe(last_elem->content))
	{
		line = fork_end_pipe();
		if (!line)
			return (0);
		tail_list = make_tokens(&line, make_env(shell));
		line = ft_strjoin_f(" ", line, 2);
		shell->last_cmd_line = ft_strjoin_f(shell->last_cmd_line, line, 3);
		last_elem->next = tail_list;
		last_elem = ft_lstlast(list);
	}
	return (1);
}
