/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:01:26 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/02 13:56:05 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_unset(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[i] != '_')
		return (1);
	while (name[i])
	{
		if (!ft_isalpha(name[i])
			&& !ft_isdigit(name[i])
			&& name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	free_first_node_list(t_env *list_env, t_shell *shell)
{
	if (list_env == shell->env)
	{
		shell->env = shell->env->next;
		free(list_env->name);
		if (list_env->content)
			free(list_env->content);
		free(list_env);
	}
}

int	del_env(t_shell *shell, char *name)
{
	t_env	*lst;
	t_env	*prev;

	if (!shell->env || !get_my_env(shell->env, name))
		return (0);
	lst = get_my_env(shell->env, name);
	if (lst == shell->env)
		free_first_node_list(lst, shell);
	else
	{
		prev = shell->env;
		while (prev->next != lst)
			prev = prev->next;
		prev->next = lst->next;
		free(lst->name);
		if (lst->content)
			free(lst->content);
		free(lst);
	}
	return (0);
}

int	unset(t_shell *shell, char *cmd[])
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		if (check_name_unset(cmd[i]))
		{
			printf("minishell: unset: %s: not a valid identifier\n", cmd[i]);
			status = 1;
		}
		else
			del_env(shell, cmd[i]);
		i++;
	}
	return (status);
}
