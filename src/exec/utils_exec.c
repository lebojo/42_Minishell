/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:15:52 by abourgue          #+#    #+#             */
/*   Updated: 2023/09/26 17:32:50 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	close_return(int fd)
{
	close(fd);
	return ;
}

void	exec_in_fork(int entry, int *tab, t_cmd *cmd, char **env)
{
	tab[0] = fork();
	if (tab[0] == 0)
	{
		dup2(tab[1], entry);
		exec_cmd(cmd, env);
		dup2(0, entry);
		close(tab[1]);
	}
	waitpid(tab[0], NULL, 0);
}

int	check_builtins(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp("echo", cmd->name))
		return (1);
	else if (ft_strcmp("cd", cmd->name))
		return (1);
	else if (ft_strcmp("pwd",cmd->name))
		return (1);
	else if (ft_strcmp("export",cmd->name))
		return (1);
	else if (ft_strcmp("unset",cmd->name))
		return (1);
	else if (ft_strcmp("env",cmd->name))
		return (1);
	else if (ft_strcmp("exit", cmd->name))
		return (1);
	return (0);
	
}

int	exec_inpipe_builtins(int entry, int fd, t_cmd *cmd, char ***env)
{
	if (check_builtins(cmd, env))
	{
		dup2(fd, entry);
		is_builtins(cmd, env);
		dup2(0, entry);
		close(fd);
		return (1);
	}
	return (0);
}