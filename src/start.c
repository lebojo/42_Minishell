/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:00:57 by jchapell          #+#    #+#             */
/*   Updated: 2023/09/25 19:36:25 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

char	**create_envar(char *key, char *value)
{
	char **res;

	res = malloc(sizeof(char *) * 3);
	res[0] = ft_strdup(key);
	res[1] = ft_strdup(value);
	res[2] = NULL;
	return (res);
}

void	create_envp(char ***envp)
{
	char **new_envp;

	printf("Create env...\n");
	new_envp = malloc(sizeof(char *) * 4);
	new_envp[0] = ft_strdup("SHLVL=0");
	new_envp[1] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	new_envp[2] = add_str("PWD=", getcwd(NULL, 0), 0);
	new_envp[3] = NULL;
	*envp = new_envp;
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