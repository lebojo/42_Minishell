/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:36:29 by jordan            #+#    #+#             */
/*   Updated: 2023/10/16 19:51:55 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

char	**init_parse(t_cmds *cmds, char *input, char ***envp, t_inc *inc)
{
	char	**split;

	if (!*input)
		return (NULL);
	split = ft_split(input, ' ');
	if (!split[0])
		return (NULL);
	inc->i = 0;
	inc->j = 0;
	sep_parse(cmds, input);
	cmds->cmd = malloc(sizeof(t_cmd) * (cmds->nb_cmd));
	if (!char_in_str(split[inc->i][0], "|<>'"))
		cmds->cmd[0] = create_cmd(expand(split[inc->i++], envp), NULL, 0);
	else
	{
		cmds->cmd[0] = create_cmd(expand(split[++inc->i], envp), NULL, 0);
		inc->i++;
	}
	inc->k = 0;
	if (split[inc->i] && !char_in_str(split[inc->i][0], "|<>"))
		cmds->cmd[0].arg = expand(split[inc->i++], envp);
	return (split);
}

int	process_parse(t_cmds *cmds, t_inc *inc, char **split, char ***envp)
{
	if (char_in_str(split[inc->i][0], "|<>"))
	{
		cmds->cmd[++inc->j].which_pipe = inc->k;
		if (!split[++inc->i])
			return (2);
		cmds->cmd[inc->j].name = expand(split[inc->i], envp);
		cmds->cmd[inc->j].arg = NULL;
		if (!split[++inc->i])
			return (2);
		if (char_in_str(split[inc->i][0], "|<>"))
			return (1);
		cmds->cmd[inc->j].arg = expand(split[inc->i], envp);
	}
	else
	{
		if (cmds->cmd[inc->j].arg && cmds->cmd[inc->j].arg[0])
			cmds->cmd[inc->j].arg = expand(add_str(
						add_str(cmds->cmd[inc->j].arg, " ", 1),
						split[inc->i], 3), envp);
		else
			cmds->cmd[inc->j].arg = expand(split[inc->i], envp);
		cmds->cmd[inc->j].which_pipe = inc->k;
	}
	return (0);
}

int	parse(t_cmds *cmds, char *input, char ***envp)
{
	char	**split;
	t_inc	inc;

	split = init_parse(cmds, input, envp, &inc);
	if (!split)
		return (1);
	while (split[inc.i])
	{
		if (char_in_str('|', split[inc.i]))
			inc.k++;
		inc.l = process_parse(cmds, &inc, split, envp);
		if (inc.l == 1)
			continue ;
		else if (inc.l == 2)
			break ;
		inc.i++;
	}
	inc.p = 0;
	while (inc.p < cmds->nb_cmd)
		if (char_in_str(cmds->cmd[inc.p++].name[0], "|<>"))
			return (1);
	free(split[0]);
	free(split);
	return (0);
}
