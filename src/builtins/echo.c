/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:53 by arthur            #+#    #+#             */
/*   Updated: 2023/06/16 22:38:46 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_echo(t_cmd *cmd, t_envp *env)
{
	(void)env;
	(void)cmd;
	// int	i;

	// i = -1;
	// while (++i < cmd->nb_prms)
	// {
	// 	if (cmd->prms[i].opt != NULL)
	// 	{
	// 		if (i != 0 && ft_strcmp(cmd->prms[0].opt, "-n") == 0)
	// 		printf("%s ", cmd->prms[i].opt);
	// 	}
	// 	if (cmd->prms[i].value != NULL)
	// 		printf("%s ", cmd->prms[i].value);
	// }
	// if (cmd->nb_prms > 0 && !(cmd->prms[0].opt && ft_strcmp(cmd->prms[0].opt, "-n")))
	// 	printf("\n");
	return ;
}