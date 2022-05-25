#include "../include/minishell.h"


int main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	*s1;
	char	*pwd;
	char	*home;
	char	*fr;

	// while (1)
	// {
	// 	str = readline("minishell> ");
	// 	s1 = getenv(str);
	// 	if (s1)
	// 		printf("%s\n", s1);
	// 	else
	// 		printf("(null)\n");
	// }
	// str = "usr/local/home/lcaitlyn/minishell";
	// s1 = "/home/lcaitlyn/";
	
	// printf("%s\n", ft_strnstr(str, s1, ft_strlen(str)) + ft_strlen(s1));

	pid_t	pid;
	char	**split;
	char	*cmd[] = {
		"ls",
		"-la",
		NULL};

	split = ft_split(getenv("PATH"), ':');
	int i = 0;
	// while (split[i])
	// 	printf ("%s\n", split[i++]);
	pid = fork();
	if (pid == 0)
	{
		if (execve(ft_strjoin_f(split[4], "/ls", 0), cmd, envp) == -1)
			perror("");
	}
	waitpid(pid, 0, 0);
	ft_free_split(split, 2);
	return (0);
}
