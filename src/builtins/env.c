/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:02 by arthur            #+#    #+#             */
/*   Updated: 2023/10/30 07:36:42 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	print_sorted_env(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i + 1])
	{
		if (strdiff(env[i], env[i + 1]) > 0)
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	ft_env(env);
	free(env);
}

void	add_env(char **arg, char ***env)
{
	int		i;
	char	**new_env;

	i = -1;
	while ((*env)[++i])
		;
	new_env = ft_calloc(sizeof(char *), i + 2);
	i = -1;
	while ((*env)[++i])
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = add_str(arg[0], "=", 0);
	new_env[i] = add_str(new_env[i], arg[1], 1);
	free_tab(*env);
	*env = new_env;
}

char	**empty_env(char *s)
{
	char	**res;

	res = malloc(sizeof(char *) * 3);
	res[0] = ft_strdup(s);
	res[1] = ft_strdup("''");
	res[2] = NULL;
	return (res);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
