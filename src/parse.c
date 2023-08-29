/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/29 17:4135 by lebojo           ###   ########.fr       */
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

	if (!*input)
		return ;
	split = ft_split(input, ' ');
	if (!split[0])
		return ;
	i = 0;
	j = 0;
	sep_parse(cmds, input);
	cmds->cmd = malloc(sizeof(t_cmd) * (cmds->nb_cmd + 1));
	if (!char_in_str(split[i][0], "|<>"))
		cmds->cmd[0].name = ft_strdup(split[i++]);
	else
	{
		cmds->cmd[0].name = ft_strdup(split[++i]);
		i++;
	}
	cmds->cmd[0].arg = NULL;
	if (split[i] && !char_in_str(split[i][0], "|<>"))
		cmds->cmd[0].arg = ft_strdup(split[i++]);
	if (!split[i])
		return ;
	while (split[i])
	{
		if (char_in_str(split[i][0], "|<>"))
		{
			j++;
			if (!split[++i])
				break ;
			cmds->cmd[j].name = split[i];
			cmds->cmd[j].arg = NULL;
			if (!split[++i])
				break ;
			if (char_in_str(split[i][0], "|<>"))
				continue ;
			cmds->cmd[j].arg = split[i];
			i++;
			continue ;
		}
		else
		{
			if (cmds->cmd[j].arg && cmds->cmd[j].arg[0])
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
