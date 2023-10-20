/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:01:23 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/21 01:19:21 by jchapell         ###   ########.fr       */
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

char	*ask_quote(enum e_quote q, char *str)
{
	char	*rp;
	char	*res;

	res = ft_strdup(str);
	while (1)
	{
		rp = readline("quote>");
		if (rp == NULL)
			return (NULL);
		res = add_str(res, rp, 1);
		if (rp[0] == '"' && q == double_q)
			return (res);
		if (rp[0] == '\'' && q == simple)
			return (res);
	}
	return (NULL);
}