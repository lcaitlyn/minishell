/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:38:22 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/02 16:38:36 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
