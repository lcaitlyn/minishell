#include "../include/minishell.h"

int	my_exit(t_shell *shell, char **cmd)
{
	int	i;

	if (!cmd)
		return (1);
	if (cmd[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	i = 0;
	while (cmd[1][i])
		if (!ft_isdigit(cmd[1][i]))
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			return (1);
		}
		else
			i++;
	i = ft_atoi(cmd[1]);
	if (i >= 0 && i <= 255)
		shell->status = i;
	else
		shell->status = i % 255;
	return (0);
}