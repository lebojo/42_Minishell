/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:09:19 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/04 15:40:12 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

char	*re_malloc(char *str, int size)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(size * sizeof(char));
	if (!res)
		return (NULL);
	while (++i < size - 2)
		res[i] = 'c';
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i + 1] = '\0';
	free(str);
	return (res);
}

int	only_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!char_in_str(str[i], " \t"))
			return (0);
	return (1);
}

int	can_space(int i, char *str, int q)
{
	if (i == 0)
	{
		if (char_in_str(str[i], "|<>")
			&& str[i + 1] != ' ' && q == none)
			return (1);
	}
	else if (char_in_str(str[i], "|<>") && (str[i - 1] != ' '
			|| str[i + 1] != ' ') && q == none)
		return (1);
	return (0);
}

char	*format_input_process(t_inc *inc, char *str, char *res, int q)
{
	if (can_space(inc->i, str, q))
	{
		if (inc->i > 0 && !char_in_str(str[inc->i - 1], "|<> "))
		{
			res = re_malloc(res, ft_strlen(res) + 2);
			res[inc->j++] = ' ';
		}
		res[inc->j++] = str[inc->i++];
		if (!char_in_str(str[inc->i], "|<> "))
		{
			res = re_malloc(res, ft_strlen(res) + 2);
			res[inc->j++] = ' ';
		}
	}
	else
		res[inc->j++] = str[inc->i++];
	return (res);
}

char	*format_input(char *str)
{
	t_inc			inc;
	char			*res;
	enum e_quote	q;

	inc.i = 0;
	inc.j = 0;
	q = none;
	if (ft_strlen(str) == 1)
		return (str);
	res = str;
	str = ft_strtrim(str, " \t");
	free(res);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	res[ft_strlen(str)] = '\0';
	while (str[inc.i])
	{
		rev_quote(&q, str[inc.i]);
		res = format_input_process(&inc, str, res, q);
	}
	free(str);
	if (q != none)
		return (ask_quote(q, res));
	return (res);
}
