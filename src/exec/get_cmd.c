/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:35:14 by arthur            #+#    #+#             */
/*   Updated: 2023/06/12 19:13:50 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	is_builtins(t_cmd *cmd, t_envp *env)
{
	if (ft_strcmp("echo",cmd->name) == 1)
		ft_echo(cmd, env);
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
	else
		return (0);
	return (1);
}

void	select_cmd(t_envp *env, t_cmd *cmd)
{
	if (is_builtins(cmd, env))
		return ;
	
}