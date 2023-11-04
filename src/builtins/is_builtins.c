/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:01:19 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/04 15:48:43 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

int	is_builtins(t_cmd *cmd, char ***envp)
{
	if (ft_strcmp("echo", cmd->name))
		ft_echo(cmd);
	else if (ft_strcmp("cd", cmd->name))
		ft_cd(cmd->arg, envp);
	else if (ft_strcmp("pwd", cmd->name))
		ft_pwd();
	else if (ft_strcmp("export", cmd->name))
		ft_export(cmd, envp);
	else if (ft_strcmp("unset", cmd->name))
		ft_unset(cmd, envp);
	else if (ft_strcmp("env", cmd->name))
		ft_env(*envp);
	else if (ft_strcmp("exit", cmd->name))
		ft_exit_cmd(NULL, cmd, envp);
	else if (ft_strcmp("..", cmd->name))
		ft_cd("..", envp);
	else
		return (0);
	update_last_exit(0, envp);
	return (1);
}
