/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:16:53 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/22 17:00:09 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	cmd_pipe(t_cmd *cmd, t_exec *exec, char **envp, int x)
{
	exec->pid[x] = fork();
	if (exec->pid[x] == 0)
	{
		if (x > 0)
		{
			if (dup2(exec->tube[x - 1][0], STDIN_FILENO) == -1)
				return ;		
			close(exec->tube[x - 1][1]);
		}
		exec_rdr(cmd, exec, envp, x);
	}
}