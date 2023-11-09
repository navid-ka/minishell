/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:35:01 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/09 11:59:56 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*charjoin(char *str, char ch)
{
	char	*copy;
	int		c;

	c = -0;
	if (str == NULL)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	copy = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!copy)
		return (free(copy), NULL);
	while (str[c])
	{
		copy[c] = str[c];
		c++;
	}
	copy[c] = ch;
	copy[c + 1] = '\0';
	free(str);
	return (copy);
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

void	*ft_realloc(void *ptr, size_t newsize, size_t oldsize)
{
	size_t	copy_size;
	void	*newptr;

	if (!ptr)
		return (malloc(newsize));
	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (newsize == oldsize)
		return (ptr);
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	if (newsize < oldsize)
		copy_size = newsize;
	else
		copy_size = oldsize;
	ft_memcpy(newptr, ptr, copy_size);
	free(ptr);
	return (newptr);
}
