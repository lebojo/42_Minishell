/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 03:46:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/22 16:59:21 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void free_cmds(t_cmds *cmds) 
{
	if (cmds == NULL)
		return;
	int i = 0;
	while (i < cmds->nb_cmd) {
		if (cmds->cmd[i].name != NULL)
			free(cmds->cmd[i].name);
		if (cmds->cmd[i].arg != NULL)
			free(cmds->cmd[i].arg);
		i++;
	}
	free(cmds->cmd);

	if (cmds->nb_cmd > 1) {
		free(cmds->sep);
	}
}

void    free_tube(t_exec *exec)
{
    int i;

    i = -1;
    while(++i < exec->s_tube)
        free(exec->tube[i]);
}

void    close_fd(t_exec *exec)
{
    if (exec->fd_in > 0)
        close(exec->fd_in);
    if (exec->fd_out > 0)
        close(exec->fd_out);
}

void    close_pipe(int *fd)
{
    close(fd[0]);
    close(fd[1]);
}