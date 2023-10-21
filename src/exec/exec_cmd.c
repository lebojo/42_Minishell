/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:19:24 by abourgue          #+#    #+#             */
/*   Updated: 2023/10/21 04:04:02 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (!paths)
		return (NULL);
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

char	**create_path_cmd(char **env)
{
	char	*path_env;
	char	**path_cmd;

	path_env = hm_get_value(env, "PATH");
	if (path_env == NULL)
		return (NULL);
	path_env = add_str(path_env, ":", 1);
	path_env = add_str(path_env, hm_get_value(env, "PWD"), 3);
	path_cmd = ft_split(path_env, ':');
	return (path_cmd);
}

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*ac_cmd;
	char	**path_cmd;
	char	**s_cmd;

	path_cmd = create_path_cmd(env);
	ac_cmd = get_cmd(path_cmd, cmd->name);
	if (!ac_cmd)
	{
		s_cmd = split_cmd(*cmd);
		if (execve(cmd->name, s_cmd, env) == -1)
		{
			if (dup2(2, STDOUT_FILENO) == -1)
				return ;
			printf("Command not found: %s\n", cmd->name);
			exit (1);
		}
		exit(0);
	}
	s_cmd = split_cmd(*cmd);
	if (execve(ac_cmd, s_cmd, env) == -1)
	{
		printf("Error execve\n");
		exit (1);
	}
	exit(0);
}
