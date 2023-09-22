/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:29:02 by lebojo            #+#    #+#             */
/*   Updated: 2023/09/22 17:44:59 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

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

void init_pipe(t_pipe *pipes, t_cmds *cmds)
{
	pipes->pid = ft_calloc(cmds->nb_cmd, sizeof(int));
	pipes->fd = open_pipes(cmds->nb_pipe);
	if (!pipes->pid || !pipes->fd)
		pipes = NULL;
}

void	 exec_line(t_cmds *cmds, char ***envp)
{
	t_pipe	pipes;
	int		i;

	init_pipe(&pipes, cmds);
	if (cmds->nb_cmd <= 0)
		return ;
	if (cmds->sep[0] != Pipe)
	{
		exec_inpipe(cmds, &pipes, envp);
		return ;
	}
	// Je pense qu'il faut créer un parse de cmds pour chaque interpipe
	//execute ça que s'il y a au moins 1 pipe:
	i = -1;
	first_pipe(cmds->cmd[0], &pipes, envp);
	while (++i < cmds->nb_pipe - 1) // le -1 c'est parce que s'il y a 1 pipe, il ne doit pas rentrer dedans, et t'as capté la logique.
	{
		mid_pipe(cmds->cmd[i + 1], &pipes, i, envp);
		close_pipe(pipes.fd[i]);
	}
	last_pipe(cmds->cmd[i + 1], &pipes, i, envp); // le +1 c'est parce qu'il y a une dernière commande après le pipes

	close_pipe(pipes.fd[i]);

	i = -1;
	while (++i <= cmds->nb_pipe)
		waitpid(pipes.pid[i], NULL, 0);
}

void	exec_inpipe(t_cmds *cmds, t_pipe *pipe, char ***envp)
{
	if (cmds->nb_cmd > 1)
		exec_sep(cmds, envp);
	else
	{
		if (!is_builtins(&cmds->cmd[0], envp))
		{
			pipe->pid[0] = fork();
			if (pipe->pid[0] < 0)
				exit(1);
			if (pipe->pid[0] == 0)
			{
				exec_cmd(&cmds->cmd[0], *envp);
				exit(0);
			}
			waitpid(pipe->pid[0], NULL, 0);
		}
	}
}

void	exec_sep(t_cmds *cmds, char ***envp)
{
	int i;

	i = 0;
	while (cmds->sep[i] != None && cmds->sep[i] != Pipe)
	{
		if (cmds->sep[i] == S_right)
			write_in_file(cmds->cmd[i + 1].name, &cmds->cmd[0], *envp);
		else if (cmds->sep[i] == D_right)
			append_to_file(cmds->cmd[i + 1].name, cmds->cmd[i].name);
		else if (cmds->sep[i] == D_left)
			heredoc(cmds->cmd[i].name);
		i++;
	}
}