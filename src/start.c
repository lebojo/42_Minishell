/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:00:57 by jchapell          #+#    #+#             */
/*   Updated: 2023/09/25 17:04:48 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_envp(char ***envp)
{
	t_cmd	tmp;

	tmp.arg = ft_strdup("SHLVL=0");
	ft_export(&tmp, envp);
	free(tmp.arg);
	tmp.arg = ft_strdup("SH=12");
	//ft_export(&tmp, envp);
}

void	start(int ac, char **av, char ***envp)
{
	printf("\e[0;32mMinishell 2\e[0m is starting...\n");
	if (!getenv("SHLVL"))
	{
		printf("Create env...\n");
		create_envp(envp);
	}
	signal(SIGINT, sigint_handler);
}