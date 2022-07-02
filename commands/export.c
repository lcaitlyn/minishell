/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:17 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/01 19:24:13 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sorting(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) < 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

char	**get_sort_env(t_env *list_env)
{
	char	**arr_sort_env;
	int		i;
	int		size_list_env;

	size_list_env = export_len(list_env);
	arr_sort_env = (char **) malloc((size_list_env + 1) * sizeof(char *));
	i = 0;
	while (list_env)
	{
		arr_sort_env[i++] = list_env->name;
		list_env = list_env->next;
	}
	arr_sort_env[i] = NULL;
	sorting(arr_sort_env);
	return (arr_sort_env);
}

int	export_print(t_env	*env)
{
	char	**sorted;
	int		i;

	if (!env)
		return (1);
	sorted = get_sort_env(env);
	i = 0;
	while (sorted[i])
	{
		printf ("declare -x %s", sorted[i]);
		if (get_env_content(env, sorted[i]))
			printf("=\"%s\"", get_env_content(env, sorted[i]));
		i++;
		printf ("\n");
	}
	free(sorted);
	return (0);
}

int	add_env(t_shell *shell, char *name)
{
	char	*new_name;

	if (!ft_strnstr(name, "=", ft_strlen(name)))
		change_env(shell, name, NULL);
	else
	{
		new_name = ft_substr(name, 0, ft_strindex(name, '='));
		change_env(shell, new_name,
			ft_strdup(ft_strnstr(name, "=", ft_strlen(name)) + 1));
		free (new_name);
	}
	return (0);
}

int	export(t_shell *shell, char *cmd[])
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!cmd[1])
		return (export_print(shell->env));
	while (cmd[i])
	{
		if (check_name_export(cmd[i]))
		{
			printf("minishell: export: %s: not a valid identifier\n", cmd[i]);
			status = 1;
		}
		else
			add_env(shell, cmd[i]);
		i++;
	}
	return (status);
}
