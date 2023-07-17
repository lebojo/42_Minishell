/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:35:14 by arthur            #+#    #+#             */
/*   Updated: 2023/07/18 00:49:09 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	is_builtins(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp("echo", cmd->name))
		ft_echo(cmd, envp);
	else if (ft_strcmp("cd", cmd->name))
		ft_cd(cmd->arg);
	else if (ft_strcmp("pwd",cmd->name))
		ft_pwd();
	else if (ft_strcmp("export",cmd->name))
		ft_export(cmd, envp);
	else if (ft_strcmp("unset",cmd->name))
		ft_unset(cmd, envp);
	else if (ft_strcmp("env",cmd->name))
		ft_env(*envp);
	else if (ft_strcmp("exit", cmd->name))
		ft_exit();
	else
		return (0);
	return (1);
}

void	select_cmd(t_cmd *cmd, char ***envp)
{
	if (is_builtins(cmd, envp))
		return ;
	printf("Command not found...\n");
}