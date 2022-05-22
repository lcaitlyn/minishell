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

	home = getenv("HOME");
	pwd = malloc(100);
	fr = pwd;
	pwd = getcwd(pwd, 256);
	pwd = ft_strnstr(pwd, home, ft_strlen(pwd));
	if (!pwd)
		pwd = getcwd(pwd, 1000);
	else
		pwd = ft_strjoin("~", pwd + ft_strlen(home), 0);
	free(fr);
	fr = pwd;
	pwd = ft_strjoin(TERM_BLUE, pwd, 0);
	free(fr);
	pwd = ft_strjoin(pwd, RESET, 1);
	return (pwd);
}
