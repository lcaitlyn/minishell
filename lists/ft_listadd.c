/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:10 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 20:30:47 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_listadd_back(t_env *lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		last = ft_listlast(lst);
		last->next = new;
		return (lst);
	}
	else
		return (new);
}
