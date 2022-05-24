/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:03:53 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/24 19:03:56 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear(t_env	*lst)
{
	t_env	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = NULL;
		lst = next;
	}
}
