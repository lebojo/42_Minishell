/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:00:57 by jchapell          #+#    #+#             */
/*   Updated: 2023/09/25 18:29:29 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_envp(char ***envp)
{
	t_cmd	tmp, tmp2;

	printf("Create env...\n");
	tmp = create_cmd("", "SHLVL=0", 0);
	ft_export(&tmp, envp);
	// free_cmd(&tmp);
	// tmp2 = create_cmd("", "PWD=0", 0);
	// ft_export(&tmp2, envp);
}

void	start(int ac, char **av, char ***envp)
{
	t_cmd	c;
	int		i = -1;

	printf("\e[0;32mMinishell 2\e[0m is starting...\n");
	if (!getenv("SHLVL"))
		create_envp(envp);
	signal(SIGINT, sigint_handler);
	c.arg = add_str("SHLVL=", ft_itoa(ft_atoi(find_path(*envp, "SHLVL", 5)) + 1), 0);
	ft_export(&c, envp);
}