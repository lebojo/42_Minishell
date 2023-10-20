/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:53 by arthur            #+#    #+#             */
/*   Updated: 2023/10/20 17:00:10 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_echo(t_cmd *cmd, char ***envp)
{
	(void) envp;
	if (!cmd->arg)
		return ;
	if (cmd->arg[0] == '-' && cmd->arg[1] == 'n' && !cmd->arg[2])
		return ;
	if (cmd->arg[0] == '-' && cmd->arg[1] == 'n' && cmd->arg[2] == ' ')
		printf("%s", cmd->arg + 3);
	else
		printf("%s\n", cmd->arg);
}
