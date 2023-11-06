/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/06 15:50:57 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	sig_her(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

static int	sep_counter(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->sep[i] == D_left)
		i++;
	return (i);
}

t_cmds	parse_heredoc(t_cmds *cmds)
{
	t_cmds	res;
	int		i;

	res.nb_cmd = cmds->nb_cmd;
	res.nb_pipe = sep_counter(cmds);
	res.sep = malloc(1);
	i = -1;
	if (res.nb_cmd == res.nb_pipe)
	{
		res.nb_cmd = cmds->nb_cmd + 1;
		create_cmds(&res);
		while (++i < res.nb_cmd - 1)
		{
			res.cmd[i].name = ft_strdup(cmds->cmd[i].name);
			res.cmd[i].arg = NULL;
			if (cmds->cmd[i].arg) //marche pas si plusieurs ont un arg
				res.cmd[res.nb_cmd - 1] = parse_cmd(cmds->cmd[i].arg);
		}
	}
	else
	{
		res.nb_cmd = cmds->nb_cmd;
		create_cmds(&res);
		res.cmd[res.nb_cmd - 1] = parse_cmd(cmds->cmd[++i].name);
		while (++i < res.nb_cmd)
		{
			res.cmd[i - 1].name = ft_strdup(cmds->cmd[i].name);
			res.cmd[i - 1].arg = NULL;
		}
	}
	return (res);
}

char	*heredoc_process(char *break_str)
{
	char	*res;
	char	*line;
	int		i;

	i = 0;
	res = ft_strdup("");
	line = NULL;
	signal(SIGINT, sig_her);
	while (g_status != 2)
	{
		line = readline("heredoc> ");
		if (line && line[0] == '\0')
			line = ft_strdup("\n");
		if (ft_strcmp(line, break_str) == 1)
			break ;
		line = add_str(line, "\n", 1);
		res = add_str(res, line, 3);
		line = NULL;
	}
	signal(SIGINT, sig_handler);
	if (g_status != 2)
		free(line);
	return (res);
}

int	heredoc(int *fd, t_cmds *cmds, char ***env)
{
	char			*res;
	static int		i = 0;
	static t_cmds	p_cmds;

	res = ft_strdup("");
	if (i == 0)
		p_cmds = parse_heredoc(cmds); 
	res = heredoc_process(p_cmds.cmd[i++].name);
	if (i == p_cmds.nb_pipe)
	{
		if (p_cmds.cmd[i].name)
		{
			write(fd[1], res, ft_strlen(res));
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			exec_in_fork(STDOUT_FILENO, fd, &p_cmds.cmd[i], *env);
			close_pipe(fd);
			dup2(1, STDIN_FILENO);
		}
		i = 0;
		free_cmds(&p_cmds);
	}
	free(res);
	return (1);
}

void	read_file(char *name, t_cmd *cmd, char ***env)
{
	int	id[2];

	id[0] = 0;
	id[1] = open(name, O_RDONLY);
	if (id[1] == -1)
		return ;
	if (exec_inpipe_builtins(STDIN_FILENO, id[1], cmd, env))
		return ;
	else
		exec_in_fork(STDIN_FILENO, id, cmd, *env);
}
