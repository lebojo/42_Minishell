/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:19:24 by abourgue          #+#    #+#             */
/*   Updated: 2023/09/26 17:15:07 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

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
	char	*ac_cmd;
	char	*path_env;
	char	**path_cmd;
	char	**s_cmd;

	path_env = find_path(env, "PATH", 4);
	path_env = add_str(path_env, ":", 0);
	path_env = add_str(path_env, find_path(env, "PWD", 3), 0);
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
		*res++;
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

int	strlen_to_char(char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*str_extractor(char *s)
{
	int		i;
	char	*res;

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
