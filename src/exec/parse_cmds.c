/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:49 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/02 02:35:42 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

enum e_sep	*sep_parse_inpipe(enum e_sep *src, int which_pipe)
{
	int			i;
	int			cnt;
	int			tmp;
	enum e_sep	*res;

	i = 0;
	cnt = 0;
	tmp = 0;
	res = NULL;
	while (which_pipe > 0 && src[i] != None)
	{
		if (src[i++] == Pipe)
			cnt++;
		if (cnt == which_pipe)
			break ;
	}
	while (src[i] != None && src[i++] != Pipe)
		tmp++;
	res = malloc(sizeof(enum e_sep) * (tmp + 2));
	i -= tmp;
	tmp = 0;
	while (src[i] != None && src[i] != Pipe)
		res[tmp++] = src[i++];
	res[tmp] = None;
	return (res);
}

t_cmds	parse_cmds(t_cmds src, int which_pipe)
{
	t_cmds	res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res.nb_cmd = 0;
	res.nb_pipe = 0;
	res.sep = sep_parse_inpipe(src.sep, which_pipe);
	while (i < src.nb_cmd)
	{
		if (src.cmd[i].which_pipe == which_pipe)
			res.nb_cmd++;
		i++;
	}
	res.cmd = malloc(sizeof(t_cmd) * res.nb_cmd);
	i = 0;
	while (i < src.nb_cmd)
	{
		if (src.cmd[i].which_pipe == which_pipe)
			res.cmd[j++] = src.cmd[i];
		i++;
	}
	return (res);
}
