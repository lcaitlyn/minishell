#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	// DIR				*dir;
	// struct dirent	*sd;
	// int i = 0;

	// printf ("%s\n", get_envp("PWD=", envp));
	// dir = opendir("/Users/lcaitlyn/Desktop/lcaitlyn");

	// if (!dir)
	// {
	// 	printf ("poshel naxui\n");
	// 	exit (0);
	// }
	// if (chdir("/Users/lcaitlyn/Desktop/lcaitlyn") == -1)
	// 	printf("Idi naxui\n");
	// printf ("%s\n", get_envp("PWD=", envp));



	pid_t   pid;
    char    *str;

    pid = fork();
    if (pid == 0)
        str = malloc(1);
    waitpid(pid, 0, 0);
    return 0;

	// char	*s;
	// int		i = 0;
	
	// s = getcwd(s, 100);
	// printf("%s\n", s);
	// chdir("/Users/lcaitlyn/Desktop/lcaitlyn");
	// s = getcwd(s, 100);
	// printf("%s\n", s);
	// i = 0;
	// while (envp[i])
	// 	printf ("%s\n", envp[i++]);
	// free (s);
//	printf ("%d\n", get_current_dir_name());
	return 0;
}
