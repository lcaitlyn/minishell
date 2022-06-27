/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_spec_sym.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:44:43 by gopal             #+#    #+#             */
/*   Updated: 2022/06/27 15:45:31 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_into_spec_sym(t_list **tokens)
{
	t_list	*list;
	char	*word;
	int		i;
	int		j;
	char	flag_open;
	char	*part1;
	char	*part2;
	char	*part3;

	list = *tokens;
	while (list)
	{
		word = list->content;
		i = 0;
		part1 = NULL;
		part2 =  NULL;
		part3 = NULL;
		flag_open = 0;
		if (is_single_token(word))
		{
			list = list->next;
			continue;
		}
		while (word[i])
		{			
			check_open_q(word[i], &flag_open);
			j = i;
			// это скип для первого слова
			while ((!is_spec_sym(word[j]) && word[j] != '\0')
				|| (is_spec_sym(word[j]) && flag_open))
			{
				j++;
				check_open_q(word[j], &flag_open);
			}
			//
			if (!word[j]) // если 1е слово идет до конца строки, то резать нечего
			{
				i = j;
				break;
			}
			if (j > i)
				part1 = ft_substr(word, i, j - i);
			i = j;
			while (is_spec_sym(word[j]))
				j++;
			part2 = ft_substr(word, i, j - i);
			part3 = NULL;
			if (word[j]) {
				i = j;
				while (word[j])
					j++;
				part3 = ft_substr(word, i, j - i);
			}

			t_list *tail;
			tail = list->next;
			free(word); 
			if (part1)
			{
				list->content = part1;
				list->next = ft_lstnew(part2);
				if (part3)
				{
					list->next->next = ft_lstnew(part3);
					list->next->next->next = tail;
					word = part3;
					i = 0;
					break;
				}
				else
				{	
					list->next->next = tail;
					list = list->next;
					break;
				}
			}
			else
			{
				list->content = part2;
				if (part3)
				{
					list->next = ft_lstnew(part3);
					list->next->next = tail;
					break;
				}
			}
			i++;
		}
		list = list->next;
	}
}