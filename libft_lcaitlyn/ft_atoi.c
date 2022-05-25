/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:10:37 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/25 20:26:31 by gopal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	ft_action(const char *str, int i)
// {
// 	long long int	x;

// 	x = 0;
// 	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
// 	{
// 		x = x * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	return (x);
// }

// int	ft_atoi(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '\0')
// 		return (0);
// 	while (str[i] == '\n' || str[i] == '\f' || str[i] == '\v'
// 		|| str[i] == '\t' || str[i] == ' ' || str[i] == '\r')
// 		i++;
// 	if (str[i] >= '0' && str[i] <= '9')
// 		return (ft_action(str, i));
// 	else if (str[i + 1] >= '0' && str[i + 1] <= '9' && str[i] == '+')
// 		return (ft_action(str, i + 1));
// 	else if (str[i + 1] >= '0' && str[i + 1] <= '9' && str[i] == '-')
// 		return (-ft_action(str, i + 1));
// 	else
// 		return (0);
// }
