/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:29:12 by jordan            #+#    #+#             */
/*   Updated: 2023/10/25 05:49:30 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*hm_get_value(char **map, char *key)
{
	char	**split_map;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while (map[i])
	{
		split_map = ft_split(map[i], '=');
		if (ft_strcmp(key, split_map[0]))
		{
			res = ft_strdup(split_map[1]);
			free_tab(split_map);
			break ;
		}
		free_tab(split_map);
		i++;
	}
	return (res);
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
