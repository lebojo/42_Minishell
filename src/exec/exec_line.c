/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:29:02 by lebojo            #+#    #+#             */
/*   Updated: 2023/10/25 07:41:53 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	is_builtins(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp("echo", cmd->name))
		ft_echo(cmd);
	else if (ft_strcmp("cd", cmd->name))
		ft_cd(cmd->arg, envp);
	else if (ft_strcmp("pwd", cmd->name))
		ft_pwd();
	else if (ft_strcmp("export", cmd->name))
		ft_export(cmd, envp);
	else if (ft_strcmp("unset", cmd->name))
		ft_unset(cmd, envp);
	else if (ft_strcmp("env", cmd->name))
		ft_env(*envp);
	else if (ft_strcmp("exit", cmd->name))
		ft_exit_cmd(cmd, envp);
	else if (ft_strcmp("..", cmd->name))
		ft_cd("..", envp);
	else
		return (0);
	return (1);
}

int	one_cmd(t_cmds *cmds, t_pipe *pipes, char ***envp)
{
	int		i;

	i = -1;
	while (cmds->sep[++i] != None)
	{
		if (cmds->sep[i] == Pipe)
		{
			i = -42;
			break ;
		}
	}
	if (i != -42)
	{
		exec_inpipe(cmds, pipes, 0, envp);
		return (1);
	}
	return (0);
}

void	exec_line(t_cmds *cmds, char ***envp)
{
	t_pipe	pipes;
	int		i;
	int		exit_status;

	init_pipe(&pipes, cmds);
	if (cmds->nb_cmd <= 0)
		return ;
	if (one_cmd(cmds, &pipes, envp))
		return ;
	i = -1;
	first_pipe(cmds, &pipes, envp);
	while (++i < cmds->nb_pipe - 1)
	{
		mid_pipe(cmds, &pipes, i, envp);
		close_pipe(pipes.fd[i]);
		free(pipes.fd[i]);
	}
	last_pipe(cmds, &pipes, i, envp);
	close_pipe(pipes.fd[i]);
	free(pipes.fd[i]);
	free(pipes.fd);
	i = -1;
	while (++i <= cmds->nb_pipe)
		waitpid(pipes.pid[i], &exit_status, 0);
	free(pipes.pid);
	update_last_exit(exit_status, envp);
}

void	exec_inpipe(t_cmds *cmds, t_pipe *pipe, int which_pipe, char ***envp)
{
	t_cmds	cmds_ip;
	int		exit_status;

	cmds_ip = parse_cmds(*cmds, which_pipe);
	if (cmds_ip.nb_cmd > 1)
		exec_sep(&cmds_ip, envp);
	else
	{
		if (!is_builtins(&cmds_ip.cmd[0], envp))
		{
			pipe->pid[0] = fork();
			if (pipe->pid[0] < 0)
				exit(1);
			if (pipe->pid[0] == 0)
			{
				exec_cmd(&cmds_ip.cmd[0], *envp);
				exit(0);
			}
			waitpid(pipe->pid[0], &exit_status, 0);
			update_last_exit(exit_status, envp);
		}
	}
	free(pipe->pid);
	free(cmds_ip.cmd);
	free(cmds_ip.sep);
}

void	exec_sep(t_cmds *cmds, char ***envp)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = NULL;
	while (cmds->sep[i] != None && cmds->sep[i] != Pipe)
	{
		if (cmds->sep[i] == S_right)
			write_in_file(res, cmds->cmd[j + 1].name, &cmds->cmd[j], envp);
		else if (cmds->sep[i] == D_right)
			append_to_file(res, cmds->cmd[j + 1].name, &cmds->cmd[j], envp);
		else if (cmds->sep[i] == S_left)
			read_file(cmds->cmd[j + 1].name, &cmds->cmd[j], envp);
		else if (cmds->sep[i] == D_left)
			res = heredoc(cmds->cmd[j++].name);
		i++;
	}
}
