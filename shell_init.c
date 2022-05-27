/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:03 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/24 18:50:17 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_clear_shell(t_shell *shell)
{
	ft_lstclear(shell->env);
	free(shell->name);
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
			content = ft_itoa(ft_atoi(ft_strchr(shell->envp[i], '=') + 1) + 1);
		else
			content = ft_strjoin("", ft_strchr(shell->envp[i], '=') + 1, 0);

		
		lstadd_back_env(shell, lst_new_env(name, content));
		i++;
	}
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
	shell->my_envp = envp;
	shell->env = NULL;
	shell_env(shell);
	return (shell);
}
