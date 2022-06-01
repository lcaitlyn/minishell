#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	char *pwd;
	char *home;

//	pwd = getcwd(0, 256);
//	printf ("%s\n", pwd);
//	free (pwd);
//	printf ("%s\n", getenv("HOME"));
//	printf ("%s\n", getenv("Hqwe"));
	home = getenv("HOME");
	if (!home)
	{
		// возможно создать нормальную функцию
		
		printf ("minishell: cd: HOME not set\n");
		return 0;
	}
	if (chdir("/pohui/blyea") == -1)
		perror("minishell: cd: ");
//	chdir(getenv("HOME"));
	pwd = getcwd(0, 256);
	printf ("%s\n", pwd);
	free (pwd);
	return 0;
}
