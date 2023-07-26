/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:59:41 by abourgue          #+#    #+#             */
/*   Updated: 2023/07/26 12:47:14 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char **split_cmd(t_cmd cmd);

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
	exec->cmd_a = split_cmd(*cmd);
	execve(exec->cmd, exec->cmd_a, env);
	exit(1);
}

int arg_counter(char *s)
{
    int i;
    int res;

    i = -1;
    if (!s)
        return (2);
    res = 3;
    while (s && s[++i])
    {
        if (s[i] == ' ' )
            res++;
        if (s[i] == '"')
        {
            while (s[++i] && s[i] != '"')
                ;
            if (!s[i] && s[i - 1] != '"')
                return (-1);
        }
        else if (s[i] == '\'')
        {
            while (s[++i] && s[i] != '\'')
                ;
            if (!s[i] && s[i - 1] != '\'')
                return (-1);
        }
    }
    return (res);
}

int    strlen_to_char(char *s, int i, char c)
{
    while (s[i] && s[i] != c)
        i++;
    return (i);
}

char    *str_extractor(char *s)
{
    int i;
    char *res;

    i = 0;
    res = ft_calloc(ft_strlen(s) - 2, sizeof(char));
    if (s[i] == '"')
    {
        while (s[++i] && s[i] != '"')
            res[i - 1] = s[i];
        if (!s[i])
            return (NULL);
    }
    else if (s[i] == '\'')
    {
        while (s[++i] && s[i] != '\'')
            res[i - 1] = s[i];
        if (!s[i])
            return (NULL);
    }
    return (res);
}

char **split_cmd(t_cmd cmd)
{
    char    **res;
    int        i;
    int        j;
    int        k;
    int        nb_arg;

    i = 0;
    j = 0;
    k = 0;
    nb_arg = arg_counter(cmd.arg);
    res = ft_calloc(nb_arg + 1, sizeof(char *));
    res[i++] = ft_strdup(cmd.name);
    if (!cmd.arg)
        return (res);
    while (--nb_arg - 1)
    {
        k = 0;
        if (cmd.arg[j] == '"')
        {
            res[i] = ft_calloc(strlen_to_char(cmd.arg, j, '"') + 1, sizeof(char));
            j++;
            while (cmd.arg[j] && cmd.arg[j] != '"')
                res[i][k++] = cmd.arg[j++];
        }
        else if (cmd.arg[j] == '\'')
        {
            res[i] = ft_calloc(strlen_to_char(cmd.arg, j, '\'') + 1, sizeof(char));
            j++;
            while (cmd.arg[j] && cmd.arg[j] != '\'')
                res[i][k++] = cmd.arg[j++];
        }
        else
        {
            res[i] = ft_calloc(strlen_to_char(cmd.arg, j, ' ') + 1, sizeof(char));
            while (cmd.arg[j] && cmd.arg[j] != ' ')
                res[i][k++] = cmd.arg[j++];
        }
        i++;
        j++;
    }
    return (res);
}
