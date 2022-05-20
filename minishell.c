/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:53:40 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/17 12:00:37 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str = "";
	char	*name;
	char	*uname;

	name = get_name(envp);
	while (ft_strcmp(str, "exit"))
	{

		str = readline(name);
		if (!str)
		{
			printf ("exit\n");
			break ;
		}
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			if (!ft_strcmp(str, "env"))
				system("env");
			else if (!ft_strcmp(str, "minishell"))
			{
				ft_exec(str, envp);
//				if (!access("./minishell", X_OK)) // access return 0
//					system("./minishell");
//				else
//					printf(RED"No such file asshole!\n"RESET);
			}
			else
				printf (TERM_BLUE "%s\n" RESET, str);
		}
		free(str);
	}
	
	free (name);
	return (0);
}
