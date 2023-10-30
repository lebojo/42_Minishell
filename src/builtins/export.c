/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:15 by arthur            #+#    #+#             */
/*   Updated: 2023/10/30 07:33:40 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	strdiff(const char *s1, const char *s2)
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
	res[i] = NULL;
	return (res);
}

void	ft_export(t_cmd *cmd, char ***env)
{
	char	**s_arg;
	char	*tmp;

	s_arg = NULL;
	if (!cmd->arg)
	{
		s_arg = copy_tab(*env);
		print_sorted_env(s_arg);
		free_tab(s_arg);
		return ;
	}
	if (ft_strchr(cmd->arg, '='))
		s_arg = ft_split(cmd->arg, '=');
	else
		s_arg = empty_env(cmd->arg);
	tmp = hm_get_value(*env, s_arg[0]);
	if (tmp)
		hm_set_value(env, s_arg[0], s_arg[1]);
	else
		add_env(s_arg, env); // <- LEAKS HERE
	free_tab(s_arg);
	free(tmp);
}
