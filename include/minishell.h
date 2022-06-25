/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:53:48 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/06/25 10:34:00 by gopal            ###   ########.fr       */
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
	int		status;
	t_env	*env;
	t_list	*list_commands;
}	t_shell;

typedef void * histdata_t;

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

void	print_echo(char *str[]);
int		echo(char *cmd[]);


//	command/export.c

char	**sorting(char **arr);
int		export_len(t_env *env);
int		export_print(t_env	*lst);
int		add_env(t_shell *shell, char *name);
int		check_name_export(char *name);
int		export(t_shell *shell, char *cmd[]);


//	command/unset.c

int		check_name_unset(char *name);
int		del_env(t_shell *shell, char *name);
int		unset(t_shell *shell, char **cmd);

//	command/exit.c

int		my_exit(t_shell *shell, char **cmd);



//	error.c

void	ft_perror(char *str);
int		print_error(char *str);


// Lexer
void	print_list(t_list *list);
void	print_redir_list(t_list *list);
t_list	**make_tokens(char **input, char**env);
int		is_single_token(char *word);

// Parser
// void	parser(char **str, char **env);
void	parser(char **input, t_shell *shell);
void	free_list_cmd(void *command);

// Executor
void	execute_list_cmds(t_shell *shell);
char	**ft_find_paths(char *envp[]);
char	*ft_find_cmd(char *cmd, char *paths[]);
void	ft_clear_paths(char *paths[]);
int		executor(t_shell *shell);


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
