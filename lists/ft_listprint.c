#include "../include/minishell.h"

void    ft_listprint(t_env *lst)
{
	printf ("my env working...\n");
    if (!lst)
        return;
    while (lst)
    {
		if (lst->content)
        	printf ("%s=%s\n", lst->name, lst->content);
        lst = lst->next;
    }
}
