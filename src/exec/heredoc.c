/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/07 19:32:59 by jchapell         ###   ########.fr       */
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

int	process_parse_heredoc(t_cmds *res, int i, int *index_cmd, char **sp)
{
	if (ft_strcmp(sp[i], "<<"))
	{
		res->cmd[(*index_cmd)].arg = ft_strdup("<<");
		res->cmd[(*index_cmd)++].name = ft_strdup(sp[++i]);
	}
	else
	{
		if (i != 0 && i > res->nb_cmd)
			printf("Syntax error heredoc\n");
		if (ft_strcmp(sp[i], ">") || ft_strcmp(sp[i], ">>"))
		{
			res->cmd[res->nb_cmd - 1].arg = ft_strdup(sp[i]);
			res->cmd[res->nb_cmd - 1].name = ft_strdup(sp[++i]);
		}
		else
		{
			res->cmd[res->nb_cmd - 2].name = ft_strdup(sp[i]);
			res->cmd[res->nb_cmd - 2].arg = NULL;
		}
	}
	i++;
	return (i);
}

t_cmds	parse_heredoc(t_cmds *cmds, int i)
{
	t_cmds	res;
	char	**sp;
	int		nb_cmd;
	int		index_cmd;

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
		i = process_parse_heredoc(&res, i, &index_cmd, sp);
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

void	heredoc(t_cmds *cmds, char ***env)
{
	char	*res;
	int		i;
	t_cmds	p_cmds;

	i = 0;
	res = ft_strdup("");
	p_cmds = parse_heredoc(cmds, i);
	while (i < p_cmds.nb_cmd - 3)
	{
		res = heredoc_process(p_cmds.cmd[i++].name);
		free(res);
	}
	res = heredoc_process(p_cmds.cmd[i].name);
	if (p_cmds.cmd[i + 1].name)
	{
		if (p_cmds.cmd[i + 2].name)
			write_in_here(&p_cmds, res, i, *env);
		else
			exec_herefork(STDOUT_FILENO, res, &p_cmds.cmd[i + 1], *env);
	}
	free(res);
}
