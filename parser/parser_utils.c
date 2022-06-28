/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:42:35 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 10:54:15 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirects(char *str)
{
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<") || !ft_strcmp(str, "<<"));
}

int	is_pipe(char *str)
{
	return (!ft_strcmp(str, "|"));
}

int	is_spec_token(char *str)
{
	return (is_redirects(str) || is_pipe(str));
}

char	**get_arr_args(t_list *list)
{
	char	**arr;
	int		size;
	int		i;

	arr = NULL;
	size = ft_lstsize(list);
	if (size)
	{
		arr = (char **) ft_calloc(size + 1, sizeof(char *));
		if (!arr)
			return (arr);
		i = 0;
		while (list)
		{
			arr[i++] = ft_strdup((char *) list->content);
			list = list->next;
		}
		arr[size] = NULL;
	}
	return (arr);
}
