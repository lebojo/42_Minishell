/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:15 by arthur            #+#    #+#             */
/*   Updated: 2023/07/15 15:12:07 by lebojo           ###   ########.fr       */
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

char *parsed_arg(char *arg)
{
	char	*res;
	char	type;
	int		i;

	i = 0;
	while (arg[i] || arg[i] != '=')
		i++;
	if (arg[i] != '=')
		return (add_str(arg, "=''", 0));
	else if (!arg[i + 1])
		return (add_str(arg, "''", 0));
	else
		type = arg[++i];
	if (type == '\'')
		printf("caca");
	return (res);
}

void	add_env(char *arg, char ***env)
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
	new_env[i] = parsed_arg(arg);
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

void	ft_export(t_cmd *cmd, char ***env)
{
	char	**s_arg;

	if (!cmd->arg)
		return (print_sorted_env(copy_tab(*env)));
	s_arg = ft_split(cmd->arg, '=');
	if (hm_get_value(*env, s_arg[0]))
		update_env(s_arg[0], s_arg[1], cmd->arg, env);
	else
		add_env(cmd->arg, env);
}
