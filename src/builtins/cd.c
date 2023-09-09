#include "../../inc/minishell.h"

int  cd(char **env, int i)
{
  char *pwd;
  pwd = getcwd();

  if (i != 2)
    perror("to many args");
  else if (chdir(pwd) == -1)
      perror("Error");
  return (1);
}
