/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:29:02 by lebojo            #+#    #+#             */
/*   Updated: 2023/09/05 19:49:26 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*find_path(char **envp, char *s, int x)
{
	while (ft_strncmp(s, *envp, x))
		envp++;
	return (*envp + (x + 1));
}

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

int	is_builtins(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp("echo", cmd->name))
		ft_echo(cmd, envp);
	else if (ft_strcmp("cd", cmd->name))
		ft_cd(cmd->arg);
	else if (ft_strcmp("pwd",cmd->name))
		ft_pwd();
	else if (ft_strcmp("export",cmd->name))
		ft_export(cmd, envp);
	else if (ft_strcmp("unset",cmd->name))
		ft_unset(cmd, envp);
	else if (ft_strcmp("env",cmd->name))
		ft_env(*envp);
	else if (ft_strcmp("exit", cmd->name))
		ft_exit();
	else
		return (0);
	return (1);
}

void init_exec(t_exec *ex, t_cmds *cmds)
{
	ex->pid = ft_calloc(cmds->nb_cmd, sizeof(int));
	ex->pipe_fd = open_pipes(cmds->nb_pipe);
	if (!ex->pid || !ex->pipe_fd)
		ex = NULL;
}

void	 exec_line(t_cmds *cmds, char ***envp)
{
	t_exec	exec;
	int		i;

	if (cmds->nb_cmd <= 0)
		return ;
	if (cmds->nb_pipe == 0)
		return ;

	//execute ça que s'il y a au moins 1 pipe:
	init_exec(&exec, cmds);
	i = -1;
	first_pipe(exec.pipe_fd[0], envp, &exec.pid[0]);
	while (++i < cmds->nb_pipe - 1) // le -1 c'est parce que s'il y a 1 pipe, il ne doit pas rentrer dedans, et t'as capté la logique.
	{
		mid_pipe(exec.pipe_fd[i], exec.pipe_fd[i + 1], envp, &exec.pid[i + 1]);
		close_pipe(exec.pipe_fd[i]);
	}
	last_pipe(exec.pipe_fd[i], envp, &exec.pid[i + 1]);

	close_pipe(exec.pipe_fd[i]);

	i = -1;
	while (++i <= cmds->nb_pipe)
		waitpid(exec.pid[i], NULL, 0);
}