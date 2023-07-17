/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:57:48 by jordan            #+#    #+#             */
/*   Updated: 2023/07/18 01:31:30 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	sep_counter(t_cmds *cmds, char *input)
{
	int	i;

	i = -1;
	cmds->nb_cmd = 1;
	cmds->nb_pipe = 0;
	while (input[++i])
	{
		if (input[i] == '|' && input[i - 1] != '|')
			cmds->nb_pipe += 1;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			cmds->nb_cmd += 1;
		if ((input[i] == '<' && input[i - 1] == '<')
			||(input[i] == '>' && input[i - 1] == '>'))
			cmds->nb_cmd -= 1;
	}
}

void	sep_parse(t_cmds *cmds, char *input)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	sep_counter(cmds, input);
	if (cmds->nb_cmd <= 1 && cmds->nb_pipe < 1)
		return ;
	cmds->sep = ft_calloc(cmds->nb_cmd, sizeof(enum e_sep));
	while (input[++i + 1])
	{
		if (input[i] == '|')
			cmds->sep[j++] = Pipe;
		if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				cmds->sep[j++] = D_left;
				i++;
				continue;
			}
			else
				cmds->sep[j++] = S_left;
			continue;
		}
			if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				cmds->sep[j++] = D_right;
				i++;
				continue;
			}
			else
				cmds->sep[j++] = S_right;
			continue;
		}
	}
}

void	parse(t_cmds *cmds, char *input)
{
	char	**split;
	int		i;
	int		j;

	split = ft_split(input, ' ');
	if (!split[0])
		return ;
	i = 0;
	j = 0;
	sep_parse(cmds, input);
	cmds->cmd = malloc(sizeof(t_cmd) * (cmds->nb_cmd + 1));
	cmds->cmd[0].name = ft_strdup(split[i++]);
	cmds->cmd[0].arg = NULL;
	if (split[i])
		cmds->cmd[0].arg = ft_strdup(split[i++]);
	if (!split[i])
		return ;
	while (split[i])
	{
		if (split[i][0] == '|')
		{
			j++;
			if (!split[++i])
				break ;
			cmds->cmd[j].name = split[i];
			cmds->cmd[j].arg = NULL;
			if (!split[++i])
				break ;
			cmds->cmd[j].arg = split[i];
			i++;
			continue ;
		}
		else
		{
			if (cmds->cmd[j].arg[0])
			{
				cmds->cmd[j].arg = add_str(cmds->cmd[j].arg, " ", 1);
				cmds->cmd[j].arg = add_str(cmds->cmd[j].arg, split[i], 3);
			}
			else
				cmds->cmd[j].arg = ft_strdup(split[i]);
		}
		i++;
	}
	free(split[0]);
	free(split);
}
