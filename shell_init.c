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

#include "include/minishell.h"

t_shell	*shell_init(char *envp[])
{
	t_shell	*shell;
	char	*name;
	char	*content;
	int		i;
	int		j;
	
	shell = (t_shell *)malloc(sizeof(t_shell *));
	if (!shell)
		return (0);
//	shell->name = get_name(envp);
	if (!shell->name)
		shell->name = ft_strjoin("", "minishell> ", 0);
	i = 0;
	while (envp[i])
	{
		printf ("%s\n", envp[i]);
		name = ft_substr(envp[i], 0, ft_strindex(envp[i], '='));
		if (ft_strnstr(name, "SHLVL", ft_strlen(name)))
		{
			printf ("ya tut\n");
			content = ft_itoa(ft_atoi(ft_strchr(envp[i], '=') + 1) + 1);
		}
		else
			content = ft_strjoin("", ft_strchr(envp[i], '=') + 1, 0);
		printf ("%s=%s\n", name, content);
//		content = ft_substr(envp[i], ft_strindex(envp[i], '=') + 2,),
		free(name);
		free(content);
		i++;
	}
//	free(shell->name);
	free(shell);
	exit (0);
}
