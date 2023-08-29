/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rdr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:02:52 by abourgue          #+#    #+#             */
/*   Updated: 2023/08/29 17:33:17 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	cmd_rdr_r(t_cmds *cmds, t_exec *exec, char ***envp, int x)
{
	exec->pid[x] = fork(); 
	if (exec->pid[x] == 0)
	{
		exec->fd_out = open(cmds->cmd[x].name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (exec->fd_out == -1)
			return ;
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
			return ;
		close(exec->tube[x][0]);
		printf("%s", exec->res);
		close(exec->fd_out);
		push_to_fd(exec, exec->res, x);
		free(exec->res);
		exit (1);
	}
}

void	cmd_rdr_l(t_cmds *cmds, t_exec *exec, char ***envp, int x)
{
	exec->pid[x] = fork();
	if (exec->pid[x] == 0)
	{
		exec->fd_in = open(cmds->cmd[x + 1].name, O_RDONLY);
		if (exec->fd_in == -1)
			return ;
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
			return ;
		exec_rdr(&cmds->cmd[x], exec, envp, x + 1);
		close(exec->fd_in);
	}
}


void	exec_rdr(t_cmd *cmd, t_exec *exec, char ***envp, int x)
{
	if (x == exec->s_tube)
    {
		if (dup2(1, STDOUT_FILENO) == -1)
        	return;
		select_cmd_type(cmd, exec, envp);
        return;
    }
	if (dup2(exec->tube[x][1], STDOUT_FILENO) == -1)
		return;
	close(exec->tube[x][0]);
	select_cmd_type(cmd, exec, envp);
	return ;
}