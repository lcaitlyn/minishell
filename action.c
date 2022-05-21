

#include "include/minishell.h"

void    action(char *str, char *envp[])
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        perror("minishell");
        return ;
    }
    else if (pid == 0)
        ft_exec(str, envp);
    waitpid(pid, 0, 0);
    return ;
}