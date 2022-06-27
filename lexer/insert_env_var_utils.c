/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:32:51 by gopal             #+#    #+#             */
/*   Updated: 2022/06/27 18:39:38 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *word, int *i, int *j)
{
	char	*key;

	while (is_sym_var_env(word[*j]))
		*j = *j + 1;
	key = ft_substr(word, *i, *j - *i);
	return (key);
}
