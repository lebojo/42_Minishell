/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:02 by arthur            #+#    #+#             */
/*   Updated: 2023/10/05 03:10:25 by jchapell         ###   ########.fr       */
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

	i = 0;
	while ((*env)[i++])
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while ((*env)[++i])
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = add_str(arg[0], "=", 1);
	new_env[i] = add_str(new_env[i], arg[1], 3);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

void	update_env(char *key, char *arg, char *new_env, char ***env)
{
	int		i;
	char	**s_env;

	i = -1;
	while ((*env)[++i])
	{
		s_env = ft_split((*env)[i], '=');
		if (ft_strcmp(s_env[0], key))
			break ;
	}
	free(*env);
	(*env)[i] = ft_strdup(new_env);
}

char	**empty_env(char *s)
{
	char	**res;

	res = malloc(sizeof(char *) * 2);
	res[0] = ft_strdup(s);
	res[1] = ft_strdup("''");
	return (res);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
