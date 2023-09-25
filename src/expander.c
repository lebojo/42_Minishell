/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 04:19:20 by jchapell          #+#    #+#             */
/*   Updated: 2023/09/25 16:32:28 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

t_cmd	create_cmd(char *name, char *arg, int which_pipe)
{
	t_cmd	res;
	
	res.name = name;
	res.arg = arg;
	res.which_pipe = which_pipe;
	return (res);
}

char	*expand(char *src, char ***envp)
{
	char	*res;
	char	*tmp;
	char	*var;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	res = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	while (src[++i])
	{
		if (src[i] == '$')
		{
			tmp = ft_calloc(ft_strlen(src) + 1, sizeof(char));
			while (src[++i] && src[i] != ' ' && src[i] != '$')
				tmp[k++] = src[i];
			var = hm_get_value(*envp, tmp);
			if (var)
			{
				res = add_str(res, var, 1);
				res = add_str(res, " ", 1);
				j += ft_strlen(var) + 1;
				free(var);
			}
			free(tmp);
			k = 0;
		}
		else
			res[j++] = src[i];
	}
	return (res);
} //Une fonction qui remplacer les variables d'environnement par leur valeur et return la string modifiée