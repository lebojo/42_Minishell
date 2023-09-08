/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:16:49 by abourgue          #+#    #+#             */
/*   Updated: 2023/09/06 10:36:49 by abourgue         ###   ########.fr       */
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
	printf("%s\n", res);
	return (res);
}