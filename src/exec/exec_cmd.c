/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:19:24 by abourgue          #+#    #+#             */
/*   Updated: 2023/10/04 18:17:58 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*ac_cmd;
	char	*path_env;
	char	**path_cmd;
	char	**s_cmd;

	path_env = find_path(env, "PATH", 4);
	path_env = add_str(path_env, ":", 0);
	path_env = add_str(path_env, find_path(env, "PWD", 3), 0);
	path_cmd = ft_split(path_env, ':');
	ac_cmd = get_cmd(path_cmd, cmd->name);
	if (!ac_cmd)
	{
		if (dup2(2, STDOUT_FILENO) == -1)
			return ;
		printf("Command not found: %s\n", cmd->name);
		exit (1);
	}
	s_cmd = split_cmd(*cmd);
	execve(ac_cmd, s_cmd, env);
	exit(0);
}
