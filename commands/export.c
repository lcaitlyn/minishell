/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:17 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/31 16:10:19 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_print(t_env	*lst)
{
	printf ("my export working...\n");
	if (!lst)
		return;
	while (lst)
	{
		printf ("declare -x %s", lst->name);
		if (lst->content)
			printf("=\"%s\"", lst->content);
		printf ("\n");
		lst = lst->next;
	}
}
