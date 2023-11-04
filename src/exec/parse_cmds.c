/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:49 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/04 17:46:37 by jchapell         ###   ########.fr       */
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
	cnt = i;
	while (src[i] != None && src[i++] != Pipe)
		tmp++;
	res = malloc(sizeof(enum e_sep) * (tmp + 1));
	tmp = 0;
	while (src[cnt] != None && src[cnt] != Pipe)
		res[tmp++] = src[cnt++];
	res[tmp] = None;
	return (res);
}

int	create_cmds(t_cmds *cmds)
{
	int	i;

	i = -1;
	cmds->cmd = ft_calloc(cmds->nb_cmd + 1, sizeof(t_cmd));
	while (++i <= cmds->nb_cmd)
	{
		cmds->cmd[i].name = NULL;
		cmds->cmd[i].arg = NULL;
		cmds->cmd[i].which_pipe = 0;
	}
	return (0);
}

t_cmds	parse_cmds(t_cmds src, int which_pipe)
{
	t_cmds	res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res.nb_cmd = 0;
	res.nb_pipe = src.nb_pipe;
	res.sep = sep_parse_inpipe(src.sep, which_pipe);
	while (i < src.nb_cmd)
	{
		if (src.cmd[i].which_pipe == which_pipe)
			res.nb_cmd++;
		i++;
	}
	create_cmds(&res);
	i = 0;
	while (i < src.nb_cmd)
	{
		if (src.cmd[i].which_pipe == which_pipe)
			res.cmd[j++] = src.cmd[i];
		i++;
	}
	return (res);
}
