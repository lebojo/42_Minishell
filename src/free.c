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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL || !tab[0])
		return ;
	while (tab[i] != NULL && tab[i][0] != '\0')
		free(tab[i++]);
	free(tab);
}

void	free_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	if (cmds == NULL)
		return ;
	while (i < cmds->nb_cmd)
		free_cmd(&cmds->cmd[i++]);
	free(cmds->cmd);
	free(cmds->sep);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	free_pipes(t_pipe *pipes, int nb_pipes)
{
	int	i;

	i = -1;
	while (++i < nb_pipes && pipes->fd)
		free(pipes->fd[i]);
	free(pipes->fd);
	free(pipes->pid);
}
