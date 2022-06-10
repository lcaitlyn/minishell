#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *arr[] = {
		"~",
		NULL
	};
	printf ("%s\n%s\n", arr[0], arr[1]);
	pid_t id;
	id = fork();
	if (id == 0)
	{
		printf ("sosi\n");
		if (execve("/bin/echo", arr, envp) == -1)
			printf ("sosi\n");
	}
		
	else
		waitpid(id, 0, 0);
	return 0;
}
