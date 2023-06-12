/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:53 by arthur            #+#    #+#             */
/*   Updated: 2023/06/12 18:42:34 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_echo(t_cmd *cmd, t_envp *env)
{
	(void)env;
	int	i;

	i = 0;
	if (ft_strcmp(cmd->prms[0].opt, "-n"))
	{
		if (cmd->nb_prms > 1)
		{
			if (cmd->prms[0].value != NULL);
				printf ("%s ", cmd->prms[0].value);
			while (++i <= cmd->nb_prms)
				printf("%s %s", cmd->prms[i].opt, cmd->prms[i].value);
			return ;
		}
		printf("%s", cmd->prms[0].value);
		return ;
	}
	if (cmd->nb_prms > 1)
	{
		if (cmd->prms[0].value != NULL);
			printf ("%s ", cmd->prms[0].value);
		while (++i <= cmd->nb_prms)
			printf("%s %s", cmd->prms[i].opt, cmd->prms[i].value);
		return ;
	}
	return ;
}