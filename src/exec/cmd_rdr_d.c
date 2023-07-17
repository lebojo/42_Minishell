/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rdr_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 20:10:05 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/26 15:13:57 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	push_to_fd(t_exec *exec ,char *res ,int x);

void	cmd_rdr_d_r(t_cmds *cmds, t_exec *exec, char **envp, int x)
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
		exec_cmd(&cmds->cmd[x], exec, envp);
		printf("SALUT\n");
		close(exec->fd_out);
		exit (1);
		return ;
	}
}

void	cmd_rdr_d_l(t_cmds *cmds, t_exec *exec, char **envp, int x)
{
	char	*heredoc;
	char	*res;
	char	*tmp;

	res = ft_strdup("");
	printf("%s\n\n", cmds->cmd[x].name);
	while (1)
	{
		heredoc = readline("heredoc>");
		if (!heredoc)
			heredoc = ft_strdup("\n");
		if (ft_strcmp(heredoc, cmds->cmd[x].name))
			break ;
		heredoc = ft_strjoin(heredoc,"\n");
		res = ft_strjoin(res, heredoc);
		free(heredoc);
	}
	exec->pid[x] = fork();
	if (exec->pid[x] == 0)
		push_to_fd(exec ,res, x);
	exit (1);
}

void	push_to_fd(t_exec *exec ,char *res,int x)
{
	if (x == exec->s_tube)
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