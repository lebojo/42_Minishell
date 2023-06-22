/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:16:53 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/22 02:07:18 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	first(t_cmd *cmd, t_exec *exec, char **env, int x);
void	second(t_cmd *cmd, t_exec *exec, char **env, int x);

void	cmd_pipe(t_cmds *cmds, t_exec *exec, char **envp, int x)
{
	exec->pid[x] = fork();
	if (exec->pid[x] == 0)
		first(&cmds->cmd[x], exec, envp, x);
	if (x == cmds->nb_cmd - 1)
		return ;
	exec->pid[x + 1] = fork();
	if (exec->pid[x + 1] == 0)
			second(&cmds->cmd[x + 1], exec, envp, x + 1);
	return ;
}

void	first(t_cmd *cmd, t_exec *exec, char **env, int x)
{
	if (x > 0)
	{
		if (dup2(exec->tube[x - 1][0], STDIN_FILENO) == -1)
			return ;		
		close(exec->tube[x - 1][1]);
	}
	if (x == exec->s_tube)
	{
		if (dup2(1, STDOUT_FILENO) == -1)
			return ;
		close_pipe(exec, x - 1);
		exec_cmd(cmd, exec, env);
		printf("\n");
		return ;
	}
	if (dup2(exec->tube[x][1], STDOUT_FILENO) == -1)
		return ;		
	close_pipe(exec, x - 1);
	exec_cmd(cmd, exec, env);
}

void second(t_cmd *cmd, t_exec *exec, char **env, int x)
{
    if (dup2(exec->tube[x - 1][0], STDIN_FILENO) == -1)
        return;
    close(exec->tube[x - 1][1]);
    if (x == exec->s_tube)
    {
        if (dup2(1, STDOUT_FILENO) == -1)
            return;
		close_pipe(exec, x - 1);
		exec_cmd(cmd, exec, env);
		printf("\n");
        return;
    }
	if (dup2(exec->tube[x][1], STDOUT_FILENO) == -1)
		return;
	close_pipe(exec, x - 1);
	exec_cmd(cmd, exec, env);
}