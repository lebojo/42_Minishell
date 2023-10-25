/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:36:29 by jordan            #+#    #+#             */
/*   Updated: 2023/10/25 04:19:00 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"


char	**split_cleaner(char **split)
{
	char	**res;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (split[++i])
		if (ft_strlen(split[i]) > 0)
			j++;
	res = malloc(sizeof(char *) * (j + 1));
	res[j] = NULL;
	i = -1;
	j = 0;
	while (ft_strlen(split[++i]) > 0)
		res[j++] = ft_strdup(split[i]);
	free_tab(split);
	return (res);
}

char	**init_parse(t_cmds *cmds, char *input, char ***envp, t_inc *inc)
{
	char	**split;

	if (!*input)
		return (NULL);
	split = ft_split(input, ' ');
	split = split_cleaner(split);
	if (!split[0])
		return (NULL);
	inc->i = 0;
	inc->j = 0;
	sep_parse(cmds, input);
	cmds->cmd = malloc(sizeof(t_cmd) * (cmds->nb_cmd));
	if (!char_in_str(split[inc->i][0], "|<>"))
		cmds->cmd[0] = create_cmd(expand(split[inc->i++], envp), NULL, 0);
	else
	{
		cmds->cmd[0] = create_cmd(expand(split[++inc->i], envp), NULL, 0);
		inc->i++;
	}
	inc->k = 0;
	quote_parse(cmds, split, inc, envp);
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
		quote_parse(cmds, split, inc, envp);
	}
	else
	{
		if (cmds->cmd[inc->j].arg && cmds->cmd[inc->j].arg[0])
			cmds->cmd[inc->j].arg = add_str(
					add_str(cmds->cmd[inc->j].arg, " ", 1),
					split[inc->i], 3);
		else
			cmds->cmd[inc->j].arg = split[inc->i];
		cmds->cmd[inc->j].which_pipe = inc->k;
	}
	return (0);
}

void	reverse_cmd(t_cmds *cmds, int i)
{
	char	*tmp;
	char	**sp;
	int		j;

	if (!cmds->cmd[i].name)
		return ;
	tmp = cmds->cmd[i].name;
	cmds->cmd[i].name = cmds->cmd[i].arg;
	cmds->cmd[i].arg = tmp;
	cmds->sep[i] = None;
	if (char_in_str(' ', cmds->cmd[i].name))
	{
		sp = ft_split(cmds->cmd[i].name, ' ');
		free(cmds->cmd[i].name);
		cmds->cmd[i].name = sp[0];
		j = 0;
		while (sp[++j])
		{
			sp[j] = add_str(sp[j], " ", 1);
			cmds->cmd[i].arg = add_str(sp[j], cmds->cmd[i].arg, 3);
		}
		free(sp);
	}
}

int	parse(t_cmds *cmds, char *input, char ***envp)
{
	char			**split;
	t_inc			inc;

	split = init_parse(cmds, input, envp, &inc);
	if (!split)
		return (1);
	while (ft_strlen(split[inc.i]) > 0)
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
	inc.p = -1;
	if (input[0] == '<')
		reverse_cmd(cmds, 0);
	while (++inc.p < cmds->nb_cmd)
		if (cmds->cmd[inc.p].name
			&& char_in_str(cmds->cmd[inc.p].name[0], "|<>")) // <- CA CRASH ICI BG, c'est nb_cmd qui n'est pas justes
			return (1);
	return (0);
}
