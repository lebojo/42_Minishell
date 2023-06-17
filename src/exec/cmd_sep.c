/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:16:53 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/17 04:28:09 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	first(t_cmd *cmd, t_exec *exec, char **env, int x);
void	second(t_cmd *cmd, t_exec *exec, char **env, int x);

void	cmd_pipe(t_cmds *cmds, t_exec *exec, char **envp, int x)
{
	exec->pid1 = fork();
	if (x * 2 == cmds->nb_cmd)
	{
		if (exec->pid1 == 0)
			first(&cmds->cmd[x], exec, envp, -42);
		printf("FIN\n");
		close_pipe(exec);
		waitpid(exec->pid1, NULL, 0);
		return ;
	}
	if (exec->pid1 == 0)
		first(&cmds->cmd[x], exec, envp, x);
	exec->pid2 = fork();
	if (exec->pid2 == 0)
	{
		if (cmds->nb_pipe > 1 && cmds->cmd[x + 2].name)
			second(&cmds->cmd[x + 1], exec, envp, x + 1);
		else
			second(&cmds->cmd[x + 1], exec, envp, -42);
	}
	close_pipe(exec);
	waitpid(exec->pid1, NULL, 0);
	waitpid(exec->pid2, NULL, 0);
}

void	first(t_cmd *cmd, t_exec *exec, char **env, int x)
{
	if (x > 0)
	{
		if (dup2(exec->tube2[0], STDIN_FILENO) == -1)
			return ;		
		close(exec->tube2[1]);
	}
	if (x == -42)
	{
		dup2(2, STDOUT_FILENO);
		exec_cmd(cmd, exec, env);
		return ;
	}
	if (dup2(exec->tube1[1], STDOUT_FILENO) == -1)
		return ;		
	close(exec->tube1[0]);
	exec_cmd(cmd, exec, env);
}

void	second(t_cmd *cmd, t_exec *exec, char **env, int x)
{
	if (dup2(exec->tube1[0], STDIN_FILENO) == -1)
		return ;		
	close(exec->tube1[1]);
	if (x == -42)
	{
		dup2(2, STDOUT_FILENO);
		printf("name: %s | arg: %s\n", cmd->name, cmd->arg);	
		exec_cmd(cmd, exec, env);
		printf("END\n");
		return ;
	}
	if (dup2(exec->tube2[1] , STDOUT_FILENO) == -1)
		return ;		
	close(exec->tube2[0]);
	exec_cmd(cmd, exec, env);
}