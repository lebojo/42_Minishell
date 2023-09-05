/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:10:32 by abourgue          #+#    #+#             */
/*   Updated: 2023/09/05 19:49:19 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	**open_pipes(int nb_pipe)
{
	int **res;
	int	i;

	res = ft_calloc(nb_pipe, sizeof(int *));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < nb_pipe)
	{
		res[i] = ft_calloc(2, sizeof(int));
		if (pipe(res[i]) != 0 || !res[i])
			return (NULL);
	}
	return (res);
}

void first_pipe(int *pipe_fd, char ***envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		exit(1) ;
	char *args[] = {"ls", "-l", NULL};
	if (*pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve("/bin/ls", args, *envp); // Et en fait ici, au lieu d'exec la cmd, il faut faire une fonction pour que ça exec tout avant la pipe (genre s'il y a des <, >, etc..)
		exit(0);
	}
}

void mid_pipe(int *pipe_fd1, int *pipe_fd2, char ***envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		exit(1) ;
	char *args[] = {"cat", "-e", NULL};
	if (*pid == 0)
	{
		close(pipe_fd1[1]);
		dup2(pipe_fd1[0], STDIN_FILENO);
		close(pipe_fd1[0]);

		close(pipe_fd2[0]);
		dup2(pipe_fd2[1], STDOUT_FILENO);
		close(pipe_fd2[1]);
		
		execve("/bin/cat", args, *envp); //same que plus haut
		exit(0);
	}
}

void last_pipe(int *pipe_fd, char ***envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		exit(1) ;
	char *args[] = {"cat", "-e", NULL};
	if (*pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);

		execve("/bin/cat", args, *envp);  //same que plus haut
		exit(0);
	}
}