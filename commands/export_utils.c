/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 02:50:50 by gopal             #+#    #+#             */
/*   Updated: 2022/06/29 04:29:02 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_export(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[i] != '_')
		return (1);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalpha(name[i])
			&& !ft_isdigit(name[i])
			&& name[i] != '_'
			&& name[i] != '=')
			return (1);
		i++;
	}
	return (0);
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
