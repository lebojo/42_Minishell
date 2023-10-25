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

void	free_cmd(t_cmd *cmd)
{
	if (cmd->name != NULL)
		free(cmd->name);
	if (cmd->arg != NULL)
		free(cmd->arg);
}

void	free_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	if (cmds == NULL)
		return ;
	while (i < cmds->nb_cmd)
		free_cmd(&cmds->cmd[i++]);
	if (cmds->nb_cmd > 1)
		free(cmds->sep);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	free_all(t_cmds *cmds, char ***env)
{
	int	i;

	i = 0;
	free_cmds(cmds);
	free(cmds);
	while ((*env)[i] != NULL)
		free((*env)[i++]);
	free(*env);
}
