#include <stdio.h>

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	**sorting(char **arr)
{
	int	i = 0;
	int	j;
	char *tmp;

	while (arr[i])
	{
		j = 0;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) < 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

int main()
{
	char *arr[] = {
		"aaaz",
		"aaab",
		"aab",
		"a",
		"aa",
		"AA",
		"A",
		"AAA",
		"a",
		NULL
	};
	char **sorted_arr = sorting(arr);
	while (*sorted_arr)
		printf ("%s\n", *sorted_arr++);
	return (0);
}
