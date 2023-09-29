/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:04:43 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/09/29 17:47:16 by fcosta-f         ###   ########.fr       */
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

//int count_expand(t_mch *sh, char *lexer, int *len);
//void expansor()....
