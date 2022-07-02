/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:45:33 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/02 11:59:49 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_execve(char *path, char *cmd, char *envp[])
{
	int		fd[2];
	pid_t	id;
	char	*name;

	name = NULL;
	if (pipe(fd) == -1)
		ft_perror("get_execve(): pipe");
	id = fork();
	if (id == -1)
		ft_perror("get_execve(): fork");
	else if (id == 0)
	{
		if (dup2(fd[1], 1) == -1)
			ft_perror("get_execve(): dup");
		ft_exec(path, cmd, envp);
	}
	waitpid(id, 0, 0);
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

	uname = get_execve("/bin/hostname", "hostname -s", envp);
	if (!uname)
		return (0);
	name = get_execve("/usr/bin/whoami", "whoami", envp);
	if (!name)
	{
		free(uname);
		return (0);
	}
	name = ft_strjoin_f(name, "@", 1);
	name = ft_strjoin_f(name, uname, 3);
	name = ft_strjoin_f(name, ":", 1);
	pwd = get_pwd_for_name(shell);
	name = ft_strjoin_f(name, pwd, 3);
	name = ft_strjoin_f(name, "[MINISHELL]> ", 1);
	return (name);
}
// name = ft_strjoin_f(READLINE_GREEN, name, 2);
// name = ft_strjoin_f(name, RESET, 1);

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
