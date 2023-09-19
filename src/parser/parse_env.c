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

void parse_env(char **env)
{
  char *res[2];
  int i;
  int eq_pos;

  i = ~0;

  while (env[++i])
  {
    eq_pos = pos_chr(env[i], "=");
    res[0] = ft_strndup(env[i], eq_pos);
    res[1] = ft_strndup(env[i], ft_strlen(env[i]) - eq_pos + 1);
  }
}

