/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:26:27 by gopal             #+#    #+#             */
/*   Updated: 2022/06/28 03:32:54 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_sym_word(char *word)
{
	char	flag_open;
	int		i;
	int		size;

	i = 0;
	size = 0;
	flag_open = 0;
	while (word[i])
	{
		if (!flag_open && is_quote(word[i]))
			flag_open = word[i];
		else if (flag_open && word[i] == flag_open)
			flag_open = 0;
		else
			size++;
		i++;
	}
	return (size);
}

char	*get_stripped_word(char *word, int size)
{
	char	flag_open;
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	flag_open = 0;
	result = (char *) ft_calloc(size + 1, sizeof(char));
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
	return (result);
}

void	strip_quotes(t_list *tokens)
{
	char	*word;
	int		size;

	while (tokens)
	{
		word = tokens->content;
		size = calc_sym_word(word);
		tokens->content = get_stripped_word(word, size);
		free(word);
		tokens = tokens->next;
	}
}
