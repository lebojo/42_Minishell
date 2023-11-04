/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 20:01:26 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/04 19:05:15 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_str(char *s1, char *s2, int f)
{
	char	*res;
	int		i;
	int		ii;

	res = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	i = -1;
	ii = 0;
	while (s1 && s1[++i])
		res[i] = s1[i];
	while (s2[ii])
		res[i++] = s2[ii++];
	res[i] = '\0';
	if (f == 1 && s1)
		free(s1);
	else if (f == 2 && s2)
		free(s2);
	else if (f == 3 && s1 && s2)
	{
		free(s1);
		free(s2);
	}
	return (res);
}

void	add_str_space(char **src, char *add)
{
	*src = add_str(*src, " ", 1);
	*src = add_str(*src, add, 1);
}
