/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:42:32 by abourgue          #+#    #+#             */
/*   Updated: 2023/09/24 05:35:53 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	write_in_file(char *name, t_cmd *cmd, char **env)
{
	int	fd;
	char	*str;
	char	*input;
	int	id;

	id = 0;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	id = fork();
	if (id == 0)
	{
		dup2(fd, STDOUT_FILENO);
		exec_cmd(cmd, env);
		close (fd);
		dup2(1, STDOUT_FILENO);
	}
	waitpid(id, NULL, 0);
}

void	append_to_file(char *name, t_cmd *cmd, char **env)
{
	int	fd;
	char	*str;
	char	*input;
	int	id;

	id = 0;
	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	id = fork();
	if (id == 0)
	{
		dup2(fd, STDOUT_FILENO);
		exec_cmd(cmd, env);
		close (fd);
		dup2(1, STDOUT_FILENO);
	}
	waitpid(id, NULL, 0);
}
