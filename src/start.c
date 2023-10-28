/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:00:57 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/28 16:08:12 by lebojo           ###   ########.fr       */
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

void	increment_shlvl(char ***env)
{
	char	*shlvl;
	char	*new_shlvl;
	t_cmd	tmp;

	shlvl = hm_get_value(*env, "SHLVL");
	new_shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	tmp = create_cmd(NULL, add_str("SHLVL=", new_shlvl, 2), 0, 2);
	free(shlvl);
	ft_export(&tmp, env);
	free_cmd(&tmp);
}

void	start(char ***env)
{
	int		i;

	i = -1;
	printf("\e[0;32mMinishell 2\e[0m is starting...\n");
	if (!getenv("PWD"))
		create_envp(env);
	else
		increment_shlvl(env);
	signal(SIGINT, sig_handler);
	if (g_status == 1)
		signal(SIGQUIT, sig_handler);
	else
		signal(SIGQUIT, SIG_IGN);
	update_last_exit(0, env);
	g_status = 0;
}
