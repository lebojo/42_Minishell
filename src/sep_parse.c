/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 04:06:46 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/21 01:24:27 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	sep_counter(t_cmds *cmds, char *input)
{
	int	i;
	enum e_quote q;

	i = -1;
	cmds->nb_cmd = 1;
	cmds->nb_pipe = 0;
	q = none;
	while (input[++i])
	{
		rev_quote(&q, input[i]);
		if (q != none)
			continue ;
		if (input[i] == '|' && input[i - 1] != '|')
			cmds->nb_pipe += 1;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			cmds->nb_cmd += 1;
		if ((input[i] == '<' && input[i - 1] == '<')
			|| (input[i] == '>' && input[i - 1] == '>'))
			cmds->nb_cmd -= 1;
	}
}

void	process_sep_parse(t_cmds *cmds, char *input, t_inc *inc)
{
	if (input[inc->i] == '|')
		cmds->sep[inc->j++] = Pipe;
	if (input[inc->i] == '<')
	{
		if (input[inc->i + 1] == '<')
		{
			cmds->sep[inc->j++] = D_left;
			inc->i++;
		}
		else
			cmds->sep[inc->j++] = S_left;
		return ;
	}
	if (input[inc->i] == '>')
	{
		if (input[inc->i + 1] == '>')
		{
			cmds->sep[inc->j++] = D_right;
			inc->i++;
		}
		else
			cmds->sep[inc->j++] = S_right;
		return ;
	}
}

void	sep_parse(t_cmds *cmds, char *input)
{
	t_inc	inc;

	inc.i = -1;
	inc.j = 0;
	sep_counter(cmds, input);
	cmds->sep = ft_calloc(cmds->nb_cmd + 1, sizeof(enum e_sep));
	cmds->sep[0] = None;
	if (cmds->nb_cmd <= 1 && cmds->nb_pipe < 1)
		return ;
	while (input[++inc.i + 1])
		process_sep_parse(cmds, input, &inc);
	cmds->sep[inc.j] = None;
}
