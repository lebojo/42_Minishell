/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:01:23 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/21 01:02:32 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	rev_quote(enum e_quote *q, char c)
{
	if (*q == none && c == '"')
		*q = double_q;
	else if (*q == double_q && c == '"')
		*q = none;
	if (*q == none && c == '\'')
		*q = simple;
	else if (*q == simple && c == '\'')
		*q = none;
}