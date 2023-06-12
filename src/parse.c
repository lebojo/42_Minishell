/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:57:48 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 18:34:54 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	parse(t_cmd *cmd, char *input)
{
	char	**split;
	int		i;

	split = ft_split(input, ' ');
	i = 0;
	while (split[i++])
		;
	cmd->nb_prms = i - 1;
	cmd->prms = malloc(sizeof(t_prms) * i);
	i = 0;
	while (split[i + 1] && split[i][0] != '|')
	{
		if (i == 0)
			cmd->name = split[i];
		else
		{
			if (split[i][0] == '-')
			{
				cmd->prms[i - 1].opt = ft_strdup(split[i]);
				if (split[i + 1] && split[i + 1][0] != '-')
				{
					cmd->prms[i - 1].value = ft_strdup(split[i + 1]);
					i++;
				}
				else
					cmd->prms[i - 1].value = NULL;
			}
			else
			{
				cmd->prms[i - 1].opt = NULL;
				cmd->prms[i - 1].value = ft_strdup(split[i]);
			}
		}
		i++;
	}
}
