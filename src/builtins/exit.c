/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:13 by arthur            #+#    #+#             */
/*   Updated: 2023/10/07 01:00:53 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_exit(void)
{
	printf("\nExiting ");
	printf(MS);
	printf("...\n");
	exit(1);
}

void	ft_exit_free(char ***envp, t_cmds *cmds)
{
	//free_all(cmds, envp);
	ft_exit();
}
