/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:59:41 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/19 18:06:04 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	exec_cmd(t_cmd *cmd, t_exec *exec, char **env)
{
	int 	x;
	int		count;
	char	*temp;

	exec->env_p = find_path(env, "PATH", 4);
	exec->cmd_p = ft_split(exec->env_p, ':');
	exec->cmd = get_cmd(exec->cmd_p, cmd->name);
	if (!exec->cmd)
	{
		printf("command not found: %s\n", cmd->name);
		return ;
	}
	count = 1;
	if (cmd->arg)
	{	
		x = 1;
		while (cmd->arg[x])
		{
			if (cmd->arg[x] == ' ' || cmd->arg[x + 1] == '\0')
			{
				if (cmd->arg[x - 1] != ' ')
					count++;
			}
			x++;
		}
	}
	exec->cmd_a = malloc(sizeof(char *) * (count + 1));
	if (cmd->arg)
	{
		temp = add_str(cmd->name, " ", 0);
		temp = add_str(temp, cmd->arg, 1);
	}
	exec->cmd_a = ft_split(temp, ' ');
	exec->cmd_a[count + 1] = NULL;
	execve(exec->cmd, exec->cmd_a, env);
	exit(1);
	free(temp);
}