/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:53 by arthur            #+#    #+#             */
/*   Updated: 2023/10/24 02:13:41 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_echo(t_cmd *cmd)
{
	if (!cmd->arg)
		return ;
	if (cmd->arg[0] == '-' && cmd->arg[1] == 'n' && !cmd->arg[2])
		return ;
	if (cmd->arg[0] == '-' && cmd->arg[1] == 'n' && cmd->arg[2] == ' ')
		printf("%s", cmd->arg + 3);
	else
		printf("%s\n", cmd->arg);
}
