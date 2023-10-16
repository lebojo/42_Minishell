/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:13 by arthur            #+#    #+#             */
/*   Updated: 2023/10/16 15:19:41 by jchapell         ###   ########.fr       */
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
	(void)envp;
	(void)cmds;
	//free_all(cmds, envp);
	ft_exit();
}
