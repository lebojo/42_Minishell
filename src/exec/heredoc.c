/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/05 10:58:21 by lebojo           ###   ########.fr       */
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
	while (cmds->sep[i] != None)
		i++;
	return (i);
}

t_cmds	parse_heredoc(t_cmds *cmds)
{
	t_cmds	res;
	int		i;

	res.nb_cmd = cmds->nb_cmd;
	/*
	X cmd parse que:
	toutes les premières cmd.name -> des heredocs à blanc
	l'avant derniere cmd.name -> le vrai heredoc
	la derniere cmd.name -> la cmd à executer

	nb_pipe = nb_sep ;)
	*/
	res.nb_pipe = sep_counter(cmds);
	i = -1;
	if (res.nb_cmd == res.nb_pipe)
	{
		res.nb_cmd = cmds->nb_cmd + 1;
		create_cmds(&res);
		while (++i < res.nb_cmd - 1) // ptetre - 1
		{
			res.cmd[i].name = ft_strdup(cmds->cmd[i].name);
			res.cmd[i].arg = NULL;
			if (cmds->cmd[i].arg) //marche pas si plusieurs ont un arg
				res.cmd[res.nb_cmd - 1].name = ft_strdup(cmds->cmd[i].arg);
		}
	}
	else
	{
		res.nb_cmd = cmds->nb_cmd;
		create_cmds(&res);
		res.cmd[res.nb_cmd - 1].name = ft_strdup(cmds->cmd[++i].name);
		while (++i < res.nb_cmd)
		{
			res.cmd[i - 1].name = ft_strdup(cmds->cmd[i].name);
			res.cmd[i - 1].arg = NULL;
		}
	}
	return (res);
}

// cat << g;
// << g cat; 
// << g;
// << g << t cat << h -> arg et 3 sep 3 cmd
// cat << g << t -> pas arg et 2 sep 3 cmd
// cat << g << t fichier1 << h << fichier 2 -> cat fichier1 et fichier2, osef des heredocs

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
	}
	signal(SIGINT, sig_handler); // les signaux -> A TESTER
	if (g_status != 2)
		free(line);
	return (res);
}

void	heredoc(int *fd, t_cmds *cmds, char ***env)
{
	char	*res;
	int		i;
	t_cmds	p_cmds;

	res = ft_strdup("");
	i = 0;
	p_cmds = parse_heredoc(cmds);
	
	/*===DEBUG===*/
	p_cmds.sep = malloc(sizeof(enum e_sep) * 2);
	p_cmds.sep[0] = None;
	p_cmds.sep[1] = None;
	print_cmds(p_cmds);
	/*==ENDEBUG==*/
	
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	
	while (g_status != 2 && res)
	{
		res = heredoc_process(p_cmds.cmd[0].name);
	}
		
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
