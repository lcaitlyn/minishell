#include "../include/minishell.h"


int main()
{
	printf ("%d\n", access("/usr/bin/whoami", F_OK));
	printf ("%d\n", access("/bin/hostname", F_OK));
	printf ("%d\n", access("/usr/bin/which", F_OK));
	pid_t	id;
	char	*argv[] = {
		"which"
		"ls",
		NULL
	};
	id = fork();
	if (id == 0)
	{
		if (execve("/usr/bin/which", argv, 0) == -1)
			perror("");
	}
//	system("echo ~");
	return 0;
}
