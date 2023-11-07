/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <bifrost@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:22:08 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/07 09:51:36 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptrs;
	size_t	i;

	if (len == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptrs = (char *) malloc(sizeof(char) * (len + 1));
	if (ptrs == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (i < len && s[i])
	{
		ptrs[i] = s[i + start];
		i++;
	}
	ptrs[i] = '\0';
	return (ptrs);
}
