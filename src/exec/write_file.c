/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:42:32 by abourgue          #+#    #+#             */
/*   Updated: 2023/10/16 15:16:10 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	write_in_file(char *str, char *name, t_cmd *cmd, char ***env)
{
	int		id[2];

	id[0] = 0;
	id[1] = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (id[1] == -1)
		return ;
	if (str)
	{
		write(id[1], str, ft_strlen(str));
		free(str);
		close(id[1]);
	}
	else if (exec_inpipe_builtins(STDOUT_FILENO, id[1], cmd, env))
		return ;
	else
		exec_in_fork(STDOUT_FILENO, id, cmd, *env);
}

void	append_to_file(char *str, char *name, t_cmd *cmd, char ***env)
{
	int		id[2];

	id[0] = 0;
	id[1] = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (id[1] == -1)
		return ;
	if (str)
	{
		write(id[1], str, ft_strlen(str));
		free(str);
		close(id[1]);
	}
	else if (exec_inpipe_builtins(STDOUT_FILENO, id[1], cmd, env))
		return ;
	else
		exec_in_fork(STDOUT_FILENO, id, cmd, *env);
}
