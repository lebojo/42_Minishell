/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:11:59 by lebojo            #+#    #+#             */
/*   Updated: 2023/07/18 01:39:46 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_unset(t_cmd *cmd, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	if (!cmd->arg)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while ((*env)[i++])
		;
	new_env = malloc(sizeof(char *) * i);
	i = -1;
	j = -1;
	while ((*env)[++i])
	{
		if (ft_strcmp(ft_split((*env)[i], '=')[0], cmd->arg) == 0)
			new_env[++j] = ft_strdup((*env)[i]);
	}
	new_env[++j] = NULL;
	(*env) = new_env;
}