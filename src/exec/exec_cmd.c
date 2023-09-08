/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:19:24 by abourgue          #+#    #+#             */
/*   Updated: 2023/09/06 11:27:11 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

// char **split_cmd(t_cmd cmd);

char	*find_path(char **envp, char *s, int x)
{
	while (ft_strncmp(s, *envp, x))
		envp++;
	return (*envp + (x + 1));
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	exec_cmd(t_cmd *cmd, char **env)
{
    char    *ac_cmd;    // = acces_command (/bin/[name])
	char	*path_env;
    char    **path_cmd;
    char    **s_cmd;    // = split_command ({"ls","-l",NULL})
    
	path_env = find_path(env, "PATH", 4);
	path_cmd = ft_split(path_env, ':');
	ac_cmd = get_cmd(path_cmd, cmd->name);
	if (!ac_cmd)
	{
		if (dup2(2, STDOUT_FILENO) == -1)
			return ;
		printf("Command not found: %s\n", cmd->name);
		exit (1);
	}
	s_cmd = split_cmd(*cmd);
	execve(ac_cmd, s_cmd, env);
	exit(0);
}

char **split_cmd(t_cmd cmd)
{
    char    **res;
    int     i;
    int     j;
    int     k;
    int     nb_arg;

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