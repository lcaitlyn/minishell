/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:38:22 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/02 12:29:27 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	print_error(char *str)
{
	printf ("%s\n", str);
	return (1);
}
