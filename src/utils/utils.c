/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:35:01 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/27 10:36:46 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*charjoin(char *s1, char c)
{
	int i;
	char *result;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	result = malloc(sizeof(char) * (ft_strlen(s1) + 1 + 1));
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	if (s1)
		free(s1);
	s1 = NULL;
	return (result);
}

char	*ft_strndup(const char *src, size_t len)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, src, len);
	return (str);
}

int	count_quotes(char *cmd)
{
	int	i;
	int	count;
	int	dquotes;
	int	quotes;

	i = ~0;
	count = 0;
	dquotes = 0;
	quotes = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '"' && !quotes)
			dquotes = (dquotes + 1) % 2;
		else if (cmd[i] == '\'' && !dquotes)
			quotes = (quotes + 1) % 2;
		if ((!quotes && !dquotes) && !(cmd[i] == ' ')
			&& ((cmd[i + 1] == ' ') || !cmd[i + 1]))
			count++;
	}
	return (count);
}
