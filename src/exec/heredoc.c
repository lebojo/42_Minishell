/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/11/04 17:49:42 by jchapell         ###   ########.fr       */
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

char	*heredoc(char *str, int fd)
{
	char	*line;
	char	*res;

	res = ft_strdup("");
	line = NULL;
	signal(SIGINT, sig_her);
	if (fd != -1)
		dup2(STDOUT_FILENO, 0);
	while (g_status != 2)
	{
		line = readline("heredoc>");
		if (line && line[0] == '\0')
			line = ft_strdup("\n");
		if (ft_strcmp(line, str) == 1)
			break ;
		line = add_str(line, "\n", 1);
		res = add_str(res, line, 3);
	}
	if (fd != -1)
		dup2(STDOUT_FILENO, fd);
	if (g_status != 2)
		free(line);
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
