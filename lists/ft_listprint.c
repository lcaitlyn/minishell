#include "../include/minishell.h"

int	ft_listprint(t_env *lst)
{
	printf ("my env working...\n");
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->content)
		printf ("%s=%s\n", lst->name, lst->content);
		lst = lst->next;
	}
	return (0);
}
