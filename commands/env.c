/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:22 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/31 16:10:24 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//int	change_env(t_shell *shell, char *name, char *newcontent)
//{
//	t_env	*tmp;
//
//	tmp = get_my_env(shell->env, name);
//	if (tmp)
//	{
//		if (tmp->content)
//			free(tmp->content);
//		tmp->content = newcontent;
//	}
//	else
//	{
//		
//	}
//
//
//}

int	env_len(t_env *env)
{
	int		env_size;
	t_env	*lst;

	lst = env;
	env_size = 0;
	while (lst)
	{
		lst = lst->next;
		env_size++;
	}
	return (env_size);
}

char	**make_env(t_shell *shell)
{
	t_env	*lst;
	char	**envp;
	int		env_size;
	int		i;

	if (!shell->env)
		return (0);
	lst = shell->env;
	env_size = env_len(shell->env);
	if (!env_size)
		return (0);
	envp = (char **)malloc(sizeof(char *) * (env_size + 1));
	i = 0;
	while (lst)
	{
		envp[i] = ft_strjoin(lst->name, "=");
		envp[i] = ft_strjoin_f(envp[i], lst->content, 1);
		lst = lst->next;
		i++;
	}
	envp[i] = NULL;
	if (shell->my_envp)
		ft_free_split(shell->my_envp);
	shell->my_envp = envp;
	return (envp);
}

char	*get_env_content(t_env *env, char *content)
{
	t_env	*lst;

	if (!env)
		return (0);
	lst = env;
	while (lst)
	{
		if (ft_strnstr(content, lst->name, ft_strlen(content)))
			return (lst->content);
		lst = lst->next;
	}
	return (0);
}

t_env	*get_my_env(t_env *env, char *name)
{
	t_env	*lst;

	if (!env)
		return (0);
	lst = env;
	while (lst)
	{
		if (ft_strnstr(name, lst->name, ft_strlen(name)))
			return (lst);
		lst = lst->next;
	}
	return (0);
}
