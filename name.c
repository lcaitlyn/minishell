/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:45:33 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/20 14:16:30 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*writer(int *fd, char *envp[])
{
	char	*str;
	char	*replace;

	(void)envp;
	str = get_next_line(fd[0]);
	replace = ft_strchr(str, '\n');
	if (replace)
		*replace = '\0';
	return (str);
}

char	*get_uname(char *envp[])
{
	int		fd[2];
	pid_t	id;
	char	*name;

	(void)envp;
	name = NULL;
	if (pipe(fd) == -1)
		ft_perror("pipe");
	id = fork();
	if (id == -1)
		ft_perror("fork");
	else if (id == 0)
	{
		
		//удалить
		// printf ("kill %d\n", getpid());
		if (dup2(fd[1], 1) == -1)
			ft_perror("dup");
		ft_exec("hostname -s", envp);
	}
	waitpid(id, 0, 0);
	if (id > 0)
		name = writer(fd, envp);
	close(fd[0]);
	close(fd[1]);
	return (name);
}

char	*get_username(char *envp[])
{
	int		fd[2];
	pid_t	id;
	char	*name;

	if (pipe(fd) == -1)
		ft_perror("pipe");
	id = fork();
	if (id == -1)
		ft_perror("fork");
	else if (id == 0)
	{
		//удалить
		// printf ("kill %d\n", getpid());
		if (dup2(fd[1], 1) == -1)
			ft_perror("dup");
		ft_exec("whoami", envp);
	}
	waitpid(id, 0, 0);
	name = NULL;
	if (id > 0)
		name = writer(fd, envp);
	close(fd[0]);
	close(fd[1]);
	return (name);
}

char	*get_color_name(t_shell *shell, char *envp[])
{
	char	*name;
	char	*uname;
	char	*pwd;

	uname = get_uname(envp);
	if (!uname)
		return (0);
	name = get_username(envp);
	if (!name)
	{
		free(uname);
		return (0);
	}
	name = ft_strjoin_f(name, "@", 1);
	name = ft_strjoin_f(name, uname, 3);
	// name = ft_strjoin_f(READLINE_GREEN, name, 2);
	// name = ft_strjoin(name, RESET, 1);
	name = ft_strjoin_f(name, ":", 1);
	pwd = get_pwd_for_name(shell);
	name = ft_strjoin_f(name, pwd, 3);
	name = ft_strjoin_f(name, "[MINISHELL]> ", 1);
	return (name);
}

char	*get_name(t_shell *shell, char *envp[])
{
	char	*name;

	name = get_color_name(shell, envp);
	if (!name)
		name = ft_strjoin("", "minishell> ");
	if (!name)
	{
		printf ("malloc error in get_name");
		exit (1);
	}
	return (name);
}
