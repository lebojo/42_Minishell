/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:11:59 by lebojo            #+#    #+#             */
/*   Updated: 2023/07/15 15:17:27 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_unset(t_cmd *cmd, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (cmd->arg[++i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (ft_strncmp(cmd->arg, (*env)[j]) == 0)
			{
				new_env = copy_tab(*env);
				free((*env)[j]);
				(*env)[j] = NULL;
				free(*env);
				*env = new_env;
			}
			j++;
		}
	}
}