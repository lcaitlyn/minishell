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
	free(shell->name);
	free(shell);
}

t_env	*shell_env(char *envp[])
{
	int		i;
	char	*name;
	char	*content;
	t_env	*env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		name = ft_substr(envp[i], 0, ft_strindex(envp[i], '='));
		if (ft_strnstr(name, "SHLVL", ft_strlen(name)))
			content = ft_itoa(ft_atoi(ft_strchr(envp[i], '=') + 1) + 1);
		else
			content = ft_strjoin_f("", ft_strchr(envp[i], '=') + 1, 0);
		env = ft_listadd_back(env, ft_listnew(name, content));
		free(content);
		free(name);
		i++;
	}
	return (env);
}

t_shell	*shell_init(char *envp[])
{
	t_shell	*shell;
	
	shell = (t_shell *)malloc(sizeof(t_shell *));
	if (!shell)
		return (0);
	shell->name = get_name(envp);
	if (!shell->name)
		shell->name = ft_strjoin_f("", "minishell> ", 0);
	shell->env = shell_env(envp);
	if (!shell->env)
	{
		
//		обработать ?)
		
		exit(1);
	}
	return (shell);
}
