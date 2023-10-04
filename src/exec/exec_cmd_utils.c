/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:15:52 by lebojo            #+#    #+#             */
/*   Updated: 2023/10/04 18:19:33 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*str_extractor(char *s)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(ft_strlen(s) - 2, sizeof(char));
	if (s[i] == '"')
	{
		while (s[++i] && s[i] != '"')
			res[i - 1] = s[i];
		if (!s[i])
			return (NULL);
	}
	else if (s[i] == '\'')
	{
		while (s[++i] && s[i] != '\'')
			res[i - 1] = s[i];
		if (!s[i])
			return (NULL);
	}
	return (res);
}

int	strlen_to_char(char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*find_path(char **envp, char *s, int x)
{
	while (ft_strncmp(s, *envp, x))
		envp++;
	return (*envp + (x + 1));
}
