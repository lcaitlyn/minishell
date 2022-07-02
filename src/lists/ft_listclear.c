/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:03:53 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/02 11:58:40 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_listclear(t_env *lst)
{
	t_env	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->name);
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = NULL;
		lst = next;
	}
}
