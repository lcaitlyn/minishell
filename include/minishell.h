/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:53:48 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/18 21:54:00 by gopal            ###   ########.fr       */
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
	t_env	*env;
}	t_shell;

typedef void * histdata_t;

// int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_f(char *s1, char *s2, int need_free);
int		ft_strindex(char *str, char a); //возвращает индекс символа в строке

// split.c
char	**ft_free_split(char **arr, int j);
int		ft_wrdcnt(char const *s, char c);
char	**ft_split(char const *s, char c);

char	*get_next_line(int fd);

char	*get_uname(char *envp[]);
char	*get_name(t_shell *shell, char *envp[]);

void	ft_perror(char *str);

char	*get_pwd_for_name(t_shell *shell);

void	change_dir(t_shell *shell, char *str, char *envp[]);

void	ls(char *str, char *envp[]);

void	action(char *str, char *envp[]);
void	ft_exec(char *argv, char *envp[]);


int		handle_signal(void);

// Lists

void	ft_listclear(t_env *lst);
void	ft_listprint(t_env *lst);



void	ft_clear_shell(t_shell *shell);
t_shell	*shell_init(char *envp[]);

// Parser
void	parser(char **str, char **env);

int		split_len(char **arr);
char	**make_env(t_shell *shell);
void	export_print(t_env	*lst);
char	*get_my_env(t_env *env, char *str);

// Lexer
void	print_list(t_list *list);
void	print_redir_list(t_list *list);
t_list	**make_tokens(char **input, char**env);
int		is_single_token(char *word);

typedef	struct s_command
{
	char	*cmd_name;
	t_list	*list_args;
	int		args_count;
	char	**args; // не забыть 0 - команда
	t_list	*redirects_read; // если NULL - Стандарт ввод
	t_list	*redirects_write;
	int		fd_read; // start -1
	int		fd_write; // start -1
	
}	t_command;

typedef struct s_redirect
{
	char	*file_name;
	char	*type_redir;	
}	t_redirect;

#endif
