/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_spec_sym.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:44:43 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 09:04:41 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_part1(char *word, int *i)
// {
// 	char	flag_open;
// 	char	*part1;
// 	// int		i;
// 	int		j;

// 	part1 = NULL;
// 	flag_open = 0;
// 	*i = 0;
// 	while (word[*i])
// 	{
// 		check_open_q(word[*i], &flag_open);
// 		j = *i;
// 		while ((!is_spec_sym(word[j]) && word[j] != '\0')
// 			|| (is_spec_sym(word[j]) && flag_open))
// 		{
// 			j++;
// 			check_open_q(word[j], &flag_open);
// 		}
// 		(*i)++;
// 	}
// 	if (!word[j]) // если 1е слово идет до конца строки, то резать нечего
// 	{
// 		*i = j;
// 		return (part1); // снаружи нужно закончить цикл
// 	}
// 	if (j > *i)
// 		part1 = ft_substr(word, *i, j - *i);
// 	*i = j;
// 	return (part1);
// }

// void	split_into_spec_sym(t_list **tokens)
// {
// 	t_list	*list;
// 	char	*word;
// 	int		i;
// 	int		j;
// 	char	flag_open;
// 	char	*part1;
// 	char	*part2;
// 	char	*part3;

// 	list = *tokens;
// 	while (list)
// 	{
// 		word = list->content;
// 		part1 = NULL;
// 		part2 =  NULL;
// 		part3 = NULL;
// 		flag_open = 0;
// 		i = 0;
// 		if (is_single_token(word))
// 		{
// 			list = list->next;
// 			continue;
// 		}
// 		while (word[i])
// 		{
// 			check_open_q(word[i], &flag_open);
// 			j = i;
// 			// это скип для первого слова
// 			while ((!is_spec_sym(word[j]) && word[j] != '\0')
// 				|| (is_spec_sym(word[j]) && flag_open))
// 			{
// 				j++;
// 				check_open_q(word[j], &flag_open);
// 			}
// 			если 1е слово идет до конца строки, то резать нечего
// 			if (!word[j]) 
// 			{
// 				i = j;
// 				break;
// 			}
// 			if (j > i)
// 				part1 = ft_substr(word, i, j - i);
// 			i = j;
// 			// part1 = get_part1(word, &i);
// 			if (!part1)
// 				break ;
// 			while (is_spec_sym(word[j]))
// 				j++;
// 			part2 = ft_substr(word, i, j - i);
// 			part3 = NULL;
// 			if (word[j]) {
// 				i = j;
// 				while (word[j])
// 					j++;
// 				part3 = ft_substr(word, i, j - i);
// 			}

// 			t_list *tail;
// 			tail = list->next;
// 			free(word); 
// 			if (part1)
// 			{
// 				list->content = part1;
// 				list->next = ft_lstnew(part2);
// 				if (part3)
// 				{
// 					list->next->next = ft_lstnew(part3);
// 					list->next->next->next = tail;
// 					word = part3;
// 					i = 0;
// 					break;
// 				}
// 				else
// 				{	
// 					list->next->next = tail;
// 					list = list->next;
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				list->content = part2;
// 				if (part3)
// 				{
// 					list->next = ft_lstnew(part3);
// 					list->next->next = tail;
// 					break;
// 				}
// 			}
// 			i++;
// 		}
// 		list = list->next;
// 	}
// }