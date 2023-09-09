#include "../../inc/minishell.h"

int  cd(char **input)
{
  int i;
  static char *pwd;
  static char *oldpwd;

  pwd = getcwd(pwd, 0);
  i = ~0;
  while (input[++i])
  {
    if (!oldpwd)
      perror("cd: OLDPWD not set0");
    if (input[i] != 2)
      perror("to many args");
    else if (chdir(pwd) == ~0)
      perror("Error");
    else if (input[i] == "cd -")
      pwd = chdir(oldpwd);
    else if (input[i] == "cd")
      chdir(HOME);
    ft_memcpy(oldpwd, pwd);
  
  }
  return (1);
}
