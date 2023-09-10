#include "../../inc/minishell.h"

int	bt_get_dirs(char **env, t_env *env_routes)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=/", 6) == 0)
			env_routes->home = env[i] + 5;
		else if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			env_routes->oldpwd = env[i] + 7;
		i++;
	}
	if (env_routes->home && env_routes->oldpwd)
		return (1);
	else if (env_routes->oldpwd)
		return (0);
	else
		return (-1);
}

// int	bt_cd(char *input, t_env env_routes) //o hacer const char *
// {
// 	//env_routes se asigna en función init
// 	int		i;
// 	char	*pwd = NULL;

// 	pwd = getcwd(pwd, 0);
// 	i = ~0;
// 	while (input[++i])
// 	{
// 		if (!env_routes.oldpwd)
// 			perror("cd: OLDPWD not set");
// 		if (chdir(pwd) == ~0)
// 			perror("Error");
// 		else if (ft_strcmp(&input[i], "cd -") == 0)
// 			chdir(env_routes.oldpwd);
// 		else if (ft_strcmp(&input[i], "cd"))
// 			chdir(env_routes.home);
// 	}
// 	return (1);
// }
//REVISAR LUEGO DE PARSEAR, OLDPWD SOLO VA CON CD ORIGINAL NO BUILTIN POR LO TANTO TIRAR DE VARIABLE STATIC