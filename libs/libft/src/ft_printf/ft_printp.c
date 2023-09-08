/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:45:20 by jareste-          #+#    #+#             */
/*   Updated: 2023/09/08 22:49:22 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_print_ptr(int fd, void *ptr)
{
	int	c_printed;
	int	aux;

	if (ft_print_string(fd, "0x") == -1)
		return (-1);
	c_printed = 2;
	aux = ft_print_hex(fd, (unsigned long)ptr, 'x', 0);
	if (aux == -1)
		return (-1);
	c_printed += aux;
	return (c_printed);
}
