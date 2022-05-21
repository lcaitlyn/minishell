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


int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *str, int a);
char	*ft_strnstr(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2, int need_free);
char	*ft_substr(char const *s, unsigned int start, int len);

char	**ft_free_split(char **arr, int j);
int		ft_wrdcnt(char const *s, char c);
char	**ft_split(char const *s, char c);

char	*get_next_line(int fd);

char	*get_uname(char *envp[]);
char	*get_name(char *envp[]);

void	ft_perror(char *str);

char	*get_envp(char *str, char *envp[]);
char	*get_pwd_for_name(char *envp[]);
char	*get_pwd(void);

void	change_dir(char *str, char *envp[]);

void    ls(char *str, char *envp[]);

void    action(char *str, char *envp[]);
void	ft_exec(char *argv, char *envp[]);


int     handle_signal(void);

#endif
