/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:21:41 by gopal             #+#    #+#             */
/*   Updated: 2022/07/02 12:33:37 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_listprint(t_env *lst)
{
	printf ("my env working...\n");
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
