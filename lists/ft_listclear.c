/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:03:53 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/27 16:10:25 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_listclear(t_env *lst)
{
	t_env	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->name);
		free(lst->content);
		free(lst);
		lst = NULL;
		lst = next;
	}
}
