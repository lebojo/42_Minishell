/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:09:19 by lebojo            #+#    #+#             */
/*   Updated: 2023/10/24 01:37:14 by jchapell         ###   ########.fr       */
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

int	only_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!char_in_str(str[i], " \t"))
			return (0);
	return (1);
}

char	*format_input_process(t_inc *inc, char *str, char *res, int q)
{
	if (char_in_str(str[inc->i], "|<>") && (str[inc->i - 1] != ' '
			|| str[inc->i + 1] != ' ') && q > 0)
	{
		if (!char_in_str(str[inc->i - 1], "|<> ") && inc->i > 0)
		{
			res = re_malloc(res, ft_strlen(res) + 1);
			res[inc->j++] = ' ';
		}
		res[inc->j++] = str[inc->i++];
		if (!char_in_str(str[inc->i], "|<> "))
		{
			res = re_malloc(res, ft_strlen(res) + 1);
			res[inc->j++] = ' ';
		}
	}
	else
		res[inc->j++] = str[inc->i++];
	return (res);
}

char	*unspacer(char *str)
{
	t_inc	i;
	char	*res;

	i.i = -1;
	i.j = -1;
	i.k = 0;
	if (!str)
		return (NULL);
	while (str[i.k] && char_in_str(str[i.k], " \t"))
		i.k++;
	i.n = ft_strlen(str);
	while (i.n > 0 && char_in_str(str[i.n], " \t"))
		--i.n;
	res = malloc(sizeof(char) * (i.n - i.k + 1));
	i.i = i.k - 1;
	while (i.i <= i.n)
		res[++i.j] = str[++i.i];
	res[i.j] = '\0';
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
	res = malloc(sizeof(char) * ft_strlen(str));
	res[ft_strlen(str)] = '\0';
	while (str[inc.i])
	{
		rev_quote(&q, str[inc.i]);
		res = format_input_process(&inc, str, res, q);
	}
	free(str);
	res[inc.j] = '\0';
	if (q != none)
		return (ask_quote(q, res));
	return (res);
}
