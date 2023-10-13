/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:53:36 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/10/13 16:00:54 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



// this will help me find the index of '='
int	pos_chr(const char *s, int c)
{
	int	i;

	if (!s)
		return (-2);
	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}

//in expansor.c maybe move to env_utils
int	env_index(t_mch *sh, char *env_name);

int is_exportable(char *e, char *env)
{
	size_t env_len;

	env_len = ft_strlen(env);
    if (ft_isdigit(e[0]))
        return (0);
    if (ft_strncmp(e, env, env_len) == 0) 
        if (e[env_len] == '\0' || e[env_len] == '+' || (e[env_len] == '=' && e[env_len + 1] != '\0'))
            return (1);
    return (0);
}

void    update_env_value;

void	append_env(t_mch *sh, const char *env_name)
{
	size_t	i;
	size_t	new_len;
	char **new_env;

	i = ~0;
	new_len = sizeof(char *) * (i + 2);
	while(sh->env[++i])
		;
	new_env = ft_realloc(sh->env, new_len, i);
	sh->env = new_env;
	sh->env[i] = ft_strdup(env_name);
	sh->env[i++] = NULL;
}

void    print_export(void)
{
	t_mch shell;
	int	i; 
	
	i = ~0;
	while (sh.env[++i])
		ft_printf(1, "declare -x %s", sh.env[i]);
}

//  export alone joins "declare -x"  with normal env
void	bt_export(t_mch *sh)
{
	int	i;
	t_parser *exp;
	char *env_name;

	i = 0;
	exp = sh->parser;
	env_name = exp->args[i];
    if (exp->next->type != CMD)
        print_export();
	while (exp->args[i])
    {
        if (is_exportable(env_name, sh->env[i]))
            update_env_value(sh, env_name); //TODO:
        else
            append_env(sh, env_name);
        i++;
    }
