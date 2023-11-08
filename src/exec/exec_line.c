/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:29:02 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/08 18:41:45 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	one_cmd(t_cmds *cmds, t_pipe *pipes, char ***envp)
{
	if (cmds->nb_pipe > 0)
		return (0);
	if (exec_heredoc(cmds, envp, 0))
		return (1);
	exec_inpipe(cmds, pipes, envp);
	return (1);
}

void	exec_line(t_cmds *cmds, char ***envp)
{
	t_pipe	pipes;
	int		i;
	int		exit_status;

	init_pipe(&pipes, cmds);
	if (cmds->nb_cmd <= 0)
		return (free_pipes(&pipes, cmds->nb_pipe));
	if (one_cmd(cmds, &pipes, envp))
		return (free_pipes(&pipes, cmds->nb_pipe));
	i = -1;
	first_pipe(cmds, &pipes, envp);
	while (++i < cmds->nb_pipe - 1)
		mid_pipe(cmds, &pipes, i, envp);
	last_pipe(cmds, &pipes, i, envp);
	close_pipe(pipes.fd[i]);
	i = -1;
	while (++i <= cmds->nb_pipe)
		waitpid(pipes.pid[i], &exit_status, 0);
	update_last_exit(exit_status, envp);
	free_pipes(&pipes, cmds->nb_pipe);
}

void	exec_inpipe(t_cmds *cmds_ip, t_pipe *pipe, char ***envp)
{
	int		exit_status;

	exec_sep(cmds_ip, envp);
	if (!is_builtins(&cmds_ip->cmd[0], envp) && cmds_ip->sep[0] == None)
	{
		pipe->pid[0] = fork();
		if (pipe->pid[0] < 0)
			exit(1);
		if (pipe->pid[0] == 0)
		{
			exec_cmd(&cmds_ip->cmd[0], *envp);
			exit(0);
		}
		waitpid(pipe->pid[0], &exit_status, 0);
		update_last_exit(exit_status, envp);
	}
}

int	exec_heredoc(t_cmds *cmds, char ***envp, int fred)
{
	int	i;

	i = -1;
	while (cmds->sep[++i] != None)
		if (cmds->sep[i] == D_left)
			break ;
	if (cmds->sep[i] == None)
		return (0);
	heredoc(cmds, envp);
	if (fred)
	{
		free(cmds->sep);
		free(cmds->cmd);
		free(cmds->line);
	}
	return (1);
}

void	exec_sep(t_cmds *cmds, char ***envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmds->sep && cmds->sep[i] != None && cmds->sep[i] != Pipe)
	{
		if (cmds->sep[i] == S_right)
			write_in_file(cmds, j, envp, STDOUT_FILENO);
		else if (cmds->sep[i] == D_right)
			append_to_file(cmds, j, envp);
		else if (cmds->sep[i] == S_left)
			read_file(cmds->cmd[j + 1].name, &cmds->cmd[0], envp);
		j++;
		i++;
	}
}
