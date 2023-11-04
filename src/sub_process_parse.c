/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_process_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:52:38 by jchapell          #+#    #+#             */
/*   Updated: 2023/11/04 16:52:44 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int	sub_process_parse_true(t_cmds *cmds, t_inc *inc, char **split, char ***envp)
{
	cmds->cmd[++inc->j].which_pipe = inc->k;
	if (!split[++inc->i])
		return (2);
	if (char_in_str(split[inc->i][0], "|<>"))
		inc->i++;
	if (split[inc->i])
		cmds->cmd[inc->j].name = expand(split[inc->i], envp);
	else
		return (2);
	cmds->cmd[inc->j].arg = NULL;
	if (!split[++inc->i])
		return (2);
	if (char_in_str(split[inc->i][0], "|<>"))
		return (1);
	quote_parse(cmds, split, inc, envp);
	return (0);
}

int	sub_process_parse_fls(t_cmds *cmds, t_inc *inc, char **split)
{
	if (cmds->cmd[inc->j].arg && cmds->cmd[inc->j].arg[0])
		cmds->cmd[inc->j].arg = add_str(
				add_str(cmds->cmd[inc->j].arg, " ", 1),
				split[inc->i++], 1);
	else
		cmds->cmd[inc->j].arg = split[inc->i++];
	cmds->cmd[inc->j].which_pipe = inc->k;
	return (0);
}
