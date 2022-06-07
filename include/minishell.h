/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:53:48 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/01 11:53:27 by gopal            ###   ########.fr       */
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
// Libft by gopal
# include "../libft/inc/libft.h"

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	**envp;
	char	**my_envp;
	char	*name;
	char	*home;
	t_env	*env;
}	t_shell;

typedef void * histdata_t;

int		exit_stat;




//	libft/

char	*ft_strjoin_f(char *s1, char *s2, int need_free);
//	возвращает индекс символа в строке
int		ft_strindex(char *str, char a);
//	доп проверка на strlen(haystack) == strlen(needle)
char	*my_strnstr(const char *haystack, const char *needle, size_t len);


//	split.c

char	**ft_free_split(char *split[]);
int		ft_wrdcnt(char const *s, char c);
char	**ft_split(char const *s, char c);


//	get_next_line/gnl.c

char	*get_next_line(int fd);


//	name.c

char	*get_uname(char *envp[]);
char	*get_name(t_shell *shell, char *envp[]);
char	*get_color_name(t_shell *shell, char *envp[]);
char	*writer(int *fd, char *envp[]);
char	*get_execve(char *path, char *cmd, char *envp[]);


//	action.c

int		split_len(char **arr);
void	action(char *str, char *envp[]);


//	ft_exec.c

void	ft_exec(char *path, char *argv, char *envp[]);


//	shlvl.c

int		ft_is_num(char *str);
char	*shlvl(char *content);


//	/lists

void	ft_listclear(t_env *lst);
int		ft_listprint(t_env *lst);


//	shell_init.c

void	ft_clear_shell(t_shell *shell);
t_env	*lst_new_env(char *name, char *content);
int		lstadd_back_env(t_shell *shell, t_env *new);
void	shell_env(t_shell *shell);
t_shell	*shell_init(char *envp[]);


//	signals/signal.c

int		handle_signal(void);


//	command/cd.c

int		open_dir(t_shell* shell, char *str);
int		micro_cd(t_shell *shell, char *str);
int		change_dir(t_shell *shell, char **str);


//	command/pwd.c

int		print_pwd(char  **cmd);
char	*get_pwd_for_name(t_shell *shell);


//	command/env.c

int		change_env(t_shell *shell, char *name, char *newcontent);
int		env_len(t_env *env);
char	**make_env(t_shell *shell);
char	*get_env_content(t_env *env, char *content);
t_env	*get_my_env(t_env *env, char *name);


//	command/echo.c

int		echo(char *cmd[]);


//	command/export.c

void	export_print(t_env	*lst);


//	error.c

void	ft_perror(char *str);
int		print_error(char *str);


//	Parser

char	*parser(char *str, char **env);



#endif
