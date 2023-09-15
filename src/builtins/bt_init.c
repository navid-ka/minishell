#include "../../inc/minishell.h"

bool bt_is_builtin(char **argv)
{
  if (ft_strcmp(argv[0], "cd") == 0)
    return (true);
  if (ft_strcmp(argv[0], "env") == 0)
    return (true);
  if (ft_strcmp(argv[0], "echo") == 0)
    return (true);
  if (ft_strcmp(argv[0], "pwd") == 0)
    return (true);
  if (ft_strcmp(argv[0], "export") == 0)
    return (true);
  if (ft_strcmp(argv[0], "unset") == 0)
    return (true);
  if (ft_strcmp(argv[0], "exit") == 0)
    return (true);
  return (false);
}

void  bt_check_builtin(char **argv, char **env)
{
  if (ft_strcmp(argv[0], "cd") == 0)
    //bt_cd(argv, env);
    ft_printf(1, "to implement\n");
  if (ft_strcmp(argv[0], "env") == 0)
    bt_env(env);
  if (ft_strcmp(argv[0], "echo") == 0)
    ft_printf(1, "to implement\n");
    //bt_echo(argv);
  if (ft_strcmp(argv[0], "pwd") == 0)
    ft_printf(1, "to implement\n");
    //bt_pwd();
  if (ft_strcmp(argv[0], "export") == 0)
    ft_printf(1, "to implement\n");
    //bt_export();
  if (ft_strcmp(argv[0], "unset") == 0)
    ft_printf(1, "to implement\n");
    //bt_unset();
  if (ft_strcmp(argv[0], "exit") == 0)
    ft_printf(1, "to implement\n");
    //bt_exit();
} 
