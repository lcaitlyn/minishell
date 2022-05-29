#include "../include/minishell.h"

void	export_print(t_env	*lst)
{
	printf ("my export working...");
	if (!lst)
        return;
    while (lst)
    {
        printf ("declare -x %s", lst->name);
		if (lst->content)
			printf("=\"%s\"", lst->content);
		printf ("\n");
        lst = lst->next;
    }
}