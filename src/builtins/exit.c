/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:13 by arthur            #+#    #+#             */
/*   Updated: 2023/10/16 19:37:55 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_exit(int status)
{
	printf("\nExiting ");
	printf(MS);
	printf("...\n");
	exit(status);
}

void	ft_exit_cmd(t_cmd *cmd)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (cmd->arg[i])
	{
		while (cmd->arg[i])
		{
			if (!ft_isdigit(cmd->arg[i]))
			{
				printf("exit: %s: numeric argument required\n", cmd->arg);
				ft_exit(2);
			}
			i++;
		}
		status = ft_atoi(cmd->arg);
	}
	ft_exit(status);
}