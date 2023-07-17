/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:35:14 by arthur            #+#    #+#             */
/*   Updated: 2023/06/26 15:34:53 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	exec_multiple(t_cmds *cmds, t_exec *exec, char **envp);

int	is_builtins(t_cmd *cmd, char **envp)
{
	if (ft_strcmp("echo", cmd->name))
		ft_echo(cmd);
	// else if (ft_strcmp("cd",cmd->name) == 1)
	// 	ft_cd(cmd, env);
	// else if (ft_strcmp("pwd",cmd->name) == 1)
	// 	ft_pwd(cmd, env);
	// else if (ft_strcmp("export",cmd->name) == 1)
	// 	ft_export(cmd, env);
	// else if (ft_strcmp("unset",cmd->name) == 1)
	// 	ft_unset(cmd, env);
	// else if (ft_strcmp("env",cmd->name) == 1)
	// 	ft_env(cmd, env);
	// else if (ft_strcmp("exit",cmd->name) == 1)
	// 	ft_exit(cmd, env);
	// else
	// 	return (0);
	return (0);
}

void	select_cmd(t_cmd *cmd, t_exec *exec, char **envp)
{
	if (is_builtins(cmd, envp))
		return ;
	else
		exec_cmd(cmd, exec, envp);
	return ;	
}

void	 exec_line(t_cmds *cmds, char **envp)
{
	t_exec	exec;
	
	if (cmds->nb_cmd <= 0)
		return ;
	else if (cmds->nb_cmd == 1)
	{
		exec.pid = malloc(sizeof(pid_t) * 1);
		exec.pid[0] = fork();
		if (exec.pid[0] == 0)
			select_cmd(&cmds->cmd[0], &exec, envp);
		waitpid(exec.pid[0], NULL, 0);
		free(exec.pid);
		return ;
	}
	exec_multiple(cmds, &exec, envp);
}

void exec_multiple(t_cmds *cmds, t_exec *exec, char **envp)
{
    int i;
    int x;

    x = -1;
    exec->tube = malloc(sizeof(int *) * (cmds->nb_cmd - 1));
    exec->s_tube = cmds->nb_cmd - 1;
    exec->pid = malloc(sizeof(pid_t) * cmds->nb_cmd);
    while (++x < cmds->nb_cmd - 1)
    {
        exec->tube[x] = malloc(sizeof(int) * 2);
        if (pipe(exec->tube[x]) == -1)
            return;
    }
    i = -1;
    while (++i < cmds->nb_cmd)
    {
        if (cmds->sep[i] == Pipe)
			cmd_pipe(&cmds->cmd[i], exec, envp, i);
		if (cmds->sep[i] == S_left)
		{
			cmd_rdr_l(cmds, exec, envp, i);
			i += 1;
		}
		if (cmds->sep[i] == S_right)
		{
			cmd_rdr_r(cmds, exec, envp, i);
			i += 1;
		}
		if (cmds->sep[i] == D_right)
			cmd_rdr_d_r(cmds, exec, envp, ++i);
		if (cmds->sep[i] == D_left)
			cmd_rdr_d_l(cmds, exec, envp, ++i);
	
		close_pipe(exec, i);
        waitpid(exec->pid[i], NULL, 0);
    }
    free(exec->pid);
    free_tube(exec);
}
