/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:10:32 by abourgue          #+#    #+#             */
/*   Updated: 2023/10/25 06:29:56 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	**open_pipes(int nb_pipe)
{
	int	**res;
	int	i;

	res = ft_calloc(nb_pipe, sizeof(int *));
	if (!res || nb_pipe == 0)
		return (NULL);
	i = -1;
	while (++i < nb_pipe)
	{
		res[i] = ft_calloc(2, sizeof(int));
		if (pipe(res[i]) != 0 || !res[i])
			return (NULL);
	}
	return (res);
}

void	first_pipe(t_cmds *cmd, t_pipe *pipes, char ***envp)
{
	pipes->pid[0] = fork();
	if (pipes->pid[0] < 0)
		exit (1);
	if (pipes->pid[0] == 0)
	{
		close(pipes->fd[0][0]);
		dup2(pipes->fd[0][1], STDOUT_FILENO);
		close(pipes->fd[0][1]);
		exec_inpipe(cmd, pipes, 0, envp);
		exit(0);
	}
}

void	mid_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp)
{
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
		exec_inpipe(cmd, pipes, i + 1, envp);
		exit(0);
	}
}

void	last_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp)
{
	pipes->pid[i] = fork();
	if (pipes->pid[i] < 0)
		exit(1);
	if (pipes->pid[i] == 0)
	{
		close(pipes->fd[i][1]);
		dup2(pipes->fd[i][0], STDIN_FILENO);
		close(pipes->fd[i][0]);
		exec_inpipe(cmd, pipes, i + 1, envp);
		exit(0);
	}
}

void	init_pipe(t_pipe *pipes, t_cmds *cmds)
{
	pipes->pid = ft_calloc(cmds->nb_cmd, sizeof(int));
	pipes->fd = open_pipes(cmds->nb_pipe);
	if (!pipes->pid || !pipes->fd)
		pipes = NULL;
}
