#include "unistd.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strindex(char *str, char a)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != a)
		i++;
	if (i < ft_strlen(str))
		return (i);
	else
		return (-1);
}

int main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*name;

	i = 0;
	write (1, "unset", 5);
	while (envp[i])
	{
		write(1, " ", 1);
		write(1, envp[i], ft_strindex(envp[i], '='));
		
//		name = ft_substr(shell->envp[i], 0, ft_strindex(shell->envp[i], '='));
//		printf (" %s", name);
//		free(name);
//		printf ("%s\n", envp[i]);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
