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
		printf ("free %s[%p] %s[%p]\n", lst->name, lst->name, lst->content, lst->content);
		write (1, lst->name, ft_strlen(lst->name));
		if (lst->content)
			write (1, lst->content, ft_strlen(lst->content));
		write(1, "\n", 1);
		next = lst->next;
		free(lst->name);
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = NULL;
		lst = next;
	}
}
