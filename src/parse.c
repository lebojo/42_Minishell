/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:36:29 by jordan            #+#    #+#             */
/*   Updated: 2023/11/07 15:17:12 by jchapell         ###   ########.fr       */
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
	init_inc(inc);
	sep_parse(cmds, input);
	create_cmds(cmds);
	cmds->line = ft_strdup(input);
	if (!char_in_str(split[inc->i][0], "|<>"))
		cmds->cmd[0] = create_cmd(expand(split[inc->i++], envp), NULL, 0, 1);
	else
	{
		cmds->cmd[0] = create_cmd(expand(split[++inc->i], envp), NULL, 0, 1);
		inc->i++;
	}
	quote_parse(cmds, split, inc, envp);
	while (split[inc->s])
		inc->s++;
	return (split);
}

int	process_parse(t_cmds *cmds, t_inc *inc, char **split, char ***envp)
{
	if (char_in_str(split[inc->i][0], "|<>"))
		return (sub_process_parse_true(cmds, inc, split, envp));
	else
		return (sub_process_parse_fls(cmds, inc, split));
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
	while (inc.i < inc.s && split[inc.i - 1] && split[inc.i])
	{
		if (char_in_str('|', split[inc.i]))
			inc.k++;
		inc.l = process_parse(cmds, &inc, split, envp);
		if (inc.l == 1)
			continue ;
		else if (inc.l == 2)
			break ;
	}
	inc.p = -1;
	if (input[0] == '<' && input[1] != '<')
		reverse_cmd(cmds, 0);
	free_tab(split);
	while (++inc.p < cmds->nb_cmd)
		if (cmds->cmd[inc.p].name
			&& char_in_str(cmds->cmd[inc.p].name[0], "|<>"))
			return (1);
	return (0);
}
