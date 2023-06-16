/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:50:37 by arthur            #+#    #+#             */
/*   Updated: 2023/06/16 04:04:12 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/proto.h"

char	*find_path(char **envp, char *s, int x)
{
	while (ft_strncmp(s, *envp, x))
		envp++;
	return (*envp + (x + 1));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}