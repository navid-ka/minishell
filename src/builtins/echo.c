#include "../../inc/minishell.h"

void bt_echo(t_token *tok)
{
  int endl;

  endl = 0;
  if (strcmp(tok->str, "-n") == 0)
    endl = 1;
  if (endl)
    tok = tok->next;
  ft_printf(1, "%s", tok->str);
  if (!endl)
    ft_printf(1, "\n");
}
