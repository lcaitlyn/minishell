/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <lcaitlyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:21:41 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 13:58:10 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_listprint(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->content)
			printf("%s=%s\n", lst->name, lst->content);
		lst = lst->next;
	}
	return (0);
}
