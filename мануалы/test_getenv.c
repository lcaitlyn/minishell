#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	char *pwd;

	pwd = getcwd(0, 256);
	printf ("%s\n", pwd);
	free (pwd);
	chdir(getenv("HOME"));
	pwd = getcwd(0, 256);
	printf ("%s\n", pwd);
	free (pwd);
	return 0;
}
