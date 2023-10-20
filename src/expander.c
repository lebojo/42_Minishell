/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 04:19:20 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/21 01:43:52 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

t_cmd	create_cmd(char *name, char *arg, int which_pipe)
{
	t_cmd	res;

	res.name = ft_strdup(name);
	if (name)
		res.name = ft_strdup(name);
	else
		res.name = NULL;
	if (arg)
		res.arg = ft_strdup(arg);
	else
		res.arg = NULL;
	res.which_pipe = which_pipe;
	return (res);
}

int	is_inquote(char *str, int i)
{
	int res;
	int	start;

	res = -1;
	start = i;
	while (i >= 0)
	{
		if (str[i--] == '\'')
		{
			res++;
			break ;
		}
	}
	i = start;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			res++;
			break;
		}
	}
	return (res);
}

void	process_expand(char ***envp, char *src, char **res, t_inc *incr)
{
	char	*tmp;
	char	*var;

	if (src[incr->i] == '$' && is_inquote(src, incr->i) != 1)
	{
		tmp = ft_calloc(ft_strlen(src), sizeof(char));
		while (src[++incr->i] && !char_in_str(src[incr->i], " \t\"'\\$")) // <-- le problème viens clairement de là
			tmp[incr->k++] = src[incr->i];
		var = hm_get_value(*envp, tmp);
		if (var)
		{
			(*res) = add_str((*res), var, 1);
			incr->j += ft_strlen(var) + 1;
			free(var);
		}
		free(tmp);
		incr->k = 0;
	}
	else
		(*res)[incr->j++] = src[incr->i];
}

char	*expand(char *src, char ***envp)
{
	char			*res;
	t_inc			incr;
	enum e_quote	quote;

	incr.i = -1;
	incr.j = 0;
	incr.k = 0;
	res = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	quote = none;
	if (!res)
		return (NULL);
	if (quote < 0)
		return (NULL);
	while (src[++incr.i])
	{
		rev_quote(&quote, src[incr.i]);
		if ((quote == double_q && src[incr.i] == '"')
			|| (quote == simple && src[incr.i] == '\''))
			continue ;
		process_expand(envp, src, &res, &incr);
	}
	res[incr.j] = '\0';
	return (res);
}
