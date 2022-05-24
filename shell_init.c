/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:03 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/24 18:50:17 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <include/minishell.h>

t_shell	*shell_init(char *envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell *));
	if (!shell)
		return (0);
	shell->name = get_name();
	if (!shell->name)
		shell->name = ft_strjoin("", "minishell> ", 0);
	
}
