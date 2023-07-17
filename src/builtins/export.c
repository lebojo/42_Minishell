/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:15 by arthur            #+#    #+#             */
/*   Updated: 2023/07/18 01:29:09 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int		strdiff(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1[i] || !s2[i])
		return (0);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	**copy_tab(char **tab)
{
	char	**res;
	int		i;
	
	i = 0;
	while (tab[i++])
		;
	res = malloc(sizeof(char *) * i);
	i = -1;
	while (tab[++i])
		res[i] = ft_strdup(tab[i]);
	return (res);
}

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
	free((*env)[i]);
	(*env)[i] = ft_strdup(new_env);
}

char	**emptyEnv(char *s)
{
	char	**res;

	res = malloc(sizeof(char *) * 2);
	res[0] = ft_strdup(s);
	res[1] = ft_strdup("''");
	return (res);
}

void	ft_export(t_cmd *cmd, char ***env)
{
	char	**s_arg;

	if (!cmd->arg)
		return (print_sorted_env(copy_tab(*env)));
	if (ft_strchr(cmd->arg, '='))
		s_arg = ft_split(cmd->arg, '=');
	else
		s_arg = emptyEnv(cmd->arg);
	if (hm_get_value(*env, s_arg[0]))
		update_env(s_arg[0], s_arg[1], cmd->arg, env);
	else
		add_env(s_arg, env);
}
