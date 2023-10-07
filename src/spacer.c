/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:09:19 by lebojo            #+#    #+#             */
/*   Updated: 2023/10/07 01:57:29 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

char	*re_malloc(char *str, int size)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(sizeof(char) * size);
	res[size] = '\0';
	while (str[++i])
		res[i] = str[i];
	free(str);
	return (res);
}

char	*format_input(char *str)
{
	t_inc	inc;
	char	*res;
	
	inc.i = 0;
	inc.j = 0;
	res = malloc(sizeof(char) * ft_strlen(str));
	res[ft_strlen(str)] = '\0';
	while (str[inc.i])
	{
		if (char_in_str(str[inc.i], "|<>"))
		{
			res = re_malloc(res, ft_strlen(res) + 1);
			res[inc.j++] = ' ';
			res[inc.j++] = str[inc.i++];
			res[inc.j++] = ' ';
		}
		else
			res[inc.j++] = str[inc.i++];
	}
	return (res);
}