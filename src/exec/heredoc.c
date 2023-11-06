/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/06 19:45:09 by jchapell         ###   ########.fr       */
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

int	heredoc_counter(t_cmds *cmds)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (cmds->sep[++i] != None)
		if (cmds->sep[i] == D_left)
			res++;
	return (res);
}

int	sepp_counter(t_cmds *cmds)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (cmds->sep[++i] != None)
		if (cmds->sep[i] == D_left)
			res++;
	return (res);
}

//<< g << t > t <<

int	has_output(enum e_sep *x)
{
	int	i;

	i = -1;
	while (x[++i] != None)
		if (x[i] == S_right | x[i] == D_right)
			return (1);
	return (0);
}

// t_cmds	parse_heredoc(t_cmds *cmds)
// {
// 	t_cmds	res;
// 	int		i;

// 	res.nb_cmd = cmds->nb_cmd;
// 	res.nb_pipe = heredoc_counter(cmds);
// 	res.sep = malloc(1);
// 	i = -1;
// 	if (res.nb_cmd == res.nb_pipe)
// 	{
// 		res.nb_cmd = cmds->nb_cmd + 1;
// 		if (has_output(cmds->sep))
// 			res.nb_cmd++;
// 		create_cmds(&res);
// 		while (++i < res.nb_cmd - 1)
// 		{
// 			res.cmd[i].name = ft_strdup(cmds->cmd[i].name);
// 			res.cmd[i].arg = NULL;
// 			if (cmds->cmd[i].arg) //marche pas si plusieurs ont un arg
// 				res.cmd[res.nb_cmd - 1] = parse_cmd(cmds->cmd[i].arg);
// 		}
// 	}
// 	else if (res.nb_cmd > res.nb_pipe)
// 	{
// 		if (has_output(cmds->sep))
// 			res.nb_cmd++;
// 		create_cmds(&res);
// 		res.cmd[res.nb_cmd - 1] = parse_cmd(cmds->cmd[++i].name);
// 		while (++i < res.nb_cmd)
// 		{
// 			res.cmd[i - 1].name = ft_strdup(cmds->cmd[i].name);
// 			res.cmd[i - 1].arg = NULL;
// 		}
// 	}
// 	return (res);
// }

t_cmds	parse_heredoc(t_cmds *cmds)
{
	t_cmds	res;
	int		nb_cmd;
	char	**sp;
	int		i;
	int		index_cmd;

	i = 0;
	index_cmd = 0;
	sp = ft_split(cmds->line, ' ');
	nb_cmd = 0;
	while (sp[i])
	{
		if (ft_strcmp(sp[i], "<<"))
			nb_cmd++;
		i++;
	}
	res.nb_cmd = nb_cmd + 2;
	create_cmds(&res);
	res.line = ft_strdup(cmds->line);
	i = 0;
	while (sp[i])
	{
		printf("sp[%i] = %s\n", i, sp[i]);
		if (ft_strcmp(sp[i], "<<"))
			res.cmd[index_cmd++].name = ft_strdup(sp[++i]);
		else
		{
			if (i != 0 && i > res.nb_cmd)
				printf("Syntax error heredoc\n");
			if (ft_strcmp(sp[i], ">") || ft_strcmp(sp[i], ">>"))
				res.cmd[res.nb_cmd - 1].name = ft_strdup(sp[++i]);
			else
				res.cmd[res.nb_cmd - 2].name = ft_strdup(sp[i]);
		}
		i++;
	}
	print_cmds(res);
	return (res);
}

char	*heredoc_process(char *break_str)
{
	char	*res;
	char	*line;

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
	//if (i == 0)
	p_cmds = parse_heredoc(cmds); 
	res = heredoc_process(p_cmds.cmd[i++].name);
	free_cmds(&p_cmds);
	return (0);
	// //===DEBUG===
	// print_cmds(*cmds);
	// printf("===here===\n");
	// print_cmds(p_cmds);
	// //==ENDEBUG==
	
	if (i == p_cmds.nb_pipe)
	{
		if (p_cmds.cmd[i].name)
		{
			write(fd[1], res, ft_strlen(res));
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			exec_in_fork(STDOUT_FILENO, fd, &p_cmds.cmd[p_cmds.nb_cmd - 1], *env);
			close_pipe(fd);
			dup2(1, STDIN_FILENO);
		}
		i = 0;
		free_cmds(&p_cmds);
		free(res);
		return (1);
	}
	free(res);
	return (0);
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
