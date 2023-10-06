/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:13 by arthur            #+#    #+#             */
/*   Updated: 2023/10/06 04:02:14 by jordan           ###   ########.fr       */
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
	free_all(cmds, envp);
	ft_exit();
}
