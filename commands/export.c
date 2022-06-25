/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:17 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/23 02:31:54 by gopal            ###   ########.fr       */
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

int	export_len(t_env *env)
{
	int		env_size;
	t_env	*lst;

	lst = env;
	env_size = 0;
	while (lst)
	{
		env_size++;
		lst = lst->next;
	}
	return (env_size);
}

int	export_print(t_env	*env)
{
	char	**sorted;
	t_env	*lst;
	int		i;

	if (!env)
		return (1);
	lst = env;
	sorted = malloc((export_len(env) + 1) * sizeof(char *));
	i = 0;
	while (lst)
	{
		sorted[i++] = lst->name;
		lst = lst->next;
	}
	sorted[i] = NULL;
	sorted = sorting(sorted);
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
		change_env(shell, new_name, ft_strdup(ft_strnstr(name, "=", ft_strlen(name)) + 1));
		free (new_name);
	}
	return (0);
}

int	check_name_export(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[i] != '_')
		return (1);
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i])
		&& name[i] != '_' && name[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

int	export(t_shell *shell, char *cmd[])
{
	printf("my export working...\n");
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
