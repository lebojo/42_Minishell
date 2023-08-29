/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rdr_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:10:05 by abourgue          #+#    #+#             */
/*   Updated: 2023/08/29 16:58:554 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	cmd_rdr_d_r(t_cmds *cmds, t_exec *exec, char ***envp, int x)
{
	int		i;
	int 	z;
	char	buf[2];

	i = 0;
	z = 1;
	exec->pid[x + 1] = fork();
	if (exec->pid[x + 1] == 0)
	{
		if (x > 0)
		{
			if (dup2(exec->tube[x - 1][0], STDIN_FILENO) == -1)
				return ;
			close(exec->tube[x - 1][1]);
		}
		exec->fd_out = open(cmds->cmd[x + 1].name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (exec->fd_out == -1)
			return ;
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
			return ;
		exec_cmd(&cmds->cmd[x], exec, *envp);
		close(exec->fd_out);
		exit (1);
	}
}

void	cmd_rdr_d_l(t_cmds *cmds, t_exec *exec, char ***envp, int x)
{
	char	*heredoc;
	char	*tmp;

	exec->res = ft_strdup("");
	while (1)
	{
		heredoc = readline("heredoc>");
		if (heredoc[0] == '\0')
			heredoc = ft_strdup("\n");
		if (ft_strcmp(heredoc, cmds->cmd[x].arg) == 1)
			break ;
		heredoc = ft_strjoin(heredoc,"\n");
		exec->res = ft_strjoin(exec->res, heredoc);
		free(heredoc);
	}
	exec->pid[x] = fork();
	if (exec->pid[x] == 0)
	{
		if (exec->res != NULL)
			push_to_fd(exec ,exec->res, x);
		exit (1);
	}
	return ;
}

void	push_to_fd(t_exec *exec ,char *res,int x)
{
	if (x + 1 == exec->s_tube)
	{
		if (dup2(1, STDOUT_FILENO) == -1)
			return ;
		close_pipe(exec, x - 1);
		printf("%s", res);
	}
	else
	{
		if (dup2(exec->tube[x][1], STDOUT_FILENO) == -1)
			return ;
		close_pipe(exec, x - 1);
		write(exec->tube[x][1], res, ft_strlen(res));
	}
}