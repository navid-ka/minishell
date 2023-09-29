/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:04:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 14:12:32 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//brace expansor https://www.gnu.org/software/bash/manual/html_node/Brace-Expansion.html
//$a{b,c,d}e
//expected abe ace ade

//arithmetic expansor https://www.gnu.org/software/bash/manual/html_node/Arithmetic-Expansion.html
//b=2*3
//echo $((b))
//expected 6

//tilde expansor https://www.gnu.org/software/bash/manual/html_node/Tilde-Expansion.html
// esta no hace falta
//sh-3.2$ ~+
//sh: /Users/nkeyani-/test: is a directory

//int count_expand(t_mch *sh, char *token, int *len);
//void expansor()....
