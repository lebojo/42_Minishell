/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:00:57 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/05 03:22:33 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_envp(char ***envp)
{
	char	**new_envp;

	printf("Create env...\n");
	new_envp = malloc(sizeof(char *) * 3);
	new_envp[0] = ft_strdup("SHLVL=1");
	new_envp[1] = add_str("PWD=", getcwd(NULL, 0), 0);
	new_envp[2] = NULL;
	*envp = new_envp;
}

void	start(char ***env)
{
	t_cmd	c;
	int		i;

	i = -1;
	printf("\e[0;32mMinishell 2\e[0m is starting...\n");
	if (!getenv("PWD"))
		create_envp(env);
	else
		c.arg = add_str("SHLVL=", ft_itoa(ft_atoi(
						find_path(*env, "SHLVL", 5)) + 1), 0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	//ft_export(&c, env);
	g_status = 0;
}
