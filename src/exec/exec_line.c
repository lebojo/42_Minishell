/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:29:02 by lebojo            #+#    #+#             */
/*   Updated: 2023/09/05 18:29:57 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void first_pipe(int *fd, char ***envp, int *pid);
void mid_pipe(int *pipe_fd1, int *pipe_fd2, char ***envp, int *pid);
void last_pipe(int *fd, char ***envp, int *pid);
int	**open_pipes(int nb_pipe);

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

void	rdr_into_file(t_cmds *cmds, t_exec *exec, int id)
{
	exec->fd_out = open(cmds->cmd[id].name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec->fd_out == -1)
		return ;
	if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
		return ;
}

void	 exec_line(t_cmds *cmds, char ***envp)
{
	t_exec	exec;

	if (cmds->nb_cmd <= 0)
		return ;
	if (cmds->nb_cmd == 1)
		return ;
	int **pipe_fd;
	int *pid = malloc(sizeof(int) * 3);

	pipe_fd = open_pipes(2);
	if (!pipe_fd)
		return ;
	first_pipe(pipe_fd[0], envp, &pid[0]);
	mid_pipe(pipe_fd[0], pipe_fd[1], envp, &pid[1]);
	last_pipe(pipe_fd[1], envp, &pid[2]);

	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);

	close(pipe_fd[1][0]);
	close(pipe_fd[1][1]);

	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);
}

int	**open_pipes(int nb_pipe)
{
	int **res;
	int	i;

	res = ft_calloc(nb_pipe, sizeof(int *));
	i = -1;
	while (++i < nb_pipe)
	{
		res[i] = ft_calloc(2, sizeof(int));
		if (pipe(res[i]) != 0)
			return (NULL);
	}
	return (res);
}

void first_pipe(int *pipe_fd, char ***envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return ;
	char *args[] = {"ls", "-l", NULL};
	if (*pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve("/bin/ls", args, *envp);
		exit(0);
	}
}

void mid_pipe(int *pipe_fd1, int *pipe_fd2, char ***envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return ;
	char *args[] = {"cat", "-e", NULL};
	if (*pid == 0)
	{
		close(pipe_fd1[1]);
		dup2(pipe_fd1[0], STDIN_FILENO);
		close(pipe_fd1[0]);

		close(pipe_fd2[0]);
		dup2(pipe_fd2[1], STDOUT_FILENO);
		close(pipe_fd2[1]);
		
		execve("/bin/cat", args, *envp);
		exit(0);
	}
}

void last_pipe(int *pipe_fd, char ***envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return ;
	char *args[] = {"cat", "-e", NULL};
	if (*pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execve("/bin/cat", args, *envp);
		exit(0);
	}
}

void	setup_exec_var(t_cmds *cmds, t_exec *exec)
{
    int x;

	x = -1;
	exec->tube = ft_calloc(cmds->nb_cmd - 1, sizeof(int *));
    exec->s_tube = cmds->nb_cmd - 1;
	exec->pid = ft_calloc(cmds->nb_cmd, sizeof(pid_t));
    while (++x < exec->s_tube)
    {
        exec->tube[x] = malloc(sizeof(int) * 2);
        if (pipe(exec->tube[x]) == -1)
            return;
    }
}