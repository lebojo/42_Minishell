/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:15 by arthur            #+#    #+#             */
/*   Updated: 2023/06/21 00:24:36 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int		strdiff(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
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

void	ft_export(t_cmd *cmd, char ***env)
{
	char	**new_env;
	int		i;

	if (!cmd->arg)
		return (print_sorted_env(copy_tab(*env)));
	i = 0;
	while ((*env)[i++])
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while ((*env)[++i])
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = ft_strdup(cmd->arg);
	*env = new_env;
}