/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:03 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 20:31:56 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_clear_shell(t_shell *shell)
{
	ft_listclear(shell->env);
//	free(shell->home);
	ft_free_split(shell->my_envp);
	free(shell);
}

t_env	*lst_new_env(char *name, char *content)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (0);
	lst->name = name;
	lst->content = content;
	lst->next = NULL;
	
	return (lst);
}

int	lstadd_back_env(t_shell *shell, t_env *new)
{
	t_env	*begin;

	if (!new)
		return (1);
	if (!shell->env)
		shell->env = new;
	else
	{
		begin = shell->env;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
	return (0);
}

void	shell_env(t_shell *shell)
{
	int		i;
	char	*name;
	char	*content;

	i = 0;
	while (shell->envp[i])
	{
		name = ft_substr(shell->envp[i], 0, ft_strindex(shell->envp[i], '='));
		if (ft_strnstr(name, "SHLVL", ft_strlen(name)))
			content = shlvl(ft_strchr(shell->envp[i], '=') + 1);
		else
			content = ft_strjoin("", ft_strchr(shell->envp[i], '=') + 1);
		lstadd_back_env(shell, lst_new_env(name, content));
		i++;
	}
	if (!get_my_env(shell->env, "SHLVL"))
		lstadd_back_env(shell, lst_new_env("SHLVL", "1"));
	if (!get_my_env(shell->env, "PWD"))
		lstadd_back_env(shell, lst_new_env(ft_strdup("PWD"), getcwd(0, 256)));
	if (!get_my_env(shell->env, "OLDPWD"))
		lstadd_back_env(shell, lst_new_env(ft_strdup("OLDPWD"), 0));
}

t_shell	*shell_init(char *envp[])
{
	t_shell	*shell;
	
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		printf ("malloc error\n");
		exit (1);
	}
	shell->envp = envp;
	shell->name = NULL;
	shell->my_envp = NULL;
	shell->env = NULL;
//	shell->home = get_execve("echo ~", envp);
	shell_env(shell);
	return (shell);
}
