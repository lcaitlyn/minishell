/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gopal <gopal@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:53:48 by lcaitlyn          #+#    #+#             */
/*   Updated: 2022/07/03 03:14:08 by gopal            ###   ########.fr       */
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
# include <fcntl.h>
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
	t_list	**list_tokens;
	t_list	*list_commands;
}	t_shell;

typedef struct s_command
{
	char	*cmd_name;
	t_list	*list_args;
	int		args_count;
	char	**args;
	t_list	*redirects_read;
	t_list	*redirects_write;
	int		fd_read;
	int		fd_write;
}	t_command;

typedef struct s_redirect
{
	char	*file_name;
	char	*type_redir;	
}	t_redirect;

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
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

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
int		signal_sigint(int sig);

//	command/cd.c
int		open_dir(t_shell *shell, char *str);
int		micro_cd(t_shell *shell, char *str);
int		change_dir(t_shell *shell, char **str);

//	command/pwd.c
int		print_pwd(char **cmd);
char	*get_pwd_for_name(t_shell *shell);

//	command/env.c
int		change_env(t_shell *shell, char *name, char *newcontent);
int		env_len(t_env *env);
void	fill_arr_env(t_env *list_env, char **arr_env);
char	**make_env(t_shell *shell);
char	*get_env_content(t_env *env, char *content);
t_env	*get_my_env(t_env *env, char *name);

//	command/echo.c
int		echo(char *args[], int fd);

//	command/export.c
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
void	check_open_q(char c, char *flag_open);
int		is_string(char c);
int		is_str_word(char *str);
void	insert_env_var_tokens(t_list *list, char **env);
char	*get_key(char *word, int *i, int *j);
int		is_quote(char c);
void	check_open_q(char c, char *flag_open);
int		is_spec_sym(char c);
int		is_sym_var_env(char c);
void	strip_quotes(t_list *tokens);
void	split_into_tokens(char *str, t_list **tokens);
void	lexer(char **input, t_shell *shell);

// Parser
void	parser(t_shell *shell);
void	free_list_cmd(void *command);
// Parser: prints
void	print_list_cmds(t_list *list_commands);
void	print_list(t_list *list);
void	print_arr_str(char **arr);
void	print_redir_list(t_list *list);
// Parser: Utils
int		is_redirects(char *str);
int		is_pipe(char *str);
int		is_spec_token(char *str);
int		is_token_only_spec_sym(char *str);
char	**get_arr_args(t_list *list);
int		is_valid_tokens(t_list *tokens);

// Executor
void	execute_list_cmds(t_shell *shell);
char	**ft_find_paths(char *envp[]);
char	*ft_find_cmd(char *cmd, char *paths[]);
void	ft_clear_paths(char *paths[]);
int		is_builtin_cmd(char *cmd_name);
void	execute_builtin_cmd(t_command *cmd, t_shell *shell);
void	check_redirs_read(t_command *cmd);
void	check_redirs_write(t_command *cmd);
void	execute_cmd(t_command *cmd, t_shell *shell);
int		executor(t_shell *shell);

#endif
