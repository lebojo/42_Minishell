/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:35:14 by arthur            #+#    #+#             */
/*   Updated: 2023/06/16 22:43:46 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	is_builtins(t_cmd *cmd, char **envp)
{
	if (ft_strcmp("echo", cmd->name))
		ft_echo(cmd);
	// else if (ft_strcmp("cd",cmd->name) == 1)
	// 	ft_cd(cmd, env);
	// else if (ft_strcmp("pwd",cmd->name) == 1)
	// 	ft_pwd(cmd, env);
	// else if (ft_strcmp("export",cmd->name) == 1)
	// 	ft_export(cmd, env);
	// else if (ft_strcmp("unset",cmd->name) == 1)
	// 	ft_unset(cmd, env);
	// else if (ft_strcmp("env",cmd->name) == 1)
	// 	ft_env(cmd, env);
	// else if (ft_strcmp("exit",cmd->name) == 1)
	// 	ft_exit(cmd, env);
	// else
	// 	return (0);
	return (1);
}

void	select_cmd(t_cmd *cmd, char **envp)
{
	if (is_builtins(cmd, envp))
		return ;
	
}