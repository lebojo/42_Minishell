/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:59:41 by abourgue          #+#    #+#             */
/*   Updated: 2023/07/18 01:47:10 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	create_tbl_exec(t_cmd *cmd, t_exec *exec);
char	**ft_split_cmd(char const *s, char c, char d, int count);

void	exec_cmd(t_cmd *cmd, t_exec *exec, char **env)
{
	int 	x;
	int		count;
	char	*temp;

	exec->env_p = find_path(env, "PATH", 4);
	exec->cmd_p = ft_split(exec->env_p, ':');
	exec->cmd = get_cmd(exec->cmd_p, cmd->name);
	if (!exec->cmd)
	{
		if (dup2(2, STDOUT_FILENO) == -1)
			return ;
		printf("command not found: %s\n", cmd->name);
		exit (1);
	}
	create_tbl_exec(cmd, exec);
	execve(exec->cmd, exec->cmd_a, env);
	exit(1);
}

void	create_tbl_exec(t_cmd *cmd, t_exec *exec)
{
	int		x;
	int		count;
	char	*tmp;
	
	count = 1;
	if (cmd->arg)
	{	
		x = -1;
		while (cmd->arg[++x])
		{
			if (cmd->arg[x] == '"')
			{
				x++;
				count++;
				while (cmd->arg[x] != '"' && cmd->arg[x])
					x++;
			}
			x++;
			if (cmd->arg[x] == ' ' || cmd->arg[x + 1] == '\0')
			{
				if (cmd->arg[x - 1] != ' ')
					count++;
			}
		}
	}
	exec->cmd_a = malloc(sizeof(char *) * (count + 1));
	if (cmd->arg)
	{
		tmp = add_str(cmd->name, " ", 0);
		tmp = add_str(tmp, cmd->arg, 1);
	}
	exec->cmd_a = ft_split_cmd(tmp,' ','"', count);
	exec->cmd_a[count] = NULL;
	free(tmp);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split_cmd(char const *s, char c, char d, int count)
{
	int	i;
	int	j;
	int		index;
	char	**res;

	res = malloc((count + 1) * sizeof(char *));
	if (!s || !res)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s[i] != d && index < 0)
			index = i;
		else if ((s[i] == d) && index >= 0)
		{
			index = ++i;
			while (s[i] != d)
				i++;
			res[j++] = word_dup(s, index, i);
			index = ++i;
		}
		else if (((s[i] == c && s[i - 1] != d) || s[i] == '\0') && index >= 0)
		{
			res[j++] = word_dup(s, index, i);
			index = ++i;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}
