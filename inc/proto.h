/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:35 by jordan            #+#    #+#             */
/*   Updated: 2023/06/20 13:29:50 by abourgue         ###   ########.fr       */
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
# include <signal.h>
# include "struct.h"
# include "libft/libft.h"

/*===================================SOURCES====================================*/

void	parse(t_cmds *cmds, char *input);
void	free_cmds(t_cmds *cmds);
void	free_tube(t_exec *exec);
void	close_pipe(t_exec *exec, int i);

/*=======EXEC=======*/

/*	CMD_PIPE				*/
void	cmd_pipe(t_cmds *cmds, t_exec *exec, char **envp, int x);

/*	CMD_RDR*/
void	cmd_rdr_l(t_cmds *cmds, t_exec *exec, char **envp, int x);
void	exec_rdr(t_cmd *cmd, t_exec *exec, char **env, int x);
// void	cmd_rdr_r(t_cmds *cmds, t_exec *exec, char **envp, int x);

/*	EXEC_CMD			*/
void	exec_cmd(t_cmd *cmd, t_exec *exec, char **env);

/*	UTILS_EXEC			*/
char	*find_path(char **envp, char *s, int x);
char	*get_cmd(char **paths, char *cmd);

/*	GET_CMD			*/
void	exec_line(t_cmds *cmds, char **envp);

/*=====BUILTINS=====*/

// /*	CD				*/
// void	ft_cd(t_cmd *cmd, t_envp *env);

/*	ECHO			*/
void	ft_echo(t_cmd *cmd);

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