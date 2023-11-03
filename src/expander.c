/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 04:19:20 by jchapell          #+#    #+#             */
/*   Updated: 2023/11/02 18:36:23 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

t_cmd	create_cmd(char *name, char *arg, int which_pipe, int fred)
{
	t_cmd	res;

	if (name)
		res.name = ft_strdup(name);
	else
		res.name = NULL;
	if (arg)
		res.arg = ft_strdup(arg);
	else
		res.arg = NULL;
	res.which_pipe = which_pipe;
	if (fred == 1)
		free(name);
	if (fred == 2)
		free(arg);
	if (fred == 3)
	{
		free(name);
		free(arg);
	}
	return (res);
}

int	is_inquote(char *str, int i)
{
	int	res;
	int	start;

	res = -1;
	start = i;
	while (i >= 0 && res == -1)
		if (str[i--] == '\'')
			res++;
	i = start;
	while (str[++i] && res == 0)
		if (str[i] == '\'')
			res++;
	return (res);
}

char	*char_to_str(char c)
{
	char	*res;

	res = malloc(sizeof(char) * 2);
	res[0] = c;
	res[1] = '\0';
	return (res);
}

char	*process_expand(char ***envp, char *src, char *res, t_inc *incr)
{
	char	*tmp;
	char	*var;

	if (src[incr->i] == '$' && is_inquote(src, incr->i) != 1)
	{
		tmp = ft_calloc(ft_strlen(src), sizeof(char));
		while (src[++incr->i] && !char_in_str(src[incr->i], " \t\"$"))
			tmp[incr->k++] = src[incr->i];
		var = hm_get_value((*envp), tmp);
		if (var)
		{
			res = add_str(res, var, 3);
			incr->i--;
		}
		free(tmp);
		incr->k = 0;
	}
	else
		res = add_str(res, char_to_str(src[incr->i]), 3);
	return (res);
}

char	*expand(char *src, char ***envp)
{
	char			*res;
	t_inc			incr;
	enum e_quote	quote;

	incr.i = -1;
	incr.j = 0;
	incr.k = 0;
	res = ft_calloc(ft_strlen(src), sizeof(char));
	quote = none;
	if (!res || !src || quote < 0)
		return (NULL);
	while (src && src[++incr.i])
	{
		if (quote == none)
			rev_quote(&quote, src[incr.i]);
		if ((quote == double_q && src[incr.i] == '"')
			|| (quote == simple && src[incr.i] == '\''))
			continue ;
		if (quote != none)
			rev_quote(&quote, src[incr.i]);
		res = process_expand(envp, src, res, &incr);
		if (!src[incr.i])
			break ;
	}
	return (res);
}
