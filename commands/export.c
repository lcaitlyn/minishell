/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:17 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/31 16:10:19 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	**sorting(char **arr)
{
	int	i = 0;
	int	j;
	char *tmp;

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

void	export_print(t_env	*env)
{
	char	**sorted;
	t_env	*lst;
	int		i;

	if (!env)
		return;
	lst = env;
	sorted = malloc((env_len(env) + 1) * sizeof(char *));
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
			printf("=\"%s\"", get_env_content(env, sorted[i++]));
		printf ("\n");
	}
	free(sorted);
}

//void	export_print(t_env	*lst)
//{
//	printf ("my export working...\n");
//	if (!lst)
//		return;
//	while (lst)
//	{
//		printf ("declare -x %s", lst->name);
//		if (lst->content)
//			printf("=\"%s\"", lst->content);
//		printf ("\n");
//		lst = lst->next;
//	}
//}
