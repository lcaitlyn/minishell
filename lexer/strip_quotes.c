/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:26:27 by gopal             #+#    #+#             */
/*   Updated: 2022/06/27 21:50:47 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_sym_word(char *word)
{
	char	flag_open;
	int		i;
	int		j;

	while (word[i])
	{
		if (!flag_open && is_quote(word[i]))
			flag_open = word[i];
		else if (flag_open && word[i] == flag_open)
			flag_open = 0;
		else
			j++;
		i++;
	}
	return (j);
}

void	strip_quotes(t_list *tokens)
{
	char	*word;
	char	*result;
	char	flag_open;
	int		i;
	int		j;

	while (tokens)
	{
		word = tokens->content;
		flag_open = 0;
		i = 0; // можно покумекать как сократить код потом (типа инверсия условии)
		j = 0;
		while (word[i] != '\0')
		{
			if (!flag_open && is_quote(word[i]))
				flag_open = word[i];
			else if (flag_open && word[i] == flag_open)
				flag_open = 0;
			else
				j++;
			i++;
		}
		result = (char *) ft_calloc(j + 1, 1);
		i = 0;
		j = 0;
		while (word[i] != '\0')
		{
			if (!flag_open && is_quote(word[i]))
				flag_open = word[i];
			else if (flag_open && word[i] == flag_open)
				flag_open = 0;
			else
				result[j++] = word[i];
			i++;
		}
		tokens->content = result;
		free(word);
		tokens = tokens->next;
	}
}