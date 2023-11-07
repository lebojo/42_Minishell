/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_herefork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:39:19 by jchapell          #+#    #+#             */
/*   Updated: 2023/11/07 19:41:33 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	exec_here_infork(int p[], char *txt, t_cmd *cmd, char **env)
{
	int		in[2];

	close(p[0]);
	dup2(p[1], STDOUT_FILENO);
	close(p[1]);
	if (pipe(in) == -1)
		exit(printf("Error: heredoc: pipe in\n"));
	write(in[1], txt, strlen(txt));
	close(in[1]);
	dup2(in[0], STDIN_FILENO);
	close(in[0]);
	exec_cmd(cmd, env);
	printf("Error: heredoc: exec\n");
	exit(1);
}

void	exec_here_outfork(int p[], pid_t pid, int fd, char **env)
{
	ssize_t	n;
	int		status;
	char	buf[BUFSIZ];

	close(p[1]);
	n = 1;
	while (n > 0)
	{
		n = read(p[0], buf, BUFSIZ);
		if (write(fd, buf, n) == -1)
			exit(printf("Error: heredoc: write\n"));
	}
	if (n == -1)
		exit(printf("Error: heredoc: read\n"));
	close(p[0]);
	waitpid(pid, &status, 0);
	update_last_exit(status, &env);
}

void	exec_herefork(int fd, char *txt, t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		p[2];

	if (pipe(p) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		exec_here_infork(p, txt, cmd, env);
	else
		exec_here_outfork(p, pid, buf, fd, env);
}
