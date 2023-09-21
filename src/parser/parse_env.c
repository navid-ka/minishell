#include "../../inc/minishell.h"

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

t_env *append_env(char *key, char *value)
{
  t_env *ls;

  ls = ft_calloc(sizeof(t_env), 1);
  if (!ls)
    return (NULL);
  ls->key = key;
  ls->value = value;
  return (ls);
}

void get_env(char **env)
{
  char *kv[2];
  int i;
  int eq_pos;
  //t_env *dict;
 
  //ft_memset(&dict, 0, sizeof(t_env));
  i = ~0;
  //dict->capacity = ~0;
  while (env[++i])
  {
    eq_pos = pos_chr(env[i], '=');
    kv[0] = ft_strndup(env[i], eq_pos);
    kv[1] = ft_strndup(env[i], ft_strlen(env[i]) - eq_pos + 1);
    //while (dict->capacity++)
      append_env(kv[0], kv[1]);
  }
  //dict->ms_env = ft_split(*env, '\n'); //TODO: find another logic for this implementation.
}

