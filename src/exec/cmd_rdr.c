/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rdr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:02:52 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/22 02:05:53 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	cmd_rdr_l(t_cmds *cmds, t_exec *exec, char **envp, int x)
{
	exec->pid[x] = fork();
	if (exec->pid[x] == 0)
	{
		exec->fd_in = open(cmds->cmd[x].name, O_RDONLY);
		if (exec->fd_in == -1)
			return ;
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
			return ;
		exec_rdr(&cmds->cmd[x + 1], exec, envp, x + 1);
		return ;
	}
}


void	exec_rdr(t_cmd *cmd, t_exec *exec, char **env, int x)
{
	if (x == exec->s_tube)
    {
		if (dup2(1, STDOUT_FILENO) == -1)
        	return;
		close_pipe(exec, x - 1);
		exec_cmd(cmd, exec, env);
		close(exec->fd_in);
        return;
    }
	if (dup2(exec->tube[x][1], STDOUT_FILENO) == -1)
		return;
	close_pipe(exec, x - 1);
	exec_cmd(cmd, exec, env);
	return ;
}