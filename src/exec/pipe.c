/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:10:32 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/08 18:55:19 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	**open_pipes(int nb_pipe)
{
	int	**res;
	int	i;

	if (nb_pipe == 0)
		return (NULL);
	res = ft_calloc(nb_pipe, sizeof(int *));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < nb_pipe)
		res[i] = ft_calloc(2, sizeof(int));
	return (res);
}

void	first_pipe(t_cmds *cmd, t_pipe *pipes, char ***envp)
{
	t_cmds	cmds_ip;

	cmds_ip = parse_cmds(*cmd, 0);
	if (pipe(pipes->fd[0]) != 0)
		exit(1);
	if (exec_heredoc(&cmds_ip, envp, 1))
		return ;
	pipes->pid[0] = fork();
	if (pipes->pid[0] < 0)
		exit (1);
	if (pipes->pid[0] == 0)
	{
		close(pipes->fd[0][0]);
		dup2(pipes->fd[0][1], STDOUT_FILENO);
		close(pipes->fd[0][1]);
		exec_inpipe(&cmds_ip, pipes, envp);
		exit(0);
	}
	free(cmds_ip.sep);
	free(cmds_ip.cmd);
	free(cmds_ip.line);
}

void	mid_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp)
{
	t_cmds	cmds_ip;

	cmds_ip = parse_cmds(*cmd, i + 1);
	if (pipe(pipes->fd[i + 1]) != 0)
		exit(1);
	if (exec_heredoc(&cmds_ip, envp, 1))
		return ;
	pipes->pid[i] = fork();
	if (pipes->pid[i] < 0)
		exit (1);
	if (pipes->pid[i] == 0)
	{
		close(pipes->fd[i][1]);
		dup2(pipes->fd[i][0], STDIN_FILENO);
		close(pipes->fd[i][0]);
		close(pipes->fd[i + 1][0]);
		dup2(pipes->fd[i + 1][1], STDOUT_FILENO);
		close(pipes->fd[i + 1][1]);
		exec_inpipe(&cmds_ip, pipes, envp);
		exit(0);
	}
	free(cmds_ip.sep);
	free(cmds_ip.cmd);
	free(cmds_ip.line);
	close_pipe(pipes->fd[i]);
}

void	last_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp)
{
	t_cmds	cmds_ip;

	cmds_ip = parse_cmds(*cmd, i + 1);
	if (exec_heredoc(&cmds_ip, envp, 1))
		return ;
	pipes->pid[i] = fork();
	if (pipes->pid[i] < 0)
		exit(1);
	if (pipes->pid[i] == 0)
	{
		close(pipes->fd[i][1]);
		dup2(pipes->fd[i][0], STDIN_FILENO);
		close(pipes->fd[i][0]);
		exec_inpipe(&cmds_ip, pipes, envp);
		exit(0);
	}
	free(cmds_ip.sep);
	free(cmds_ip.cmd);
	free(cmds_ip.line);
}

void	init_pipe(t_pipe *pipes, t_cmds *cmds)
{
	pipes->pid = ft_calloc(cmds->nb_cmd, sizeof(int));
	pipes->fd = open_pipes(cmds->nb_pipe);
	if (!pipes->pid || !pipes->fd)
		pipes = NULL;
}
