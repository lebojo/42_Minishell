/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/09/25 17:57:28 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*heredoc(char *str) // ex : << s  <-- dans cette situation on passe cmds->cmd[0].name
{
	char	*line;
	char	*res;

	res = ft_strdup("");
	while (1)
	{
		line = readline("heredoc>");
		if (line[0] == '\0')
			line = ft_strdup("\n");
		if (ft_strcmp(line, str) == 1)
			break ;
		line = ft_strjoin(line,"\n");
		res = ft_strjoin(res, line);
		free(line);
	}
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