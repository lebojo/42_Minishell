/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:49 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/08 18:07:45 by jchapell         ###   ########.fr       */
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
	cmds->line = NULL;
	while (++i <= cmds->nb_cmd)
	{
		cmds->cmd[i].name = NULL;
		cmds->cmd[i].arg = NULL;
		cmds->cmd[i].which_pipe = 0;
	}
	return (0);
}

char	*parse_line(char *str, int wh_pipe)
{
	char	*res;
	char	**sp;

	sp = ft_split(str, '|');
	if (!sp[1])
	{
		free_tab(sp);
		return (str);
	}
	res = ft_strdup(sp[wh_pipe]);
	free_tab(sp);
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
	res.nb_pipe = src.nb_pipe;
	res.sep = sep_parse_inpipe(src.sep, which_pipe);
	while (i < src.nb_cmd)
	{
		if (src.cmd[i].which_pipe == which_pipe)
			res.nb_cmd++;
		i++;
	}
	create_cmds(&res);
	res.line = parse_line(src.line, which_pipe);
	i = 0;
	while (i < src.nb_cmd)
	{
		if (src.cmd[i].which_pipe == which_pipe)
			res.cmd[j++] = src.cmd[i];
		i++;
	}
	return (res);
}

t_cmd	parse_cmd(char *str)
{
	t_cmd	rs;
	char	**sp;
	int		i;

	i = 0;
	sp = ft_split(str, ' ');
	rs = create_cmd(sp[i++], NULL, 0, 0);
	if (sp[i])
	{
		rs.arg = ft_strdup(sp[i++]);
		while (sp[i])
			add_str_space(&rs.arg, sp[i++]);
	}
	free_tab(sp);
	return (rs);
}
