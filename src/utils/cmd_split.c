/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:46:00 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/26 11:56:32 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_char(char *cmd, char c)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (!(cmd[i] == c))
			break ;
	return (i);
}

int	count_word_len(char *cmd)
{
	int	i;
	int	quotes;
	int	dquotes;

	i = -1;
	quotes = 0;
	dquotes = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && !dquotes)
			quotes = (quotes + 1) % 2;
		else if (cmd[i] == '"' && !quotes)
			dquotes = (dquotes + 1) % 2;
		if (!quotes && !dquotes && (cmd[i] == ' '))
			break ;
	}
	return (i);
}

char	**split_cmd(char *cmd, int quotes)
{
	char	**split;
	int		i;
	int		j;
	int		wlen;

	i = 0;
	split = malloc(sizeof(char *) * (quotes + 1));
	i = -1;
	j = 0;
	while (++i < quotes)
	{
		j += count_char(&cmd[j], ' ');
		wlen = count_word_len(&cmd[j]);
		if ((cmd[j] == '"' && cmd[j + wlen - 1] == '"')
			|| (cmd[j] == '\'' && cmd[j + wlen - 1] == '\''))
			split[i] = ft_strndup(&cmd[j + 1], wlen - 1);
		else
			split[i] = ft_strndup(&cmd[j], wlen + 1);
		j += wlen;
	}
	split[i] = NULL;
	return (split);
}

/*int main(void)
{
	char *cmd = "'hola' 'que tal'";
	char **output = split_cmd(cmd, 2);

	for (int i = 0; i < 2; i++) {
	ft_printf(1, "%s,\n", output[i]);
	}
}*/
