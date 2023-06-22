/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:53 by arthur            #+#    #+#             */
/*   Updated: 2023/06/22 02:06:17 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	print_echo(char *arg, char ***envp)
{
	char	**split_arg;
	char	*tmp;
	int		i;

	split_arg = ft_split(arg, ' ');
	i = -1;
	while (split_arg[++i])
	{
		if (split_arg[i][0] == '$' && split_arg[i][1] && split_arg[i][1] != ' ')
		{
			tmp = hm_get_value(*envp, ++split_arg[i]);
			if (tmp)
				printf("%s ", tmp);
			free(tmp);
			continue ;
		}
		printf("%s ", split_arg[i]);
	}
}

void	ft_echo(t_cmd *cmd, char ***envp)
{
	if (!cmd->arg)
		return ;
	if(cmd->arg[0] == '-' && cmd->arg[1] == 'n' && cmd->arg[2] == ' ')
	{
		cmd->arg += 3;
		print_echo(cmd->arg, envp);
		cmd->arg -= 3;
	}
	else
	{
		print_echo(cmd->arg, envp);
		printf("\n");
	}
}