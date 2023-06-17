/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:35:14 by arthur            #+#    #+#             */
/*   Updated: 2023/06/17 04:15:46 by abourgue         ###   ########.fr       */
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

void	exec_line(t_cmds *cmds, char **envp)
{
	t_exec	exec;
	
	if (cmds->nb_cmd <= 0)
		return ;
	else if (cmds->nb_cmd == 1)
	{
		exec.pid1 = fork();
		if (exec.pid1 == 0)
			select_cmd(&cmds->cmd[0], &exec, envp);
		waitpid(exec.pid1, NULL, 0);
		return ;
	}
	exec_multiple(cmds, &exec, envp);
}

void	exec_multiple(t_cmds *cmds, t_exec *exec, char **envp)
{
	int i;
	int	x;
	
	i = 0;
	x = 0;
	if (pipe(exec->tube1))
		return ;
	if (pipe(exec->tube2))
		return ;
	printf("tot : %d\n", cmds->nb_cmd);
	printf("pipe : %d\n", cmds->nb_pipe);
	x = 0;
	while (i < cmds->nb_cmd)
	{
		if (cmds->sep[x] == Pipe)
		{
			printf("x: %d | i: %d\n", x, i);
			cmd_pipe(cmds, exec, envp, x);
		}
		// else if (cmds->sep[x] == S_left)
		// 	cmd_redir_l(cmds, exec, envp, x);
		// else if (cmds->sep[x] == D_left)
		// 	cmd_redir_l(cmds, exec, envp, x);
		// else if (cmds->sep[x] == S_right)
		// 	cmd_redir_r(cmds, exec, envp, x);
		// else if (cmds->sep[x] == D_right)
		// 	cmd_redir_r(cmds, exec, envp, x);
		x += 1;
		i += 2;
	}
}