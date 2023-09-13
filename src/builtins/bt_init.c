#include "../../inc/minishell.h"

void  bt_check_builtin(char **argv, char **env)
{
  if (ft_strcmp(argv[0], "cd") == 0)
    bt_cd(argv, env);
  if (ft_strcmp(argv[0], "env") == 0)
    bt_env(env);
  if (ft_strcmp(argv[0], "echo") == 0)
    bt_echo(argv);
  if (ft_strcmp(argv[0], "pwd") == 0)
    bt_pwd();
  if (ft_strcmp(argv[0], "export") == 0)
    bt_export();
  if (ft_strcmp(argv[0], "unset" == 0))
    bt_unset();
  if (ft_strcmp(argv[0], "exit") == 0)
    bt_exit();
} 
