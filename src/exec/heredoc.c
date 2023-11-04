/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/04 21:17:12 by jchapell         ###   ########.fr       */
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

t_cmds	parse_heredoc(t_cmds *cmds)
{
	t_cmds	res;
	char	**sp;
	int		i;

	res.nb_cmd = 2;
	create_cmds(&res);
	i = 0;
	if (cmds->nb_cmd == 1)
	{
		res.nb_cmd = 1;
		res.cmd[0] = create_cmd(cmds->cmd[0].name, NULL, 0, 0);
		if (cmds->cmd[0].arg)
		{
			res.nb_cmd = 2;
			sp = ft_split(cmds->cmd[0].arg, ' ');
			res.cmd[1].name = sp[0];
			while (sp[++i])
				add_str_space(&res.cmd[1].arg, sp[i]); // Peut etre ca marche pas parce que arg est a NULL
		}
	}
	else
	{
		res.cmd[0] = create_cmd(cmds->cmd[1].name, NULL, 0, 0);
		if (cmds->cmd[0].arg)
			res.cmd[1] = cmds->cmd[0];
		else
			res.cmd[1].name = cmds->cmd[0].name;
	}
	return (res);
}

// cat << g;
// << g cat; 
// << g;

void	heredoc(int *fd, t_cmds *cmds, char ***env)
{
	char	*line;
	char	*res;
	t_cmds	p_cmds;

	res = ft_strdup("");
	line = NULL;
	p_cmds = parse_heredoc(cmds);
	print_cmds(p_cmds);
	signal(SIGINT, sig_her);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	while (g_status != 2)
	{
		line = readline("heredoc> ");
		if (line && line[0] == '\0')
			line = ft_strdup("\n");
		if (ft_strcmp(line, p_cmds.cmd[0].name) == 1)
			break ;
		line = add_str(line, "\n", 1);
		res = add_str(res, line, 3);
	}
	if (g_status != 2)
		free(line);
	signal(SIGINT, sig_handler);
	write(fd[1], res, ft_strlen(res));
	if (p_cmds.cmd[1].arg)
		exec_in_fork(STDIN_FILENO, fd, &p_cmds.cmd[1], *env);
	free(res);
	close_pipe(fd);
	free_cmds(&p_cmds);
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
