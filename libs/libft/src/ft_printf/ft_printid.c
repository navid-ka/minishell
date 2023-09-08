/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:24:21 by jareste-          #+#    #+#             */
/*   Updated: 2023/09/08 22:48:42 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_print_decimal(int fd, int n)
{
	char	*num;
	int		c_printed;

	c_printed = 0;
	num = ft_itoa(n);
	if (!num)
		return (-1);
	c_printed = ft_print_string(fd, num);
	if (c_printed == -1)
	{
		free(num);
		return (-1);
	}
	free(num);
	return (c_printed);
}
