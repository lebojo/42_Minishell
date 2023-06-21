/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:29:12 by jordan            #+#    #+#             */
/*   Updated: 2023/06/21 17:02:54 by jordan           ###   ########.fr       */
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

void	hm_set_value(char ***map, char *key, char *value)
{
}