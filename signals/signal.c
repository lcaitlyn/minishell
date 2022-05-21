#include "../include/minishell.h"

int    signal_sigint(int sig)
{
    printf ("\n");
    return (1);
}

void    signal_sigtstp(void)
{
    return ;
}

void    signal_sigquit(void)
{
    return ;
}

int    handle_signal(void)
{
    if (signal(SIGINT, (void *)&signal_sigint))
        return (1);
    signal(SIGTSTP, (void *)&signal_sigtstp);
    signal(SIGQUIT, (void *)&signal_sigquit);
    return (0);
}