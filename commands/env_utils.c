/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 02:28:51 by gopal             #+#    #+#             */
/*   Updated: 2022/06/29 02:54:04 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_arr_env(t_env *list_env, char **arr_env)
{
	int	i;

	i = 0;
	while (list_env)
	{
		if (list_env->content)
		{
			arr_env[i] = ft_strjoin(list_env->name, "=");
			arr_env[i] = ft_strjoin_f(arr_env[i], list_env->content, 1);
			i++;
		}
		list_env = list_env->next;
	}
	arr_env[i] = NULL;
}
