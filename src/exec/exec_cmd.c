/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:59:41 by abourgue          #+#    #+#             */
/*   Updated: 2023/06/16 22:10:02 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	exec_cmd(t_cmds *cmds, t_exec *exec, char **env, int i)
{
	int x;
	int	z;
	int	count;

	exec->cmd = get_cmd(exec->cmd_p, cmds->cmd[i].name);
	if (!exec->cmd)
	{
		printf("command not found: %s\n", cmds->cmd[i].name);
		free_cmds(cmds);
		return ;
	}
	x = 0;
	count = 0;
	if (cmds->cmd[i].name)
		count++;
	if (cmds->cmd[i].arg)
	{	
		while (cmds->cmd[i].arg[x])
		{
			if (cmds->cmd[i].arg[x] == ' ' || cmds->cmd[i].arg[x + 1] == '\0')
			{
				if (cmds->cmd[i].arg[x - 1] != ' ')
					count++;
			}
			x++;
		}
	}
	exec->cmd_a = malloc(sizeof(char *) * (count + 1));
	x = 0;
	z = 0;
	if (count > 1)
	{
		while (z < count)
		{
			if (cmds->cmd[i].name)
				exec->cmd_a[z++] = ft_strdup(cmds->cmd[i].name);
			if (cmds->cmd[i].arg)
				exec->cmd_a[z++] = ft_strdup(cmds->cmd[i].arg);
		
		}
	}
	exec->cmd_a[z] = NULL;
	execve(exec->cmd, exec->cmd_a, env);
	free_cmds(cmds);
}

void	simple_cmd(t_cmds *cmds, char **env)
{
	t_exec	exec;
	
	exec.env_p = find_path(env, "PATH", 4);
	exec.cmd_p = ft_split(exec.env_p, ':');
	exec.pid1 = fork();
	cmds->cmd = malloc(sizeof(t_cmd) * 1);
	cmds->cmd[0].name = ft_strdup("echo");
	cmds->cmd[0].arg = ft_strdup("salut");
	cmds->nb_cmd = 1;
	if (exec.pid1 == 0)
		exec_cmd(cmds, &exec, env, 0);
	waitpid(exec.pid1, NULL, 0);
}