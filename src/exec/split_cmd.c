/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:17:14 by lebojo            #+#    #+#             */
/*   Updated: 2023/10/05 02:39:22 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	process_split_cmd(t_inc	*inc, char **res, t_cmd *cmd)
{
	inc->k = 0;
	if (cmd->arg[inc->j] == '"')
	{
		res[inc->i] = ft_calloc(strlen_to_char(cmd->arg, inc->j, '"') + 1,
				sizeof(char));
		inc->j++;
		while (cmd->arg[inc->j] && cmd->arg[inc->j] != '"')
			res[inc->i][inc->k++] = cmd->arg[inc->j++];
	}
	else if (cmd->arg[inc->j] == '\'')
	{
		res[inc->i] = ft_calloc(strlen_to_char(cmd->arg, inc->j, '\'') + 1,
				sizeof(char));
		inc->j++;
		while (cmd->arg[inc->j] && cmd->arg[inc->j] != '\'')
			res[inc->i][inc->k++] = cmd->arg[inc->j++];
	}
	else
	{
		res[inc->i] = ft_calloc(strlen_to_char(cmd->arg, inc->j, ' ') + 1,
				sizeof(char));
		while (cmd->arg[inc->j] && cmd->arg[inc->j] != ' ')
			res[inc->i][inc->k++] = cmd->arg[inc->j++];
	}
}

char	**split_cmd(t_cmd cmd)
{
	char	**res;
	t_inc	inc;
	int		nb_arg;

	inc.i = 0;
	inc.j = 0;
	inc.k = 0;
	nb_arg = arg_counter(cmd.arg);
	res = ft_calloc(nb_arg + 1, sizeof(char *));
	res[inc.i++] = ft_strdup(cmd.name);
	if (!cmd.arg)
		return (res);
	while (--nb_arg - 1)
	{
		process_split_cmd(&inc, res, &cmd);
		inc.i++;
		inc.j++;
	}
	return (res);
}

int	process_arg_counter(int	*res, int *i, char *s)
{
	if (s[*i] == ' ' )
		*res += 1;
	if (s[*i] == '"')
	{
		while (s[++*i] && s[*i] != '"')
			;
		if (!s[*i] && s[*i - 1] != '"')
			return (-1);
	}
	else if (s[*i] == '\'')
	{
		while (s[++*i] && s[*i] != '\'')
			;
		if (!s[*i] && s[*i - 1] != '\'')
			return (-1);
	}
	return (0);
}

int	arg_counter(char *s)
{
	int	i;
	int	res;
	int	status;

	i = -1;
	status = 0;
	if (!s)
		return (2);
	res = 3;
	while (s && s[++i] && status)
		status = process_arg_counter(&res, &i, s);
	if (status == -1)
		return (-1);
	return (res);
}
