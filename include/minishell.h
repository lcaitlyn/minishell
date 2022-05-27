/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaitlyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:53:48 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/05/24 16:53:50 by lcaitlyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "color.h"
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	**envp;
	char	*name;
	t_env	*env;
}	t_shell;

typedef void * histdata_t;







int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *str, int a);
char	*ft_strnstr(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2, int need_free);
char	*ft_substr(char const *s, unsigned int start, int len);
char	*ft_itoa(int nb);
int		ft_atoi(const char *str);
int		ft_strindex(char *str, char a); //возвращает индекс символа в строке

char	**ft_free_split(char **arr, int j);
int		ft_wrdcnt(char const *s, char c);
char	**ft_split(char const *s, char c);

char	*get_next_line(int fd);

char	*get_uname(char *envp[]);
char	*get_name(char *envp[]);

void	ft_perror(char *str);

char	*get_pwd_for_name(char *envp[]);

void	change_dir(char *str, char *envp[]);

void	ls(char *str, char *envp[]);

void	action(char *str, char *envp[]);
void	ft_exec(char *argv, char *envp[]);


int		handle_signal(void);


t_env	*ft_lstnew(char *name, char *content);
t_env	*ft_lstadd_back(t_env *lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env *lst);

void	ft_clear_shell(t_shell *shell);
t_shell	*shell_init(char *envp[]);


#endif
