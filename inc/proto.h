/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:35 by jordan            #+#    #+#             */
/*   Updated: 2023/06/16 04:04:03 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

/*===================================INCLUDES====================================*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "libft/libft.h"

/*===================================SOURCES====================================*/

void	parse(t_cmd *cmd, char *input);
void	free_cmds(t_cmds *cmds);

/*=======EXEC=======*/

/*	EXEC_CMD			*/
void	simple_cmd(t_cmds *cmds, char **env);

/*	UTILS_EXEC			*/
char	*find_path(char **envp, char *s, int x);
char	*get_cmd(char **paths, char *cmd);

/*	GET_CMD				*/
void	select_cmd(t_cmds *cmds, char **env);

/*=====BUILTINS=====*/

// /*	CD				*/
// void	ft_cd(t_cmd *cmd, t_envp *env);

/*	ECHO			*/
void	ft_echo(t_cmd *cmd, char **env);

// /*	ENV				*/
// void	ft_env(t_cmd *cmd, t_envp *env);

// /*	EXIT			*/
// void	ft_exit(t_cmd *cmd, t_envp *env);

// /*	EXPORT			*/
// void	ft_export(t_cmd *cmd, t_envp *env);

// /*	PWD				*/
// void	ft_pwd(t_cmd *cmd, t_envp *env);

// /*	UNSET			*/
// void	ft_unset(t_cmd *cmd, t_envp *env);

#endif