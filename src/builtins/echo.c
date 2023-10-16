/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:53 by arthur            #+#    #+#             */
/*   Updated: 2023/10/16 18:16:31 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_echo(t_cmd *cmd, char ***envp)
{
	if (!cmd->arg)
		return ;
	if (cmd->arg[0] == '-' && cmd->arg[1] == 'n' && !cmd->arg[2])
		return ;
	if (cmd->arg[0] == '-' && cmd->arg[1] == 'n' && cmd->arg[2] == ' ')
		printf("%s", expand(cmd->arg + 3, envp));
	else
		printf("%s\n", expand(cmd->arg, envp));
}
