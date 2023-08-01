/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:35:14 by arthur            #+#    #+#             */
/*   Updated: 2023/08/01 15:56:26 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	exec_multiple(t_cmds *cmds, t_exec *exec, char ***envp);
void	setup_exec_var(t_cmds *cmds, t_exec *exec);
void	select_cmd_type(t_cmd *cmd, t_exec *exec, char ***envp);

int	is_builtins(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp("echo", cmd->name))
		ft_echo(cmd, envp);
	else if (ft_strcmp("cd", cmd->name))
		ft_cd(cmd->arg);
	else if (ft_strcmp("pwd",cmd->name))
		ft_pwd();
	else if (ft_strcmp("export",cmd->name))
		ft_export(cmd, envp);
	else if (ft_strcmp("unset",cmd->name))
		ft_unset(cmd, envp);
	else if (ft_strcmp("env",cmd->name))
		ft_env(*envp);
	else if (ft_strcmp("exit", cmd->name))
		ft_exit();
	else
		return (0);
	return (1);
}

void	 exec_line(t_cmds *cmds, char ***envp)
{
	t_exec	exec;
	
	if (cmds->nb_cmd <= 0)
		return ;
	else if (cmds->nb_cmd == 1)
	{
		exec.pid = malloc(sizeof(pid_t) * 1);
		exec.pid[0] = fork();
		if (exec.pid[0] == 0)
			select_cmd_type(&cmds->cmd[0], &exec, envp);
		waitpid(exec.pid[0], NULL, 0);
		free(exec.pid);
		return ;
	}
	exec_multiple(cmds, &exec, envp);
}

void	select_cmd_type(t_cmd *cmd, t_exec *exec, char ***envp)
{
	if (is_builtins(cmd, envp))
		return ;
	else
		exec_cmd(cmd, exec, *envp);
	return ;	
}

void	exec_multiple(t_cmds *cmds, t_exec *exec, char ***envp)
{
    int i;

    i = -1;
	setup_exec_var(cmds, exec);
    while (++i < cmds->nb_cmd)
    {
        if (cmds->sep[i] == Pipe)
			cmd_pipe(&cmds->cmd[i], exec, envp, i); // execute uniquement la commande i puis passe a la ligne 99
		else if (cmds->sep[i] == S_left)
			cmd_rdr_l(cmds, exec, envp, i++); // i++ car execution de la redirection depuis i puis execution de la commande i + 1
		else if (cmds->sep[i] == S_right)
			cmd_rdr_r(cmds, exec, envp, i++);
		else if (cmds->sep[i] == D_right)
			cmd_rdr_d_r(cmds, exec, envp, i++);
		else if (cmds->sep[i] == D_left)
			cmd_rdr_d_l(cmds, exec, envp, ++i);
		close_pipe(exec, i);
        waitpid(exec->pid[i], NULL, 0);
    }
    free(exec->pid);
    free_tube(exec);
}

void	setup_exec_var(t_cmds *cmds, t_exec *exec)
{
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
}