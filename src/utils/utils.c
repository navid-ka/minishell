#include "../../inc/minishell.h"

char  *charjoin(char *s1, char c)
{
  int i;
  char *result;
  
  i = 0;
  if (!s1)
  {
    s1 = malloc(sizeof(char) * 1);
    if (!s1)
      return (NULL);
    s1[0] = '\0';
  }
  result = malloc(sizeof(char) * (ft_strlen(s1) + 1 + 1));
  while(s1[i])
  {
    result[i] = s1[i];
    i++;
  }
  result[i++] = c;
  result[i] = '\0';
  if (s1)
    free(s1);
  s1 = NULL; 
  return (result);
}
