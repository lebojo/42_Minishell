/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/10/21 23:15:09 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ptain(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

char	*heredoc(char *str)
{
	char	*line;
	char	*res;

	res = ft_strdup("");
	signal(SIGINT, ptain);
	while (g_status != 2)
	{
		line = readline("heredoc>");
		if (line[0] == '\0')
			line = ft_strdup("\n");
		if (ft_strcmp(line, str) == 1)
			break ;
		line = ft_strjoin(line, "\n");
		res = ft_strjoin(res, line);
		free(line);
	}
	signal(SIGINT, sig_handler);
	return (res);
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
