/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:01:26 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/10 13:01:30 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i])
		&& name[i] != '_')
			return (1);
		i++;
	}
	if (ft_isalpha(name[0]))
	{
		i = 0;
		while (ft_isdigit(name[i]))
			i++;
		if (i != ft_strlen(name))
			return (1);
	}
	return (0);
}

int	del_env(t_env *env, char *name)
{
	t_env	*lst;
	t_env	*prev;
	
	if (!env || !get_my_env(env, name))
		return (0);
	lst = get_my_env(env, name);
	if (lst == env)
	{
		free(env);
		env = lst->next;
	}
	else
	{
		prev = env;
		while (prev->next != lst || prev->next)
			prev = prev->next;
		prev->next = lst->next;
		free(lst->name);
		if (lst->content)
			free(lst->content);
		free(lst);
	}
	return (0);
}

int	unset(t_shell *shell, char **cmd)
{
	printf("my unset working...\n");
	t_env	*prev;
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		if (check_name(cmd[i]))
		{
			printf("minishell: unset: %s: not a valid identifier\n", cmd[i]);
			status = 1;
		}
			
		else
			del_env(shell->env, cmd[i]);
		i++;
	}
	return (status);
}
