#include <stdio.h>
#include <stdlib.h>

char    **ft_free_split(char *split[])
{
    int    i;

    i = 0;
    if (!split)
        return (NULL);
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
    return (NULL);
}

int main() {
  char **arr;
  int i = 0;
  arr = malloc(sizeof(char *) * 6);
  while (i < 5)
    arr[i++] = calloc(sizeof(char), 5);
  arr[i] = NULL;
  ft_free_split(arr);    
  return 0;
}
