/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:00:57 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/02 04:43:20 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_envp(char ***envp)
{
	char	**new_envp;

	printf("Create env...\n");
	new_envp = malloc(sizeof(char *) * 4);
	new_envp[0] = ft_strdup("SHLVL=1");
	new_envp[1] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	new_envp[2] = add_str("PWD=", getcwd(NULL, 0), 0);
	new_envp[3] = NULL;
	*envp = new_envp;
}

void	start(int ac, char **av, char ***env)
{
	t_cmd	c;
	int		i = -1;

	printf("\e[0;32mMinishell 2\e[0m is starting...\n");
	if (!getenv("PWD"))
		create_envp(env);
	else
		c.arg = add_str("SHLVL=", ft_itoa(ft_atoi(find_path(*env, "SHLVL", 5)) + 1), 0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	//ft_export(&c, env);
	g_status = 0;
}