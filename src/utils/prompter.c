#include "../../inc/minishell.h"

void  pr(char *s)
{
  while (*s)
    write(1,s++,1);
}

void prompter(void)
{
  pr("\x1b[35m\n");
  pr("   _     _     _     _     _     _     _     _     _     _  \n");
  pr("  / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\ \n");
  pr(" ( m ) ( i ) ( n ) ( i ) ( c ) ( o ) ( n ) ( c ) ( h ) ( a )\n");
  pr("  \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/ \n");
  pr("\n\n\x1b[0m");
}

char *shell_prompt(void)
{
    char *pwd;
    char *prompt;
    char *ansi;
    char *prompt_left;
    char *prompt_right;
    int i;

    pwd = NULL;
    ansi = "\033[0;36m\033[1m";
    pwd = getcwd(pwd, 0);
    i = ft_strlen(pwd) - 1;
    while (i >= 0 && pwd[i] != '/')
        i--;
    if (i >= 0)
        prompt_left = &pwd[i + 1];
    else 
        prompt_left = pwd;
    prompt_right = ft_strjoin(ansi, prompt_left);
    prompt_left = "\033[0m 🔞👅 \x1b[35mConcha( ͡° ͜ʖ ͡°)\n▸ \033[0m";
    prompt = ft_strjoin(prompt_right, prompt_left);
    free(prompt_right);
    free(pwd);
    return (prompt);
}
