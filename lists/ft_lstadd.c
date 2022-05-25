/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:10 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/24 19:10:12 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_lstadd_back(t_env *lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		last = ft_lstlast(lst);
		last->next = new;
		return (lst);
	}
	else
		return (new);
}