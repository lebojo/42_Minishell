/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:29:12 by jordan            #+#    #+#             */
/*   Updated: 2023/10/06 02:28:06 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*hm_get_value(char **map, char *key)
{
	char	**split_map;
	int		i;

	i = 0;
	while (map[i])
	{
		split_map = ft_split(map[i], '=');
		if (ft_strcmp(key, split_map[0]))
		{
			free(split_map[0]);
			return (split_map[1]);
		}
		free(split_map);
		i++;
	}
	return (NULL);
}

int	hm_set_value(char ***map, char *key, char *new_val)
{
	char	**split_map;
	int		i;

	i = 0;
	while ((*map)[i])
	{
		split_map = ft_split((*map)[i], '=');
		if (ft_strcmp(key, split_map[0]))
		{
			free((*map)[i]);
			(*map)[i] = add_str(key, "=", 0);
			(*map)[i] = add_str((*map)[i], new_val, 1);
			free(split_map[0]);
			free(split_map[1]);
			free(split_map);
			return (1);
		}
		free(split_map);
		i++;
	}
	return (0);
}
