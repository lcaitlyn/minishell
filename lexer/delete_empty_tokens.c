/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:49:49 by gopal             #+#    #+#             */
/*   Updated: 2022/06/27 17:02:07 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// а если нужно удалить первое значение? и больше ничего нет
// "" echo "" ""
// echo "" ""

void	cut_node_list(t_list *list, t_list *tail)
{
	char	*word;

	word = tail->content;
	if (!ft_strcmp(word, ""))
	{
		list->next = tail->next;
		ft_lstdelone(tail, free);
		tail = NULL;
	}
}

void	delete_empty_tokens(t_list **tokens)
{
	t_list	*tail;
	t_list	*list;
	t_list	*prev;
	char	*word;

	list = *tokens;
	prev = NULL;
	while (list)
	{
		word = list->content;
		tail = list->next;
		if (!prev && word[0] == '\0')
		{
			ft_lstdelone(list, free);
			list = *tokens;
			*tokens = tail;
			continue ;
		}
		if (tail)
			cut_node_list(list, tail);
		prev = list;
		list = list->next;
	}
}
