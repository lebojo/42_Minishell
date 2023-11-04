/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:42:32 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/04 19:36:49 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	write_in_file(t_cmds *cmds, int x, char ***env)
{
	int		id[2];

	id[0] = 0;
	if (cmds->cmd[x + 1].name != NULL)
		id[1] = open(cmds->cmd[x + 1].name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		id[1] = open(cmds->cmd[x].name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return ;
	}
	if (id[1] == -1)
		return ;
	if (cmds->sep[x + 1] != Pipe && cmds->sep[x + 1] == S_right)
		return ;
	if (exec_inpipe_builtins(STDOUT_FILENO, id[1], &cmds->cmd[0], env))
		return ;
	else
		exec_in_fork(STDOUT_FILENO, id, &cmds->cmd[0], *env);
}

void	append_to_file(t_cmds *c, int x, char ***env)
{
	int		id[2];

	id[0] = 0;
	if (c->cmd[x + 1].name != NULL)
		id[1] = open(c->cmd[x + 1].name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		id[1] = open(c->cmd[x].name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return ;
	}
	if (id[1] == -1)
		return ;
	if (c->sep[x + 1] != Pipe && c->sep[x + 1] == D_right)
		return ;
	if (exec_inpipe_builtins(STDOUT_FILENO, id[1], &c->cmd[0], env))
		return ;
	else
		exec_in_fork(STDOUT_FILENO, id, &c->cmd[0], *env);
}
